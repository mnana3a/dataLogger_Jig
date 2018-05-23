CC = gcc
OBJECTS = test_lib.o fat16.o
FLAGS = -Wall -D_WRITE
RM = /bin/rm -f


all: $(OBJECTS)
	$(CC) $(FLAGS) $^ -o test_lib

clean:
	$(RM) *.o test_lib

%.o: %.c
	$(CC) $(FLAGS) -c $^ -o $@
