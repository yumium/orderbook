#include "../src/OrderBook.cpp"

#include <gtest/gtest.h>

TEST(TradeTest, TradeGetterTest) {
  TradeInfo bidTrade (0, 10, 10);
  TradeInfo askTrade (1, -10, 10);
  Trade trade = Trade(bidTrade, askTrade);
  EXPECT_EQ(trade.GetBidTrade(), bidTrade);
  EXPECT_EQ(trade.GetAskTrade(), askTrade);
}

TEST(OrderModifyTest, OrderModifyGetterTest) {
  OrderModify orderModify (1, Side::Buy, 10, 10);
  EXPECT_EQ(orderModify.GetOrderId(), 1);
  EXPECT_EQ(orderModify.GetSide(), Side::Buy);
  EXPECT_EQ(orderModify.GetPrice(), 10);
  EXPECT_EQ(orderModify.GetQuantity(), 10);
}

TEST(OrderModifyTest, OrderModifyOrderPointerTest) {
  OrderModify orderModify (1, Side::Buy, 10, 10);
  std::shared_ptr<Order> p = orderModify.ToOrderPointer(OrderType::FillAndKill);
  EXPECT_EQ(p->GetOrderId(), 1);
  EXPECT_EQ(p->GetSide(), Side::Buy);
  EXPECT_EQ(p->GetPrice(), 10);
  EXPECT_EQ(p->GetInitialQuantity(), 10);
  EXPECT_EQ(p->GetOrderType(), OrderType::FillAndKill);
}

TEST(OrderTest, OrderGetterTest) {
  Order order (OrderType::FillAndKill, 1, Side::Buy, 10, 10);
  EXPECT_EQ(order.GetOrderId(), 1);
  EXPECT_EQ(order.GetSide(), Side::Buy);
  EXPECT_EQ(order.GetPrice(), 10);
  EXPECT_EQ(order.GetOrderType(), OrderType::FillAndKill);
  EXPECT_EQ(order.GetInitialQuantity(), 10);
  EXPECT_EQ(order.GetRemainingQuantity(), 10);
  EXPECT_EQ(order.GetFilledQuantity(), 0);
}

TEST(OrderTest, OrderIsFilledTest) {
  Order order (OrderType::FillAndKill, 1, Side::Buy, 10, 10);
  order.Fill(10);
  EXPECT_TRUE(order.isFilled());
}

TEST(OrderTest, OrderNotFilledTest) {
  Order order (OrderType::FillAndKill, 1, Side::Buy, 10, 10);
  order.Fill(5);
  EXPECT_FALSE(order.isFilled());
}

TEST(OrderTest, OrderFillTest) {
  Order order (OrderType::FillAndKill, 1, Side::Buy, 10, 10);
  order.Fill(5);
  EXPECT_EQ(order.GetRemainingQuantity(), 5);
}

TEST(OrderTest, OrderNotFillTest) {
  Order order (OrderType::FillAndKill, 1, Side::Buy, 10, 10);
  EXPECT_THROW(order.Fill(11), std::logic_error);
}

TEST(OrderBookTest, OrderBookAddOrderDuplicateTest) {
  Orderbook orderBook;
  orderBook.AddOrder(std::make_shared<Order>(OrderType::GoodTillCancel, 1, Side::Buy, 100, 10));
  // The order below is dropped as the OrderID already exists
  orderBook.AddOrder(std::make_shared<Order>(OrderType::GoodTillCancel, 1, Side::Sell, 120, 10));
  EXPECT_EQ(orderBook.Size(), 1);
}

TEST(OrderBookTest, OrderBookAddOrderTest) {
  Orderbook orderBook;
  orderBook.AddOrder(std::make_shared<Order>(OrderType::GoodTillCancel, 1, Side::Buy, 100, 10));
  orderBook.AddOrder(std::make_shared<Order>(OrderType::GoodTillCancel, 2, Side::Sell, 120, 10));
  EXPECT_EQ(orderBook.Size(), 2);
}

TEST(OrderBookTest, OrderBookAddOrderFillAndKilTest) {
  Orderbook orderBook;
  orderBook.AddOrder(std::make_shared<Order>(OrderType::GoodTillCancel, 1, Side::Buy, 100, 10));
  orderBook.AddOrder(std::make_shared<Order>(OrderType::GoodTillCancel, 2, Side::Sell, 120, 10));
  orderBook.AddOrder(std::make_shared<Order>(OrderType::FillAndKill, 3, Side::Sell, 99, 12));
  EXPECT_EQ(orderBook.Size(), 1);
}

TEST(OrderBookTest, OrderBookAddOrderGoodTillCancelTest) {
  Orderbook orderBook;
  orderBook.AddOrder(std::make_shared<Order>(OrderType::GoodTillCancel, 1, Side::Buy, 100, 10));
  orderBook.AddOrder(std::make_shared<Order>(OrderType::GoodTillCancel, 2, Side::Sell, 120, 10));
  orderBook.AddOrder(std::make_shared<Order>(OrderType::GoodTillCancel, 3, Side::Sell, 99, 12));
  EXPECT_EQ(orderBook.Size(), 2);
}

TEST(OrderBookTest, OrderBookCancelOrderTest) {
  Orderbook orderBook;
  orderBook.AddOrder(std::make_shared<Order>(OrderType::GoodTillCancel, 1, Side::Buy, 100, 10));
  orderBook.CancelOrder(1);
  EXPECT_EQ(orderBook.Size(), 0);
}

TEST(OrderBookTest, OrderBookCancelOrderFailTest) {
  Orderbook orderBook;
  orderBook.AddOrder(std::make_shared<Order>(OrderType::GoodTillCancel, 1, Side::Buy, 100, 10));
  orderBook.CancelOrder(2);
  EXPECT_EQ(orderBook.Size(), 1);
}

TEST(OrderBookTest, OrderBookModifyOrderTest) {
  Orderbook orderBook;
  orderBook.AddOrder(std::make_shared<Order>(OrderType::GoodTillCancel, 1, Side::Buy, 100, 10));
  orderBook.AddOrder(std::make_shared<Order>(OrderType::GoodTillCancel, 2, Side::Sell, 120, 10));
  orderBook.AddOrder(std::make_shared<Order>(OrderType::GoodTillCancel, 3, Side::Sell, 110, 12));
  orderBook.ModifyOrder(OrderModify (3, Side::Sell, 99, 12));
  EXPECT_EQ(orderBook.Size(), 2);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  // Runs all tests
  return RUN_ALL_TESTS(); // 0 if all tests successful, 1 otherwise
}