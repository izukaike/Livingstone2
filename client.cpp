#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

const int PORT_NUMBER = 4;
const char* SERVER_IP = "192.168.1.215"; // Replace with your server's IP address

class client {
    public:
	client()
        { 
	   /*
	    txBuffer  = new uint8_t[5];
	    for(int i = 0; i <5;++i)
	    {
		    txBuffer[i] = -13;
	    }
	    */
	   
	}
        int create_socket()
        {
            // Create socket
            clientSocket = socket(AF_INET, SOCK_STREAM,0);
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
            
            if (send(clientSocket, message, strlen(message), 0) == -1)
	    {
                std::cerr << "Error sending message to server" << std::endl;
      
                return 1;
            }

            std::cout << "Message sent to server: " << message << std::endl;

            return 0;
            
        }
        int* get_from_server()
        {
	    int bytes = 0;
	    while(bytes ==  0)
	    {
		 bytes = recv(clientSocket,txBuffer, sizeof(txBuffer)-1,0);
	    }
          
            if(bytes == -1)
            {
                std::cout << "add system health code here\n";
            }
            else if (bytes == -1)
            {
                std::cout << "add system health code here\n";
            }
            
            return txBuffer;
        }
        ~client() {
            close(clientSocket);
	   // delete[] txBuffer;
        }
    private:
        int    clientSocket;
        struct sockaddr_in serverAddr;
        int    txBuffer[5];
};

int main() {

    client pi;
    int*  data;
 
    pi.create_socket();
    pi.connect_to_server("192.168.1.215", 4);
    pi.send_to_server("sent from client to  server!");
    data =  pi.get_from_server();
    std::cout <<"\n\n\n" << std::endl;
    for(int i = 0; i < 5;++i)
    {
	    std::cout << data[i] << " ";
    }
    std::cout << "\n\n\n 2nd\n" <<std:: endl;
    data = pi.get_from_server();
    for(int i = 0; i < 5;++i)
    {
	    std::cout << data[i] << " ";
    }

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
    serverAddr.sin_family = AF_INET; serverAddr.sin_port = htons(PORT_NUMBER);
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
