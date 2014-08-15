#include "CMSClient.hpp"
#include "NetworkException.hpp"

namespace cms
{

	CMSClient::CMSClient(const std::string& hostname, int port)
		: hostname(hostname), port(port)
	{
	}

	void CMSClient::connect()
	{
		socket.connect(hostname, port);
	}

	std::string CMSClient::executeCommand(const std::string& commandStr)
	{
		socket.send(commandStr);
		return socket.receive();
	}

}