#include "Socket.hpp"
#include "NetworkException.hpp"
#include "Util.hpp"
#include <vector>
#include <algorithm>

#include <iostream>

using namespace boost::asio;

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
			// in the ip::tcp::resolver::iterator object
			ip::tcp::resolver nameResolver(ioService);
			ip::tcp::resolver::query query(ip::tcp::v4(), hostname, util::fromInt(port));
			ip::tcp::resolver::iterator endpointIterator = nameResolver.resolve(query);
			ip::tcp::resolver::iterator iteratorEnd;

			tcpSocket = boost::shared_ptr<TCPSocket>(new TCPSocket(ioService));
			// Try and connect to one of the resolved endpoints
			// If a connection with neither could be established, throw exception
			boost::system::error_code error = error::host_not_found;			
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
		
			write(*tcpSocket, buffer(&data[0], data.size()));
		}

		ByteBuffer Socket::receive(size_t maxBytes)
		{
			if (!connected())
			{
				throw NetworkException("Cannot receive data -- socket not connected");
			}

			ByteBuffer receivedData(maxBytes);
			boost::system::error_code error;
			tcpSocket->read_some(buffer(receivedData), error);

			if (error == error::eof) // connection cleanly closed
			{
				throw NetworkException("Connection with CMS server closed");
			}
			else if (error)
			{
				std::stringstream errorMessage;
				errorMessage << "Error receiving data (error code: " << error << ")";
				throw NetworkException(errorMessage.str());
			}
			else
			{
				return receivedData;
			}
		}

		void Socket::close()
		{
			if (connected())
			{
				tcpSocket->close();
			}
		}

	}

}