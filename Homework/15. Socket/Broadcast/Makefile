CC := gcc
#LDFLAGS := -lm

SOURCER1 := server
SOURCER2 := client

.PHONY := all clear

all: $(SOURCER1) $(SOURCER2)


$(SOURCER1): $(SOURCER1).c
		gcc $(SOURCER1).c -o $(SOURCER1) -g -pthread -lrt

$(SOURCER2): $(SOURCER2).c
		gcc $(SOURCER2).c -o $(SOURCER2) -g -pthread

clear:
		rm $(SOURCER1) $(SOURCER2)
