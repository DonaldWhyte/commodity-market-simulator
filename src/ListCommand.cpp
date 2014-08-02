#include "ListCommand.hpp"

namespace cms
{

	ListCommand::ListCommand(const std::string& dealerID,
		const std::string& commodityFilter, const std::string& dealerFilter)
		: Command("LIST", dealerID), dealerToList(dealerFilter)
	{
		// If a commodity to filter by has been given
		if (!commodityFilter.empty())
		{
			commodityToList = toCommodity(commodityFilter);
		}
	}

	ListCommand::~ListCommand()
	{
	}

	std::string ListCommand::execute(OrderManagerPtr orderManager)
	{
		// TODO
		return dealerID() + " - " + COMMODITY_STRINGS[commodityToList] + " - " + dealerToList;
	}

}