//
// Created by Justin on 30.05.2020.
//

#ifndef PROXYSERVER_MONITORINGCLIENT_H
#define PROXYSERVER_MONITORINGCLIENT_H

#include <string>

#include "ServerConfig.h"
#include "RedisClient.h"

using namespace std;

namespace mmo {

    class MonitoringClient {

    public:
        void init(ServerConfig *serverConfig, RedisClient *redisClient);
        void execute();
        double getUptimeInSeconds();

    private:
        int serverID;
        string serverTitle;

        ServerConfig *serverConfig;
        RedisClient *redisClient;
    };

}


#endif //PROXYSERVER_MONITORINGCLIENT_H
