# High-Frequency Trading (HFT) System

This project implements a simple High-Frequency Trading (HFT) system with a client-server architecture. The system facilitates stock tick data retrieval, order execution, and basic order book management.

## Table of Contents

- [Overview](#overview)
- [Components](#components)
- [Prerequisites](#prerequisites)
- [Usage](#usage)
- [Configuration](#configuration)
- [License](#license)

## Overview

The HFT system consists of two main components: the client (HFT firm) and the server (stock exchange). The client connects to the server through the TCP/IP protocol, requests stock tick data every minute, stores the data in a CSV file, and sends orders to the server for execution. The server handles order execution, maintains an order book, and provides stock tick data to the clients.

## Components

1. **Client (hft_client.cpp)**
   - Connected through TCP/IP protocol with the server.
   - Requests stock tick data every minute and stores it in a CSV file.
   - Sends orders to the server and receives execution results.

2. **Server (stock_exchange_server.cpp)**
   - Connects with clients through the TCP/IP protocol.
   - Provides stock tick data to clients.
   - Accepts order requests from clients, executes them, and responds with results.
   - Maintains an order book.

3. **Additional Modules**
   - **Tick Loader (tick_loader.cpp):** Loads tick data from a CSV file.
   - **Order Execution (order_execution.cpp):** Handles order execution logic.
   - **Order Book (order_book.cpp):** Manages the order book.

## Prerequisites

- C++ compiler (supporting C++11)
- Linux environment (for Makefile)
- Internet connection (for TCP/IP communication)

## Usage

1. **Clone the Repository:**

    ```bash
    git clone https://github.com/your_username/hft-trading-system.git
    ```

2. **Navigate to the Project Directory:**

    ```bash
    cd hft-trading-system
    ```

3. **Build the Client and Server:**

    ```bash
    make
    ```

4. **Run the Server:**

    ```bash
    ./stock_exchange_server
    ```

5. **Run the Client:**

    ```bash
    ./hft_client
    ```

## Configuration

- **Client Configuration:**
    - Modify the `serverAddress` and `serverPort` variables in `hft_client.cpp` to match the address and port of your stock exchange server.

- **Server Configuration:**
    - Modify the server settings (e.g., port number) directly in `stock_exchange_server.cpp`.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
