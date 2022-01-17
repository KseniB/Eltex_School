BIN := main
SOURCES := main.c lib/lib.c
HEADERS := lib/lib.h

.PHONY := clean

all: bin_exe clean

bin_exe: $(SOURCES)
		gcc $(SOURCES) -o $(BIN) -Wall
		./$(BIN)
		
bin: $(SOURCES)
		gcc $(SOURCES) -o $(BIN) -Wall
		
debug: $(SOURCES)
		gcc $(SOURCES) -o $(BIN) -g
		gdb $(BIN)
		rm -rf $(BIN)

$(BIN): $(HEADERS)

clean: $(SOURCES)
		rm -rf $(BIN)
