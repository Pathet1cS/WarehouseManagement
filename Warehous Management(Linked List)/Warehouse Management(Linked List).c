#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

#define BLK "\e[0;30m"
#define RED "\e[0;91m"
#define GRN "\e[0;92m"
#define YEL "\e[0;93m"
#define BLU "\e[0;94m"
#define PNK "\e[0;95m"
#define CYN "\e[0;96m"
#define WHT "\e[0;37m"
#define CRESET "\e[0m"


struct item {
	int id;
	char nama[50];
	int jumlah;
};

struct node{
	struct item item;
	struct node *next;
};

struct node *head = NULL;

void insert(int id, char nama[], int jumlah){
    struct node *ptr = head;

    while (ptr != NULL) {
        if (ptr->item.id == id) {
            printf(RED"Barang dengan ID: %d sudah ada di gudang\n"CRESET, id);
            return;
        }
        ptr = ptr->next;
    }	
	
	struct node *newNode = malloc(sizeof(struct node));
	newNode->item.id = id;
	strcpy(newNode->item.nama, nama);
	newNode->item.jumlah = jumlah;
	newNode->next = NULL;
	
	if(head == NULL){
		head = newNode;
	}
	
	else{
		newNode->next = head;
		head = newNode;	
	}
	printf("+------------------------------------------------------------------------------+\n");
    printf("|"GRN"                       Barang Berhasil Ditambahkan                            "CRESET"|\n");
    printf("+------------+----------------------------------------------------+------------+\n");
    printf("| "GRN"ID"CRESET"         | "GRN"Nama Barang"CRESET"                                        | "GRN"Jumlah     "CRESET"|\n");
    printf("+------------+----------------------------------------------------+------------+\n");
	printf("| "GRN"%-10d"CRESET" | "GRN"%-50s"CRESET" | "GRN"%-10d"CRESET" |\n",id, nama, jumlah);
	printf("+------------------------------------------------------------------------------+\n\n");

}

void displayItem(){
	struct node *ptr = head;
	
	printf("+------------------------------------------------------------------------------+\n");
    printf("|"GRN"                            Barang di Warehouse                               "CRESET"|\n");
    printf("+------------+----------------------------------------------------+------------+\n");
    printf("| "GRN"ID"CRESET"         | "GRN"Nama Barang"CRESET"                                        | "GRN"Jumlah     "CRESET"|\n");
    printf("+------------+----------------------------------------------------+------------+\n");
	while(ptr != NULL){
		printf("| ");
		printf(GRN"%-10d", ptr->item.id);
		printf(CRESET" | ");
		printf(GRN"%-50s", ptr->item.nama);
		printf(CRESET" | ");
		printf(GRN"%-10d", ptr->item.jumlah);
		printf(CRESET" |\n");
		ptr = ptr->next;
	}
	printf("+------------------------------------------------------------------------------+\n");
}

 void searchItem(int id){
	struct node *ptr = head;
	
	while(ptr != NULL){
		if(ptr->item.id == id){
			printf("+------------------------------------------------------------------------------+\n");
    		printf("|"GRN"                            Barang ditemukan                                  "CRESET"|\n");
    		printf("+------------+----------------------------------------------------+------------+\n");
    		printf("| "GRN"ID"CRESET"         | "GRN"Nama Barang"CRESET"                                        | "GRN"Jumlah     "CRESET"|\n");
    		printf("+------------+----------------------------------------------------+------------+\n");
			printf("| "GRN"%-10d"CRESET" | "GRN"%-50s"CRESET" | "GRN"%-10d"CRESET" |\n", ptr->item.id, ptr->item.nama, ptr->item.jumlah);
			printf("+------------------------------------------------------------------------------+\n\n");
			return;
		}
		ptr = ptr->next;
	}
	printf(RED"Barang dengan ID: %d tidak ditemukan\n"CRESET, id);
}

void updateItem(int id, char nama[], int jumlah){
	struct node *ptr = head;
	
	while(ptr != NULL){
		if(ptr->item.id == id){
		printf("+------------------------------------------------------------------------------+\n");
    	printf("|"GRN"                            Sebelum di Update                                 "CRESET"|\n");
    	printf("+------------+----------------------------------------------------+------------+\n");
    	printf("| "GRN"ID"CRESET"         | "GRN"Nama Barang"CRESET"                                        | "GRN"Jumlah     "CRESET"|\n");
    	printf("+------------+----------------------------------------------------+------------+\n");
		printf("| "GRN"%-10d"CRESET" | "GRN"%-50s"CRESET" | "GRN"%-10d"CRESET" |\n", ptr->item.id, ptr->item.nama, ptr->item.jumlah);
		printf("+------------------------------------------------------------------------------+\n\n");
			ptr->item.id = id;
			strcpy(ptr->item.nama, nama);
			ptr->item.jumlah = jumlah;
		printf("+------------------------------------------------------------------------------+\n");
    	printf("|"GRN"                            Sesudah di Update                                 "CRESET"|\n");
    	printf("+------------+----------------------------------------------------+------------+\n");
    	printf("| "GRN"ID"CRESET"         | "GRN"Nama Barang"CRESET"                                        | "GRN"Jumlah     "CRESET"|\n");
    	printf("+------------+----------------------------------------------------+------------+\n");
		printf("| "GRN"%-10d"CRESET" | "GRN"%-50s"CRESET" | "GRN"%-10d"CRESET" |\n", ptr->item.id, ptr->item.nama, ptr->item.jumlah);
		printf("+------------------------------------------------------------------------------+\n\n");
			return;
		}
		ptr = ptr->next;
	}
	printf(RED"Barang dengan ID: %d tidak ditemukan\n"CRESET, id);	
}

void deleteItem(int id){
	struct node *ptr = head;
	struct node *prev = NULL;
	
	while(ptr != NULL && ptr->item.id != id){
		prev = ptr;
		ptr = ptr->next;
	}
	
	if(ptr == NULL){
		printf(RED"Barang dengan ID: %d tidak ditemukan\n"CRESET, id);
		return;
	}
	else if(prev == NULL){
		head = ptr->next;
	}
	else{
		prev->next = ptr->next;
	}
	
	free(ptr);
	printf(RED"Barang dengan ID: %d berhasil dihapus\n"CRESET, id);
	
}

void loadFile(){
	FILE *fp = fopen("warehouse.txt", "r");
	
	if(fp == NULL){
		printf("File tidak ditemukan\n");
		return;
	}
	
	int id, jumlah;
	char nama[50];
	
	while(fscanf(fp, "%d#%[^#]#%d\n", &id, nama, &jumlah) == 3){
		insert(id, nama, jumlah);
	}
	fclose(fp);
}

void saveFile(){
	FILE *fp = fopen("warehouse.txt", "w");
	
	if(fp == NULL){
		printf("File tidak ditemukan\n");
		return;
	}
	
	struct node *ptr = head;
	while(ptr != NULL){
		fprintf(fp, "%d#%s#%d\n", ptr->item.id, ptr->item.nama, ptr->item.jumlah);
		ptr = ptr->next;
	}
	
	fclose(fp);
}

void displayMenu(int selected) {
	int i;
	
	system("cls");
	printf(GRN);
    printf("+______________________________________________________________+ \n");
    printf("|   ______                  __                         __      | \n");
    printf("|  /   __ |                |  |                       |  |     | \n");
    printf("| |  /                     |  |                       |  |     | \n");
    printf("| |  , ___   __   __     _ |  |    ___ __   __  ___   |  |___  | \n");
    printf("| |   /   | |  | |  |  /  _   |  /  __'  \\ |  '__  \\  |  /  /  | \n");
    printf("| |   \\_  | |  |_|  | |  |_|  | |  |__|  | |  |  |  | |     \\  | \n");
    printf("|  \\ ____ /  \\ _ ,__|  \\ __,__|  \\ ___,__| |__,  |__| |__|\\__\\ | \n");
    printf("+______________________________________________________________+ \n");
	printf(CRESET);

	const char *menuItems[] = {
		"1. Input Barang",
		"2. Update Barang",
		"3. Delete Barang",
		"4. Display Barang",
		"5. Cari Barang",
		"6. Save and Exit"
	};

	for (i = 0; i < 6; i++) {
		if (i == selected) {
			printf(GRN">>");
			printf(YEL" %s ", menuItems[i]);
			printf(GRN"<<\n");
			printf(CRESET);
		} else {
			printf("  %s\n", menuItems[i]);
		}
	}
}

void returnToMenu(){
	printf("Tekan enter untuk kembali ke menu...\n");
	getch();
}

int main(){
	int choice = 0;
	int id, jumlah;
	char nama[50];
	
	loadFile();
	system("cls");

	displayMenu(choice);

	int key;
	while (1) {
		key = _getch();

		if (key == 224) { // Special keys (arrows, function keys, etc.)
			key = _getch();
			switch (key) {
				case 72: // Up arrow
					choice = (choice == 0) ? 5 : choice - 1;
					break;
				case 80: // Down arrow
					choice = (choice == 5) ? 0 : choice + 1;
					break;
			}
			displayMenu(choice);
		} else if (key == 13) { // Enter key
			switch (choice) {
				case 0:
					system("cls");
					printf("==========="GRN" Input Barang "CRESET"==========\n");
					printf(GRN"Masukkan ID Barang: ");
					scanf("%d", &id); getchar();
					printf("Masukkan Nama Barang: ");
					scanf("%[^\n]", nama);
					printf("Masukkan Jumlah Barang: ");
					scanf("%d", &jumlah);
					printf("====================================\n");
					printf(CRESET);
					system("cls");
					insert(id, nama, jumlah);
					returnToMenu();
					break;
				
				case 1:
					system("cls");
					printf("========== "GRN"Update Barang"CRESET" ==========\n");
					printf(GRN"Masukkan ID Barang: ");
					scanf("%d", &id); getchar();
					printf("Masukkan Nama Barang: ");
					scanf("%[^\n]", nama);
					printf("Masukkan Jumlah Barang: ");
					scanf("%d", &jumlah);
					printf("==================================\n");
					printf(CRESET);
					system("cls");
					updateItem(id, nama, jumlah);
					returnToMenu();
					break;
				
				case 2:
					system("cls");
					printf("=========== "GRN"Delete Barang"CRESET" ===========\n");
					printf(GRN"Masukkan ID Barang: ");
					scanf("%d", &id);
					printf("=====================================\n");
					system("cls");
					deleteItem(id);
					returnToMenu();
					printf(CRESET);
					break;
				
				case 3:
					system("cls");
					displayItem();
					returnToMenu();
					break;
				
				case 4:
					system("cls");
					printf("========== "GRN"Cari Barang"CRESET" ===========\n");
					printf(GRN"Masukkan ID Barang: ");
					scanf("%d", &id);
					printf("=========================\n");
					printf(CRESET);
					system("cls");
					searchItem(id);
					returnToMenu();
					break;
				
				case 5:
					system("cls");
					printf(GRN"Saving and Exit\n");
					saveFile();
					printf(CRESET);
					exit(0);
			}
			displayMenu(choice);
		}
	}
	return 0;
}

