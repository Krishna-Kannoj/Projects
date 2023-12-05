// main.cpp
#include "tcp_server.cpp"
#include "tick_loader.cpp"
#include "order_execution.cpp"
#include "order_book.cpp"

int main() {
    // Initialize and run the stock exchange server components
    TCPServer tcpServer;
    TickLoader tickLoader("tick_data.csv");
    OrderBook orderBook;
    OrderExecutionEngine orderExecutionEngine(orderBook);

    // Run the TCP server to handle client connections
    tcpServer.start();

    return 0;
}
