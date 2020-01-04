#include "HttpImp.h"
#include "servant/Application.h"

using namespace std;
extern map<string, st_cgi_conf> g_map_cgi_conf;

class HttpCGICallBack : public HttpApp::HttpCGIPrxCallback
{
public:
	HttpCGICallBack(){
		TLOGDEBUG("HttpCGICallBack constructor" << endl);
	}

    virtual ~HttpCGICallBack(){}
    virtual void callback_get(tars::Int32 ret,  const HttpApp::st_cgi_rsp& rsp)
	{
		TLOGDEBUG("callback_get ret: " << ret 
					<< ", rsp ret: " << rsp.ret
					<< ", msg: " << rsp.msg
					<< endl);
	}

    virtual void callback_get_exception(tars::Int32 ret)
	{
		TLOGDEBUG("callback_get_exception ret: " << ret << endl);
	}
};

class HttpCGICoroCallback : public HttpApp::HttpCGICoroPrxCallback
{
public:
    virtual ~HttpCGICoroCallback(){}

    virtual void callback_get(tars::Int32 ret,  const HttpApp::st_cgi_rsp& rsp)
    { 
		_iRet = ret;
		_rsp = rsp;
   	}
    virtual void callback_get_exception(tars::Int32 ret)
	{
		_iException = ret;
	}

public:
	int		_iException;
	int		_iRet;
	HttpApp::st_cgi_rsp _rsp;
};
typedef tars::TC_AutoPtr<HttpCGICoroCallback> HttpCGICoroCallbackPtr;

//////////////////////////////////////////////////////
void HttpImp::initialize()
{
    //initialize servant here:
    //...
	//_pPrx = Application::getCommunicator()->stringToProxy<HttpApp::HttpCGIPrx>("HttpApp.HttpCGIServer.HttpCGIObj");
	_pPrx = Application::getCommunicator()->stringToProxy<HttpApp::HttpCGIPrx>("HttpApp.HttpCGIServer.HttpCGIObj@tcp -h 9.134.74.246 -p 18601");
	//LoadConfig();
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
	HttpApp::st_cgi_req cgi_req;
	HttpApp::st_cgi_rsp cgi_rsp;

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

	//hello_get(cgi_req, cgi_rsp);
	//coro_hello_get(cgi_req, cgi_rsp);

	map<string, st_cgi_conf>::iterator it = g_map_cgi_conf.begin();
	for(; it != g_map_cgi_conf.end(); ++it)
	{
		TLOGDEBUG("cgi conf: " << it->second.toString() << endl);
	}

	stringstream ss;
	ss << "HttpCGI, this is Http."
	   << "\nOrigin: " << request.getOriginRequest() 
	   << "\nrequest URL: " << request.getRequestUrl()
	   << "\nURL: " << request.getURL().getURL() 
	   << "\nParam: " << request.getRequestParam() 
	   << endl;
	TC_HttpResponse rsp;
	rsp.setResponse(ss.str().c_str(), ss.str().size());
	rsp.encode(buffer);

	_BLOCK_END_

	// cgi resp
	set_cgi_resp(ret, cgi_rsp);

	return 0;
}

int HttpImp::set_cgi_resp(int & ret, HttpApp::st_cgi_rsp & cgi_rsp)
{
	return 0;
}


int HttpImp::hello_get(HttpApp::st_cgi_req & req, HttpApp::st_cgi_rsp & rsp)
{
	req.query["aaa"] = "123";
	req.query["bbb"] = "456";

	TLOGDEBUG("in hello_get" << endl);

    Communicator comm;
    try
    {
		HttpApp::HttpCGIPrx prx;
        comm.stringToProxy("HttpApp.HttpCGIServer.HttpCGIObj@tcp -h 9.134.74.246 -p 18601" , prx);

		// async call not success // TODO
		HttpApp::HttpCGIPrxCallbackPtr cb = new HttpCGICallBack();
		//prx->tars_set_timeout(3000);
		prx->async_get(cb, req);
		TLOGDEBUG("do async_get" << endl);

		// sync call success
        /*int ret = prx->get(req, rsp);
		TLOGDEBUG("do get, ret: " << ret << ", svr ret: " << rsp.ret << ", msg: " << rsp.msg << endl);*/
    }
    catch(exception& e)
    {
        cerr<<"exception:"<<e.what() <<endl;
    }
    catch (...)
    {
        cerr<<"unknown exception."<<endl;
    }

	return 0;
}

int HttpImp::coro_hello_get(HttpApp::st_cgi_req & req, HttpApp::st_cgi_rsp & rsp)
{
	req.query["aaa"] = "123";
	req.query["bbb"] = "456";

	TLOGDEBUG("in coro_hello_get" << endl);

    //Communicator comm;
    try
    {
		//HttpApp::HttpCGIPrx prx;
        //comm.stringToProxy("HttpApp.HttpCGIServer.HttpCGIObj@tcp -h 9.134.74.246 -p 18601" , prx);

		//HttpApp::HttpCGIPrx _pPrx;
		//_pPrx = Application::getCommunicator()->stringToProxy<HttpApp::HttpCGIPrx>("HttpApp.HttpCGIServer.HttpCGIObj");

	    CoroParallelBasePtr sharedPtr = new CoroParallelBase(1);
		
	    HttpCGICoroCallbackPtr cb1 = new HttpCGICoroCallback();
	    cb1->setCoroParallelBasePtr(sharedPtr);
	    _pPrx->coro_get(cb1, req);

	    //AServantCoroCallbackPtr cb2 = new AServantCoroCallback();
	    //cb2->setCoroParallelBasePtr(sharedPtr);
	    //_pPrx->coro_testStr(cb2, sIn);

	    coroWhenAll(sharedPtr);

		TLOGDEBUG("coro_get, ret: " << cb1->_iRet << ", exception ret: " << cb1->_iException
					<< ", svr ret: " << cb1->_rsp.ret << ", msg: " << cb1->_rsp.msg << endl);
    }
    catch(exception& e)
    {
        cerr<<"exception:"<<e.what() <<endl;
    }
    catch (...)
    {
        cerr<<"unknown exception."<<endl;
    }

	return 0;
}

int HttpImp::parseParams(const string & params, string & cgi_name, HttpApp::st_cgi_req & cgi_req)
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
