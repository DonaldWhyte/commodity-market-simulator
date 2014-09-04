#include "Order.hpp"
#include "Util.hpp"
#include "CMSException.hpp"

namespace cms
{

	Commodity toCommodity(const std::string& str)
	{
		for (unsigned int index = 1; (index < NUM_COMMODITIES); ++index)
		{
			if (str == COMMODITY_STRINGS[index])
			{
				return static_cast<Commodity>(index);
			}
		}
		throw CMSException("UNKNOWN_COMMODITY");
	}

	Side toSide(const std::string& str)
	{
		for (unsigned int index = 1; (index < NUM_SIDES); ++index)
		{
			if (str == SIDE_STRINGS[index])
			{
				return static_cast<Side>(index);
			}
		}
		throw CMSException("UNKNOWN_SIDE");
	}

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
		outputStr += " " + SIDE_STRINGS[orderSide];
		outputStr += " " + COMMODITY_STRINGS[orderCommodity];
		outputStr += " " + util::fromInt(orderAmount);
		outputStr += " " + util::fromDouble(orderPrice);
		return outputStr;
	}

	bool Order::operator==(const Order& otherOrder) const
	{
		return (dealerID() == otherOrder.dealerID()
			&& side() == otherOrder.side()
			&& commodity() == otherOrder.commodity()
			&& amount() == otherOrder.amount()
			&& price() == otherOrder.price()
		);
	}

	bool Order::operator!=(const Order& otherOrder) const
	{
		return (!(*this == otherOrder));
	}

}