#include "node.h"

/*
    Вспомогательные методы
*/

node_t *last_node(node_t *HEAD)
{
    for(; HEAD && HEAD->next; HEAD = HEAD->next);
    return HEAD;
}

int add(node_t **HEAD, void   *data)
{
    node_t *last = NULL;
    node_t *new_node = calloc(1, sizeof(node_t));
    if(new_node == NULL)
    {
        return -1;
    }
    last = last_node(*HEAD);
    new_node->data = data;
    new_node->next = NULL;
    if (*HEAD == NULL)
    {
        *HEAD = new_node;
        return 0;
    }
    last->next = new_node;
    return 0;
}

int del(node_t **HEAD, node_t *del_n)
{
    node_t *prev_node = NULL;
    node_t *sought_node = *HEAD;
    if(HEAD == NULL)
    {
        return -1;
    }

    if(*HEAD == del_n)
    {
        *HEAD = sought_node->next;
        free(sought_node);
        sought_node = NULL;
        return 0;
    }

    while(sought_node != del_n)
    {
        if(sought_node->next == NULL)
        {
            return -2;
        }
        prev_node = sought_node;
        sought_node = sought_node->next;
    }
    prev_node->next = sought_node->next;
    free(sought_node);
    sought_node = NULL;
    return 0;
}

node_t *find_by_num(node_t *HEAD, uint64_t num)
{
    node_t *sought_node = HEAD;
    while(((item_t *)(sought_node->data))->num != num)
    {
        if(sought_node->next == NULL)
        {
            return NULL;
        }
        sought_node = sought_node->next;
    }
    return sought_node;
}

item_t *create_item(node_t **HEAD)
{
    item_t *new_item = calloc(1, sizeof(item_t));
    if (new_item == NULL)
    {
        return NULL;
    }
    if(add(HEAD, (item_t *)new_item) == -1)
    {
         return NULL;
    }
    return new_item;
}

int remove_item(node_t **HEAD, item_t *del_i)
{
    node_t *sought_node = *HEAD;
    while(((item_t *)(sought_node->data)) != del_i)
    {
        if(sought_node->next == NULL)
        {
            return -1;
        }
        sought_node = sought_node->next;
    }
    if(del(HEAD, sought_node) != 0)
    {
        return -2;
    }
    free(del_i);
    del_i = NULL;
    return 0;
}

item_t *search_by_num(node_t *HEAD, uint64_t num)
{
    node_t *sought_node = NULL;
    sought_node = find_by_num(HEAD, num);
    if(sought_node == NULL)
    {
        return NULL;
    }
    return sought_node->data;
}

void trashclean()
{
	while (getchar() != '\n');
}
