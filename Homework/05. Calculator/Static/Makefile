CC := gcc

LIB := static_calc
BIN := main
SOURCES := main.c 
LIB_SOURCES := plus.c minus.c divide.c multiply.c
HEADERS := mycalc.h

.PHONY := clean

all: bin_exe clean

bin_exe: $(SOURCES) $(LIB_SOURCES)
                gcc -c $(LIB_SOURCES)
                ar rc lib$(LIB).a *.o
		gcc $(SOURCES) -L. -l$(LIB) -o $(BIN) -Wall
		./$(BIN)
		
bin: $(SOURCES) $(LIB_SOURCES)
                gcc -c $(LIB_SOURCES)
                ar rc lib$(LIB).a *.o
		gcc $(SOURCES) -o $(BIN) -Wall
		
debug: $(SOURCES) $(LIB_SOURCES)
                gcc -c $(LIB_SOURCES)
                ar rc lib$(LIB).a *.o
		gcc $(SOURCES) -o $(BIN) -g
		gdb $(BIN)
		rm -rf $(BIN)

$(BIN): $(HEADERS)

clean: $(SOURCES)
		rm -rf $(BIN)
                rm -rf *.o
                rm -rf lib$(LIB).a
