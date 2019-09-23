#include <stdio.h>
#include <signal.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>

int s_fd, a_fd;
int c_fd;
int playServer_tcp()
{
    struct sockaddr_in serv;
    struct sockaddr_in peer;
    char buf[100];
    memset(&serv, 0, sizeof(serv));
    memset(&peer, 0, sizeof(peer));
    int peerAddrLen = sizeof(peer);

    //getprotoent
    //protocol
    if((s_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket:");
        return -1;
    }

    serv.sin_family = AF_INET;
    serv.sin_port = 9999;
    serv.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(s_fd, (struct sockaddr *) &serv, sizeof(serv)) < 0) {
        perror("bind:");
        return -1;
    }

    if(listen(s_fd, 5) < -1) {
        perror("listen:");
        close(s_fd);
        return -1;
    }

    printf("Starting server\n");
    if((a_fd = accept(s_fd, (struct sockaddr *) &peer, &peerAddrLen)) < 0 ) {
        perror("accept");
        close(s_fd);
        return -1;
    }

    while(1) {
        if(read(a_fd, buf, 100) < 0) {
            perror("read:");
            close(a_fd);
            close(s_fd);
            return -1;
        }
        printf("%s\n", buf);
        if(strstr(buf, "kill")) {
            close(a_fd);
            close(s_fd);
            return 0;
        }
    }
}

int playClient_tcp()
{
    char buf[100];
    struct sockaddr_in servAddr;
    memset(&servAddr, 0 , sizeof(servAddr));
    if((c_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket:");
        return -1;
    }

    servAddr.sin_family = AF_INET;
    servAddr.sin_port = 9999;
    if(inet_pton(AF_INET, "127.0.0.1", (struct sockaddr *) &servAddr.sin_addr.s_addr) == 0) {
        perror("inet_pton:");
        return -1;
    }

    printf("Starting client\n");

    if(connect(c_fd, (struct sockaddr *) &servAddr, sizeof(servAddr)) != 0) {
        perror("connect:");
        close(c_fd);
        return -1;
    }

    printf("connected\n");

    while(1) {
        fgets(buf, 100, stdin);
        write(c_fd, buf, strlen(buf));
        if(strstr(buf, "kill")) {
            close(c_fd);
            return 0;
        }
    }
}

void sig_handler(int sig_no)
{
    close(s_fd);
    close(a_fd);
    close(c_fd);

}

int main(int argc, char **argv)
{
    signal(SIGKILL, sig_handler);
    signal(SIGINT, sig_handler);
    signal(SIGPIPE, sig_handler);
    if(strstr(*argv, "client")) {
        printf("client\n");
        playClient_tcp();
    } else if (strstr(*argv, "server")) {
        printf("server\n");
        playServer_tcp();
    }
    else
        printf("Invalid");
}
