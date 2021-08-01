CC := gcc
#LDFLAGS := -lm

BIN := main
SOURCES := main.c
#HEADERS := main.h

.PHONY := all clean

all: $(BIN)

$(BIN):	$(SOURCES)
                gcc $(SOURCES) -o $(BIN)
                ./$(BIN)
                rm -rf $(BIN)

#$(BIN): $(HEADERS)

clean: 
                rm -rf $(BIN)
