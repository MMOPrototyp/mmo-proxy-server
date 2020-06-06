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

using boost::asio::ip::tcp;

/*void mmo::ProxyServer::ProxyServer(int maxNumberOfClients) {
    //
}*/

void mmo::ProxyServer::start(string_view ip, int tcpPort, int udpPort) {
    this->endpoint = tcp::endpoint(tcp::v4(), tcpPort);

    io_service.run();
}