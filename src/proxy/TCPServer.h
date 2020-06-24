//
// Created by Justin on 07.06.2020.
//

#ifndef PROXYSERVER_TCPSERVER_H
#define PROXYSERVER_TCPSERVER_H

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


#include "TCPConnection.h"
#include "RedisClient.h"

using namespace std;
using boost::asio::ip::tcp;


namespace mmo {

    class TCPServer {
    public:
        TCPServer(boost::asio::io_context& io_context,
                  const tcp::endpoint &endpoint, mmo::RedisClient *redisClient) : io_context_(io_context),
                                                                                  acceptor_(io_context, endpoint) {
            this->redisClient = redisClient;
            start_accept();
        }

    private:
        void start_accept() {
            TCPConnection::pointer new_connection =
                    TCPConnection::create(io_context_, this->redisClient);

            acceptor_.async_accept(new_connection->socket(),
                                   boost::bind(&TCPServer::handle_accept, this, new_connection,
                                               boost::asio::placeholders::error));

            /*TCPConnection::pointer new_connection =
                    TCPConnection::create(acceptor_.get_executor().context());

            acceptor_.async_accept(new_connection->socket(),
                                   boost::bind(&TCPServer::handle_accept, this, new_connection,
                                               boost::asio::placeholders::error));

            acceptor_.async_accept(socket_,
                                   [this](boost::system::error_code ec) {
                                       if (!ec) {
                                           cout << "new connection";
                                           //std::make_shared<chat_session>(std::move(socket_), room_)->start();
                                       }

                                       start_accept();
                                   });*/
        }

        void handle_accept(TCPConnection::pointer new_connection,
                           const boost::system::error_code &error) {
            if (!error) {
                new_connection->start();
            }

            start_accept();
        }

        boost::asio::io_context& io_context_;
        tcp::acceptor acceptor_;
        mmo::RedisClient *redisClient;
    };

}


#endif //PROXYSERVER_TCPSERVER_H
