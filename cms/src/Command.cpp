#include "Command.hpp"

namespace cms
{

	Command::Command(const std::string& cmdType, const std::string& cmdDealerID)
		: cmdType(cmdType), cmdDealerID(cmdDealerID)
	{
	}

	std::string Command::run(OrderManagerLockPtr orderManagerLock)
	{
		try
		{
			OrderManagerPtr orderManager = *(orderManagerLock->acquire());
			std::string output = execute(orderManager);
			orderManagerLock->release();
			return output;
		}
		catch (const CMSException& ex)
		{
			orderManagerLock->release();
			throw ex;
		}
		catch (const std::exception& ex)
		{
			orderManagerLock->release();
			throw ex;
		}
	}

	const std::string& Command::type() const
	{
		return cmdType;
	}

	const std::string& Command::dealerID() const
	{
		return cmdDealerID;
	}

}