#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

const int PORT_NUMBER = 4;
const char* SERVER_IP = "192.168.0.11"; // Replace with your server's IP address

class client {
    int create_socket()
    {
        // Create socket
        clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (clientSocket == -1) {
            std::cerr << "Error creating socket" << std::endl;
            return 1;
        }
        return 0;
    }

    int connect_to_server(const char* ip, const int port)
    {
        // Set server address and port
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(PORT_NUMBER);
        inet_pton(AF_INET, SERVER_IP, &serverAddr.sin_addr);

        // Connect to server
        if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
            std::cerr << "Error connecting to server" << std::endl;
            close(clientSocket);
            return 1;
        }


        return 0;
    }
    int send_to_server(const char* message)
    {
        // Send message to server
        const char* message = "This message is from the pi";
        if (send(clientSocket, message, strlen(message), 0) == -1) {
            std::cerr << "Error sending message to server" << std::endl;
            close(clientSocket);
            return 1;
        }

        std::cout << "Message sent to server: " << message << std::endl;

        return 0;
        
    }
    ~client() {
        close(clientSocket);
    }
    private:
        int clientSocket;
        struct sockaddr_in serverAddr;
        char txBuffer[1024];
};

int main() {

    client pi;

    pi.create_socket();
    pi.connect_to_server("192.168.0.11", 4);
    pi.send_to_server("Hi this is object oriented pi!!!")

    /*
    int clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[1024];

    // Create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    // Set server address and port
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT_NUMBER);
    inet_pton(AF_INET, SERVER_IP, &serverAddr.sin_addr);

    // Connect to server
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Error connecting to server" << std::endl;
        close(clientSocket);
        return 1;
    }

    // Send message to server
    const char* message = "This message is from the pi";
    if (send(clientSocket, message, strlen(message), 0) == -1) {
        std::cerr << "Error sending message to server" << std::endl;
        close(clientSocket);
        return 1;
    }

    std::cout << "Message sent to server: " << message << std::endl;

    close(clientSocket);
    */

    return 0;
}
