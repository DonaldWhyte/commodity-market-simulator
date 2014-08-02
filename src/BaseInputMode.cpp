#include "BaseInputMode.hpp"
#include "ParseException.hpp"

namespace cms
{

	void BaseInputMode::run(OrderManagerPtr orderManager,
		std::tr1::shared_ptr<CommandParser> commandParser)
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
				try
				{
					// Parse textual command and execute it
					CommandPtr command = commandParser->parse(input);
					std::cout << "> " << command->execute(orderManager) << std::endl;
				}
				catch (const CMSException& ex)
				{
					// Display exception message
					std::cout << "INVALID COMMAND: " << ex.what() << std::endl;
				}
			}
		}
	}

}