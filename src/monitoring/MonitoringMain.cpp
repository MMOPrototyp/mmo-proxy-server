//
// Created by Justin on 30.05.2020.
//

#include "MonitoringMain.h"
#include "ProxyConfig.h"
#include "ServerConfig.h"
#include <string>

#include <cstdlib>
#include <iostream>

#define REDISCPP_HEADER_ONLY

//#include <redis-cpp/stream.h>
//#include <redis-cpp/execute.h>

#include <string>

#include <config4cpp/Configuration.h>
#include <iostream>
#include <thread>
#include <chrono>

#include "RedisClient.h"
#include "MonitoringClient.h"

using namespace config4cpp;
using namespace std;

int main() {
    static_assert("C++17");

    cout << "################################" << endl;
    cout << "# MMO Monitoring Client    #" << endl;
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

    mmo::MonitoringClient * monitoringClient;

    //TODO: initialize monitoring client (set redis client and config)

    //send data every minute to redis server
    while (true) {
        monitoringClient->execute();
        std::this_thread::sleep_for(std::chrono::seconds(60));
    }

    //TODO: add code here

    return 0;
}
