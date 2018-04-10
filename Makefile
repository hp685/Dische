

CC=gcc

CFLAGS= -I ./src/ -I ./unity/src/ -std=c99
TFLAGS= ./unity/src/unity.c -pthread
SRCDIR = ./src/
TESTDIR = ./tests/

test: test_tp test_q test_cache

test_tp: $(TESTDIR)test_threadpool.c
	$(CC) $(CFLAGS) $(TFLAGS) $(SRCDIR)queue.c $(SRCDIR)threadpool.c $(TESTDIR)test_threadpool.c -o $(TESTDIR)test_tp.o
	$(TESTDIR)/test_tp.o
test_q: $(TESTDIR)test_queue.c
	$(CC) $(CFLAGS) $(TFLAGS) $(SRCDIR)queue.c $(TESTDIR)test_queue.c -o $(TESTDIR)test_q.o
	$(TESTDIR)test_q.o
test_cache: $(TESTDIR)test_cache.c
	$(CC) $(CFLAGS) $(TFLAGS) $(SRCDIR)cache.c $(TESTDIR)test_cache.c -o $(TESTDIR)test_cache.o
	$(TESTDIR)test_cache.o
clean:
	rm $(TESTDIR)*.o
