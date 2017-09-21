CC = gcc

CFLAGS = -I$(INCDIR)

SRCDIR = ../src/
INCDIR = ../include/

all: linked priority run clean 

linked:
	$(CC) $(SRCDIR)linked_list.c test_LL.c $(CFLAGS) -o $@

priority:
	$(CC) $(SRCDIR)priority_queue.c test_PQ.c $(CFLAGS) -o $@

run:
	./priority && ./linked

clean:
	rm priority && rm linked
