#include "PostCommand.hpp"
#include "Util.hpp"

namespace cms
{

	PostCommand::PostCommand(const std::string& dealerID, const Order& order) :
		Command("POST", dealerID), orderToPost(order)
	{
	}

	std::string PostCommand::execute(OrderManagerPtr orderManager)
	{
		int orderID = orderManager->postOrder(order());
		return util::fromInt(orderID) + " " + order().toString() + " HAS BEEN POSTED";
	}

	const Order& PostCommand::order() const
	{
		return orderToPost;
	}

}