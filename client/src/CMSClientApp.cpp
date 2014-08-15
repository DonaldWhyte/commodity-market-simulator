#include "CMSClient.hpp"
#include "Util.hpp"
#include "CMSException.hpp"
#include <iostream>
#include <sstream>

using namespace cms;

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

	// Start interactive session
	CMSClient client(hostname, port);
	std::string input;
	while (true)
	{
		// Get command from user
		std::getline(std::cin, input);

		if (input == "Q" || input == "QUIT"
			|| input == "q" || input == "quit")
		{
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
				std::cout << ex.what() << std::endl;
				std::cout << "TERMINATING APPLICATION" << std::endl;
				break;
			}
		}
	}

	return 0;
}