//
// Created by Justin on 06.06.2020.
//

#ifndef PROXYSERVER_PROXYSERVER_H
#define PROXYSERVER_PROXYSERVER_H

#define REDISCPP_HEADER_ONLY

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>

#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <utility>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

#include "TCPServer.h"

using boost::asio::ip::tcp;

using namespace std;


namespace mmo {

    class ProxyServer {
    public:
        ProxyServer(int maxNumberOfClients) {
            this->maxNumberOfClients = maxNumberOfClients;
        }

        void start(string_view ip, int tcpPort, int udpPort, mmo::RedisClient *redisClient);
        void stop();

    private:
        string_view ip;
        int tcpPort;
        int udpPort;

        int maxNumberOfClients;

        boost::asio::io_context io_context;
        //boost::asio::io_service io_service;
        //TCPServer tcpServer = null;

        tcp::endpoint endpoint;
    };

}


#endif //PROXYSERVER_PROXYSERVER_H
