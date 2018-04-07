#include<arpa/inet.h>
#include <sys/socket.h>
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "cache.h"
#include "queue.h"
#include "threadpool.h"

#define NUM_THREADS 10
#define MAX_BYTES 65536

#define GET "GET"
#define SET "SET"
#define DELETE "DELETE"


const int LISTEN_BACKLOG = 512;
const Cache* cache = (Cache*) malloc(sizeof(Cache));

void do_work(Task* work){
/**/

}




char* dispatch(char* item){

  const char* delim = " ";
  char* token = strtok(item, delim);
  char* action = (char* ) malloc(sizeof(token));
  strcpy(action, token);

  if (strcmp(action, GET) == 0){

    token = strtok(NULL, delim);
    char* key = (char* ) malloc(sizeof(token));
    strcpy(key, token);
    return getKey(cache, key);

  }else if(strcmp(action, SET) == 0){

    token = strtok(NULL, delim);
    char* key =  (char* ) malloc(sizeof(token));
    strcpy(key, token);
    token = strtok(NULL, delim);
    char* value = (char* ) malloc(sizeof(token));
    strcpy(value, token);
    return setKey(cache, key, value);

  }else if(strcmp(action, DELETE) == 0){

    token = strtok(NULL, delim);
    char* key = (char*) malloc(sizeof(token));
    strcpy(key, token);
    return deleteKey(cache, key);

  }else{
    perror("Bad command!");
    exit(EXIT_FAILURE);
  }
}


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
    ThreadPool* pool = create_new_pool();
    pthread_mutex_t* pool_lock = pool->work_q->lock;
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
		            Task* request = create_new_task(client_fd);
                request->item = read(client_fd, buffer, MAX_BYTES);
                /*TODO: Make this an inqueue with its own lock to prevent server from blocking to obtain work_q lock*/
                pthread_mutex_lock(&pool_lock);
                put(pool->work_q, request);
                pthread_mutex_unlock(&pool_lock);
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
