

CC=gcc

CFLAGS= -I ./src/ -I ./unity/src/ -std=c99 -pthread
TFLAGS= ./unity/src/unity.c 
SRCDIR = ./src/
TESTDIR = ./tests/



test: test_q test_cache test_pool

test_pool: $(TESTDIR)test_threadpool.c
	$(CC) $(CFLAGS) $(TFLAGS) $(SRCDIR)queue.c $(SRCDIR)threadpool.c $(TESTDIR)test_threadpool.c -o $(TESTDIR)test_tp.o
	$(TESTDIR)test_tp.o

test_q: $(TESTDIR)test_queue.c
	$(CC) $(CFLAGS) $(TFLAGS) $(SRCDIR)queue.c $(TESTDIR)test_queue.c -o $(TESTDIR)test_q.o
	$(TESTDIR)test_q.o

test_cache: $(TESTDIR)test_cache.c
	$(CC) $(CFLAGS) $(TFLAGS) $(SRCDIR)cache.c $(TESTDIR)test_cache.c -o $(TESTDIR)test_cache.o
	$(TESTDIR)test_cache.o

server:
	$(CC) $(CFLAGS) $(SRCDIR)cache.h $(SRCDIR)queue.h $(SRCDIR)threadpool.h  $(SRCDIR)cache.c $(SRCDIR)queue.c $(SRCDIR)threadpool.c $(SRCDIR)server.c -o server

client:
	$(CC)  $(SRCDIR)test_client.c -o client

clean:
	rm $(TESTDIR)*.o
