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

    //https://www.boost.org/doc/libs/1_73_0/doc/html/boost_asio/examples.html

    //https://www.boost.org/doc/libs/1_73_0/doc/html/boost_asio/example/cpp17/coroutines_ts/chat_server.cpp

    class TCPConnection : public boost::enable_shared_from_this<TCPConnection> {
    public:
        typedef boost::shared_ptr<TCPConnection> pointer;

        static pointer create(boost::asio::io_context& io_context, mmo::RedisClient *redisClient) {
            return pointer(new TCPConnection(io_context, redisClient));
        }

        tcp::socket &socket() {
            return socket_;
        }

        void start() {
            cout << "new client: " << socket_.remote_endpoint().address() << socket_.remote_endpoint().port() << endl;

            //message_ = make_daytime_string();

            /*boost::asio::async_write(socket_, boost::asio::buffer(message_),
                                     boost::bind(&TCPConnection::handle_write, shared_from_this(),
                                                 boost::asio::placeholders::error,
                                                 boost::asio::placeholders::bytes_transferred));*/

            /*boost::asio::async_write(socket_, boost::asio::buffer(message_),
                    boost::bind(&TCPConnection::handle_write, shared_from_this()));*/
        }

    private:
        TCPConnection(boost::asio::io_context& io_context, mmo::RedisClient *redisClient)
                : socket_(io_context) {
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
