#ifndef CMS_CMSCLIENT_H
#define CMS_CMSCLIENT_H

#include <string>
#include <boost/asio.hpp>
#include "Socket.hpp"

namespace cms
{

	/*
	 * CLASS: CMSClient
	 * DESCRIPTION:
	 * High-level client interface to CMS server. The user executes 
	 * commands on the remote CMS server by passing command strings
	 * to the executeCommand() method. The result of the command is
	 * received from the server, which is the return value of
	 * executeCommand().
	 */
	class CMSClient
	{

	public:
		CMSClient(const std::string& hostname, int port);
		virtual ~CMSClient();

		/* Connect to CMS server using stored hostname and port. */
		void connect();
		/* Terminate connection with CMS server.
		 * Does nothing if no connection was established. */
		void disconnect();

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
		net::Socket socket;

	};

}

#endif