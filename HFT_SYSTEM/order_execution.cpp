// order_execution.cpp

#include "order_book.cpp" // Include the OrderBook definition

struct Order {
    std::string orderType;
    std::string stockName;
    double price;
    int quantity;
    // Add more fields as needed
};

class OrderExecutionEngine {
public:
    OrderExecutionEngine(OrderBook& orderBook) : orderBook(orderBook) {
        // Initialization code for the order execution engine
    }

    std::string processOrder(const Order& order) {
        if (order.orderType == "BUY") {
            return executeBuyOrder(order);
        } else if (order.orderType == "SELL") {
            return executeSellOrder(order);
        } else {
            return "Invalid order type";
        }
    }

private:
    OrderBook& orderBook;

    std::string executeBuyOrder(const Order& buyOrder) {
        // Implement logic to execute a buy order and update the order book
        // Example: Buy order is simply added to the order book in this example
        orderBook.addBuyOrder(buyOrder);

        return "Buy order executed successfully";
    }

    std::string executeSellOrder(const Order& sellOrder) {
        // Implement logic to execute a sell order and update the order book
        // Example: Sell order is simply added to the order book in this example
        orderBook.addSellOrder(sellOrder);

        return "Sell order executed successfully";
    }
};
