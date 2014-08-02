#include "CMSClient.hpp"
#include "NetworkException.hpp"

namespace cms
{

	CMSClient::CMSClient(const std::string& hostname, int port)
		: hostname(hostname), port(port)
	{
	}

	bool CMSClient::connect()
	{
		try
		{
			socket.connect(hostname, port);
			return true;
		}
		// Catch exceptions and return false to indicate connection error
		catch (const net::NetworkException& ex)
		{
			return false;
		}
	}

	std::string CMSClient::executeCommand(const std::string& commandStr)
	{
		return "TODO";
	}

}