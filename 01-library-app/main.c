#include <stdio.h>

typedef struct CategoryBook {
    char name[20];
} Category;

typedef struct PublisherBook {
    char name[20];
} Publisher;

typedef struct Books {
    int id;
    char title[255];
    int count;
    char author[255];
    char isbnNumber[255];
    Category *category;
    Publisher *publisher;
} Book;

Category categories[] = {{"Fiksi"}, {"Kuliner"}, {"Biologi"}, {"Filsafat"}, {"Komputer"}, {"Manajemen"}};
Publisher publishers[] = {{"Erlangga"}, {"Tiga Sekawan"}, {"Gramedia"}};

void selectMenu(int *inputMenu);
void inputBook(Book *book);
void viewBook(Book books[], int count);

int main() {
    Book books[5];
    int inputMenu;
    int count = 0;
    printf("     -= APLIKASI PERPUSTAKAN LITE =-\n");
    do {
        selectMenu(&inputMenu);
        if (inputMenu == 1) {
            if (count+1 > 5) {
                printf("Error : Buku tidak bisa ditambahkan lagi, maks 5 buku.");
                continue;
            }
            inputBook(&books[count]);
            printf("Buku berhasil ditambahkan.\n");
            count++;
        } else if (inputMenu == 2) {
            if (count == 0) {
                printf("Error : Buku masih kosong, silahkan input data.\n");
                continue;
            }
            viewBook(books, count);
        } else if (inputMenu != 0) {
            printf("Error : Pilihan tidak valid\n");
        }
    } while (inputMenu != 0);
    return 0;
}

void selectMenu(int *inputMenu) {
    printf("\nMenu Aplikasi\n");
    printf("1. Input Data Buku\n");
    printf("2. Cetak Data Buku\n");
    printf("0. Keluar\n");
    printf("Masukkan pilihan (0-1) : ");
    scanf("%d", inputMenu);
}

void inputBook(Book *book) {
    int categoryCount = sizeof(categories)/sizeof(Category);
    int publisherCount = sizeof(publishers)/sizeof(Publisher);
    int inputCategory;
    int inputPublisher;
    printf("\nInput Data Buku\n");
    printf("ID : ");
    scanf("%d", &book->id);
    printf("Judul : ");
    scanf("%s", book->title);
    printf("Jumlah : ");
    scanf("%d", &book->count);
    printf("Penulis : ");
    scanf("%s", book->author);
    printf("No. ISBN : ");
    scanf("%s", book->isbnNumber);
    printf("Kategori :\n");
    for (int i=0; i<categoryCount; i++) {
        printf("%d. %s\n", i+1, categories[i].name);
    }
    do {
        printf("Masukkan pilihan (1-%d) : ", categoryCount);
        scanf("%d", &inputCategory);
        if (inputCategory < 1 || inputCategory > categoryCount) {
            printf("Error : Pilihan tidak valid\n");
        }
    } while (inputCategory < 1 || inputCategory > categoryCount);
    book->category = &categories[inputCategory-1];
    printf("Penerbit :\n");
    for (int i=0; i<publisherCount; i++) {
        printf("%d. %s\n", i+1, publishers[i].name);
    }
    do {
        printf("Masukkan pilihan (1-%d) : ", publisherCount);
        scanf("%d", &inputPublisher);
        if (inputPublisher < 1 || inputPublisher > publisherCount) {
            printf("Error : Pilihan tidak valid\n");
        }
    } while (inputPublisher < 1 || inputPublisher > publisherCount);
    book->publisher = &publishers[inputPublisher-1];
}

void viewBook(Book books[], int count) {
    printf("\nList Buku di Perpustakaan\n");
    printf("-------------------------------------------------------------------------------------------\n");
    printf("|%2s|%15s|%6s|%15s|%15s|%15s|%15s|\n", "ID", "Judul", "Jumlah", "Penulis", "No. ISBN", "Kategori", "Penerbit");
    printf("-------------------------------------------------------------------------------------------\n");
    for (int i=0; i<count; i++) {
        printf("|%2d|%15s|%6d|%15s|%15s|%15s|%15s|\n",
            books[i].id,
            books[i].title,
            books[i].count,
            books[i].author,
            books[i].isbnNumber,
            books[i].category->name,
            books[i].publisher->name
        );
    }
    printf("-------------------------------------------------------------------------------------------\n");
    printf("\n");
}