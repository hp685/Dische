//
// Created by harshpatel on 3/30/18.
//

#include <sys/socket.h>
#include <errno.h>

const int LISTEN_BACKLOG = 512;

void listen_forever(){

    struct sockaddr_in address;
    struct sockaddr_in client_address;

    int sock = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_port = htons(7777);

    if (sock >= 0) {
        if (bind(sock, (struct sockaddr *) &address, sizeof(address)) == 0){
            if(listen(sock, LISTEN_BACKLOG) < 0){
                perror("Error on listen");
            }
            while(1){
                client_fd = accept(sock, (struct sockaddr *) &client_address, sizeof(client_address));

            }
        }
        else{
            perror("Cannot bind socket %d", sock);
        }

    }
    else{
        perror("Error creating socket");
    }
    }

int main(){

    listen_forever();
    return 0;
}