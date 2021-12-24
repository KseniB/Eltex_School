#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

/*Структура контакта*/
typedef struct
{
    uint64_t num;
    char     f_name[128];
    char     l_name[128];
} item_t;

/*Структура списка*/
typedef struct node_s
{
    struct node_s *next;
    item_t        *data;
} node_t;

node_t *last_node(node_t *HEAD);
int add(node_t **HEAD, void   *data);
int del(node_t **HEAD, node_t *del_n);
node_t *find_by_num(node_t *HEAD, uint64_t num);
item_t *create_item(node_t **HEAD);
int remove_item(node_t **HEAD, item_t *del_i);
item_t *search_by_num(node_t *HEAD, uint64_t num);
void trashclean();
