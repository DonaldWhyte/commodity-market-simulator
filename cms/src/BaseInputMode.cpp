#include "BaseInputMode.hpp"
#include "ParseException.hpp"
#include <sstream>

namespace cms
{

	void BaseInputMode::run(OrderManagerLockPtr orderManager,
		boost::shared_ptr<CommandParser> commandParser)
	{
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
				std::string output = "";
				try
				{
					// Parse textual command and execute it
					CommandPtr command = commandParser->parse(input);
					output = command->run(orderManager);
				}
				catch (const CMSException& ex)
				{
					// Retrieve error message if exception is thrown
					output = ex.what();
				}
				// Display output, making sure to prefix all lines with "\n"
				std::istringstream outputStream(output);
				std::string line;
				while (!outputStream.eof())
				{
					std::getline(outputStream, line);
					std::cout << "> " << line << std::endl;
				}
			}
		}
	}

}