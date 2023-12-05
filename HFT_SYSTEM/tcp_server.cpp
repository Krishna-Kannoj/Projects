// tcp_server.cpp
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <winsock.h>
#include <sys/socket.h>
#include <netinet/in.h>

class TCPServer {
public:
    TCPServer(int port) : port(port) {
        // Initialization code for the TCP server
    }

    void start() {
        // Create socket
        int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (serverSocket == -1) {
            std::cerr << "Error creating socket" << std::endl;
            return;
        }

        // Configure server address
        sockaddr_in serverAddress{};
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = INADDR_ANY;
        serverAddress.sin_port = htons(port);

        // Bind the socket
        if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
            std::cerr << "Error binding socket" << std::endl;
            close(serverSocket);
            return;
        }

        // Listen for incoming connections
        if (listen(serverSocket, BACKLOG) == -1) {
            std::cerr << "Error listening for connections" << std::endl;
            close(serverSocket);
            return;
        }

        std::cout << "Server listening on port " << port << std::endl;

        // Accept and handle incoming connections for order execution
        while (true) {
            sockaddr_in clientAddress{};
            socklen_t clientAddressSize = sizeof(clientAddress);
            int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressSize);

            if (clientSocket == -1) {
                std::cerr << "Error accepting connection" << std::endl;
                close(serverSocket);
                return;
            }

            // Handle client communication (you will need to implement this part)
            handleClient(clientSocket);

            // Close the client socket
            close(clientSocket);
        }
        // Accept and handle incoming connections for tick data
         while (true) {
            sockaddr_in clientAddress{};
            socklen_t clientAddressSize = sizeof(clientAddress);
            int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressSize);

            if (clientSocket == -1) {
                std::cerr << "Error accepting connection" << std::endl;
                close(serverSocket);
                return;
            }

            // Handle client communication
            std::thread clientThread(&TCPServer::handleClient, this, clientSocket);
            clientThread.detach(); // Detach the thread to run independently

            // Close the client socket (detached thread will handle it)
            // close(clientSocket);
        }

        // Close the server socket
        close(serverSocket);
    }

private:
    static const int BACKLOG = 10;
    int port;

    void handleClient(int clientSocket) {
        char buffer[1024];
        ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);

        if (bytesRead > 0) {
            buffer[bytesRead] = '\0';

            // Parse the order from the received message
            std::string orderMessage(buffer);
            Order order = parseOrder(orderMessage);

            // Process and execute the order
            std::string executionResult = executeOrder(order);

            // Respond to the client with the execution result
            send(clientSocket, executionResult.c_str(), executionResult.size(), 0);
        }

        // For tick data 
        while (true) {
            // Send stock tick data to the client every minute
            std::vector<Tick> tickData = tickLoader.loadTickData();
            for (const auto& tick : tickData) {
                std::string tickMessage = createTickMessage(tick);
                send(clientSocket, tickMessage.c_str(), tickMessage.size(), 0);
                std::this_thread::sleep_for(std::chrono::minutes(1));
            }

            // Process order if any (as before)
            char buffer[1024];
            ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);

            if (bytesRead > 0) {
                buffer[bytesRead] = '\0';
                std::string orderMessage(buffer);
                Order order = parseOrder(orderMessage);
                std::string executionResult = executeOrder(order);
                send(clientSocket, executionResult.c_str(), executionResult.size(), 0);
            }
        }
    }

    Order parseOrder(const std::string& orderMessage) {
        // Implement logic to parse the order message and create an Order object
        // Example: orderMessage format: "BUY AAPL 150.25 100"
        // You need to adapt this based on your order format
        Order order;

        // Parse orderMessage and fill in the order fields
        // Example parsing logic (replace with your own logic):
        std::istringstream iss(orderMessage);
        iss >> order.orderType >> order.stockName >> order.price >> order.quantity;

        return order;
    }

    std::string executeOrder(const Order& order) {
        // Implement logic to execute the order and update the order book
        // Example: Execute the order and respond with a success message
        // You need to adapt this based on your execution logic
        // For simplicity, this example assumes all orders are successful

        orderBook.addOrder(order);

        return "Order executed successfully";
    }

    std::string createTickMessage(const Tick& tick) {
        // Create a message from the tick data to send to the client
        // You can modify this based on your desired message format
        std::ostringstream oss;
        oss << "Tick: " << tick.time << " - Open: " << tick.open << ", Close: " << tick.close
            << ", High: " << tick.high << ", Low: " << tick.low << ", Volume: " << tick.volume << std::endl;
        return oss.str();
    }

};
