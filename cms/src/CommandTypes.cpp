#include "CommandTypes.hpp"

namespace cms
{

	const CommandType* getCommandType(const std::string& commandName)
	{
		for (unsigned int i = 0; (i < NUM_COMMAND_TYPES); i++)
		{
			if (commandName == COMMAND_TYPES[i].name)
			{
				return &COMMAND_TYPES[i];
			}
		}
		// If this point is reached, no type with given name exists
		return NULL;
	}

}