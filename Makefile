INCLUDE_DIR = ./ 
LIBRARY_DIR = ./

CC = gcc
CFLAGS = -O3 -Wall #-DDEBUG
LDGLAGS =  
LIBS = -lpthread  

CFLAGS += -I$(INCLUDE_DIR)

test_bitops: test_bitops.o bitops.o
	$(CC) $(LDFLAGS) test_bitops.o bitops.o -o test_bitops -L$(LIBRARY_DIR) $(LIBS)

test_atomic_ops: test_atomic_ops.o
	$(CC) $(LDFLAGS) test_atomic_ops.o -o test_atomic_ops -L$(LIBRARY_DIR) $(LIBS)

test_timer: test_timer.o
	$(CC) $(LDFLAGS) test_timer.o -o test_timer -L$(LIBRARY_DIR) $(LIBS)

run_explorer: processor_map.o run_explorer.o util.o 
	$(CC) $(LDFLAGS) processor_map.o run_explorer.o util.o -o run_explorer -L$(LIBRARY_DIR) $(LIBS)


%.o : %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf *.o
