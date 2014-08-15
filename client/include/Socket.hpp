#ifndef CMS_NET_SOCKET_H
#define CMS_NET_SOCKET_H

#include <boost/asio.hpp>
#include <tr1/memory>
#include <vector>

namespace cms
{

	namespace net
	{

		/* We deal with buffers of bytes when sending/receiving
		 * data through boost::asio sockets. std::vector<char>
		 * is used instead of char[] for RAII benefits. */
		typedef std::vector<char> ByteBuffer;

		class Socket
		{

		public:
			Socket(); // default constructor -- unconnected socket

			/* Establish connection to TCP server. 
			 * If error in connection, a NetworkException is thrown. */
			void connect(const std::string& hostname, int port);
			/* Return true if socket is connected to server and false otherwise. */
			bool connected() const;

			/* Send string to connected host. */
			void send(const ByteBuffer& data);
			/* Block until data is received from the connected host. */
			ByteBuffer receive(size_t maxBytes);

			/* Close connection with host. */
			void close();

		private:
			bool connectionEstablished;

			boost::asio::io_service ioService;
			// Typedef'd simply for more concise code
			typedef boost::asio::ip::tcp::socket TCPSocket;
			std::tr1::shared_ptr<TCPSocket> tcpSocket;


		};

	}

}

#endif