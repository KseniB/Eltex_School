#include "menu.h"

/*
    Методы функций меню
*/

int list_contact(node_t *HEAD)
{
	system("clear");
	printf("\tСontact list\n----------------------------\n");
	for(node_t *n = HEAD; n; n = n->next)
	{
		item_t *i = n->data;
		printf("First name: %s\nLast name: %s\nNumber: %ld\n", 
		    i->f_name, i->l_name, i->num);
		puts("----------------------------");
	}
	puts("\nPress Enter to return to the menu");
	getchar();

	return 0;
}

int add_contact(node_t *HEAD)
{
	uint64_t num;
    char     f_name[128];
    char     l_name[128];
    
    system("clear");
	printf("\tAdd contact\n----------------------------\n");
	printf("Enter Number: ");
	if (1 != scanf("%ld", &num))
	{
		trashclean();
		system("clear");
		fprintf(stderr, "Invalid input");
    	puts("\nPress Enter to return to the menu");
	    getchar();

		return -1;
	}

	item_t *i = search_by_num(HEAD, num);
	if (i != NULL)
	{
		system("clear");
		fprintf(stderr, "This Number: %ld is already on the list\n", num);
	    puts("\nPress Enter to return to the menu");
	    getchar();

		return -1;
	}
	else
	{
		i = create_item(&HEAD);

		i->num = num;

		printf("Enter first name: ");
		scanf("%s", f_name);
		trashclean();
		strncpy(i->f_name, f_name, sizeof(i->f_name));

		printf("Enter last name: ");
		scanf("%s", l_name);
		trashclean();
		strncpy(i->l_name, l_name, sizeof(i->l_name));

		puts("\nProduct added successfully.");
		puts("Press Enter to return to the menu");
	}

	return 0;
}

int del_contact(node_t *HEAD)
{
	uint64_t num;

    system("clear");
    printf("\tDelete contact\n----------------------------\n");
    printf("Enter Number: ");
	if (1 != scanf("%ld", &num))
	{
		trashclean();
		system("clear");
		fprintf(stderr, "Invalid input");
		puts("\nPress Enter to return to the menu");
	    getchar();

		return -1;
	}
	
	item_t * i = search_by_num(HEAD, num);
	if(i == NULL)
	{
	    system("clear");
	    fprintf (stderr, "This Number: %ld is not listed\n", num);
		puts("Press Enter to return to the menu");
	    getchar();
	    
	    return -1;
	}
	else
	{
		remove_item(&HEAD, i);
    	puts("\nThe product was removed successfully.");
    	puts("Press Enter to return to the menu");
    	getchar();
    	
    	return 0;
	}
}

int search_contact(node_t *HEAD)
{
	uint64_t num;
    
    system("clear");
    printf("\tContact search\n----------------------------\n");
    printf("Enter Number:");
	if (1 != scanf("%ld", &num))
	{
		trashclean();
		system("clear");
		fprintf(stderr, "Invalid input");
		puts("\nPress Enter to return to the menu");
	    getchar();

		return -1;
	}

	item_t *i = search_by_num(HEAD, num);
	if (i == NULL)
	{
		system("clear");
		fprintf(stderr, "This Number: %ld not found\n", num);
		puts("\nPress Enter to return to the menu");
	    getchar();

		return -1;
	}
	else
	{
	    system("clear");
    	printf("Number: %ld\n", i->num);
    	printf("First name: %s\n", i->f_name);
    	printf("Last name: %s\n", i->l_name);
    	puts("\nPress Enter to return to the menu");
		getchar();
	}
	return 0;
}

int exit_menu(node_t *HEAD)
{
    node_t *i = HEAD;
    for(; HEAD && HEAD->next; HEAD = HEAD->next)
    {
        remove_item(&HEAD, i->data);
    }
    return 0;
}

int loop_menu(node_t *HEAD)
{
    system("clear");
	puts("Select an action:");
    puts("1. Add contact");
    puts("2. Delete contact");
    puts("3. Search for a contact");
    puts("4. Display the entire list of contacts");
    puts("5. Exit");
    
    int menu;
	if (1 != scanf("%d", &menu))
	{
		trashclean();
		return -1;
	}
	
	if (menu == 1)
	{
		add_contact(HEAD);
	}
    else if (menu == 2)
    {
	    del_contact(HEAD);    
    }
    else if (menu == 3)    
    {
		search_contact(HEAD);
    }
    else if (menu == 4)    
	{
		list_contact(HEAD);
	}
    else if (menu == 5)
	{
	    exit_menu(HEAD);
	    system("clear");
        printf("Exiting the program...");
	    exit(0);
	}
	else
	{
	    return 0;
	}
	
	getchar();
	return 0;
}
