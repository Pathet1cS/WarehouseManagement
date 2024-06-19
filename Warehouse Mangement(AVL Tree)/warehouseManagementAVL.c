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

struct tree {
    struct item Item;
    struct tree *left;
    struct tree *right;
    int height;
};

void saveNode(struct tree *node, FILE *fp) {
    if (node != NULL) {
        fprintf(fp, "%d#%s#%d\n", node->Item.id, node->Item.nama, node->Item.jumlah);
        saveNode(node->left, fp);
        saveNode(node->right, fp);
    }
}

void saveFile(struct tree *root) {
    FILE *fp = fopen("warehouse.txt", "w");
    if (fp == NULL) {
        printf("File tidak ditemukan!\n");
        return;
    }
    saveNode(root, fp);
    fclose(fp);
}

int treeHeight(struct tree *node) {
    if (node == NULL) {
        return 0;
    } else {
        return node->height;
    }
}

struct tree* RightRot(struct tree *y) {
    struct tree* x = y->left;
    struct tree* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(treeHeight(y->left), treeHeight(y->right)) + 1;
    x->height = max(treeHeight(x->left), treeHeight(x->right)) + 1;

    return x;
}

struct tree* LeftRot(struct tree *x) {
    struct tree* y = x->right;
    struct tree* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(treeHeight(x->left), treeHeight(x->right)) + 1;
    y->height = max(treeHeight(y->left), treeHeight(y->right)) + 1;

    return y;
}

int balanceF(struct tree *node) {
    if (node == NULL) {
        return 0;
    } else {
        return treeHeight(node->left) - treeHeight(node->right);
    }
}

struct tree* inputItem(struct tree *node, struct item Item) {
    if (node == NULL) {
        struct tree* newNode = (struct tree*) malloc(sizeof(struct tree));
        newNode->Item = Item;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->height = 1;
        return newNode;
    }

    if (Item.id > node->Item.id) {
        node->right = inputItem(node->right, Item);
    } else if (Item.id < node->Item.id) {
        node->left = inputItem(node->left, Item);
    } else {
        printf(RED"Barang dengan ID: %d sudah ada di gudang\n"CRESET, Item.id);
        return node;
    }

    node->height = 1 + max(treeHeight(node->left), treeHeight(node->right));
    int balance = balanceF(node);

    if (balance > 1 && Item.id < node->left->Item.id) {
        return RightRot(node);
    }
    if (balance < -1 && Item.id > node->right->Item.id) {
        return LeftRot(node);
    }
    if (balance > 1 && Item.id > node->left->Item.id) {
        node->left = LeftRot(node->left);
        return RightRot(node);
    }
    if (balance < -1 && Item.id < node->right->Item.id) {
        node->right = RightRot(node->right);
        return LeftRot(node);
    }
    printf("+------------------------------------------------------------------------------+\n");
    printf("|"GRN"                       Barang Berhasil Ditambahkan                            "CRESET"|\n");
    printf("+------------+----------------------------------------------------+------------+\n");
    printf("| "GRN"ID"CRESET"         | "GRN"Nama Barang"CRESET"                                        | "GRN"Jumlah     "CRESET"|\n");
    printf("+------------+----------------------------------------------------+------------+\n");
    printf("| "GRN"%-10d"CRESET" | "GRN"%-50s"CRESET" | "GRN"%-10d"CRESET" |\n", Item.id, Item.nama, Item.jumlah);
    printf("+------------------------------------------------------------------------------+\n\n");
    return node;
}

void traversal(struct tree *root) {
    if (root != NULL) {
        traversal(root->left);
        printf("| "GRN"%-10d"CRESET" | "GRN"%-50s"CRESET" | "GRN"%-10d"CRESET" |\n", root->Item.id, root->Item.nama, root->Item.jumlah);
        traversal(root->right);
    }
}

struct tree* searchid(struct tree *node, int id) {
    if (node == NULL || node->Item.id == id) {
        return node;
    }
    if (node->Item.id < id) {
        return searchid(node->right, id);
    }
    return searchid(node->left, id);
}

struct tree* searchName(struct tree *node, const char *nama) {
    if (node == NULL || strcmp(node->Item.nama, nama) == 0) {
        return node;
    }
    if (strcmp(nama, node->Item.nama) > 0) {
        return searchName(node->right, nama);
    }
    return searchName(node->left, nama);
}

void updateItem(struct tree *root, int id, char* nama, int jumlah) {
    struct tree* node = searchid(root, id);
    if (node != NULL) {
        printf("+------------------------------------------------------------------------------+\n");
        printf("|"GRN"                            Sebelum di Update                                 "CRESET"|\n");
        printf("+------------+----------------------------------------------------+------------+\n");
        printf("| "GRN"ID"CRESET"         | "GRN"Nama Barang"CRESET"                                        | "GRN"Jumlah     "CRESET"|\n");
        printf("+------------+----------------------------------------------------+------------+\n");
        printf("| "GRN"%-10d"CRESET" | "GRN"%-50s"CRESET" | "GRN"%-10d"CRESET" |\n", node->Item.id, node->Item.nama, node->Item.jumlah);
        printf("+------------------------------------------------------------------------------+\n\n");
        node->Item.id = id;
		node->Item.jumlah = jumlah;
        strcpy(node->Item.nama, nama);
        printf("+------------------------------------------------------------------------------+\n");
        printf("|"GRN"                            Sesudah di Update                                 "CRESET"|\n");
        printf("+------------+----------------------------------------------------+------------+\n");
        printf("| "GRN"%-10d"CRESET" | "GRN"%-50s"CRESET" | "GRN"%-10d"CRESET" |\n", node->Item.id, node->Item.nama, node->Item.jumlah);
        printf("+------------------------------------------------------------------------------+\n\n");
    } else {
        printf(RED"Barang tidak dapat ditemukan.\nPeriksa kembali ID yang dimasukkan.\n"CRESET);
    }
}

struct tree* maxValue(struct tree *node) {
    struct tree* curr = node;
    while (curr->right != NULL) {
        curr = curr->right;
    }
    return curr;
}

struct tree* takeItem(struct tree *root, int id) {
    if (root == NULL) {
        return root;
    }

    if (id < root->Item.id) {
        root->left = takeItem(root->left, id);
    } else if (id > root->Item.id) {
        root->right = takeItem(root->right, id);
    } else {
        if ((root->left == NULL) || (root->right == NULL)) {
            struct tree* temp;
            if (root->left != NULL) {
                temp = root->left;
            } else {
                temp = root->right;
            }

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
        } else {
            struct tree* temp = maxValue(root->left);
            root->Item = temp->Item;
            root->left = takeItem(root->left, temp->Item.id);
        }
    }

    if (root == NULL) {
        return root;
    }

    root->height = max(treeHeight(root->left), treeHeight(root->right)) + 1;
    int balance = balanceF(root);

    if (balance > 1 && balanceF(root->left) >= 0) {
        return RightRot(root);
    }
    if (balance < -1 && balanceF(root->right) <= 0) {
        return LeftRot(root);
    }
    if (balance > 1 && balanceF(root->left) < 0) {
        root->left = LeftRot(root->left);
        return RightRot(root);
    }
    if (balance < -1 && balanceF(root->right) > 0) {
        root->right = RightRot(root->right);
        return LeftRot(root);
    }
    return root;
}

void deleteItem(struct tree **root, int id) {
    struct tree* item = searchid(*root, id);
    if (item != NULL) {
        printf("+------------------------------------------------------------------------------+\n");
        printf("|"RED"                       Barang Berhasil Dihapus                                 "CRESET"|\n");
        printf("+------------+----------------------------------------------------+------------+\n");
        printf("| "RED"ID"CRESET"         | "RED"Nama Barang"CRESET"                                        | "RED"Jumlah     "CRESET"|\n");
        printf("+------------+----------------------------------------------------+------------+\n");
        printf("| "RED"%-10d"CRESET" | "RED"%-50s"CRESET" | "RED"%-10d"CRESET" |\n", item->Item.id, item->Item.nama, item->Item.jumlah);
        printf("+------------------------------------------------------------------------------+\n\n");
        *root = takeItem(*root, id);
    } else {
        printf(RED"Barang tidak ditemukan.\n"CRESET);
    }
}

void displayAllItems(struct tree *root) {
    if (root != NULL) {
        printf("+------------------------------------------------------------------------------+\n");
        printf("|"GRN"                            Daftar Barang di Gudang                           "CRESET"|\n");
        printf("+------------+----------------------------------------------------+------------+\n");
        printf("| "GRN"ID"CRESET"         | "GRN"Nama Barang"CRESET"                                        | "GRN"Jumlah     "CRESET"|\n");
        printf("+------------+----------------------------------------------------+------------+\n");
        traversal(root);
        printf("+------------+----------------------------------------------------+------------+\n");
    } else {
        printf(RED"Gudang kosong.\n"CRESET);
    }
}

void displayItem(struct tree *node) {
    if (node != NULL) {
        printf("+------------------------------------------------------------------------------+\n");
        printf("|"GRN"                              Barang Ditemukan                                "CRESET"|\n");
        printf("+------------+----------------------------------------------------+------------+\n");
        printf("| "GRN"ID"CRESET"         | "GRN"Nama Barang"CRESET"                                        | "GRN"Jumlah     "CRESET"|\n");
        printf("+------------+----------------------------------------------------+------------+\n");
        printf("| "GRN"%-10d"CRESET" | "GRN"%-50s"CRESET" | "GRN"%-10d"CRESET" |\n", node->Item.id, node->Item.nama, node->Item.jumlah);
        printf("+------------------------------------------------------------------------------+\n\n");
    } else {
        printf(RED"Barang tidak ditemukan.\n"CRESET);
    }
}

void loadData(struct tree **root) {
    FILE *fp = fopen("warehouse.txt", "r");

    if (fp == NULL) {
        printf("File tidak ditemukan!");
        return;
    }

    int id, jumlah;
    char nama[50];

    while (fscanf(fp, "%d#%[^#]#%d", &id, nama, &jumlah) == 3) {
        struct item newItem;
        newItem.id = id;
        newItem.jumlah = jumlah;
        strcpy(newItem.nama, nama);
        *root = inputItem(*root, newItem);
    }
    fclose(fp);
}


void displayMenu(int selected){

	int i;
	
	system("cls");
	printf(GRN);
    printf("+--------------------------------------------------------------+ \n");
    printf("|   ______                  __                         __      | \n");
    printf("|  /   __ |                |  |                       |  |     | \n");
    printf("| |  /                     |  |                       |  |     | \n");
    printf("| |  , ___   __   __     _ |  |    ___ __   __  ___   |  |___  | \n");
    printf("| |   /   | |  | |  |  /  _   |  /  __'  \\ |  '__  \\  |  /  /  | \n");
    printf("| |   \\_  | |  |_|  | |  |_|  | |  |__|  | |  |  |  | |     \\  | \n");
    printf("|  \\ ____ /  \\ _ ,__|  \\ __,__|  \\ ___,__| |__,  |__| |__|\\__\\ | \n");
    printf("+--------------------------------------------------------------+ \n");
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

void searchItem(struct tree *node, int id){
	struct tree *found = searchid(node, id);
	displayItem(node);
}

int main() {
    struct tree* root = NULL;
    struct item newItem;
    loadData(&root);
    int id, jumlah;
    char nama[50];
    int choice = 0;
    
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
					scanf("%d", &newItem.id); getchar();
					printf("Masukkan Nama Barang: ");
					scanf("%[^\n]", newItem.nama);
					printf("Masukkan Jumlah Barang: ");
					scanf("%d", &newItem.jumlah);
					printf("====================================\n");
					printf(CRESET);
					system("cls");
					inputItem(root, newItem);
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
					updateItem(root, id, nama, jumlah);
					returnToMenu();
					break;
				
				case 2:
					system("cls");
					printf("=========== "GRN"Delete Barang"CRESET" ===========\n");
					printf(GRN"Masukkan ID Barang: ");
					scanf("%d", &id);
					printf("=====================================\n");
					system("cls");
					deleteItem(&root, id);
					returnToMenu();
					printf(CRESET);
					break;
				
				case 3:
					system("cls");
					displayAllItems(root);
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
					searchItem(root, id);
					returnToMenu();
					break;
				
				case 5:
					system("cls");
					printf(GRN"Saving and Exit\n");
					saveFile(root);
					printf(CRESET);
					exit(0);
			}
			displayMenu(choice);
		}
	}
	return 0;
}

