// server.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
/*

Author: Izuka Ikedionwu

Description: Network server code for windows machines


Created: 4/13/24


Features:


*/
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>



class server {
public:
    int server_startup()
    {
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            std::cerr << "WSAStartup failed\n";
            return 1;
        }
    }

    int create_socket() {
        this->serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (serverSocket == INVALID_SOCKET) {
            std::cerr << "Error creating socket\n";
            WSACleanup();
            return 1;
        }
    }

    int bind_socket(const char* ip_addr, int port)
    {
        // Bind socket
        sockaddr_in serverAddr;
        //Change this IP depending on machine
        const char* ip = ip_addr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = INADDR_ANY;  // Accept connections on any local IP address
        //change this if not working
        serverAddr.sin_port = htons(port); // Server port
        if (bind(this->serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
            std::cerr << "Bind failed\n";
            closesocket(serverSocket);
            WSACleanup();
            return 1;
        }

    }
    int listen_and_accept_client()
    {
        // Listen for incoming connections
        if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
            std::cerr << "Listen failed\n";
            closesocket(serverSocket);
            WSACleanup();
            return 1;
        }

        std::cout << "Server is listening for incoming connections...\n";

        // Accept incoming connection
        this->clientSocket = accept(serverSocket, NULL, NULL);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Accept failed\n";
            closesocket(serverSocket);
            WSACleanup();
            return 1;
        }

        std::cout << "Client connected\n";

        return 0;
    }

    int recieve()
    {
        // Receive data from client

        int bytesReceived = recv(clientSocket, rxBuffer, sizeof(rxBuffer) - 1, 0);
        if (bytesReceived == SOCKET_ERROR) {
            std::cerr << "recv() failed\n";
        }
        else if (bytesReceived == 0) {
            std::cerr << "Connection closed by the client\n";
        }
        else {
            rxBuffer[bytesReceived] = '\0';
            std::cout << "Received " << bytesReceived << " bytes from client: " << rxBuffer << std::endl;
        }

        return 0;


    }
    ~server()
    {
        // Clean up
        closesocket(clientSocket);
        closesocket(serverSocket);
        WSACleanup();

    }

private:
    SOCKET serverSocket;
    SOCKET clientSocket;
    char rxBuffer[1024];


};

#pragma comment(lib, "ws2_32.lib")

int main() {
    //sets up windows socket API -> interacts with OS and HW

    server mypc;

    mypc.server_startup();
    mypc.create_socket();
    mypc.bind_socket("192.168.0.11", 4);
    mypc.listen_and_accept_client();
    mypc.recieve();

    /*
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed\n";
        return 1;
    }

    // Create socket
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "Error creating socket\n";
        WSACleanup();
        return 1;
    }

    // Bind socket
    sockaddr_in serverAddr;
    //Change this IP depending on machine
    const char* ip = "192.168.0.11";
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;  // Accept connections on any local IP address
    //change this if not working
    serverAddr.sin_port = htons(4); // Server port
    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed\n";
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Listen failed\n";
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Server is listening for incoming connections...\n";

    // Accept incoming connection
    SOCKET clientSocket = accept(serverSocket, NULL, NULL);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Accept failed\n";
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Client connected\n";

    // Receive data from client
    char recvBuffer[1024];
    int bytesReceived = recv(clientSocket, recvBuffer, sizeof(recvBuffer) - 1, 0);
    if (bytesReceived == SOCKET_ERROR) {
        std::cerr << "recv() failed\n";
    }
    else if (bytesReceived == 0) {
        std::cerr << "Connection closed by the client\n";
    }
    else {
        recvBuffer[bytesReceived] = '\0';
        std::cout << "Received " << bytesReceived << " bytes from client: " << recvBuffer << std::endl;
    }

    // Clean up
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();
    */

    return 0;
}
