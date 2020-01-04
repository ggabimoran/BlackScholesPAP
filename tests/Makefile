BINARIES_DIR = bin

CC = g++

all : test.out

test.out : ../$(BINARIES_DIR)/tests.o ../$(BINARIES_DIR)/math.o 
	$(CC) $^ -o $@

../$(BINARIES_DIR)/tests.o : tests.cpp  
	$(CC) -c $^ -o $@

clean:
	rm *.out
