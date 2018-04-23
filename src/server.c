/*
 * tcpserver.c - A simple TCP echo server
 * usage: tcpserver <port>
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "threadpool.h"
#include "cache.h"
#define BUFSIZE 1024

#if 0
/*
 * Structs exported from in.h
 */

/* Internet address */
struct in_addr {
  unsigned int s_addr;
};

/* Internet style socket address */
struct sockaddr_in  {
  unsigned short int sin_family; /* Address family */
  unsigned short int sin_port;   /* Port number */
  struct in_addr sin_addr;	 /* IP address */
  unsigned char sin_zero[...];   /* Pad to size of 'struct sockaddr' */
};

/*
 * Struct exported from netdb.h
 */

/* Domain name service (DNS) host entry */
struct hostent {
  char    *h_name;        /* official name of host */
  char    **h_aliases;    /* alias list */
  int     h_addrtype;     /* host address type */
  int     h_length;       /* length of address */
  char    **h_addr_list;  /* list of addresses */
}
#endif

/*
 * error - wrapper for perror
 */


 #define MAX_BYTES 1024

 #define GET "GET"
 #define SET "SET"
 #define DELETE "DELETE"
 #define ACK "OK"

 const int LISTEN_BACKLOG = 512;


 char* dispatch(char* item){

     if (item == NULL)
         return item;
     const char* delim = " ";
     char* token = strtok(item, delim);

     char* action = (char* ) malloc(sizeof(char)* strlen(token));
     strcpy(action, token);

     if(!action)
         return NULL;

     if (strcmp(action, GET) == 0){

         token = strtok(NULL, delim);
         char* key = (char* ) malloc(sizeof(char) * strlen(token));

         strncpy(key, token, strlen(token)-1);
         char* result = (char*) get_value(key);

         if (result == NULL){
             return NULL;
         }
         char* copy = malloc(sizeof(char)* strlen(result+1));
         strcpy(copy, result);
         return copy;

     }else if(strcmp(action, SET) == 0){

         token = strtok(NULL, delim);
         char* key =  (char* ) malloc(sizeof(char)* strlen(token));
         strcpy(key, token);
         token = strtok(NULL, delim);
         char* value = (char* ) malloc(sizeof(char)* strlen(token));
         strncpy(value, token, strlen(token)-1);

         set(key, value);
         return ACK;

     }else if(strcmp(action, DELETE) == 0){

         token = strtok(NULL, delim);
         char* key = (char*) malloc(sizeof(char)* strlen(token));
         strcpy(key, token);
         delete(key);
         return ACK;

     }else{

         puts("Invalid command!");
         return NULL;

     }
 }


 void do_work(Task* request){
     char* result = dispatch(request->item);

     puts(result);
     if (write(request->fd, result, strlen(result) + 1) == -1){
         perror("Error writing to fd");
     }

 }

void error(char *msg) {
  perror(msg);
  exit(1);
}


void process_task(char* buf, int childfd, ThreadPool* pool, int bytes_read){


    Task* request = new_task(childfd);
    if (bytes_read <= 0 )
        return;
    request->item = buf; //malloc(sizeof(char)* bytes_read);
    //bzero(request->item, sizeof(request->item));
    //strncpy(request->item, buf, bytes_read);
    request->function = do_work;
    request->argument = request;
    put(pool->work_q, request);
}

int main(int argc, char **argv) {
  int parentfd; /* parent socket */
  int childfd; /* child socket */
  int portno; /* port to listen on */
  int clientlen; /* byte size of client's address */
  struct sockaddr_in serveraddr; /* server's addr */
  struct sockaddr_in clientaddr; /* client addr */
  struct hostent *hostp; /* client host info */
  char buf[BUFSIZE]; /* message buffer */
  char *hostaddrp; /* dotted decimal host addr string */
  int optval; /* flag value for setsockopt */
  int n; /* message byte size */
  ThreadPool* pool = create_new_pool(); /*Create thread pool to process tasks*/
  init_cache();
  /*
   * check command line arguments
   */
  if (argc != 2) {
    fprintf(stderr, "usage: %s <port>\n", argv[0]);
    exit(1);
  }
  portno = atoi(argv[1]);

  /*
   * socket: create the parent socket
   */
  parentfd = socket(AF_INET, SOCK_STREAM, 0);
  if (parentfd < 0)
    error("ERROR opening socket");

  /* setsockopt: Handy debugging trick that lets
   * us rerun the server immediately after we kill it;
   * otherwise we have to wait about 20 secs.
   * Eliminates "ERROR on binding: Address already in use" error.
   */
  optval = 1;
  setsockopt(parentfd, SOL_SOCKET, SO_REUSEADDR,
	     (const void *)&optval , sizeof(int));

  /*
   * build the server's Internet address
   */
  bzero((char *) &serveraddr, sizeof(serveraddr));

  /* this is an Internet address */
  serveraddr.sin_family = AF_INET;

  /* let the system figure out our IP address */
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

  /* this is the port we will listen on */
  serveraddr.sin_port = htons((unsigned short)portno);

  /*
   * bind: associate the parent socket with a port
   */
  if (bind(parentfd, (struct sockaddr *) &serveraddr,
	   sizeof(serveraddr)) < 0)
    error("ERROR on binding");

  /*
   * listen: make this socket ready to accept connection requests
   */
  if (listen(parentfd, 5) < 0) /* allow 5 requests to queue up */
    error("ERROR on listen");

  /*
   * main loop: wait for a connection request, echo input line,
   * then close connection.
   */
  clientlen = sizeof(clientaddr);
  while (1) {

    /*
     * accept: wait for a connection request
     */
    childfd = accept(parentfd, (struct sockaddr *) &clientaddr, &clientlen);
    if (childfd < 0)
      error("ERROR on accept");

    /*
     * gethostbyaddr: determine who sent the message
     */
    hostp = gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr,
			  sizeof(clientaddr.sin_addr.s_addr), AF_INET);
    if (hostp == NULL)
      error("ERROR on gethostbyaddr");
    hostaddrp = inet_ntoa(clientaddr.sin_addr);
    if (hostaddrp == NULL)
      error("ERROR on inet_ntoa\n");
    printf("server established connection with %s (%s)\n",
	   hostp->h_name, hostaddrp);

    /*
     * read: read input string from the client
     */
    bzero(buf, BUFSIZE);
    n = read(childfd, buf, BUFSIZE);
    if (n < 0)
      error("ERROR reading from socket");
    printf("server received %d bytes: %s", n, buf);


    process_task(buf, childfd, pool, n);


  }
}
