#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

#include "node/node.h"

int list_contact(node_t *HEAD);
int add_contact(node_t *HEAD);
int del_contact(node_t *HEAD);
int search_contact(node_t *HEAD);
int exit_menu(node_t *HEAD);
int loop_menu(node_t *HEAD);
