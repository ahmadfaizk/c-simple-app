#include <stdio.h>

void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int findIndex(int arr[], int size, int element)
{
    for (int i=0; i<size; i++) {
        if (arr[i] == element) {
            return i;
        }
    }
    return -1;
}

int main()
{
    int size, element, index;
    int arr[100];
    printf("Input jumlah elemen array : ");
    scanf("%d", &size);
    printf("Input %d angka (dengan dipisah enter) :\n", size);
    for (int i=0; i<size; i++) {
        scanf("%d", &arr[i]);
    }
    sort(arr, size);
    printf("Input angka yang dicari : ");
    scanf("%d", &element);
    index = findIndex(arr, size, element);
    if (index != -1) {
        printf("Angka ditemukan pada index ke-%d\n", index);
    } else {
        printf("Angka tidak ditemukan\n");
    }
    printf("Urutan angka yang diinputkan : ");
    printArray(arr, size);
    return 0;
}