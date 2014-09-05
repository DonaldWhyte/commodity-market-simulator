#ifndef CMS_ORDER_H
#define CMS_ORDER_H

#include <string>

namespace cms
{

	/*
	 * Enumerator: Commodity
	 * Description: Enumerator that defines all commodities traded in CMS. 
	*/
	enum Commodity
	{
		COMMODITY_UNKNOWN = 0,
		COMMODITY_GOLD,
		COMMODITY_SILVER,
		COMMODITY_PORK,
		COMMODITY_OIL,
		COMMODITY_RICE,

		// Used to iterate through enumerator, should always be last
		NUM_COMMODITIES
	};
	static const std::string COMMODITY_STRINGS[] = {
		"UNKNOWN", "GOLD", "SILV", "PORK", "OIL", "RICE"
	};	

	/*
	 * Enumerator: Side
	 * Description: Enumerator that defines the two valid trading sides.
	*/
	enum Side
	{
		SIDE_UNKNOWN = 0,
		SIDE_BUY,
		SIDE_SELL,

		NUM_SIDES
	};
	static const std::string SIDE_STRINGS[] = {
		"UNKNOWN", "BUY", "SELL" 
	};

	/* These convert strings to the Commodity and Side types respective.
	 * NOTE: These string conversion functions throw CMSException
	 * if the strings do not represent valid commodities/sides/numbers. */
	Commodity toCommodity(const std::string& str);
	Side toSide(const std::string& str);

	/*
	 * Class: Order
	 * Description: Represents an order posted on the CMS. It contains
	 * which dealer posted the order, the commodity and side of the order
	 * as well as the amount of contracts and the price they are being
	 * bought/sold for.
	*/
	class Order
	{

	public:
		Order(const std::string& dealerID, Side orderSide,
			Commodity orderCommodity, int orderAmount, double orderPrice);

		const std::string& dealerID() const;
		Side side() const;
		Commodity commodity() const;
		int amount() const;
		double price() const;

		bool reduceAmount(int amountToReduce);

		/* Return textual representation of order, in the
		 * format described in the CMS' formal specification. */
		std::string toString() const;

		/* Equality operators for comparing orders. */
		bool operator==(const Order& otherOrder) const;
		bool operator!=(const Order& otherOrder) const;

	private:
		std::string orderDealerID;
		Side orderSide;
		Commodity orderCommodity;
		int orderAmount;
		double orderPrice;

	};

}

#endif