HEADERS_DIR = headers
SOURCES_DIR = sources
BINARIES_DIR = bin
CC = g++

all : main

main : $(BINARIES_DIR)/option.o $(BINARIES_DIR)/heatpde1d.o $(BINARIES_DIR)/matrix.o $(BINARIES_DIR)/main.o
	$(CC) $^ -o $@

$(BINARIES_DIR)/option.o : $(SOURCES_DIR)/option.cpp $(HEADERS_DIR)/option.h  
	$(CC) -c $< -o $@

$(BINARIES_DIR)/heatpde1d.o : $(SOURCES_DIR)/heatpde1d.cpp $(HEADERS_DIR)/heatpde1d.h $(HEADERS_DIR)/option.h
	$(CC) -c $< -o $@

$(BINARIES_DIR)/matrix.o : $(SOURCES_DIR)/matrix.cpp $(HEADERS_DIR)/matrix.h
	$(CC) -c $< -o $@

$(BINARIES_DIR)/main.o : $(SOURCES_DIR)/main.cpp $(HEADERS_DIR)/matrix.h $(HEADERS_DIR)/heatpde1d.h $(HEADERS_DIR)/option.h
	$(CC) -c $< -o $@

clean:
	rm $(BINARIES_DIR)/*.o

$(shell mkdir -p $(BINARIES_DIR))
