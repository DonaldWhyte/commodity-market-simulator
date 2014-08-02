#include "RevokeCommand.hpp"

namespace cms
{

	RevokeCommand::RevokeCommand(const std::string& dealerID, OrderID orderToRevoke)
		: Command("REVOKE", dealerID), orderToRevoke(orderToRevoke)
	{

	}

	RevokeCommand::~RevokeCommand()
	{

	}

	std::string RevokeCommand::execute(OrderManagerPtr orderManager)
	{
		return "TODO";
	}

}