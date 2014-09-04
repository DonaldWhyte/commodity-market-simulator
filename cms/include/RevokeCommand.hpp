#ifndef CMS_REVOKECOMMAND_HPP
#define CMS_REVOKECOMMAND_HPP

#include "Command.hpp"

namespace cms
{

	class RevokeCommand : public Command
	{

	public:
		RevokeCommand(const std::string& dealerID, OrderID orderToRevoke);
		virtual ~RevokeCommand();

		virtual std::string execute(OrderManagerPtr orderManager);

		OrderID orderID() const;

	private:
		OrderID orderToRevoke;

	};

}

#endif