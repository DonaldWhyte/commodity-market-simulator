#ifndef CMS_NET_SOCKET_H
#define CMS_NET_SOCKET_H

#include <boost/asio.hpp>

namespace cms
{

	namespace net
	{

		class Socket
		{

		public:
			Socket(); // default constructor -- unconnected socket

			/* Establish connection to TCP server. 
			 * If error in connection, a NetworkException is thrown. */
			void connect(const std::string& hostname, int port);
			/* Return true if socket is connected to server and false otherwise. */
			bool connected() const;

		private:
			bool connectionEstablished;

		};

	}

}

#endif