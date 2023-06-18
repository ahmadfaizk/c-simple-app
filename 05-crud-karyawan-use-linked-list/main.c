#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Employee {
    int id;
    char name[35];
    char birthPlace[35];
    char birthDate[15];
    char position[55];
};

struct Node {
    struct Employee *data;
    struct Node* next;
};

int maxData = 5;
struct Node* head;

void insert();
void edit();
void display();
void delete();
void deleteAll();
void sortByID();
struct Node * searchEmployeeNode(int id);
int getLength();
int validateDate(char* date);

int main()
{
    printf("\t-= Aplikasi Manajemen Karyawan =-\n");
    int choice;
    while (choice != 6) {
        printf("\nMenu Utama\n");
        printf("1. Tampilkan List Karyawan\n");
        printf("2. Tambah Karyawan\n");
        printf("3. Edit Karyawan\n");
        printf("4. Hapus Karyawan\n");
        printf("5. Hapus Semua Karyawan\n");
        printf("6. Keluar\n");
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
            deleteAll();
            break;
        case 6:
            printf("Keluar\n");
            break;
        default:
            printf("Pilihan tidak tersedia\n");
            break;
        }
    }
    return 0;
}

void insert()
{
    int id;
    char name[35], birthPlace[35], birthDate[15], position[55];
    printf("\nTambah Karyawan\n");
    if (getLength() >= maxData) {
        printf("Data Karyawan sudah penuh\n");
        return;
    }
    printf("Input ID Karwayan : ");
    scanf("%d", &id);
    if (id > 99999 || id < 1) {
        printf("ID Karyawan harus 1-99999\n");
        return;
    }
    if (searchEmployeeNode(id) != NULL) {
        printf("ID Karyawan sudah dipakai\n");
        return;
    }
    printf("Input Nama Karyawan : ");
    scanf(" %[^\n]", name);
    if (strlen(name) > 30) {
        printf("Nama Karyawan maksimal 30 karakter\n");
        return;
    }
    printf("Input Tempat Lahir Karyawan : ");
    scanf(" %[^\n]", birthPlace);
    if (strlen(birthPlace) > 30) {
        printf("Tempat Lahir Karyawan maksimal 30 karakter\n");
        return;
    }
    printf("Input Tanggal Lahir Karyawan (dd-mm-yyyy) : ");
    scanf(" %[^\n]", birthDate);
    if (validateDate(birthDate) == 0) {
        printf("Format tanggal salah\n");
        return;
    }
    printf("Input Jabatan Karyawan : ");
    scanf(" %[^\n]", position);
    if (strlen(position) > 50) {
        printf("Jabatan Karyawan maksimal 50 karakter\n");
        return;
    }
    struct Employee *employee = (struct Employee*)malloc(sizeof(struct Employee));
    employee->id = id;
    strcpy(employee->name, name);
    strcpy(employee->birthPlace, birthPlace);
    strcpy(employee->birthDate, birthDate);
    strcpy(employee->position, position);
    struct Node *node = (struct Node*)malloc(sizeof(struct Node));
    node->data = employee;
    node->next = NULL;
    if (head == NULL) {
        head = node;
    } else {
        struct Node *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = node;
    }
}

void edit()
{
    int id;
    printf("\nEdit Karyawan\n");
    printf("Input ID Karwayan : ");
    scanf("%d", &id);
    struct Node *node = searchEmployeeNode(id);
    if (node == NULL) {
        printf("ID Karyawan tidak ditemukan\n");
        return;
    }
    int choice;
    while (choice != 5) {
        char text[60];
        printf("\nMenu Edit\n");
        printf("1. Nama\n");
        printf("2. Tanggal Lahir\n");
        printf("3. Tempat Lahir\n");
        printf("4. Jabatan\n");
        printf("5. Kembali\n");
        printf("\nPilihan : ");
        scanf("%d", &choice);
        switch (choice) {
        case 1:
            printf("Nama Karyawan : %s\n", node->data->name);
            printf("Input Nama Karyawan : ");
            scanf(" %[^\n]", text);
            if (strlen(text) > 30) {
                printf("Nama Karyawan maksimal 30 karakter\n");
                break;
            }
            strcpy(node->data->name, text);
            break;
        case 2:
            printf("Tanggal Lahir Karyawan : %s\n", node->data->birthDate);
            printf("Input Tanggal Lahir Karyawan (dd-mm-yyyy) : ");
            scanf(" %[^\n]", text);
            if (validateDate(text) == 0) {
                printf("Format tanggal salah\n");
                break;
            }
            strcpy(node->data->birthDate, text);
            break;
        case 3:
            printf("Tempat Lahir Karyawan : %s\n", node->data->birthPlace);
            printf("Input Tempat Lahir Karyawan : ");
            scanf(" %[^\n]", text);
            if (strlen(text) > 30) {
                printf("Tempat Lahir Karyawan maksimal 30 karakter\n");
                break;
            }
            strcpy(node->data->birthPlace, text);
            break;
        case 4:
            printf("Jabatan Karyawan : %s\n", node->data->position);
            printf("Input Jabatan Karyawan : ");
            scanf(" %[^\n]", text);
            if (strlen(text) > 50) {
                printf("Jabatan Karyawan maksimal 50 karakter\n");
                break;
            }
            strcpy(node->data->position, text);
            break;
        case 5:
            printf("Kembali\n");
            break;
        default:
            printf("Pilihan tidak tersedia\n");
            break;
        }
    }
}

void delete()
{
    int id;
    printf("\nHapus Karyawan\n");
    printf("Input ID Karwayan : ");
    scanf("%d", &id);
    struct Node *node = searchEmployeeNode(id);
    if (node == NULL) {
        printf("ID Karyawan tidak ditemukan\n");
        return;
    }
    if (node == head) {
        head = node->next;
    } else {
        struct Node *temp = head;
        while (temp->next != node) {
            temp = temp->next;
        }
        temp->next = node->next;
    }
    free(node->data);
    free(node);
}

void deleteAll()
{
    struct Node *temp = head;
    while (temp != NULL) {
        struct Node *next = temp->next;
        free(temp->data);
        free(temp);
        temp = next;
    }
    head = NULL;
}

void display()
{
    printf("\nList Karyawan\n");
    sortByID();
    struct Node *temp = head;
    if (temp == NULL) {
        printf("List Karyawan Kosong\n");
        return;
    }
    printf("%-6s %-20s %-15s %-15s %-15s\n", "ID", "Nama", "Tempat Lahir", "Tanggal Lahir", "Jabatan");
    while (temp != NULL) {
        printf("%-6d %-20s %-15s %-15s %-15s\n", temp->data->id, temp->data->name, temp->data->birthPlace, temp->data->birthDate, temp->data->position);
        temp = temp->next;
    }
}

struct Node * searchEmployeeNode(int id)
{
    struct Node *temp = head;
    while (temp != NULL) {
        if (temp->data->id == id) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

int getLength()
{
    int length = 0;
    struct Node *temp = head;
    while (temp != NULL) {
        length++;
        temp = temp->next;
    }
    return length;
}

void sortByID()
{
    if (head == NULL) {
        return;
    }
    int swapped;
    do {
        swapped = 0;
        struct Node *temp = head;
        while (temp->next != NULL) {
            if (temp->data->id > temp->next->data->id) {
                struct Employee *employee = temp->data;
                temp->data = temp->next->data;
                temp->next->data = employee;
                swapped = 1;
            }
            temp = temp->next;
        }
    } while (swapped);
}

int validateDate(char *date)
{
    int day, month, year;
    if (sscanf(date, "%d-%d-%d", &day, &month, &year) != 3) {
        return 0;
    }
    if (day < 1 || day > 31) {
        return 0;
    }
    if (month < 1 || month > 12) {
        return 0;
    }
    if (year < 1900 || year > 9999) {
        return 0;
    }
    return 1;
}