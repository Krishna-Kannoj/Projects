// order_book.cpp

#include <iostream>
#include <vector>

struct Order {
    std::string orderType;
    std::string stockName;
    double price;
    int quantity;
    // Add more fields as needed
};

class OrderBook {
public:
    void addBuyOrder(const Order& buyOrder) {
        // Add a buy order to the buy orders vector
        buyOrders.push_back(buyOrder);

        // Optionally, implement logic to match buy and sell orders
        matchOrders();
    }

    void addSellOrder(const Order& sellOrder) {
        // Add a sell order to the sell orders vector
        sellOrders.push_back(sellOrder);

        // Optionally, implement logic to match buy and sell orders
        matchOrders();
    }

    // Add other methods as needed

private:
    std::vector<Order> buyOrders;
    std::vector<Order> sellOrders;

    void matchOrders() {
        // Implement logic to match buy and sell orders
        // For simplicity, this example matches orders based on price and time priority
        while (!buyOrders.empty() && !sellOrders.empty()) {
            Order buyOrder = buyOrders.front();
            Order sellOrder = sellOrders.front();

            if (buyOrder.price >= sellOrder.price) {
                // Execute the matched orders (update quantities, handle transactions, etc.)
                executeMatchedOrders(buyOrder, sellOrder);

                // Remove matched orders from the order book
                buyOrders.erase(buyOrders.begin());
                sellOrders.erase(sellOrders.begin());
            } else {
                // No further matching is possible
                break;
            }
        }
    }

    void executeMatchedOrders(const Order& buyOrder, const Order& sellOrder) {
        // Implement logic to execute matched orders
        // For simplicity, this example prints a message to the console
        std::cout << "Matched order: Buy " << buyOrder.quantity << " of " << buyOrder.stockName
                  << " at $" << buyOrder.price << " with Sell " << sellOrder.quantity << " at $" << sellOrder.price
                  << std::endl;
    }
};
