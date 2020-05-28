// mmo-proxy-server.cpp: Definiert den Einstiegspunkt für die Anwendung.
//

#include "mmo-proxy-server.h"
#include "ProxyConfig.h"
#include <string>
//#include "3rdparty/cpp_redis/includes/cpp_redis/core/client.hpp"

//#include<cpp_redis/cpp_redis.h>

using namespace std;

int main()
{
	cout << "################################" << endl;
	cout << "# MMO Prototyp Proxy Server    #" << endl;
	cout << "#                              #" << endl;
	cout << "# Version: " << std::to_string(PROXY_VERSION_MAJOR) << "." << std::to_string(PROXY_VERSION_MINOR) << "." << std::to_string(PROXY_VERSION_PATCH) << "               #" << endl;
	cout << "################################" << endl;

	//scpp_redis::client client;

	return 0;
}
