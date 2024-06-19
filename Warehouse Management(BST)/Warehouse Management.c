#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct item{
	int id;
	char nama[50];
	int jumlah;
};

struct node{
	struct item item;
	struct node *right;
	struct node *left;
};

#define BLK "\e[0;30m"
#define RED "\e[0;91m"
#define GRN "\e[0;92m"
#define YEL "\e[0;93m"
#define BLU "\e[0;94m"
#define PNK "\e[0;95m"
#define CYN "\e[0;96m"
#define WHT "\e[0;37m"
#define CRESET "\e[0m"

struct node *root = NULL;

void saveToFile(FILE *fp, struct node *node){
	if(node == NULL){
		return;
	}
	fprintf(fp, "%d#%s#%d\n", node->item.id, node->item.nama, node->item.jumlah);
	saveToFile(fp, node->left);
	saveToFile(fp, node->right);
}

void saveFile(){
	FILE *fp = fopen("warehouse.txt", "w");
	if(fp == NULL){
		printf("File tidak ditemukan!\n");
		return;
	}
	
	saveToFile(fp, root);
	fclose(fp);
}

struct node *insertBST(struct node *node, struct item item);

void loadFile(){
	FILE *fp = fopen("warehouse.txt", "r");
	
	if(fp == NULL){
		printf("File tidak ditemukan!\n");
		return;
	}
	
	int id, jumlah;
	char nama[50];
	
	while(fscanf(fp, "%d#%[^#]#%d", &id, nama, &jumlah) == 3){
		struct item item;
		item.id = id;
		strcpy(item.nama, nama);
		item.jumlah = jumlah;
		root = insertBST(root, item);
	}
	
	fclose(fp);
}

struct node *createNode(struct item item){
	struct node *newNode = malloc(sizeof(struct node));
	newNode->item = item;
	newNode->left = NULL;
	newNode->right = NULL;
	
	return newNode;
}

struct node *insertBST(struct node *node, struct item item){
	if(node == NULL){
		return createNode(item);
	}
	if(item.id == node->item.id){
		printf(RED"Barang dengan ID: %d sudah ada di gudang"CRESET, item.id);
	}
	else if(item.id < node->item.id){
		node->left = insertBST(node->left, item);
	}
	else{
		node->right = insertBST(node->right, item);
	}
	
	
	return node;
}

void insertItem(int id, char nama[], int jumlah){
	struct item item;
	item.id = id;
	strcpy(item.nama, nama);
	item.jumlah = jumlah;
	
	root = insertBST(root, item);
	
	printf("+------------------------------------------------------------------------------+\n");
    printf("|"GRN"                       Barang Berhasil Ditambahkan                            "CRESET"|\n");
    printf("+------------+----------------------------------------------------+------------+\n");
    printf("| "GRN"ID"CRESET"         | "GRN"Nama Barang"CRESET"                                        | "GRN"Jumlah     "CRESET"|\n");
    printf("+------------+----------------------------------------------------+------------+\n");
	printf("| "GRN"%-10d"CRESET" | "GRN"%-50s"CRESET" | "GRN"%-10d"CRESET" |\n",id, nama, jumlah);
	printf("+------------------------------------------------------------------------------+\n\n");
}


struct node *searchBST(struct node *node, int id){
	if(node == NULL || node->item.id == id){
		return node;
	}
	if(id < node->item.id){
		return searchBST(node->left, id);
	}
	return searchBST(node->right, id);
}

void searchItem(int id){
	struct node *node = searchBST(root, id);
	
	if(node != NULL){
		printf("+------------------------------------------------------------------------------+\n");
    	printf("|"GRN"                            Barang ditemukan                                  "CRESET"|\n");
    	printf("+------------+----------------------------------------------------+------------+\n");
    	printf("| "GRN"ID"CRESET"         | "GRN"Nama Barang"CRESET"                                        | "GRN"Jumlah     "CRESET"|\n");
    	printf("+------------+----------------------------------------------------+------------+\n");
		printf("| "GRN"%-10d"CRESET" | "GRN"%-50s"CRESET" | "GRN"%-10d"CRESET" |\n", node->item.id, node->item.nama, node->item.jumlah);
		printf("+------------------------------------------------------------------------------+\n\n");
	}
	else{
		printf(RED"Barang dengan ID: %d tidak ditemukan\n"CRESET, id);
	}
}

void displayItem(struct node *node){
	if(node == NULL){
		return;
	}
	printf("+------------------------------------------------------------------------------+\n");
    printf("|"GRN"                            Barang di Warehouse                               "CRESET"|\n");
    printf("+------------+----------------------------------------------------+------------+\n");
    printf("| "GRN"ID"CRESET"         | "GRN"Nama Barang"CRESET"                                        | "GRN"Jumlah     "CRESET"|\n");
    printf("+------------+----------------------------------------------------+------------+\n");
	displayItem(node->left);
	printf("| "GRN"%-10d"CRESET" | "GRN"%-50s"CRESET" | "GRN"%-10d"CRESET" |\n", node->item.id, node->item.nama, node->item.jumlah);
	displayItem(node->right);
	printf("+------------------------------------------------------------------------------+\n");
}

void updateItem(int id, char nama[], int jumlah){
	struct node *node = searchBST(root, id);
	if(node != NULL){
		printf("+------------------------------------------------------------------------------+\n");
    	printf("|"GRN"                            Sebelum di Update                                 "CRESET"|\n");
    	printf("+------------+----------------------------------------------------+------------+\n");
    	printf("| "GRN"ID"CRESET"         | "GRN"Nama Barang"CRESET"                                        | "GRN"Jumlah     "CRESET"|\n");
    	printf("+------------+----------------------------------------------------+------------+\n");
		printf("| "GRN"%-10d"CRESET" | "GRN"%-50s"CRESET" | "GRN"%-10d"CRESET" |\n", node->item.id, node->item.nama, node->item.jumlah);
		printf("+------------------------------------------------------------------------------+\n\n");
		node->item.id = id;
		strcpy(node->item.nama, nama);
		node->item.jumlah = jumlah;
		printf("+------------------------------------------------------------------------------+\n");
    	printf("|"GRN"                            Sesudah di Update                                 "CRESET"|\n");
    	printf("+------------+----------------------------------------------------+------------+\n");
    	printf("| "GRN"ID"CRESET"         | "GRN"Nama Barang"CRESET"                                        | "GRN"Jumlah     "CRESET"|\n");
    	printf("+------------+----------------------------------------------------+------------+\n");
		printf("| "GRN"%-10d"CRESET" | "GRN"%-50s"CRESET" | "GRN"%-10d"CRESET" |\n", node->item.id, node->item.nama, node->item.jumlah);
		printf("+------------------------------------------------------------------------------+\n\n");
	}
	else{
		printf(RED"Barang dengan ID: %d tidak ditemukan\n"CRESET, id);
	}
}

struct node *findMin(struct node *node){
	while(node->left != NULL){
		node = node->left;
	}
	return node;
}

struct node *deleteBST(struct node *node, int id){
	if(node == NULL){
		printf(RED"Barang tidak dengan ID: %d ditemukan\n"CRESET, id);
		return node;
	}
	else if(id < node->item.id){
		node->left = deleteBST(node->left, id);
	}
	else if(id > node->item.id){
		node->right = deleteBST(node->right, id);
	}
	else{
		if(node->left == NULL){
			struct node *temp = node->right;
			free(node);
			return temp;
		}
		else if(node->right == NULL){
			struct node *temp = node->left;
			free(node);
			return temp;
		}
		
		struct node *temp = findMin(node->right);
		node->item = temp->item;
		node->right = deleteBST(node->right, temp->item.id);
		
		printf(RED"Barang dengan ID: %d berhasil dihapus\n"CRESET, id);
	}
	return node;
}

void deleteItem(int id) {
    root = deleteBST(root, id);
}

void displayMenu(int selected) {
	int i;
	
	system("cls");
	printf("=======================================================\n");
	printf(GRN);
	printf(" _ _ _ _____ _____ _____ _____ _____ _____ _____ _____ \n");
	printf("| | | |  _  | __  |   __|  |  |     |  |  |   __|   __|\n");
	printf("| | | |     |    -|   __|     |  |  |  |  |__   |   __|\n");
	printf("|_____|__|__|__|__|_____|__|__|_____|_____|_____|_____|\n");
	printf(CRESET);
	printf("=======================================================\n");

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
			printf("   %s\n", menuItems[i]);
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
					printf("==========="GRN" Input Barang "CRESET"===========\n");
					printf(GRN"Masukkan ID Barang: ");
					scanf("%d", &id); getchar();
					printf("Masukkan Nama Barang: ");
					scanf("%[^\n]", nama);
					printf("Masukkan Jumlah Barang: ");
					scanf("%d", &jumlah);
					printf("====================================\n");
					printf(CRESET);
					system("cls");
					insertItem(id, nama, jumlah);
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
					printf("====================================\n");
					printf(CRESET);
					system("cls");
					updateItem(id, nama, jumlah);
					returnToMenu();
					break;
				
				case 2:
					system("cls");
					printf("==========="GRN" Delete Barang "CRESET"===========\n");
					printf(GRN"Masukkan ID Barang: ");
					scanf("%d", &id);
					printf("=====================================\n");
					printf(CRESET);
					system("cls");
					deleteItem(id);
					returnToMenu();
					break;
				
				case 3:
					system("cls");
					displayItem(root);
					returnToMenu();
					break;
				
				case 4:
					system("cls");
					printf("==========="GRN" Cari Barang "CRESET"===========\n");
					printf(GRN"Masukkan ID Barang: ");
					scanf("%d", &id);
					printf("===================================\n");
					system("cls");
					printf(CRESET);
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

