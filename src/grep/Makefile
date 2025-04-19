СС = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -std=gnu11

all: s21_grep

s21_grep: main.o initializeArrays.o checkArguments.o grep.o
	$(CC) main.o initializeArrays.o checkArguments.o grep.o -o s21_grep
	
main.o: main.c
	$(CC) $(CFLAGS) -c main.c

initializeArrays.o: initializeArrays.c 
	$(CC) $(CFLAGS) -c initializeArrays.c

checkArguments.o: checkArguments.c 
	$(CC) $(CFLAGS) -c checkArguments.c

grep.o: grep.c
	$(CC) $(CFLAGS) -c grep.c

clean:
	rm -rf *.o s21_grep