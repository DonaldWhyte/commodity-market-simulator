#include "TCPInputMode.hpp"
#include <iostream>

namespace cms
{

	TCPInputMode::TCPInputMode(int port) : port(port)
	{
	}

	void TCPInputMode::run(OrderManagerPtr orderManager,
		std::tr1::shared_ptr<CommandParser> commandParser)
	{
		// TODO
		std::cout << "TODO" << std::endl;
	}

}