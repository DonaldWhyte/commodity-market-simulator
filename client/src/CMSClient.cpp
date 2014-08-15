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

	CMSClient::~CMSClient()
	{
		socket.close();
	}

	void CMSClient::connect()
	{
		socket.connect(hostname, port);
	}

	void CMSClient::disconnect()
	{
		socket.close();
	}

	std::string CMSClient::executeCommand(const std::string& commandStr)
	{
		// Send command to server and receive result

		// TODO: detect sending info / connection error and throw
		// exception so client is terminated if server has been terminated!!

		socket.send(toByteBuffer(commandStr));
		std::string result = fromByteBuffer(socket.receive(MAX_BYTES_TO_RECEIVE));

		return result;
	}

}