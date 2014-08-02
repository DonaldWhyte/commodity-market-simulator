#ifndef CMS_LISTCOMMAND_HPP
#define CMS_LISTCOMMAND_HPP

#include "Command.hpp"
#include "Order.hpp"

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
		// filters
		Commodity commodityToList;
		std::string dealerToList;

	};

}

#endif