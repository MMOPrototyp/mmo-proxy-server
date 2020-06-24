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
#include <boost/asio.hpp>

#include "TCPConnection.h"

using namespace std;
using boost::asio::ip::tcp;


namespace mmo {

    class TCPServer {
    public:
        TCPServer(boost::asio::io_service &io_service,
                  const tcp::endpoint &endpoint) : acceptor_(io_service, endpoint),
                                                   socket_(io_service) {
            start_accept();
        }

    private:
        void start_accept() {
            TCPConnection::pointer new_connection =
                    TCPConnection::create(acceptor_.get_io_service());

            acceptor_.async_accept(new_connection->socket(),
                                   boost::bind(&tcp_server::handle_accept, this, new_connection,
                                               boost::asio::placeholders::error));

            acceptor_.async_accept(socket_,
                                   [this](boost::system::error_code ec) {
                                       if (!ec) {
                                           cout << "new connection";
                                           //std::make_shared<chat_session>(std::move(socket_), room_)->start();
                                       }

                                       start_accept();
                                   });
        }

        void handle_accept(TCPConnection::pointer new_connection,
                           const boost::system::error_code& error)
        {
            if (!error)
            {
                new_connection->start();
            }

            start_accept();
        }

        tcp::acceptor acceptor_;
        tcp::socket socket_;
    };

}


#endif //PROXYSERVER_TCPSERVER_H
