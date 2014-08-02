#ifndef CMS_CMSCLIENT_H
#define CMS_CMSCLIENT_H

#include <string>
#include <boost/asio.hpp>
#include "Socket.hpp"

namespace cms
{

	class CMSClient
	{

	public:
		CMSClient(const std::string& hostname, int port);

		/* Connect client to server. Returns true if connection
		 * was successful and false otherwise. */
		bool connect();

		/* Send text command to CMS server.
		 * Returns server output as string or throws a CMSException
		 * if client is not connected to the server or some other
		 * communication error occurs. */
		std::string executeCommand(const std::string& commandStr);

	private:
		net::Socket socket;
		std::string hostname;
		int port;

	};

}

#endif