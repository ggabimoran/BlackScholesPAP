BINARIES_DIR = bin

CC = g++

all : tests.out

tests.out : ../$(BINARIES_DIR)/tests.o ../$(BINARIES_DIR)/math.o ../$(BINARIES_DIR)/option.o ../$(BINARIES_DIR)/heatpde1d.o
	$(CC) $^ -o $@

../$(BINARIES_DIR)/tests.o : tests.cpp  
	$(CC) -c $^ -o $@

clean:
	rm *.out
