#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <alloca.h>

struct Phonebook{
	char fname[15];
	char lname[15];
	unsigned long int num;
};

void Menu(){
    printf ("Select an action: \n");
    printf ("1. Add contact \n");
    printf ("2. Delete contact \n");
    printf ("3. Search for a contact \n");
    printf ("4. Display the entire list of contacts \n");
    printf ("5. Exit \n");
}


int main() {

	struct Phonebook *pb_list = malloc(sizeof(struct Phonebook));;
	int index = 0;
	int menu = 0;
	int menu2 = 0;
	char a[255];
	char str[255];
	int find = 0;
	int j = 0;
	unsigned long int numF = 0;
	do{
		system("clear");
		Menu();
		fgets(&a, 2, stdin);
		menu = atoi(&a);
		switch(menu){
		    
		    case 1:
			system("clear");
			printf("\tAdd contact\n----------------------------\n");
			for(int i  = 0; i < index; i++){
				if(pb_list[i].num == 0){
					printf("Enter first name:");
	                scanf("%s", pb_list[i].fname);
                    printf("Enter last name:");
	                scanf("%s", pb_list[i].lname);
	                printf("Enter Number: ");
	                scanf("%ld", &pb_list[i].num);
					break;
				}
					
				if(i == (index - 1)){
					pb_list = realloc(pb_list, (sizeof(struct Phonebook) * (index + 1)));
					printf("Enter first name:");
	                scanf("%s", pb_list[index].fname);
                    printf("Enter last name:");
	                scanf("%s", pb_list[index].lname);
	                printf("Enter Number: ");
	                scanf("%ld", &pb_list[index].num);
					index++;
					break;
				}
			}
			
			if(index == 0){
				index++;
				printf("Enter first name:");
	            scanf("%s", pb_list[0].fname);
                printf("Enter last name:");
	            scanf("%s", pb_list[0].lname);
	            printf("Enter Number: ");
	            scanf("%ld", &pb_list[0].num);
			}
			printf("Contact added\n----------------------------\n");
			printf("Press Enter to return to the menu\n");
			scanf("%c",&str);
            break;
            
            case 2:
		    system("clear");
			find = 0;
			printf("\tDelete contact\n----------------------------\n");
			printf("Enter Number:");
			unsigned long int x;
			scanf("%ld", &x);
			for(int i = 0; i < index; i++) {
                if(x == pb_list[i].num){
					j = i;
                    break;
                }
			}
			if(j == (index - 1)){
                pb_list = realloc(pb_list, sizeof(struct Phonebook) * (index - 1));
                index--;
            }else{
                for(int i = j; i < index - 1; i++) {
                    strcpy(pb_list[i].fname, pb_list[i + 1].fname);
                    strcpy(pb_list[i].lname, pb_list[i + 1].lname);
                    pb_list[i].num = pb_list[i + 1].num;
                }
                pb_list = realloc(pb_list, sizeof(struct Phonebook) * (index - 1));
				index--;
                }
            printf("Contact deleted\n----------------------------\n");
			printf("Press Enter to return to the menu\n");
			scanf("%c",&str);    
            break;
            
            case 3:
			system("clear");
            printf("\tContact search\n----------------------------\n");
			printf("Search by: \n");
            printf("1. First name \n");
            printf("2. Last name \n");
            printf("3. Number \n");
            getchar();
			fgets(&a, 2, stdin);
		    menu2 = atoi(&a);
			switch(menu2){
			    
			    case 1:
			    system("clear");
                printf("\tContact search\n----------------------------\n");
			    printf("Enter first name:");
			    *str = "";
			    scanf("%s", str);
			    for(int i = 0; i < index; i++){
				    if(strcmp(str, pb_list[i].fname) == 0){
					    find++;
					    printf("First name: %s\nLast name: %s\nNumber: %ld\n", pb_list[i].fname, pb_list[i].lname, pb_list[i].num);
				    }
			    }
			    if(find == 0) {
					printf("No one found\n"); 
				}else{
					find = 0;
				}
			    break;
			    
			    case 2:
			    system("clear");
                printf("\tContact search\n----------------------------\n");
			    printf("Enter last name:");
			    *str = "";
			    scanf("%s", str);
			    for(int i = 0; i < index; i++){
				    if(strcmp(str, pb_list[i].lname) == 0){
					    find++;
					    printf("First name: %s\nLast name: %s\nNumber: %ld\n", pb_list[i].fname, pb_list[i].lname, pb_list[i].num);
				    }
			    }
			    if(find == 0) {
					printf("No one found\n"); 
				}else{
					find = 0;
				}
			    break;
			    
			    case 3:
			    system("clear");
                printf("\tContact search\n----------------------------\n");
			    printf("Enter Number:");
			    scanf("%ld", &numF);
			    for(int i = 0; i < index; i++){
				    if(numF == pb_list[i].num){
					    find++;
					    printf("First name: %s\nLast name: %s\nNumber: %ld\n", pb_list[i].fname, pb_list[i].lname, pb_list[i].num);
				    }
			    }
			    if(find == 0) {
					printf("No one found\n"); 
				}else{
					find = 0;
				}
			    break;
			}	
			printf("Press Enter to return to the menu\n");
			scanf("%c", &str);
            break;
            
			case 4:
			system("clear");
			printf("\tСontact list\n----------------------------\n");
			for(int i = 0; i < index; i++) {
				if(pb_list[i].num != 0){
					printf("First name: %s\nLast name: %s\nNumber: %ld\n", pb_list[i].fname, pb_list[i].lname, pb_list[i].num);
					printf("----------------------------\n");
				}
			}
			printf("Press Enter to return to the menu\n");
			scanf("%c",&str);
			break;

			case 5:
			free(pb_list);
			_Exit(0);
			break;
			
			default:
			break;
		}
		scanf("%c",&a);
	}while(1);
}
