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

using namespace std;
using boost::asio::ip::tcp;


namespace mmo {

    class TCPServer {
    public:
        TCPServer(boost::asio::io_service &io_service,
                  const tcp::endpoint &endpoint) : acceptor_(io_service, endpoint),
                                                   socket_(io_service) {
            do_accept();
        }

    private:
        void do_accept() {
            acceptor_.async_accept(socket_,
                                   [this](boost::system::error_code ec) {
                                        cout << "new connection";

                                       if (!ec) {
                                           //std::make_shared<chat_session>(std::move(socket_), room_)->start();
                                       }

                                       do_accept();
                                   });
        }

        tcp::acceptor acceptor_;
        tcp::socket socket_;
    };

}


#endif //PROXYSERVER_TCPSERVER_H