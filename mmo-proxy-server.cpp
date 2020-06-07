// mmo-proxy-server.cpp: Definiert den Einstiegspunkt für die Anwendung.
//

#include "mmo-proxy-server.h"
#include "ProxyConfig.h"
#include "ServerConfig.h"
#include <string>
//#include "3rdparty/cpp_redis/includes/cpp_redis/core/client.hpp"

//#include<cpp_redis/cpp_redis>

#include <cstdlib>
#include <iostream>

#define REDISCPP_HEADER_ONLY

//#include <redis-cpp/stream.h>
//#include <redis-cpp/execute.h>

#include <string>

#include <config4cpp/Configuration.h>
#include <iostream>

#include "RedisClient.h"
#include "proxy/ProxyServer.h"

using namespace config4cpp;
using namespace std;

int main() {
    static_assert("C++17");

    cout << "################################" << endl;
    cout << "# MMO Prototyp Proxy Server    #" << endl;
    cout << "#                              #" << endl;
    cout << "# Version: " << std::to_string(PROXY_VERSION_MAJOR) << "." << std::to_string(PROXY_VERSION_MINOR) << "."
         << std::to_string(PROXY_VERSION_PATCH) << "               #" << endl;
    cout << "################################" << endl;

    //https://stackoverflow.com/questions/6892754/creating-a-simple-configuration-file-and-parser-in-c

    //https://stackoverflow.com/questions/6892754/creating-a-simple-configuration-file-and-parser-in-c/6900247

    mmo::ServerConfig serverConfig;

    if (!serverConfig.parse("config/redis.cfg")) {
        cerr << "Error: Cannot parse config file";
        return 1;
    }

    mmo::RedisConfig redisConfig = serverConfig.getRedisConfig();
    mmo::ProxyConfig proxyConfig = serverConfig.getProxyConfig();
    mmo::RedisClient redisClient(redisConfig.ip, redisConfig.port);

    redisClient.setPassword(redisConfig.password);

    if (!redisClient.connect()) {
        cerr << "Cannot connect to redis server";
        return 1;
    }

    //check, if proxy server is already in list
    string_view serverID = proxyConfig.getUrl() + ":" + to_string(PROXY_VERSION_MAJOR) + "." + to_string(PROXY_VERSION_MINOR) + "." + to_string(PROXY_VERSION_PATCH);
    redisClient.removeListEntry("proxy-server-list", serverID);

    //push list entry
    redisClient.addListEntry("proxy-server-list", proxyConfig.getUrl() + ":" + to_string(PROXY_VERSION_MAJOR) + "." + to_string(PROXY_VERSION_MINOR) + "." + to_string(PROXY_VERSION_PATCH));

    //std::cout << rediscpp::execute(*stream, "ping").as<std::string>() << std::endl;

    //TODO: start tcp and udp server
    mmo::ProxyServer proxyServer(proxyConfig.maxNumberOfClients);
    proxyServer.start("0.0.0.0", proxyConfig.port, proxyConfig.udpPort);

    cout << endl;
    cout << "tcp server is listen on port " << to_string(proxyConfig.port) << endl;
    cout << "udp server is listen on port " << to_string(proxyConfig.udpPort) << endl;
    cout << "Type 'quit' to quit proxy server" << endl;

    while (true) {
        string input;
        getline (cin, input);

        if(input.compare("quit") == 0) {
            break;
        } else {
            //command_list.append(input);
        }
    }

    //stop server and remove server from list
    cout << "Stop proxy server now" << endl;
    redisClient.removeListEntry("proxy-server-list", serverID);

    return 0;
}
