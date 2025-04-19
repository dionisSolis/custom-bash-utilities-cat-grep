СС = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11 -std=gnu11

all: s21_cat

s21_cat: main.o initializeArrays.o checkArguments.o applyFlagsOnLine.o
	$(CC) main.o initializeArrays.o checkArguments.o applyFlagsOnLine.o -o s21_cat
	
main.o: main.c
	$(CC) $(CFLAGS) -c main.c

initializeArrays.o: initializeArrays.c 
	$(CC) $(CFLAGS) -c initializeArrays.c

checkArguments.o: checkArguments.c 
	$(CC) $(CFLAGS) -c checkArguments.c

applyFlagsOnLine.o: applyFlagsOnLine.c
	$(CC) $(CFLAGS) -c applyFlagsOnLine.c

clean:
	rm -rf *.o s21_cat