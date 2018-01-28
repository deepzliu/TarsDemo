#ifndef _HttpImp_H_
#define _HttpImp_H_

#include "servant/Application.h"
#include "Http.h"

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
};
/////////////////////////////////////////////////////
#endif
