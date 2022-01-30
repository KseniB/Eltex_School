SENDER_BIN := sender_bin
RECEIVER_BIN := receiver_bin
SENDER_SOURCES := sender.c
RECEIVER_SOURCES := receiver.c

.PHONY: clean

sender_bin: $(SENDER_SOURCES)
		gcc $(SENDER_SOURCES) -o $(SENDER_BIN) -lrt -lpthread -Wall
		./$(SENDER_BIN)
		rm -rf $(SENDER_BIN)

receiver_bin: $(RECEIVER_SOURCES)
		gcc $(RECEIVER_SOURCES) -o $(RECEIVER_BIN) -lrt -lpthread -Wall
		./$(RECEIVER_BIN)
		rm -rf $(RECEIVER_BIN)
                
sender_debug: $(SENDER_SOURCES)
		gcc $(SENDER_SOURCES) -o $(SENDER_BIN) -lrt -lpthread -g -Wall
		gdb $(SENDER_BIN)
		rm -rf $(SENDER_BIN)

receiver_debug: $(RECEIVER_SOURCES)
		gcc $(RECEIVER_SOURCES) -o $(RECEIVER_BIN) -lrt -lpthread -g -Wall
		gdb $(RECEIVER_BIN)
		rm -rf $(RECEIVER_BIN)

clean:
		rm -rf $(SENDER_BIN)
		rm -rf $(RECEIVER_BIN)
