// mmo-proxy-server.cpp: Definiert den Einstiegspunkt für die Anwendung.
//

#include "mmo-proxy-server.h"
#include "ProxyConfig.h"
#include <string>

using namespace std;

int main()
{
	cout << "################################" << endl;
	cout << "# MMO Prototyp Proxy Server    #" << endl;
	cout << "#                              #" << endl;
	cout << "# Version: " << std::to_string(PROXY_VERSION_MAJOR) << "." << std::to_string(PROXY_VERSION_MINOR) << "." << std::to_string(PROXY_VERSION_PATCH) << "               #" << endl;
	cout << "################################" << endl;

	return 0;
}
