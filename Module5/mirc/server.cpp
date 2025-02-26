#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <vector>

#define PORT 8080
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 10

struct ClientInfo {
    int socket;
    std::string name;
};

std::vector<ClientInfo> clients;
pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

void broadcast_message(const std::string& sender, const std::string& message, int sender_socket) {
    pthread_mutex_lock(&clients_mutex);
    for (const auto& client : clients) {
        if (client.socket != sender_socket) {
            std::string formatted_message = sender + ": " + message;
            send(client.socket, formatted_message.c_str(), formatted_message.length(), 0);
        }
    }
    pthread_mutex_unlock(&clients_mutex);
}

void* handle_client(void* arg) {
    int client_socket = *((int*)arg);
    char buffer[BUFFER_SIZE];

    // Get client name
    memset(buffer, 0, BUFFER_SIZE);
    recv(client_socket, buffer, BUFFER_SIZE, 0);
    std::string client_name(buffer);

    pthread_mutex_lock(&clients_mutex);
    clients.push_back({client_socket, client_name});
    pthread_mutex_unlock(&clients_mutex);

    std::cout << client_name << " joined the chat!" << std::endl;
    broadcast_message("Server", client_name + " has joined the chat!", client_socket);

    while (true) {
        memset(buffer, 0, BUFFER_SIZE);
        int bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0) {
            std::cout << client_name << " disconnected." << std::endl;
            break;
        }

        std::cout << client_name << ": " << buffer << std::endl;
        broadcast_message(client_name, buffer, client_socket);
    }

    // Remove client
    pthread_mutex_lock(&clients_mutex);
    clients.erase(std::remove_if(clients.begin(), clients.end(), [client_socket](const ClientInfo& c) {
        return c.socket == client_socket;
    }), clients.end());
    pthread_mutex_unlock(&clients_mutex);

    broadcast_message("Server", client_name + " has left the chat.", client_socket);
    close(client_socket);
    return nullptr;
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    pthread_t thread;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        std::cerr << "Error creating socket." << std::endl;
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        std::cerr << "Bind failed." << std::endl;
        return 1;
    }

    if (listen(server_socket, MAX_CLIENTS) == -1) {
        std::cerr << "Listen failed." << std::endl;
        return 1;
    }

    std::cout << "Server listening on port " << PORT << "..." << std::endl;

    while (true) {
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_len);
        if (client_socket == -1) {
            std::cerr << "Client connection failed." << std::endl;
            continue;
        }

        pthread_create(&thread, nullptr, handle_client, &client_socket);
        pthread_detach(thread);
    }

    close(server_socket);
    return 0;
}
