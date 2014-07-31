#include "Command.hpp"

namespace cms
{

	Command::Command(const std::string& cmdType, const std::string& cmdDealerID)
		: cmdType(cmdType), cmdDealerID(cmdDealerID)
	{
	}

	const std::string& Command::type() const
	{
		return cmdType;
	}

	const std::string& Command::dealerID() const
	{
		return cmdDealerID;
	}

}