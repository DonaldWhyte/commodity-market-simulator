/* Don't define main() function to client executable
 * if tests are running. This is to prevent multiple
 * main() functions from being defined, which is
 * disallowed by the compiler. */
#ifndef TESTS_RUNNING

#include "CMSClient.hpp"
#include "Util.hpp"
#include "CMSException.hpp"
#include <iostream>
#include <sstream>

using namespace cms;

static const std::string TERMINATION_MESSAGE = "TERMINATING CLIENT";

int main(int argc, char* argv[])
{
	// Parse command line arguments
	if (argc < 3)
	{
		std::cout << "Usage: " << argv[0] << " <hostname> <port>" << std::endl;
		return 1;
	}
	std::string hostname = argv[1];
	int port = util::toInt(argv[2]);
	if (port < 0 || port > 65535)
	{
		std::cout << "Port number must be in range [0-65535]" << std::endl;
		return 1;
	}

	// Open connection to CMS server
	CMSClient client(hostname, port);
	try
	{
		client.connect();
	}
	catch (const CMSException& ex)
	{
		std::cout << ex.what() << std::endl;
		std::cout << TERMINATION_MESSAGE << std::endl;
		return 1;
	}

	// Start interactive session
	std::string input;
	while (true)
	{
		// Get command from user
		std::getline(std::cin, input);

		// If user wishes to quit the application, make
		// sure the client has disconnected from the CMS server
		if (input == "Q" || input == "QUIT"
			|| input == "q" || input == "quit")
		{
			client.disconnect();
			break;
		}
		else
		{
			try
			{
				// Execute command remotely on server
				std::string output = client.executeCommand(input);
				// Display output, making sure to prefix all lines with "\n"
				std::istringstream outputStream(output);
				std::string line;
				while (!outputStream.eof())
				{
					std::getline(outputStream, line);
					std::cout << "> " << line << std::endl;
				}				
			}
			catch (const std::exception& ex) // communication error
			{
				std::cout << "ERROR: " << ex.what() << std::endl;
				client.disconnect();
				break;
			}
		}
	}

	std::cout << TERMINATION_MESSAGE << std::endl;

	return 0;
}

#endif