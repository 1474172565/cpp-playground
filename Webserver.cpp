#include <iostream>
#include <string>
#include <sstream>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib") // 链接 Winsock 库

const int PORT = 8080;

// 解析 GET 请求，获取路径
std::string parse_path(const std::string& request_line) {
    std::istringstream iss(request_line);
    std::string method, path, version;
    iss >> method >> path >> version;
    if (method != "GET") return "";
    return path;
}

// 构建 HTTP 响应
std::string build_response(const std::string& body) {
    std::string response = "HTTP/1.1 200 OK\r\n";
    response += "Content-Type: text/plain\r\n";
    response += "Content-Length: " + std::to_string(body.size()) + "\r\n";
    response += "\r\n";
    response += body;
    return response;
}

int main() {
    // 初始化 Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed\n";
        return 1;
    }

    // 创建监听 socket
    SOCKET server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_socket == INVALID_SOCKET) {
        std::cerr << "socket failed\n";
        WSACleanup();
        return 1;
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        std::cerr << "bind failed\n";
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    if (listen(server_socket, 5) == SOCKET_ERROR) {
        std::cerr << "listen failed\n";
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }

    std::cout << "Server running on port " << PORT << "...\n";

    while (true) {
        SOCKET client_socket = accept(server_socket, nullptr, nullptr);
        if (client_socket == INVALID_SOCKET) {
            std::cerr << "accept failed\n";
            continue;
        }

        char buffer[1024] = {0};
        int bytes = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes > 0) {
            std::string request(buffer, bytes);
            std::string path = parse_path(request);

            std::string reply_text = "Hello! You requested: " + path;
            std::string response = build_response(reply_text);

            send(client_socket, response.c_str(), response.size(), 0);
        }

        closesocket(client_socket);
    }

    closesocket(server_socket);
    WSACleanup();
    return 0;
}