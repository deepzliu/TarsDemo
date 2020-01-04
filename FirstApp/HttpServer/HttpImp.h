#ifndef _HttpImp_H_
#define _HttpImp_H_

#include "servant/Application.h"
#include "common.h"
#include "error.h"
#include "http_cgi.h"

struct st_cgi_conf
{
	st_cgi_conf():timeout(0){}

	void init()
	{
		name = "";
		svrobj = "";
		svrset = "";
		timeout = 0;
	}

	string toString()
	{
		ostringstream oss;
		oss << "{name=" << name
			<< ";svrobj=" << svrobj
			<< ";svrset=" << svrset
			<< ";timeout=" << timeout
			<< "}";
		return oss.str();
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
	int parseParams(const string & params, string & cgi_name, HttpApp::st_cgi_req & cgi_req);
	int set_cgi_resp(int & ret, HttpApp::st_cgi_rsp & cgi_rsp);

	int hello_get(HttpApp::st_cgi_req & req, HttpApp::st_cgi_rsp & rsp);
	int coro_hello_get(HttpApp::st_cgi_req & req, HttpApp::st_cgi_rsp & rsp);

private:
	HttpApp::HttpCGIPrx _pPrx;
};

/////////////////////////////////////////////////////
#endif
