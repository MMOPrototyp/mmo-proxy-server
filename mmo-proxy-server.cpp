// mmo-proxy-server.cpp: Definiert den Einstiegspunkt für die Anwendung.
//

#include "mmo-proxy-server.h"
#include "ProxyConfig.h"
#include <string>
//#include "3rdparty/cpp_redis/includes/cpp_redis/core/client.hpp"

//#include<cpp_redis/cpp_redis>

#include <cstdlib>
#include <iostream>

#include <redis-cpp/stream.h>
#include <redis-cpp/execute.h>

//#include "3rdparty/inih/cpp/INIReader.h"

#include <config4cpp/Configuration.h>
#include <iostream>
using namespace config4cpp;
using namespace std;

int main()
{
	cout << "################################" << endl;
	cout << "# MMO Prototyp Proxy Server    #" << endl;
	cout << "#                              #" << endl;
	cout << "# Version: " << std::to_string(PROXY_VERSION_MAJOR) << "." << std::to_string(PROXY_VERSION_MINOR) << "." << std::to_string(PROXY_VERSION_PATCH) << "               #" << endl;
	cout << "################################" << endl;

	//https://stackoverflow.com/questions/6892754/creating-a-simple-configuration-file-and-parser-in-c

	//https://stackoverflow.com/questions/6892754/creating-a-simple-configuration-file-and-parser-in-c/6900247

    Configuration *  cfg = Configuration::create();

	//cpp_redis::client client;

	return 0;
}
