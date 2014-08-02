#include "Socket.hpp"
#include "NetworkException.hpp"

namespace cms
{

	namespace net
	{

		Socket::Socket() : connectionEstablished(false)
		{
		}

		void Socket::connect(const std::string& hostname, int port)
		{
			// TODO
			throw NetworkException("Socket::connect() not implemented");
		}

		bool Socket::connected() const
		{
			return connectionEstablished;
		}

	}

}