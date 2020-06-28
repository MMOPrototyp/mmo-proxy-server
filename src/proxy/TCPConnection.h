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

#include <cstdlib>
#include <deque>
#include <list>
#include <memory>
#include <set>
#include <utility>

#include <boost/asio/awaitable.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/redirect_error.hpp>
#include <boost/asio/signal_set.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/use_awaitable.hpp>
#include <boost/asio/write.hpp>


#include "RedisClient.h"

using boost::asio::ip::tcp;
//using boost::asio::awaitable;
//using boost::asio::co_spawn;
using boost::asio::detached;
using boost::asio::redirect_error;
//using boost::asio::use_awaitable;



namespace mmo {

    //https://www.boost.org/doc/libs/1_73_0/doc/html/boost_asio/examples.html

    //https://www.boost.org/doc/libs/1_73_0/doc/html/boost_asio/example/cpp17/coroutines_ts/chat_server.cpp

    class TCPConnection : public boost::enable_shared_from_this<TCPConnection> {
    public:
        typedef boost::shared_ptr<TCPConnection> pointer;

        static pointer create(boost::asio::io_context &io_context, mmo::RedisClient *redisClient) {
            return pointer(new TCPConnection(io_context, redisClient));
        }

        tcp::socket &socket() {
            return socket_;
        }

        void start() {
            cout << "new client: " << socket_.remote_endpoint().address() << socket_.remote_endpoint().port() << endl;

            this->enableTCPKeepAlive(&socket_);

            /*awaitable<void> reader() {
                try {
                    for (std::string read_msg;;) {
                        std::size_t n = co_await
                        boost::asio::async_read_until(socket_,
                                                      boost::asio::dynamic_buffer(read_msg, 1024), "\n", use_awaitable);

                        //room_.deliver(read_msg.substr(0, n));
                        read_msg.erase(0, n);
                    }
                }
                catch (std::exception &) {
                    stop();
                }
            }

            awaitable<void> writer() {
                try {
                    while (socket_.is_open()) {
                        if (write_msgs_.empty()) {
                            boost::system::error_code ec;
                            co_await
                            timer_.async_wait(redirect_error(use_awaitable, ec));
                        } else {
                            co_await boost::asio::async_write(socket_,
                                                              boost::asio::buffer(write_msgs_.front()), use_awaitable);
                            write_msgs_.pop_front();
                        }
                    }
                }
                catch (std::exception &) {
                    stop();
                }
            }*/

            /*co_spawn(socket_.get_executor(),
                     [self = shared_from_this()]{ return self->reader(); },
                     detached);

            co_spawn(socket_.get_executor(),
                     [self = shared_from_this()]{ return self->writer(); },
                     detached);*/

            //message_ = make_daytime_string();

            /*boost::asio::async_write(socket_, boost::asio::buffer(message_),
                                     boost::bind(&TCPConnection::handle_write, shared_from_this(),
                                                 boost::asio::placeholders::error,
                                                 boost::asio::placeholders::bytes_transferred));*/

            /*boost::asio::async_write(socket_, boost::asio::buffer(message_),
                    boost::bind(&TCPConnection::handle_write, shared_from_this()));*/
        }

    private:
        TCPConnection(boost::asio::io_context &io_context, mmo::RedisClient *redisClient)
                : timer_(socket_.get_executor()), socket_(io_context) {
            this->redisClient = redisClient;
            cout << "new tcp connection" << endl;
        }

        void handle_write(const boost::system::error_code & /*error*/,
                          size_t /*bytes_transferred*/) {
        }

        void enableTCPKeepAlive(boost::asio::ip::tcp::socket *tcpsocket) {
            //enable tcp keepalive
            // the timeout value
            unsigned int timeout_milli = 10000;

            // platform-specific switch
            #if defined _WIN32 || defined WIN32 || defined OS_WIN64 || defined _WIN64 || defined WIN64 || defined WINNT
                // use windows-specific time
                int32_t timeout = timeout_milli;
                setsockopt(tcpsocket->native_handle(), SOL_SOCKET, SO_RCVTIMEO, (const char *) &timeout, sizeof(timeout));
                setsockopt(tcpsocket->native_handle(), SOL_SOCKET, SO_SNDTIMEO, (const char *) &timeout, sizeof(timeout));
            #else
                // assume everything else is posix
                struct timeval tv;
                tv.tv_sec  = timeout_milli / 1000;
                tv.tv_usec = (timeout_milli % 1000) * 1000;
                setsockopt(tcpsocket->native_handle(), SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
                setsockopt(tcpsocket->native_handle(), SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv));
            #endif
        }

        tcp::socket socket_;
        //std::string message_;

        boost::asio::steady_timer timer_;

        mmo::RedisClient *redisClient;
    };

}


#endif //PROXYSERVER_TCPCONNECTION_H
