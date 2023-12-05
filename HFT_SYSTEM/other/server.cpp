// threaded_client_server.cpp
#include <iostream>
#include <thread>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include "client.cpp"

void clientThread() {
    // Create a socket
   HFTClient client1;
   client1.start();
}

void serverThread() {
    // Create a socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Error creating socket in server" << std::endl;
        return;
    }

    // Set up the server address structure
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8080);

    // Bind the socket to the address and port
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Error binding socket in server" << std::endl;
        close(serverSocket);
        return;
    }

    // Listen for incoming connections
    if (listen(serverSocket, 10) == -1) {
        std::cerr << "Error listening for connections in server" << std::endl;
        close(serverSocket);
        return;
    }

    std::cout << "Server listening on port 8080..." << std::endl;

    // Accept incoming connections
    sockaddr_in clientAddress;
    socklen_t clientAddressLength = sizeof(clientAddress);
    int clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLength);
    if (clientSocket == -1) {
        std::cerr << "Error accepting connection in server" << std::endl;
        close(serverSocket);
        return;
    }

    std::cout << "Connection accepted from " << inet_ntoa(clientAddress.sin_addr) << std::endl;

    // Receive data from the client
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));

    if (recv(clientSocket, buffer, sizeof(buffer), 0) == -1) {
        std::cerr << "Error receiving data from client in server" << std::endl;
    } else {
        std::cout << "Received from client: " << buffer << std::endl;
    }

    // Close the sockets
    close(clientSocket);
    close(serverSocket);
}

int main() {
    // Start the server thread
    std::thread server(serverThread);

    // Give some time for the server to start before starting the client
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // Start the client thread
    std::thread client(clientThread);

    // Join the threads to wait for them to finish
    client.join();
    server.join();

    return 0;
}
