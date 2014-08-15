#include "CMSClient.hpp"
#include "NetworkException.hpp"

namespace cms
{

	/* Convert string to a vector of bytes. */
	net::ByteBuffer toByteBuffer(const std::string& str)
	{
		net::ByteBuffer buffer(str.length());
		std::copy(str.begin(), str.end(), buffer.begin());
		return buffer;
	}
	/* Convert vector of bytes to a string. */
	std::string fromByteBuffer(const net::ByteBuffer& buffer)
	{
		std::string str;
		str.resize(buffer.size());
		std::copy(buffer.begin(), buffer.end(), str.begin());
		return str;
	}

	CMSClient::CMSClient(const std::string& hostname, int port)
		: hostname(hostname), port(port)
	{
	}

	std::string CMSClient::executeCommand(const std::string& commandStr)
	{
		// Connect to CMS server via TCP socket
		net::Socket socket;
		socket.connect(hostname, port);
		// Send command to server and receive result
		socket.send(toByteBuffer(commandStr));
		std::string result = fromByteBuffer(socket.receive(MAX_BYTES_TO_RECEIVE));
		// Close connection with CMS server
		socket.close();

		return result;
	}

}