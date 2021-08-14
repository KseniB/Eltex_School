CC := gcc
#LDFLAGS := -lm

LIB := statiCalc
BIN := statiCalc_lib
SOURCES := main.c
LIB_SOURCES := plus.c minus.c divide.c multiply.c
HEADERS := mycalc.h

.PHONY := all clear

all: $(LIB) $(BIN) clear

$(LIB): $(LIB_SOURCES)
                gcc -c $(LIB_SOURCES)
                ar rc lib$(LIB).a *.o

$(BIN):	$(SOURCES)
                gcc $(SOURCES) -L. -l$(LIB) -o $(BIN)
                ./$(BIN)

#$(BIN): $(HEADERS)

clear: 
                rm -rf $(BIN)
                rm -rf *.o
                rm -rf lib$(LIB).a
