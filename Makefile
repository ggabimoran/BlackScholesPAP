HEADERS_DIR = headers
SOURCES_DIR = sources
BINARIES_DIR = bin
CC = g++

all : $(BINARIES_DIR)/option.o  $(BINARIES_DIR)/math.o $(BINARIES_DIR)/heatpde1d.o $(BINARIES_DIR)/fdm.o

$(BINARIES_DIR)/option.o : $(SOURCES_DIR)/option.cpp $(HEADERS_DIR)/option.h $(HEADERS_DIR)/math.h 
	$(CC) -c $< -o $@

$(BINARIES_DIR)/math.o : $(SOURCES_DIR)/math.cpp $(HEADERS_DIR)/math.h 
	$(CC) -c $< -o $@

$(BINARIES_DIR)/heatpde1d.o : $(SOURCES_DIR)/heatpde1d.cpp $(HEADERS_DIR)/heatpde1d.h $(HEADERS_DIR)/math.h $(HEADERS_DIR)/option.h
	$(CC) -c $< -o $@

$(BINARIES_DIR)/fdm.o : $(SOURCES_DIR)/fdm.cpp $(HEADERS_DIR)/fdm.h $(HEADERS_DIR)/math.h $(HEADERS_DIR)/option.h $(HEADERS_DIR)/heatpde1d.h $(HEADERS_DIR)/matrix.h
	$(CC) -c $< -o $@

clean:
	rm $(BINARIES_DIR)/*.o

$(shell mkdir -p $(BINARIES_DIR))
