//
// Created by Justin on 07.06.2020.
//

#ifndef PROXYSERVER_TCPSESSION_H
#define PROXYSERVER_TCPSESSION_H

#include <cstdlib>
#include <deque>
#include <iostream>
#include <list>
#include <memory>
#include <set>
#include <utility>
#include <boost/asio.hpp>

#include "TCPMessage.h"

using namespace std;
using boost::asio::ip::tcp;


namespace mmo {

    class TCPSession : public std::enable_shared_from_this<TCPSession> {
    public:
        TCPSession(tcp::socket socket/*, chat_room& room*/)
                : socket_(std::move(socket))
        //room_(room)
        {
            //
        }

        void start() {
            //room_.join(shared_from_this());
            do_read_header();
        }

        /*void deliver(const chat_message& msg)
        {
            bool write_in_progress = !write_msgs_.empty();
            write_msgs_.push_back(msg);
            if (!write_in_progress)
            {
                do_write();
            }
        }*/

    private:
        void do_read_header() {
            auto self(shared_from_this());
            boost::asio::async_read(socket_,
                                    boost::asio::buffer(read_msg_.data(), TCPMessage::header_length),
                                    [this, self](boost::system::error_code ec, std::size_t /*length*/) {
                                        if (!ec && read_msg_.decode_header()) {
                                            do_read_body();
                                        } else {
                                            //room_.leave(shared_from_this());
                                        }
                                    });
        }

        void do_read_body() {
            auto self(shared_from_this());
            boost::asio::async_read(socket_,
                                    boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
                                    [this, self](boost::system::error_code ec, std::size_t /*length*/) {
                                        if (!ec) {
                                            //room_.deliver(read_msg_);
                                            do_read_header();
                                        } else {
                                            //room_.leave(shared_from_this());
                                        }
                                    });
        }

        void do_write() {
            auto self(shared_from_this());
            /*boost::asio::async_write(socket_,
                                     boost::asio::buffer(write_msgs_.front().data(),
                                                         write_msgs_.front().length()),
                                     [this, self](boost::system::error_code ec, std::size_t length) {
                                         if (!ec) {
                                             write_msgs_.pop_front();
                                             if (!write_msgs_.empty()) {
                                                 do_write();
                                             }
                                         } else {
                                             room_.leave(shared_from_this());
                                         }
                                     });*/
        }

        tcp::socket socket_;
        //chat_room& room_;
        TCPMessage read_msg_;
        //chat_message_queue write_msgs_;
    };

}


#endif //PROXYSERVER_TCPSESSION_H
