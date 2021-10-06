CC := gcc
#LDFLAGS := -lm

SENDER_BIN := sender_bin
RECEIVER_BIN := receiver_bin
SENDER_SOURCES := sender.c
RECEIVER_SOURCES := receiver.c

.PHONY: clear

sender: $(SENDER_SOURCES)
		@gcc $(SENDER_SOURCES) -o $(SENDER_BIN) -ansi -pedantic -Wall -lrt -lpthread
		@./$(SENDER_BIN)
		@rm -rf $(SENDER_BIN)

receiver: $(RECEIVER_SOURCES)
		@gcc $(RECEIVER_SOURCES) -o $(RECEIVER_BIN) -ansi -pedantic -Wall -lrt -lpthread
		@./$(RECEIVER_BIN)
		@rm -rf $(RECEIVER_BIN)
                
sender_debug: $(SENDER_SOURCES)
		@gcc $(SENDER_SOURCES) -o $(SENDER_BIN) -ansi -pedantic -Wall -lrt -lpthread -g
		@gdb $(SENDER_BIN)
		@rm -rf $(SENDER_BIN)

receiver_debug: $(RECEIVER_SOURCES)
		@gcc $(RECEIVER_SOURCES) -o $(RECEIVER_BIN) -ansi -pedantic -Wall -lrt -lpthread -g
		@gdb $(RECEIVER_BIN)
		@rm -rf $(RECEIVER_BIN)

clear:
		@rm -rf $(SENDER_BIN)
		@rm -rf $(RECEIVER_BIN)
