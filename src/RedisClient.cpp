//
// Created by Justin on 29.05.2020.
//

#define REDISCPP_HEADER_ONLY
#include <redis-cpp/stream.h>
#include <redis-cpp/execute.h>

#define REDISCPP_HEADER_ONLY
#include "RedisClient.h"

void mmo::RedisClient::setPassword(string password) {
    this->password = password;
}

bool mmo::RedisClient::connect() {
    try {
        cout << endl;
        cout << "Redis Server: " << ip << ":" << port << endl;
        cout << endl;

        this->stream = rediscpp::make_stream(const_cast<char *>(ip.c_str()), port);

        if (!password.empty()) {
            //authentificate
            auto loginResponse = rediscpp::execute(*stream, "AUTH", password);
            std::cout << loginResponse.as<std::string>() << std::endl;
        }

        auto response = rediscpp::execute(*stream, "ping");
        std::cout << response.as<std::string>() << std::endl;
    }
    catch (std::exception const &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }

    return true;
}

void mmo::RedisClient::addListEntry(string_view key, string_view value) {
    try {
        auto response = rediscpp::execute(*stream, string_view("LPUSH"), key, value);
        //std::cout << response.as<std::string>() << std::endl;
    }
    catch (std::exception const &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void mmo::RedisClient::removeListEntry(string_view key, string_view value) {
    try {
        auto response = rediscpp::execute(*stream, string_view("LREM"), key, to_string(10), value);
        //std::cout << response.as<std::string>() << std::endl;
    }
    catch (std::exception const &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}