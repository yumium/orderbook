#pragma once

#include <map>
#include <unordered_map>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <numeric>

#include "Usings.h"
#include "Order.h"
#include "OrderModify.h"
#include "OrderbookLevelInfos.h"
#include "Trade.h"

class Orderbook
{
private:

    struct OrderEntry
    {
        OrderPointer order_ { nullptr };
        OrderPointers::iterator location_;
    };

    std::map<Price, OrderPointers, std::greater<Price>> bids_;
    std::map<Price, OrderPointers, std::less<Price>> asks_;
    std::map<OrderId, OrderEntry> orders_;

    bool CanMatch(Side side, Price price) const;
    Trades MatchOrders();

public:
    /* Adds order `order` and performs any matching possible */
    Trades AddOrder(OrderPointer order);

    /* Cancels order with `orderId`. No op if `orderId` does not exist in the order book */
    void CancelOrder(OrderId orderId);

    /* Modifies order `order` and performs any matching possible. No op if the order ID does not exist in the order book */
    Trades ModifyOrder(OrderModify order);

    /* Returns number of orders in the order book */    
    std::size_t Size() const;
    OrderbookLevelInfos GetOrderInfos() const;
};