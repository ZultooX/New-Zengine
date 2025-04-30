#include <iostream>
#include "Server.h"

int main()
{
	Zengine::Networking::Server server;
	server.Startup();

	while (server.IsRunning())
		server.Update();

	return 0;
}