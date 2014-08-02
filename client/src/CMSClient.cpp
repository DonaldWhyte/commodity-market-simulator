#include "CMSClient.hpp"

namespace cms
{

	CMSClient::CMSClient(const std::string& hostname, int port)
		: hostname(hostname), port(port)
	{
	}

	bool CMSClient::connect()
	{
		// TODO
		return false;
	}

	std::string CMSClient::executeCommand(const std::string& commandStr)
	{
		return "TODO";
	}

}