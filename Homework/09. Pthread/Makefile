BIN := main
SOURCES := main.c
#HEADERS := main.h

.PHONY := clean

all: bin_exe clean

bin_exe: $(SOURCES)
		gcc $(SOURCES) -o $(BIN) -lpthread -Wall
		./$(BIN)
		
bin: $(SOURCES)
		gcc $(SOURCES) -o $(BIN) -lpthread -Wall
		
debug: $(SOURCES)
		gcc $(SOURCES) -o $(BIN) -g -lpthread
		gdb $(BIN)
		rm -rf $(BIN)

#$(BIN): $(HEADERS)

clean: $(SOURCES)
		rm -rf $(BIN)
