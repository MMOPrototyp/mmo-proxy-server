//
// Created by Justin on 29.05.2020.
//

#include <config4cpp/Configuration.h>
#include <iostream>

#include "ServerConfig.h"

using namespace config4cpp;
using namespace std;

bool mmo::ServerConfig::parse(string configFile) {
    //see also: http://www.config4star.org/config4star-getting-started-guide/overview-of-config4star-syntax.html
    try {
        cfg->parse(configFile.c_str());

        //parse redis config
        const char *scope = "Redis";
        redisConfig.ip = cfg->lookupString(scope, "ip");
        redisConfig.port = cfg->lookupInt(scope, "port");
        redisConfig.password = cfg->lookupString(scope, "password");

        //parse server config
        string proxyServerScope = "ProxyServer";
        proxyConfig.ip = cfg->lookupString(proxyServerScope.c_str(), "ip");
        proxyConfig.port = cfg->lookupInt(proxyServerScope.c_str(), "port");
        proxyConfig.udpPort = cfg->lookupInt(proxyServerScope.c_str(), "udpPort");
        proxyConfig.publicServer = cfg->lookupBoolean(proxyServerScope.c_str(), "public");
        proxyConfig.maxNumberOfClients = cfg->lookupInt(proxyServerScope.c_str(), "maxNumberOfClients");

        //parse monitoring config
        string monitoringClientScope = "MonitoringClient";
        monitoringConfig.use_static_id = cfg->lookupBoolean(monitoringClientScope.c_str(), "use_static_id");
        monitoringConfig.static_id = cfg->lookupInt(monitoringClientScope.c_str(), "static_id");
        monitoringConfig.title = cfg->lookupString(monitoringClientScope.c_str(), "title");
    } catch (const ConfigurationException &ex) {
        cerr << ex.c_str() << endl;
        cfg->destroy();
        return false;
    }

    cfg->destroy();
    return true;
}
