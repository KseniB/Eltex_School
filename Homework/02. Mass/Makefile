CC := gcc
#LDFLAGS := -lm

BIN := main
SOURCES := main.c
#HEADERS := main.h

.PHONY := clear

all: $(BIN)

$(BIN):	$(SOURCES)
		gcc $(SOURCES) -o $(BIN)
		./$(BIN)
		rm -rf $(BIN)

#$(BIN): $(HEADERS)

clear: 
		rm -rf $(BIN)
