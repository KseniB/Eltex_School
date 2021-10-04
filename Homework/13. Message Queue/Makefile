CC := gcc
#LDFLAGS := -lm

SERVER_BIN := mq_server
CLIENT_BIN := mq_client
SERVER_SOURCES := server.c
CLIENT_SOURCES := client.c

.PHONY: clear

server: $(SERVER_SOURCES)
		@gcc $(SERVER_SOURCES) -o $(SERVER_BIN) -ansi -pedantic -Wall -lrt -lpthread
		@./$(SERVER_BIN)
		@rm -rf $(SERVER_BIN)

client: $(CLIENT_SOURCES)
		@gcc $(CLIENT_SOURCES) -o $(CLIENT_BIN) -ansi -pedantic -Wall -lrt -lpthread
		@./$(CLIENT_BIN)
		@rm -rf $(CLIENT_BIN)
                
server_debug: $(SERVER_SOURCES)
		@gcc $(SERVER_SOURCES) -o $(SERVER_BIN) -ansi -pedantic -Wall -lrt -lpthread -g
		@gdb $(SERVER_BIN)
		@rm -rf $(SERVER_BIN)

client_debug: $(CLIENT_SOURCES)
		@gcc $(CLIENT_SOURCES) -o $(CLIENT_BIN) -ansi -pedantic -Wall -lrt -lpthread -g
		@gdb $(CLIENT_BIN)
		@rm -rf $(CLIENT_BIN)

clear:
		@rm -rf $(SERVER_BIN)
		@rm -rf $(CLIENT_BIN)
