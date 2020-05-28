// mmo-proxy-server.cpp: Definiert den Einstiegspunkt für die Anwendung.
//

#include "mmo-proxy-server.h"
#include "ProxyConfig.h"
#include <string>
//#include "3rdparty/cpp_redis/includes/cpp_redis/core/client.hpp"

//#include<cpp_redis/cpp_redis>

#include <cstdlib>
#include <iostream>

#include <redis-cpp/stream.h>
#include <redis-cpp/execute.h>

#include <string>

#include <config4cpp/Configuration.h>
#include <iostream>
using namespace config4cpp;
using namespace std;

int main()
{
	cout << "################################" << endl;
	cout << "# MMO Prototyp Proxy Server    #" << endl;
	cout << "#                              #" << endl;
	cout << "# Version: " << std::to_string(PROXY_VERSION_MAJOR) << "." << std::to_string(PROXY_VERSION_MINOR) << "." << std::to_string(PROXY_VERSION_PATCH) << "               #" << endl;
	cout << "################################" << endl;

	//https://stackoverflow.com/questions/6892754/creating-a-simple-configuration-file-and-parser-in-c

	//https://stackoverflow.com/questions/6892754/creating-a-simple-configuration-file-and-parser-in-c/6900247

    Configuration *  cfg = Configuration::create();
    const char *     scope = "Redis";
    const char *     configFile = "config/redis.cfg";
    const char *     ip;
    int       port;
    const char *     password;
    //bool             true_false;

    //see also: http://www.config4star.org/config4star-getting-started-guide/overview-of-config4star-syntax.html
    try {
        cfg->parse(configFile);
        ip        = cfg->lookupString(scope, "ip");
        port       = cfg->lookupInt(scope, "port");
        password   = cfg->lookupString(scope, "password");
        //true_false = cfg->lookupBoolean(scope, "true_false");
    } catch(const ConfigurationException & ex) {
        cerr << ex.c_str() << endl;
        cfg->destroy();
        return 1;
    }

    cout << endl;
    cout << "Redis Server: " << ip << ":" << port << endl;
    cout << endl;

    //see also: https://github.com/tdv/redis-cpp

    //connect to redis server
    auto stream = rediscpp::make_stream(ip, std::to_string(port));

    //std::cout << rediscpp::execute(*stream, "ping").as<std::string>() << std::endl;
	return 0;
}
