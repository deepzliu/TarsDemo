#ifndef _HttpServer_H_
#define _HttpServer_H_

#include <iostream>
#include "servant/Application.h"

using namespace tars;

/**
 *
 **/
class HttpServer : public Application
{
public:
    /**
     *
     **/
    virtual ~HttpServer() {};

    /**
     *
     **/
    virtual void initialize();

    /**
     *
     **/
    virtual void destroyApp();

	static void loadCGIConfig();
	bool procUpdate(const string& command, const string& params, string& result);
};

extern HttpServer g_app;

////////////////////////////////////////////
#endif
