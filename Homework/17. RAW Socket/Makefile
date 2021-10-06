CC := gcc
#LDFLAGS := -lm

SERVER_BIN := server_bin
CLIENT_UDP_BIN := client_udp_bin
CLIENT_IP_BIN := client_ip_bin
CLIENT_ETHERNET_BIN := client_ethernet_bin

SERVER_SOURCES := server.c
CLIENT_UDP_SOURCES := client_udp.c
CLIENT_IP_SOURCES := client_ip.c
CLIENT_ETHERNET_SOURCES := client_ethernet.c

.PHONY: clear

server: $(SERVER_SOURCES)
		@gcc $(SERVER_SOURCES) -o $(SERVER_BIN) -ansi -pedantic -Wall -lrt -lpthread
		@./$(SERVER_BIN)
		@rm -rf $(SERVER_BIN)

client_udp: $(CLIENT_UDP_SOURCES)
		@gcc $(CLIENT_UDP_SOURCES) -o $(CLIENT_UDP_BIN) -ansi -pedantic -Wall -lrt -lpthread
		@./$(CLIENT_UDP_BIN)
		@rm -rf $(CLIENT_UDP_BIN)
		
client_ip: $(CLIENT_IP_SOURCES)
		@gcc $(CLIENT_IP_SOURCES) -o $(CLIENT_IP_BIN) -ansi -pedantic -Wall -lrt -lpthread
		@./$(CLIENT_IP_BIN)
		@rm -rf $(CLIENT_IP_BIN)
		
client_ethernet: $(CLIENT_ETHERNET_SOURCES)
		@gcc $(CLIENT_ETHERNET_SOURCES) -o $(CLIENT_ETHERNET_BIN) -ansi -pedantic -Wall -lrt -lpthread
		@./$(CLIENT_ETHERNET_BIN)
		@rm -rf $(CLIENT_ETHERNET_BIN)
                
server_debug: $(SERVER_SOURCES)
		@gcc $(SERVER_SOURCES) -o $(SERVER_BIN) -ansi -pedantic -Wall -lrt -lpthread -g
		@gdb $(SERVER_BIN)
		@rm -rf $(SERVER_BIN)

client_udp_debug: $(CLIENT_UDP_SOURCES)
		@gcc $(CLIENT_UDP_SOURCES) -o $(CLIENT_UDP_BIN) -ansi -pedantic -Wall -lrt -lpthread -g
		@gdb $(CLIENT_UDP_BIN)
		@rm -rf $(CLIENT_UDP_BIN)
		
client_ip_debug: $(CLIENT_IP_SOURCES)
		@gcc $(CLIENT_IP_SOURCES) -o $(CLIENT_IP_BIN) -ansi -pedantic -Wall -lrt -lpthread -g
		@gdb $(CLIENT_IP_BIN)
		@rm -rf $(CLIENT_IP_BIN)
		
client_ethernet_debug: $(CLIENT_ETHERNET_SOURCES)
		@gcc $(CLIENT_ETHERNET_SOURCES) -o $(CLIENT_ETHERNET_BIN) -ansi -pedantic -Wall -lrt -lpthread -g
		@gdb $(CLIENT_ETHERNET_BIN)
		@rm -rf $(CLIENT_ETHERNET_BIN)

clear:
		@rm -rf $(SERVER_BIN)
		@rm -rf $(CLIENT_UDP_BIN)
		@rm -rf $(CLIENT_IP_BIN)
		@rm -rf $(CLIENT_ETHERNET_BIN)
