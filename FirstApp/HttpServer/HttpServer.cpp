#include "HttpServer.h"
#include "HttpImp.h"

using namespace std;

HttpServer g_app;
map<string, st_cgi_conf> g_map_cgi_conf;
int CError::_business_code = 1;
int CError::_service_code = 1;
int CError::_module_code = 1;

struct HttpProtocol
{
    /**
     * 解析http请求
     * @param in
     * @param out
     *
     * @return int
     */
    static int parseHttp(string &in, string &out)
    {
        try
        {
            //判断请求是否是HTTP请求
            bool b = TC_HttpRequest ::checkRequest(in.c_str(), in.length());
            //完整的HTTP请求
            if(b)
            {
                out = in;
                in  = "";
                return TC_EpollServer::PACKET_FULL;
            }
            else
            {
                return TC_EpollServer::PACKET_LESS;
            }
        }
        catch(exception &ex)
        {
        	TLOGDEBUG("parse http failed: " << ex.what() << endl);
            return TC_EpollServer::PACKET_ERR;
        }

        return TC_EpollServer::PACKET_LESS;             //表示收到的包不完全
    }

};

/////////////////////////////////////////////////////////////////
void
HttpServer::initialize()
{
    //initialize application here:
    //...

	ServerConfig::OpenCoroutine = true;
    addServant<HttpImp>(ServerConfig::Application + "." + ServerConfig::ServerName + ".HttpObj");
    addServantProtocol(ServerConfig::Application + "." + ServerConfig::ServerName + ".HttpObj",&HttpProtocol::parseHttp);
	HttpServer::loadCGIConfig();

	TARS_ADD_ADMIN_CMD_NORMAL("UPDATE", HttpServer::procUpdate);
}
/////////////////////////////////////////////////////////////////
void
HttpServer::destroyApp()
{
    //destroy application here:
    //...
}
/////////////////////////////////////////////////////////////////
bool HttpServer::procUpdate(const string& command, const string& params, string& result)
{
	TLOGDEBUG("cmd: " << command << ", params: " << params << ", result: " << result << endl);
	if("UPDATE" == command && "conf" == params)
	{
		HttpServer::loadCGIConfig();
	}
	return false;
}

void HttpServer::loadCGIConfig()
{
	TC_Config conf;
	string conf_file = ServerConfig::BasePath + "cgi.conf";

	try{

		st_cgi_conf cgi_conf;
		vector<string> domain_list;
		map<string, st_cgi_conf> map_cgi_conf;
		string sTemp;

		conf.parseFile(conf_file);
		conf.getDomainVector("/cgi", domain_list);

		for(unsigned int i = 0; i < domain_list.size(); i++)
		{
			cgi_conf.init();
			cgi_conf.name = domain_list[i];
			cgi_conf.svrobj = conf.get("/cgi/" + domain_list[i] + "<svrobj>");
			cgi_conf.svrset = conf.get("/cgi/" + domain_list[i] + "<set>");
			sTemp = conf.get("/cgi/" + domain_list[i] + "<timeout>");
			cgi_conf.timeout = atoi(sTemp.c_str());
			map_cgi_conf[cgi_conf.name] = cgi_conf;
			TLOGDEBUG(i << ": cgi conf domain: " << domain_list[i] << ", conf: " << cgi_conf.toString() << endl);
		}

		if(map_cgi_conf.size() > 0)
		{
			// 有必要时，再用两个map交叉使用，一个用于加载配置，另一个当前使用
			g_map_cgi_conf = map_cgi_conf; 
		}
	}
    catch (TC_Config_Exception & ex)
    {
        TLOGDEBUG("load config: " << conf_file << ", error: " << ex.what() << endl);
    }
    catch (exception &ex)
    {
        TLOGDEBUG("load config: " << conf_file << ", error: " << ex.what() << endl);
    }
}
/////////////////////////////////////////////////////////////////

int
main(int argc, char* argv[])
{
    try
    {
        g_app.main(argc, argv);
        g_app.waitForShutdown();
    }
    catch (std::exception& e)
    {
        cerr << "std::exception:" << e.what() << std::endl;
    }
    catch (...)
    {
        cerr << "unknown exception." << std::endl;
    }
    return -1;
}
/////////////////////////////////////////////////////////////////
