

CC=gcc

CFLAGS= -I ./unity/src/

TFLAGS= ./unity/src/unity.c -pthread

test: test_tp test_q test_cache

test_tp: test_threadpool.c
	$(CC) $(CFLAGS) $(TFLAGS) queue.c threadpool.c test_threadpool.c -o test_tp.o
	./test_tp.o
test_q: test_queue.c
	$(CC) $(CFLAGS) $(TFLAGS) queue.c test_queue.c -o test_q.o
	./test_q.o
test_cache: test_cache.c
	$(CC) $(CFLAGS) $(TFLAGS) cache.c test_cache.c -o test_cache.o
	./test_cache.o
clean:
	rm *.o
