#include<arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "threadpool.h"
#include "cache.h"

#define MAX_BYTES 65536

#define GET "GET"
#define SET "SET"
#define DELETE "DELETE"
#define ACK "OK"

const int LISTEN_BACKLOG = 512;

char* dispatch(char* item){

    const char* delim = " ";
    char* token = strtok(item, delim);
    char* action = (char* ) malloc(sizeof(token));
    strcpy(action, token);

    if (strcmp(action, GET) == 0){

        token = strtok(NULL, delim);
        char* key = (char* ) malloc(sizeof(token));
        strcpy(key, token);

        return get_value(key);

    }else if(strcmp(action, SET) == 0){

        token = strtok(NULL, delim);
        char* key =  (char* ) malloc(sizeof(token));
        strcpy(key, token);
        token = strtok(NULL, delim);
        char* value = (char* ) malloc(sizeof(token));
        strcpy(value, token);

        set(key, value);
        return ACK;

    }else if(strcmp(action, DELETE) == 0){

        token = strtok(NULL, delim);
        char* key = (char*) malloc(sizeof(token));
        strcpy(key, token);

        delete(key);
        return ACK;

    }else{

        perror("Bad command!");
        exit(EXIT_FAILURE);

    }
}


void do_work(Task* request){

    char* result = dispatch(request->item);
    puts(request->item);
    puts("\n");
    if (write(request->fd, result, strlen(result) + 1) == -1){
        perror("Error writing to fd");
    }
    //close(request->fd);
}


void serve_forever(){

    struct sockaddr_in address;
    struct sockaddr_in client_address;
    char buffer[MAX_BYTES];
    ThreadPool* pool = create_new_pool();

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
		            Task* request = new_task(client_fd);
                read(client_fd, buffer, MAX_BYTES);
                request->item = malloc(sizeof(char) * strlen(buffer));
                /* TODO split buffer by item delimiter*/
                strcpy(request->item, buffer);
                request->function = do_work;

                /*TODO: Make this an inqueue with its own lock to prevent server from blocking to obtain work_q lock*/
                pthread_mutex_lock(&pool->work_q->lock);

                put(pool->work_q, request);
                pthread_mutex_unlock(&pool->work_q->lock);
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

    serve_forever();

    return 0;
}
