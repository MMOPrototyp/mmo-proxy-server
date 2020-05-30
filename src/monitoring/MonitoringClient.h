//
// Created by Justin on 30.05.2020.
//

#ifndef PROXYSERVER_MONITORINGCLIENT_H
#define PROXYSERVER_MONITORINGCLIENT_H

namespace mmo {

    class MonitoringClient {

    public:
        void execute();

        double getUptimeInSeconds();
    };

}


#endif //PROXYSERVER_MONITORINGCLIENT_H
