CC = gcc
CFLAGS = -g -Wall -pedantic
COMPILE = $(CC) $(CFLAGS)
PROGRAM = hashMapTest

all: $(PROGRAM)

fixedHashMap.o: fixedHashMap.c fixedHashMap.h
	$(COMPILE) -c $<

hashMapRunner.o: hashMapRunner.c
	$(COMPILE) -c $<

$(PROGRAM): fixedHashMap.o hashMapRunner.o
	$(COMPILE) -o $@ $^

clean:
	rm -rfv *.o *.gch $(PROGRAM)