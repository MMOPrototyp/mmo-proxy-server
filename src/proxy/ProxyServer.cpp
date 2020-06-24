//
// Created by Justin on 06.06.2020.
//

#include "ProxyServer.h"

#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <utility>
#include <boost/asio.hpp>

#include "TCPServer.h"

using boost::asio::ip::tcp;

/*void mmo::ProxyServer::ProxyServer(int maxNumberOfClients) {
    //
}*/

void mmo::ProxyServer::start(string_view ip, int tcpPort, int udpPort, mmo::RedisClient *redisClient) {
    cout << "start tcp server on port " << tcpPort << endl;

    try {
        this->endpoint = tcp::endpoint(tcp::v4(), tcpPort);
        TCPServer tcpServer(io_context, endpoint, redisClient);

        io_context.run();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}