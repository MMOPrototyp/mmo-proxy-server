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

using namespace std;


namespace mmo {

    class ProxyServer {
    public:
        ProxyServer(int maxNumberOfClients) {
            this->maxNumberOfClients = maxNumberOfClients;
        }

        void start(string_view ip, int tcpPort, int udpPort);
        void stop();

    private:
        string_view ip;
        int tcpPort;
        int udpPort;

        int maxNumberOfClients;
    };

}


#endif //PROXYSERVER_PROXYSERVER_H
