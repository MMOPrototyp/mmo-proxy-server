//
// Created by Justin on 07.06.2020.
//

#ifndef PROXYSERVER_TCPMESSAGE_H
#define PROXYSERVER_TCPMESSAGE_H

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

    //see also: https://www.boost.org/doc/libs/1_63_0/doc/html/boost_asio/example/cpp11/chat/chat_message.hpp

    class TCPMessage {
    public:
        enum {
            header_length = 4
        };
        enum {
            max_body_length = 1024
        };

        TCPMessage()
                : body_length_(0) {
        }

        const char *data() const {
            return data_;
        }

        char *data() {
            return data_;
        }

        std::size_t length() const {
            return header_length + body_length_;
        }

        const char *body() const {
            return data_ + header_length;
        }

        char *body() {
            return data_ + header_length;
        }

        std::size_t body_length() const {
            return body_length_;
        }

        void body_length(std::size_t new_length) {
            body_length_ = new_length;
            if (body_length_ > max_body_length)
                body_length_ = max_body_length;
        }

        bool decode_header() {
            char header[header_length + 1] = "";
            std::strncat(header, data_, header_length);
            body_length_ = std::atoi(header);
            if (body_length_ > max_body_length) {
                body_length_ = 0;
                return false;
            }
            return true;
        }

        void encode_header() {
            char header[header_length + 1] = "";
            std::sprintf(header, "%4d", static_cast<int>(body_length_));
            std::memcpy(data_, header, header_length);
        }

    private:
        char data_[header_length + max_body_length];
        std::size_t body_length_;
    };

}


#endif //PROXYSERVER_TCPMESSAGE_H
