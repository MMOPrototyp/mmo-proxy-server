//
// Created by Justin on 30.05.2020.
//

#include "MonitoringClient.h"

#include <string>
#include <cstdlib>
#include <iostream>

//#include <stdio.h>
#include <stdlib.h>
#include <cstring>

#include <chrono>
#include <fstream>

#include <nlohmann/json.hpp>

#ifdef _WIN32
#include <windows.h>
#include <stdio.h>
#include <tchar.h>

#define DIV 1048576
#define WIDTH 7
#endif

#ifdef linux
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <fstream>
#include <sys/sysinfo.h>
#endif

using namespace std;

// for convenience
//using json = nlohmann::json;

void mmo::MonitoringClient::init(ServerConfig *serverConfig, RedisClient *redisClient) {
    this->serverConfig = serverConfig;
    this->redisClient = redisClient;
}

void mmo::MonitoringClient::execute() {
    cout << "execute monitoring" << endl;

    nlohmann::json json;
    json["type"] = "proxy-server";
    json["server.id"] = serverID;
    json["server.title"] = serverTitle;

#ifdef BOOST_OS_WINDOWS
    cout << "Windows is not supported in monitoring yet" << endl;
    return;
#endif

#ifdef __unix__
    cout << "Linux" << endl;
#elif defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)

#define OS_Windows

    cout << "Windows is not supported in monitoring yet" << endl;
    return;
#endif
    //TODO: get uptime
    cout << to_string(getUptimeInSeconds()) << endl;

    //TODO: get temperature

    //TODO: get free memory

    //see also: https://stackoverflow.com/questions/8666378/detect-windows-or-linux-in-c-c
    char cmd[30];
    int flag = 0;
    FILE *fp;
    char line[130];
    int TotalMem, TotalFree, TotalUsed;

    flag = 0;
    memcpy(cmd, "\0", 30);
    sprintf(cmd, "free -t -m|grep Total");
    fp = popen(cmd, "r");
    while (fgets(line, sizeof line, fp)) {
        flag++;
        sscanf(line, "%*s %d %d %d", &TotalMem, &TotalUsed, &TotalFree);
    }
    pclose(fp);

    if (flag)
        printf("TotalMem:%d -- TotalUsed:%d -- TotalFree:%d\n", TotalMem, TotalUsed, TotalFree);
    else
        printf("not found\n");

    //https://linuxwiki.de/proc/uptime

    //cat /proc/loadavg

    //TODO: add code here

    //TODO: publish json object to redis and store it to redis map
}

double mmo::MonitoringClient::getUptimeInSeconds() {
    //see also: https://stackoverflow.com/questions/30095439/how-do-i-get-system-up-time-in-milliseconds-in-c

#ifdef BOOST_OS_WINDOWS
    cout << "Windows is not supported in monitoring yet" << endl;
    return;
#endif

#ifdef __unix__
    //cout << "Linux" << endl;
#elif defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64)

#define OS_Windows

    cout << "Windows is not supported in monitoring yet" << endl;
    return;
#endif

    std::chrono::milliseconds uptime(0u);
    double uptime_seconds;
    if (ifstream("/proc/uptime", std::ios::in) >> uptime_seconds) {
        uptime = std::chrono::milliseconds(
                static_cast<unsigned long long>(uptime_seconds * 1000.0)
        );

        return uptime_seconds;
    }

    return -1;
}