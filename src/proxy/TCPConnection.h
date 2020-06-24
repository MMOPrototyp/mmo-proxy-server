//
// Created by Justin on 24.06.2020.
//

#ifndef PROXYSERVER_TCPCONNECTION_H
#define PROXYSERVER_TCPCONNECTION_H

#include <ctime>
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

#include "RedisClient.h"

using boost::asio::ip::tcp;


namespace mmo {

    class TCPConnection : public boost::enable_shared_from_this<TCPConnection> {
    public:
        typedef boost::shared_ptr<TCPConnection> pointer;

        static pointer create(boost::asio::io_service &io_service, mmo::RedisClient *redisClient) {
            return pointer(new TCPConnection(io_service, redisClient));
        }

        tcp::socket &socket() {
            return socket_;
        }

        void start() {
            //message_ = make_daytime_string();

            /*boost::asio::async_write(socket_, boost::asio::buffer(message_),
                                     boost::bind(&TCPConnection::handle_write, shared_from_this(),
                                                 boost::asio::placeholders::error,
                                                 boost::asio::placeholders::bytes_transferred));*/
        }

    private:
        TCPConnection(boost::asio::io_service &io_service, mmo::RedisClient *redisClient)
                : socket_(io_service) {
            this->redisClient = redisClient;
            cout << "new tcp connection" << endl;
        }

        void handle_write(const boost::system::error_code & /*error*/,
                          size_t /*bytes_transferred*/) {
        }

        tcp::socket socket_;
        std::string message_;

        mmo::RedisClient *redisClient;
    };

}


#endif //PROXYSERVER_TCPCONNECTION_H
