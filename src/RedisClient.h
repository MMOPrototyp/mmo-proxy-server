//
// Created by Justin on 29.05.2020.
//

#ifndef PROXYSERVER_REDISCLIENT_H
#define PROXYSERVER_REDISCLIENT_H

#define REDISCPP_HEADER_ONLY

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>

using namespace std;

namespace mmo {

    class RedisClient {

        // Access specifier
    public:

        //Default Constructor
        RedisClient(string ip, int port) {
            this->ip = ip;
            this->port = port;

            cout << "init redis client" << endl;
        }

        void setPassword(string password);
        bool connect();

        void addListEntry(string_view key, string_view value);
        void removeListEntry(string_view key, string_view value);

    private:
        // Data Members

        //server data
        string ip;
        int port;
        string username;
        string password;

        //redis stream
        std::shared_ptr<std::iostream> stream;
    };

}

#endif //PROXYSERVER_REDISCLIENT_H
