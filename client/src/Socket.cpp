#include "Socket.hpp"
#include "NetworkException.hpp"
#include "Util.hpp"
#include <vector>
#include <algorithm>

#include <iostream>

using boost::asio::ip::tcp;

namespace cms
{

	namespace net
	{

		Socket::Socket() : connectionEstablished(false)
		{
		}

		void Socket::connect(const std::string& hostname, int port)
		{
			// NOTE: For some reason boost::asio requires port numbers
			// to be strings, so we need to convert the integer port
			// number given to a string.

			// Resolve hostname to IP address(es), which are stored
			// in the tcp::resolver::iterator object
			tcp::resolver nameResolver(ioService);
			tcp::resolver::query query(tcp::v4(), hostname, util::fromInt(port));
			tcp::resolver::iterator endpointIterator = nameResolver.resolve(query);
			tcp::resolver::iterator iteratorEnd;

			tcpSocket = std::tr1::shared_ptr<TCPSocket>(new TCPSocket(ioService));
			// Try and connect to one of the resolved endpoints
			// If a connection with neither could be established, throw exception
			boost::system::error_code error = boost::asio::error::host_not_found;			
			while (error && endpointIterator != iteratorEnd)
			{
				tcpSocket->connect(*endpointIterator, error);
				endpointIterator++;
			}

			if (error)
			{
				std::string errorMessage = "Could not connect to endpoint "
					+ hostname + " on port " + util::fromInt(port);
				throw NetworkException(errorMessage);
			}
			else
			{
				connectionEstablished = true;	
			}
		}

		bool Socket::connected() const
		{
			return connectionEstablished;
		}

		void Socket::send(const ByteBuffer& data)
		{
			if (!connected())
			{
				throw NetworkException("Cannot send data -- socket not connected");
			}
			
			boost::asio::write(*tcpSocket,
				boost::asio::buffer(&data[0], data.size()));
		}

		ByteBuffer Socket::receive(size_t maxBytes)
		{
			if (!connected())
			{
				throw NetworkException("Cannot receive data -- socket not connected");
			}

			ByteBuffer receivedData(maxBytes);
			boost::system::error_code error;
			size_t length = tcpSocket->read_some(
				boost::asio::buffer(receivedData), error);
			return receivedData;
		}

		void Socket::close()
		{
			tcpSocket->close();
		}

	}

}