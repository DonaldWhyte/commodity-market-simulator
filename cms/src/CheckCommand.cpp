#include "CheckCommand.hpp"
#include <sstream>

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
		try
		{
			// Find order that should be revoked and
			// check dealer is same as one that posted it
			const Order& order = orderManager->getOrder(orderToCheck);
			if (order.dealerID() == this->dealerID())
			{
				std::stringstream stream;
				if (order.amount() == 0) // if entire order has been filled
				{
					stream << orderToCheck << " HAS BEEN FILLED";
				}
				else
				{
					stream << orderToCheck << " " << order.toString();	
				}

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

	OrderID CheckCommand::orderID() const
	{
		return orderToCheck;
	}

}