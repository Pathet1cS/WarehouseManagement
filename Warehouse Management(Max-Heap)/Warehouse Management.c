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

#define MAX_ITEMS 100 

struct item {
    int id;
    char nama[50];
    int jumlah;
};

struct maxHeap {
    struct item items[MAX_ITEMS];
    int size;
};

struct maxHeap heap = { .size = 0 };

int i;

const char *filename = "warehouse.txt";

void heapifyUp(int index) {
    int parent = (index - 1) / 2;
    if (index && heap.items[index].id > heap.items[parent].id) {
        struct item temp = heap.items[index];
        heap.items[index] = heap.items[parent];
        heap.items[parent] = temp;
        heapifyUp(parent);
    }
}

void heapifyDown(int index) {
    int largest = index;
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;

    if (leftChild < heap.size && heap.items[leftChild].id > heap.items[largest].id) {
        largest = leftChild;
    }

    if (rightChild < heap.size && heap.items[rightChild].id > heap.items[largest].id) {
        largest = rightChild;
    }

    if (largest != index) {
        struct item temp = heap.items[index];
        heap.items[index] = heap.items[largest];
        heap.items[largest] = temp;
        heapifyDown(largest);
    }
}

void insert(int id, char nama[], int jumlah) {
	int i;
    if (heap.size == MAX_ITEMS) {
        printf(RED"Warehouse sudah penuh!!\n"CRESET);
        return;
    }

    for (i = 0; i < heap.size; i++) {
        if (heap.items[i].id == id) {
            printf(RED"Barang dengan ID: %d sudah ada di gudang\n"CRESET, id);
            return;
        }
    }

    struct item newItem = { .id = id, .nama = "", .jumlah = jumlah };
    strcpy(newItem.nama, nama);
    heap.items[heap.size] = newItem;
    heapifyUp(heap.size);
    heap.size++;

    printf("+------------------------------------------------------------------------------+\n");
    printf("|"GRN"                       Barang Berhasil Ditambahkan                            "CRESET"|\n");
    printf("+------------+----------------------------------------------------+------------+\n");
    printf("| "GRN"ID"CRESET"         | "GRN"Nama Barang"CRESET"                                        | "GRN"Jumlah     "CRESET"|\n");
    printf("+------------+----------------------------------------------------+------------+\n");
    printf("| "GRN"%-10d"CRESET" | "GRN"%-50s"CRESET" | "GRN"%-10d"CRESET" |\n", id, nama, jumlah);
    printf("+------------------------------------------------------------------------------+\n\n");
}

void displayItem() {
	int i;
    if (heap.size == 0) {
        printf("No items in the inventory.\n");
        return;
    }

    printf("+------------------------------------------------------------------------------+\n");
    printf("|"GRN"                            Barang di Warehouse                               "CRESET"|\n");
    printf("+------------+----------------------------------------------------+------------+\n");
    printf("| "GRN"ID"CRESET"         | "GRN"Nama Barang"CRESET"                                        | "GRN"Jumlah     "CRESET"|\n");
    printf("+------------+----------------------------------------------------+------------+\n");
    for (i = 0; i < heap.size; i++) {
        printf("| "GRN"%-10d"CRESET" | "GRN"%-50s"CRESET" | "GRN"%-10d"CRESET" |\n", heap.items[i].id, heap.items[i].nama, heap.items[i].jumlah);
    }
    printf("+------------------------------------------------------------------------------+\n");
}

void searchItem(int id) {
    for (i = 0; i < heap.size; i++) {
        if (heap.items[i].id == id) {
            printf("+------------------------------------------------------------------------------+\n");
            printf("|"GRN"                            Barang ditemukan                                  "CRESET"|\n");
            printf("+------------+----------------------------------------------------+------------+\n");
            printf("| "GRN"ID"CRESET"         | "GRN"Nama Barang"CRESET"                                        | "GRN"Jumlah     "CRESET"|\n");
            printf("+------------+----------------------------------------------------+------------+\n");
            printf("| "GRN"%-10d"CRESET" | "GRN"%-50s"CRESET" | "GRN"%-10d"CRESET" |\n", heap.items[i].id, heap.items[i].nama, heap.items[i].jumlah);
            printf("+------------------------------------------------------------------------------+\n\n");
            return;
        }
    }
    printf(RED"Barang dengan ID: %d tidak ditemukan\n"CRESET, id);
}

void updateItem(int id, char nama[], int jumlah) {
    for (i = 0; i < heap.size; i++) {
        if (heap.items[i].id == id) {
            printf("+------------------------------------------------------------------------------+\n");
            printf("|"GRN"                            Sebelum di Update                                 "CRESET"|\n");
            printf("+------------+----------------------------------------------------+------------+\n");
            printf("| "GRN"ID"CRESET"         | "GRN"Nama Barang"CRESET"                                        | "GRN"Jumlah     "CRESET"|\n");
            printf("+------------+----------------------------------------------------+------------+\n");
            printf("| "GRN"%-10d"CRESET" | "GRN"%-50s"CRESET" | "GRN"%-10d"CRESET" |\n", heap.items[i].id, heap.items[i].nama, heap.items[i].jumlah);
            printf("+------------------------------------------------------------------------------+\n\n");

            strcpy(heap.items[i].nama, nama);
            heap.items[i].jumlah = jumlah;
            heapifyDown(i);
            heapifyUp(i);

            printf("+------------------------------------------------------------------------------+\n");
            printf("|"GRN"                            Sesudah di Update                                 "CRESET"|\n");
            printf("+------------+----------------------------------------------------+------------+\n");
            printf("| "GRN"ID"CRESET"         | "GRN"Nama Barang"CRESET"                                        | "GRN"Jumlah     "CRESET"|\n");
            printf("+------------+----------------------------------------------------+------------+\n");
            printf("| "GRN"%-10d"CRESET" | "GRN"%-50s"CRESET" | "GRN"%-10d"CRESET" |\n", heap.items[i].id, heap.items[i].nama, heap.items[i].jumlah);
            printf("+------------------------------------------------------------------------------+\n\n");
            return;
        }
    }
    printf(RED"Barang dengan ID: %d tidak ditemukan\n"CRESET, id);
}

void deleteItem(int id) {
    for (i = 0; i < heap.size; i++) {
        if (heap.items[i].id == id) {
            break;
        }
    }

    if (i == heap.size) {
        printf(RED"Barang dengan ID: %d tidak ditemukan\n"CRESET, id);
        return;
    }

    heap.items[i] = heap.items[--heap.size];
    heapifyDown(i);
    heapifyUp(i);

    printf(RED"Barang dengan ID: %d berhasil dihapus\n"CRESET, id);
}

void loadFile() {
    FILE *fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("File tidak ditemukan\n");
        return;
    }

    int id, jumlah;
    char nama[50];

    heap.size = 0;
    while (fscanf(fp, "%d#%[^#]#%d\n", &id, nama, &jumlah) == 3) {
        struct item newItem = { .id = id, .nama = "", .jumlah = jumlah };
        strcpy(newItem.nama, nama);
        heap.items[heap.size] = newItem;
        heapifyUp(heap.size);
        heap.size++;
    }
    fclose(fp);
}

void saveFile() {
    FILE *fp = fopen(filename, "w");

    if (fp == NULL) {
        printf("File tidak ditemukan\n");
        return;
    }

    for (i = 0; i < heap.size; i++) {
        fprintf(fp, "%d#%s#%d\n", heap.items[i].id, heap.items[i].nama, heap.items[i].jumlah);
    }

    fclose(fp);
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

void returnToMenu() {
    printf("Tekan enter untuk kembali ke menu...\n");
    getch();
}

int main() {
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

