#ifndef _HttpImp_H_
#define _HttpImp_H_

#include "servant/Application.h"
#include "common.h"
#include "error.h"
#include "http_cgi.h"

struct st_cgi_conf
{
	st_cgi_conf():timeout(200){}

	void init()
	{
		name = "";
		svrobj = "";
		svrset = "";
		timeout = 0;
	}

	string toString() const
	{
		ostringstream oss;
		oss << "{name=" << name
			<< ";svrobj=" << svrobj
			<< ";svrset=" << svrset
			<< ";timeout=" << timeout
			<< "}";
		return oss.str();
	}

	bool isValid() const
	{
		if(name.empty() || svrobj.empty())
		{
			TLOGDEBUG("cgi conf is invalid, conf: " << toString() << endl);
			return false;
		}
		return true;
	}

	string name;
	string svrobj;
	string svrset;
	int timeout;
};

/**
 *
 *
 */
class HttpImp : public Servant
{
public:
    /**
     *
     */
    virtual ~HttpImp() {}

    /**
     *
     */
    virtual void initialize();

    /**
     *
     */
    virtual void destroy();

    /**
     *
     */
	int doRequest(TarsCurrentPtr current, vector<char> &buffer);

private:
	int parseParams(const string & params, string & cgi_name, HttpProto::st_cgi_req & cgi_req);
	int coroHttpGet(const st_cgi_conf & cgi_conf, HttpProto::st_cgi_req & req, HttpProto::st_cgi_rsp & rsp);
	int set_cgi_resp(int & ret, HttpProto::st_cgi_rsp & cgi_rsp, vector<char> &buffer);
};

/////////////////////////////////////////////////////
#endif
