#include "PostCommand.hpp"

namespace cms
{

	PostCommand::PostCommand(const std::string& dealerID, const Order& order) :
		Command("POST", dealerID), orderToPost(order)
	{
	}

	std::string PostCommand::execute(OrderManagerPtr orderManager)
	{
		return "TODO";
	}

	const Order& PostCommand::order() const
	{
		return orderToPost;
	}

}