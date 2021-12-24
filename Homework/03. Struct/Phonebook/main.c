#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

#include "node/node.h"
#include "menu/menu.h"

int main(){
    
    node_t * HEAD = NULL;
    int n = 15;

    /*Готовые контакты для примера работы*/
    item_t *first = create_item(&HEAD);
    first->num = 123;
    strncpy(first->f_name, "Qwe", n);
    strncpy(first->l_name, "Wer", n);

    item_t *second = create_item(&HEAD);
    second->num = 234;
    strncpy(second->f_name, "Ert", n);
    strncpy(second->l_name, "Rty", n);

    item_t *third = create_item(&HEAD);
    third->num = 345;
    strncpy(third->f_name, "Tyu", n);
    strncpy(third->l_name, "Yui", n);
    
    do{
        loop_menu(HEAD);
    }while(1);
    
    return 0;
}
