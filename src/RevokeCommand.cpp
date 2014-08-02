#include "RevokeCommand.hpp"
#include <sstream>

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
		
		try
		{
			// Find order that should be revoked and
			// check dealer is same as one that posted it
			const Order& order = orderManager->getOrder(orderToRevoke);
			if (order.dealerID() == this->dealerID())
			{
				orderManager->revokeOrder(orderToRevoke);
				std::stringstream stream;
				stream << orderToRevoke << " HAS BEEN REVOKED";
				return stream.str();
			}
			// Dealer who posted order is not the same as the one
			// who wants to revoke it
			else
			{
				return "UNAUTHORIZED";
			}
		}
		catch (const OrderException& ex) // order w/ id could not be found
		{
			return "UNKNOWN_ORDER";	
		}
	}

}