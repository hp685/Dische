//
// Created by harshpatel on 3/30/18.
//

#include<arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


#define NUM_THREADS 10
#define MAX_BYTES 65536



const int LISTEN_BACKLOG = 512;


void handle_message(int fd){
    char* buffer;
    ssize_t bytes_read = read(fd, buffer, MAX_BYTES);

    if (bytes_read <= 0){
      perror("Error reading from socket");
      exit(EXIT_FAILURE);
    }

    printf("Bytes read: {%lu} with data {%s}", bytes_read, buffer);

    write(fd, buffer, bytes_read);
    close(fd);
}


void handle_in_thread(int fd){
  pthread_t  thread;
  void *res;
  int rc = pthread_create(thread, NULL, handle_message, (void*) fd);
  if (rc != 0){
    perror("Error creating thread");
    exit(EXIT_FAILURE);
  }
  pthread_join(thread, &res);
}


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
                int client_fd = accept(sock, (struct sockaddr *) &client_address, sizeof(client_address));
		            handle_in_thread(client_fd);
            }
        }
        else{
            perror("Cannot bind socket");
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
