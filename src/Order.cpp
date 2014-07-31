#include "Order.hpp"
#include "Util.hpp"

namespace cms
{

	Order::Order(const std::string& dealerID, Side side,
		Commodity commodity, int amount, double price) :
		orderDealerID(dealerID), orderSide(side), orderCommodity(commodity),
		orderAmount(amount), orderPrice(price)
	{
	}

	const std::string& Order::dealerID() const
	{
		return orderDealerID;
	}

	Side Order::side() const
	{
		return orderSide;
	}

	Commodity Order::commodity() const
	{
		return orderCommodity;
	}

	int Order::amount() const
	{
		return orderAmount;
	}

	double Order::price() const
	{
		return orderPrice;
	}

	bool Order::reduceAmount(int amountToReduce)
	{
		if (orderAmount >= amountToReduce)
		{
			orderAmount -= amountToReduce;
			return true;
		}
		else
		{
			return false;
		}
	}

	std::string Order::toString() const
	{
		std::string outputStr = orderDealerID;
		outputStr += " " + COMMODITY_STRINGS[orderCommodity];
		outputStr += " " + SIDE_STRINGS[orderSide];
		outputStr += " " + util::fromInt(orderAmount);
		outputStr += " " + util::fromDouble(orderPrice);
		return outputStr;
	}

}