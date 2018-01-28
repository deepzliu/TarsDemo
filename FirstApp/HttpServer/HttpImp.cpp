#include "HttpImp.h"
#include "servant/Application.h"

using namespace std;

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
	TC_HttpRequest request;
	vector<char> v = current->getRequestBuffer();
	string sBuf;
	sBuf.assign(&v[0], v.size());
	request.decode(sBuf);

	TLOGDEBUG("URL: " << request.getOriginRequest() << endl);
	TLOGDEBUG("URL: " << request.getURL().getURL() << endl);

	stringstream ss;
	ss << "Hello, this is Http."
	   << "\nOrigin: " << request.getOriginRequest() 
	   << "\nrequest URL: " << request.getRequestUrl()
	   << "\nURL: " << request.getURL().getURL() 
	   << "\nParam: " << request.getRequestParam() 
	   << endl;

	TC_HttpResponse rsp;
	rsp.setResponse(ss.str().c_str(), ss.str().size());
	rsp.encode(buffer);

	return 0;
}
