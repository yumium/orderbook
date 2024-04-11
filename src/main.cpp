#include "OrderBook.cpp"
#include <iostream>
#include <vector>
// #include <exception>
#include <functional>


// std::format
// std::list
// std::shared_ptr
// std::greater

class Base {
        int width;
    public:
        int height;
    private:
        int depth;
    public:
        Base (int w, int h, int d)
            : width(w)
            , height(h)
            , depth(d)
        { };

        int volume() { return width*height*depth; };
};


int main ()
{
    std::vector<int> numbers = {1, 2, 3};
    std::cout << numbers.size() << std::endl;
    numbers.resize(numbers.size() + 1);
    std::cout << numbers.back() << std::endl;
    std::cout << std::greater<int>()(numbers.at(2), numbers.at(0)) << std::endl;

    Base cube (2,3,4);
    std::cout << cube.volume() << std::endl;

    // Orderbook orderbook;
    // const OrderId orderId = 1;
    // orderbook.AddOrder(std::make_shared<Order>(OrderType::GoodTillCancel, orderId, Side::Buy, 100, 10));
    // std::cout << orderbook.Size() << std::endl;
    // orderbook.CancelOrder(orderId);
    // std::cout << orderbook.Size() << std::endl;
    return 0;
}
