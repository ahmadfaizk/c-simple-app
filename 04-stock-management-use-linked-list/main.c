#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Product {
    char code[255];
    char name[255];
    int stock;
    char createdAt[255];
    char updatedAt[255];
};

struct Node {
    struct Product *data;
    struct Node* next;
    struct Node* prev;
};

struct Node* head;

void insert();
void edit();
void display();
void delete();
struct Node * searchProductNode(char *value);
int compareString(char* a, char* b);
char * getCurrentTime();
int validateProductCode(char* code);

int main()
{
    int choice;
    printf("\t-= Aplikasi Manajemen Stok Produk =-\n");
    while (choice != 5) {
        printf("\nMenu Utama\n");
        printf("1. Tampilkan List Produk\n");
        printf("2. Buat Produk Baru\n");
        printf("3. Edit Produk\n");
        printf("4. Hapus Produk\n");
        printf("5. Keluar\n");
        printf("\nPilihan : ");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            display();
            break;
        case 2:
            insert();
            break;
        case 3:
            edit();
            break;
        case 4:
            delete();
            break;
        case 5:
            printf("Keluar\n");
            break;
        default:
            printf("Pilihan tidak tersedia\n");
            break;
        }
        printf("\n");
    }
    return 0;
}

void insert()
{
    char code[255];
    printf("\nTambah Produk Baru\n");
    printf("Input kode produk : ");
    scanf(" %[^\n]%*c", code);
    if (validateProductCode(code) == 0) {
        return;
    }
    struct Product* newProduct = (struct Product*)malloc(sizeof(struct Product));
    strcpy(newProduct->code, code);
    printf("Input nama produk : ");
    scanf(" %[^\n]%*c", newProduct->name);
    printf("Input stok produk : ");
    scanf(" %d", &newProduct->stock);
    if (newProduct->stock < 0) {
        printf("Error: Stok tidak boleh kurang dari 0\n");
        return;
    }
    char * currentTime = getCurrentTime();
    strcpy(newProduct->createdAt, currentTime);
    strcpy(newProduct->updatedAt, currentTime);
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = newProduct;
    temp->next = NULL;
    if (head == NULL) {
        temp->prev = NULL;
        head = temp;
        return;
    }
    struct Node* last = head;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = temp;
    temp->prev = last;
}

void delete()
{
    char code[255];
    printf("\nHapus Produk\n");
    printf("Input kode product yang akan dihapus : ");
    scanf(" %[^\n]%*c", code);
    struct Node* temp = searchProductNode(code);
    if (temp != NULL) {
        if (temp->prev == NULL) {
            head = temp->next;
            head->prev = NULL;
        } else if (temp->next == NULL) {
            temp->prev->next = NULL;
        } else {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }
        free(temp);
    } else {
        printf("Error: Data tidak ditemukan\n");
    }
}

void edit()
{
    char code[255];
    printf("\nEdit Produk\n");
    printf("Input kode produk yang akan diedit : ");
    scanf(" %[^\n]%*c", code);
    struct Node* temp = searchProductNode(code);
    if (temp != NULL) {
        int choice;
        while (choice != 5) {
            printf("\nEdit Menu\n");
            printf("1. Nama\n");
            printf("2. Tambah Stok\n");
            printf("3. Kurangi Stok\n");
            printf("4. Edit Stok\n");
            printf("5. Keluar\n");
            printf("Pilihan : ");
            scanf("%d", &choice);
            switch (choice) {
            case 1:
                printf("Input nama produk : ");
                scanf(" %[^\n]%*c", temp->data->name);
                strcpy(temp->data->updatedAt, getCurrentTime());
                break;
            case 2:
                printf("Input jumlah stok yang ditambah : ");
                int stock;
                scanf(" %d", &stock);
                temp->data->stock += stock;
                strcpy(temp->data->updatedAt, getCurrentTime());
                break;
            case 3:
                printf("Input jumlah stok yang dikurangi : ");
                scanf(" %d", &stock);
                if (temp->data->stock < stock) {
                    printf("Error: Stok tidak cukup\n");
                    break;
                }
                temp->data->stock -= stock;
                strcpy(temp->data->updatedAt, getCurrentTime());
                break;
            case 4:
                printf("Input stok produk : ");
                scanf(" %d", &temp->data->stock);
                strcpy(temp->data->updatedAt, getCurrentTime());
                break;
            case 5:
                printf("Keluar\n");
                break;
            default:
                printf("Pilihan tidak tersedia\n");
                break;
            }
        }
    } else {
        printf("Error: Data tidak ditemukan\n");
    }
}

void display()
{
    struct Node* temp = head;
    printf("\nList Produk\n");
    if (temp == NULL) {
        printf("Kosong\n");
        return;
    }
    printf("%-10s %-15s %-5s %-20s %-20s\n", "Kode", "Nama", "Stok", "Created At", "Updated At");
    while (temp != NULL) {
        printf("%-10s %-15s %-5d %-20s %-20s\n", temp->data->code, temp->data->name, temp->data->stock, temp->data->createdAt, temp->data->updatedAt);
        temp = temp->next;
    }
}

struct Node * searchProductNode(char* value)
{
    struct Node* temp = head;
    while (temp != NULL) {
        int isSame = compareString(temp->data->code, value);
        if (isSame == 1) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

int compareString(char* a, char* b)
{
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) {
            return 0;
        }
        i++;
    }
    return 1;
}

char * getCurrentTime()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    char *time = (char *)malloc(sizeof(char) * 255);
    sprintf(time, "%d-%d-%d %d:%d:%d", tm.tm_year + 1900, tm.tm_mon + 1,
        tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    return time;
}

int validateProductCode(char* code)
{
    struct Node* temp = searchProductNode(code);
    if (temp != NULL) {
        printf("Error: Kode produk sudah digunakan\n");
        return 0;
    }
    int i = 0;
    while (code[i] != '\0') {
        if (code[i] == ' ') {
            printf("Error: Kode produk tidak boleh mengandung spasi\n");
            return 0;
        }
        i++;
    }
    return 1;
}