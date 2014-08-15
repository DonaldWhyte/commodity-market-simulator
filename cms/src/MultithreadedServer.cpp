#include "MultithreadedServer.hpp"
#include "CMSException.hpp"
#include <iostream>
#include <boost/asio.hpp>
#include <tr1/memory>

using namespace boost::asio;

namespace cms
{

	MultithreadedServer::MultithreadedServer(int port) : port(port)
	{
	}

	void MultithreadedServer::run(OrderManagerPtr orderManager,
		std::tr1::shared_ptr<CommandParser> commandParser)
	{
		std::cout << "TODO" << std::endl;
	}

}