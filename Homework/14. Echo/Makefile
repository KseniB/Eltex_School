SERVER_BIN := server_bin
CLIENT_BIN := client_bin
SERVER_SOURCES := server.c
CLIENT_SOURCES := client.c

.PHONY := clean

server_bin: $(SERVER_SOURCES)
		gcc $(SERVER_SOURCES) -o $(SERVER_BIN) -lrt -lpthread -Wall
		./$(SERVER_BIN)
		rm -rf $(SERVER_BIN)
		
client_bin: $(CLIENT_SOURCES)
		gcc $(CLIENT_SOURCES) -o $(CLIENT_BIN) -lrt -lpthread -Wall
		./$(CLIENT_BIN)
		rm -rf $(CLIENT_BIN)
		
server_debug: $(SERVER_SOURCES)
		gcc $(SERVER_SOURCES) -o $(SERVER_BIN) -lrt -lpthread -g -Wall
		gdb $(SERVER_BIN)
		rm -rf $(SERVER_BIN)

client_debug: $(CLIENT_SOURCES)
		gcc $(CLIENT_SOURCES) -o $(CLIENT_BIN) -lrt -lpthread -g -Wall
		gdb $(CLIENT_BIN)
		rm -rf $(CLIENT_BIN)

#$(BIN): $(HEADERS)

clean: $(SOURCES)
		rm -rf $(SERVER_BIN)
		rm -rf $(CLIENT_BIN)
