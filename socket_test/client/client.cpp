#include <stdio.h>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main (int argc, const char * argv[]){
    struct sockaddr_in server_addr;
    server_addr.sin_len = sizeof(struct sockaddr_in);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(11332);
    server_addr.sin_addr.s_addr = inet_addr("10.29.2.92");
    bzero(&(server_addr.sin_zero),8);


    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("socket error");
        return 1;
    }
    char recv_msg[1024] = {0};

    if (!connect(server_socket, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_in))==0)
    {
        perror("not connected.");
        return -1;
    }

    while (true) {
        memset(recv_msg, 0, 1024);
        std::string reply_msg = "";

        long byte_num = recv(server_socket, recv_msg, 1024, 0);
        printf("server said:%s\n",recv_msg);

        std::cout << "reply:";
        std::cin >> reply_msg;

        if (send(server_socket, reply_msg.c_str(), reply_msg.size(), 0) == -1) {
            perror("send error");
        }
    }

    return 0;
}