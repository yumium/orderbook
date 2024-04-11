#include "../src/OrderBook.h"

#include <gtest/gtest.h>

TEST(TradeTest, TradeGetterTest) {
  TradeInfo bidTrade = TradeInfo(0, 10, 10);
  TradeInfo askTrade = TradeInfo(1, -10, 10);
  Trade trade = Trade(bidTrade, askTrade);
  EXPECT_EQ(trade.GetBidTrade(), askTrade);
  EXPECT_EQ(trade.GetAskTrade(), askTrade);
}

TEST(OrderModifyTest, OrderModifyGetterTest) {
  
}

TEST(OrderModifyTest, OrderModifyOrderPointerTest) {
  // stuff
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  // Runs all tests
  return RUN_ALL_TESTS(); // 0 if all tests successful, 1 otherwise
}