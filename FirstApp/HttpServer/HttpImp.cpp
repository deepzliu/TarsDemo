#include "HttpImp.h"
#include "servant/Application.h"

using namespace std;
extern map<string, st_cgi_conf> g_map_cgi_conf;

class HttpCGICoroCallback : public HttpProto::HttpCGICoroPrxCallback
{
public:
	HttpCGICoroCallback(HttpProto::st_cgi_rsp & rsp)
			:_iException(0), _iRet(0), _rsp(rsp)
	{
		_cost = tars::TC_TimeProvider::getInstance()->getNowMs();
	}

    virtual ~HttpCGICoroCallback(){}

    virtual void callback_get(const HttpProto::st_cgi_rsp& rsp)
    { 
		//_iRet = ret; // 这个错误码不需要
		_rsp = rsp;
		_cost = tars::TC_TimeProvider::getInstance()->getNowMs() - _cost;
   	}
    virtual void callback_get_exception(tars::Int32 ret)
	{
		_iException = ret;
		_iRet = CError::E_REMOTE_SVR_FAILED;
		_cost = tars::TC_TimeProvider::getInstance()->getNowMs() - _cost;
	}

public:
	int		_iException;
	int		_iRet;
	int		_cost;
	HttpProto::st_cgi_rsp & _rsp;
};
typedef tars::TC_AutoPtr<HttpCGICoroCallback> HttpCGICoroCallbackPtr;

//////////////////////////////////////////////////////
void HttpImp::initialize()
{
    //initialize servant here:
    //...
}

//////////////////////////////////////////////////////
void HttpImp::destroy()
{
    //destroy servant here:
    //...
}

int HttpImp::doRequest(TarsCurrentPtr current, vector<char> &buffer)
{
	int ret = 0;
	int cost = tars::TC_TimeProvider::getInstance()->getNowMs();
	HttpProto::st_cgi_req cgi_req;
	HttpProto::st_cgi_rsp cgi_rsp;

	_BLOCK_START_

	TC_HttpRequest request;
	vector<char> v = current->getRequestBuffer();
	string sBuf;
	sBuf.assign(&v[0], v.size());
	request.decode(sBuf);

	TLOGDEBUG("URL: " << request.getOriginRequest() << endl);

	string cgi_name;
	parseParams(request.getRequestParam(), cgi_name, cgi_req);
	if(cgi_name.empty())
	{
		ret = CError::E_INVALID_PARAM;
		break;
	}

	map<string, st_cgi_conf>::iterator conf_it = g_map_cgi_conf.find(cgi_name);
	if(conf_it == g_map_cgi_conf.end())
	{
		TLOGDEBUG("invalid cgi name: " << cgi_name << endl);
		ret = CError::E_NOT_FOUND_CGI_CONF;
		break;
	}

	const st_cgi_conf & cgi_conf = conf_it->second;

	// verify login token // TODO
	
	ret = coroHttpGet(cgi_conf, cgi_req, cgi_rsp);

	_BLOCK_END_

	// cgi resp
	set_cgi_resp(ret, cgi_rsp, buffer);

	cost = tars::TC_TimeProvider::getInstance()->getNowMs() - cost;
	TLOGDEBUG("cgi complete, ret: " << ret 
		 	  << ", svr ret: " << cgi_rsp.ret 
		 	  << ", cost: " << cost << endl);

	return 0;
}

int HttpImp::set_cgi_resp(int & ret, HttpProto::st_cgi_rsp & cgi_rsp, vector<char> &buffer)
{
	TC_HttpResponse rsp;
	rsp.setContentType("application/json");
	if(!cgi_rsp.out_json.empty())
	{
		rsp.setResponse(cgi_rsp.out_json.c_str(), cgi_rsp.out_json.size());
	}
	else
	{
		// TODO: jsonp
		string out;
		int errcode = 0;
		string msg = CError::getErrDesc(ret, &errcode);
		out = "{\"ret\":" + tars::TC_Common::tostr<int>(errcode) 
				+ ", \"msg\":\"" + msg + "\"}";
		rsp.setResponse(out.c_str(), out.size());
	}
	rsp.encode(buffer);

	return 0;
}

int HttpImp::coroHttpGet(const st_cgi_conf & cgi_conf, HttpProto::st_cgi_req & req, HttpProto::st_cgi_rsp & rsp)
{
	TLOGDEBUG("in " << __func__ << endl);

	int ret = 0;
	if(!cgi_conf.isValid())
	{
		return CError::E_INVALID_CGI_CONF;
	}

    try
    {
		HttpProto::HttpCGIPrx pHttpPrx;
		pHttpPrx = Application::getCommunicator()->stringToProxy<HttpProto::HttpCGIPrx>(cgi_conf.svrobj);
		if(cgi_conf.timeout > 0)
		{
			pHttpPrx->tars_set_timeout(cgi_conf.timeout);
		}

	    CoroParallelBasePtr sharedPtr = new CoroParallelBase(1);
		
	    HttpCGICoroCallbackPtr httpcb = new HttpCGICoroCallback(rsp);
	    httpcb->setCoroParallelBasePtr(sharedPtr);
	    pHttpPrx->coro_get(httpcb, req);

	    coroWhenAll(sharedPtr);

		ret = httpcb->_iRet;
		TLOGDEBUG("coro_get, ret: " << httpcb->_iRet << ", exception ret: " << httpcb->_iException
					<< ", svr ret: " << rsp.ret << ", msg: " << rsp.msg 
					<< ", cost: " << httpcb->_cost << endl);
    }
    catch(exception& e)
    {
        cerr << "cgi name: " << cgi_conf.name << ", exception:" << e.what() << endl;
    }
    catch (...)
    {
        cerr << "cgi name: " << cgi_conf.name << ", unknown exception." << endl;
    }

	return ret;
}

int HttpImp::parseParams(const string & params, string & cgi_name, HttpProto::st_cgi_req & cgi_req)
{
	vector<string> vec_params = tars::TC_Common::sepstr<string>(params, "&");
	vector<string> vec_pair;
	for(unsigned int i = 0; i < vec_params.size(); i++)
	{
		vec_pair.clear();
		vec_pair = tars::TC_Common::sepstr<string>(vec_params[i], "=");
		if(vec_pair.size() == 1)
		{
			cgi_req.query[vec_pair[0]] = "";
			TLOGDEBUG("param key: " << vec_pair[0] << endl);
		}
		if(vec_pair.size() == 2)
		{
			cgi_req.query[vec_pair[0]] = vec_pair[0];
			if(vec_pair[0] == "name")
			{
				cgi_name = vec_pair[1];
			}
			TLOGDEBUG("param key: " << vec_pair[0] << ", value: " << vec_pair[1] << endl);
		}
	}

	return 0;
}
