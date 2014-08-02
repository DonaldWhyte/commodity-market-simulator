#ifndef CMS_LISTCOMMAND_HPP
#define CMS_LISTCOMMAND_HPP

#include "Command.hpp"
#include "Order.hpp"
#include <vector>

namespace cms
{

	class ListCommand : public Command
	{

	public:
		ListCommand(const std::string& dealerID,
			const std::string& commodityFilter = "",
			const std::string& dealerFilter = "");
		virtual ~ListCommand();

		virtual std::string execute(OrderManagerPtr orderManager);

	private:
		void filterByCommodity(OrderCollection& orders, Commodity commodity);
		void filterByDealer(OrderCollection& orders, const std::string& dealerID);

		// filters
		Commodity commodityToList;
		std::string dealerToList;

	};

}

#endif