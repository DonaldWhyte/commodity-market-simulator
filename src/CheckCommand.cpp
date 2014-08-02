#include "CheckCommand.hpp"

namespace cms
{

	CheckCommand::CheckCommand(const std::string& dealerID, OrderID orderToCheck)
		: Command("CHECK", dealerID), orderToCheck(orderToCheck)
	{

	}
	
	CheckCommand::~CheckCommand()
	{

	}

	std::string CheckCommand::execute(OrderManagerPtr orderManager)
	{
		return "TODO";
	}

}