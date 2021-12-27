CC := gcc

LIB := mycalc
BIN := main
SOURCES := main.c 
LIB_SOURCES := lib/plus.c lib/minus.c lib/divide.c lib/multiply.c lib/menu.c lib/trashclean.c
HEADERS := lib/mycalc.h

.PHONY := clean

all: bin_exe clean

bin_exe: $(SOURCES) $(LIB_SOURCES)
		gcc -fPIC -c $(LIB_SOURCES)
		gcc -shared -o lib$(LIB).so *.o
		gcc $(SOURCES) -o $(BIN) -L. -l$(LIB) -Wall
		LD_LIBRARY_PATH=$$PWD:$$LD_LIBRARY_PATH ./$(BIN)
		
bin: $(SOURCES) $(LIB_SOURCES)
		gcc -fPIC -c $(LIB_SOURCES)
		gcc -shared -o lib$(LIB).so *.o
		gcc $(SOURCES) -o $(BIN) -L. -l$(LIB) -Wall
		
debug: $(SOURCES) $(LIB_SOURCES)
		gcc -fPIC -c $(LIB_SOURCES)
		gcc -shared -o lib$(LIB).so *.o
		gcc $(SOURCES) -o $(BIN) -L. -l$(LIB) -g
		gdb $(BIN)
		rm -rf $(BIN)

$(BIN): $(HEADERS)

clean: $(SOURCES)
		@rm -rf $(BIN)
		@rm -rf *.o
		@rm -rf *.so
