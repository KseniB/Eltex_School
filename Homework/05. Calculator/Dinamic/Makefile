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
                gcc -fPIC -c $(LIB_SOURCES)
		gcc -shared -o lib$(LIB).so *.o

$(BIN):	$(SOURCES)
                gcc $(SOURCES) -L. -l$(LIB) -o $(BIN)
                gcc -c $(SOURCES)
                gcc main.o -L. -l$(LIB) -o $(BIN)
                $ LD_LIBRARY_PATH =. ./$(BIN)

clear: 
                rm -rf $(BIN)
                rm -rf *.o
                rm -rf lib$(LIB).so
