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

	TC_HttpResponse rsp;
	string s = "hello";
	rsp.setResponse(s.c_str(), s.size());
	rsp.encode(buffer);

	return 0;
}
