//
// Created by Justin on 29.05.2020.
//

#ifndef PROXYSERVER_SERVERCONFIG_H
#define PROXYSERVER_SERVERCONFIG_H

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>

#include <config4cpp/Configuration.h>
#include <iostream>

using namespace config4cpp;
using namespace std;

namespace mmo {

    class RedisConfig {
    public:
        string ip;
        int port;
        string username;
        string password;
    };

    class ProxyConfig {
    public:
        string ip;
        int port;
        bool publicServer;

        string getUrl() {
            return ip + ":" + std::to_string(port);
        }
    };

    class ServerConfig {
    public:
        RedisConfig getRedisConfig() {
            return redisConfig;
        }

        ProxyConfig getProxyConfig() {
            return proxyConfig;
        }

        bool parse(string filePath);

    private:
        Configuration *cfg = Configuration::create();

        RedisConfig redisConfig;
        ProxyConfig proxyConfig;
    };

}


#endif //PROXYSERVER_SERVERCONFIG_H