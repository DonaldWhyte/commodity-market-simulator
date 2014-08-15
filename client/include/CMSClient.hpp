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

		/* Send text command to CMS server.
		 * Returns server output as string or throws a CMSException
		 * if client is not connected to the server or some other
		 * communication error occurs. */
		std::string executeCommand(const std::string& commandStr);

	private:
		// Maximum number of bytes to receive from CMS server in one command.
		static const unsigned int MAX_BYTES_TO_RECEIVE = 1024 * 1024;
		
		std::string hostname;
		int port;

	};

}

#endif