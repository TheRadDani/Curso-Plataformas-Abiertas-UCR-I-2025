#include <iostream>
#include <memory>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

struct FdCloser {
    void operator()(int* fd) const {
        if (fd && *fd >= 0) {
            ::close(*fd);
            delete fd;
        }
    }
};

class SocketServer {
    private:
        std::unique_ptr<int, FdCloser> socketFd;

    public:
        explicit SocketServer(int port) :
            socketFd(new int(socket(AF_INET, SOCK_STREAM, 0))) {
            
            if(*socketFd < 0) {
                throw std::runtime_error("Failed to create socket");
            }

            sockaddr_in serverAddr{};
            serverAddr.sin_family = AF_INET;
            serverAddr.sin_addr.s_addr = INADDR_ANY;
            serverAddr.sin_port = htons(port);

            if (bind(*socketFd, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) < 0) {
                throw std::runtime_error("Failed to bind socket");
            }

            if (listen(*socketFd, 5) < 0) {
                throw std::runtime_error("Failed to listen on socket");
            }
        
            std::cout << "Server listening on port " << port << "\n";
        }

        std::unique_ptr<int, FdCloser> acceptConnection() {

            sockaddr_in clientAddr{};
            socklen_t addrLen = sizeof(clientAddr);

            int clientFd = accept(*socketFd, reinterpret_cast<sockaddr*>(&clientAddr), &addrLen);
            if (clientFd < 0) {
                throw std::runtime_error("Failed to accept connection");
            }
            std::cout << "Client connected\n";
            return std::unique_ptr<int, FdCloser>(new int(clientFd));

        }

        void handleClient(std::unique_ptr<int, FdCloser> clientSocket) {
            if(!clientSocket) {
                throw std::runtime_error("Invalid client socket");
            }
            char buffer[1024] = "Hello client\n";

            send(*clientSocket, buffer, strlen(buffer), 0);
        }
};  


int main() {

    try {
        SocketServer server(8001);
        auto client = server.acceptConnection();
        if(client) {
            server.handleClient(std::move(client));
        } else {
            std::cerr << "No client connected." << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}