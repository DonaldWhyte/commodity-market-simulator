#ifndef CMS_COMMAND_H
#define CMS_COMMAND_H

#include <tr1/memory>
#include <string>
#include "OrderManager.hpp"

namespace cms
{

	class Command
	{

	public:
		Command(const std::string& cmdType, const std::string& cmdDealerID);

		const std::string& type() const;
		const std::string& dealerID() const;

		virtual std::string execute(OrderManagerPtr orderManager) = 0;

	private:
		std::string cmdType;
		std::string cmdDealerID;

	};

	typedef std::tr1::shared_ptr<Command> CommandPtr;

}

#endif