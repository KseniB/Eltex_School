CC := gcc

BIN := main
SOURCES := main.c
SOURCES_LIB := node/node.c menu/menu.c
HEADERS := node/node.h menu/menu.h

.PHONY := clean

all: bin_exe clean

bin_exe: $(SOURCES)
		gcc $(SOURCES) -o $(BIN) -Wall
		gcc $(SOURCES) -o 
		./$(BIN)
		
bin: $(SOURCES)
		gcc $(SOURCES) -o $(BIN) -Wall
		gcc $(SOURCES) -o 
		
debug: $(SOURCES)
		gcc $(SOURCES) -o $(BIN) -g
		gcc $(SOURCES) -o -g
		gdb $(BIN)
		rm -rf $(BIN)

$(BIN): $(HEADERS)

clean: $(SOURCES)
		rm -rf $(BIN)
