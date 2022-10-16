#include <stdio.h>

typedef struct EmployeeCategory {
    char name[20];
    int salary;
} Category;

typedef struct Employees {
    int nip;
    char name[255];
    char address[255];
    char phoneNumber[15];
    Category *category;
    int workingHour;
} Employee;

Employee * findEmployee(int nip);
void inputEmployee(Employee *employee);
void inputWorkingHour();
void viewPayslip();
void selectMenu(int *inputMenu);

Category categories[] = {
    {"Staff D1", 2500000},
    {"Staff D2", 2000000},
    {"Staff D3", 1500000}
};
const int overtimeFeeHourly = 20000;
const int workingHourDaily = 8;
const int workingDaysMonthly = 20;
Employee employees[25];
int countEmployee = 0;

int main()
{
    int inputMenu;
    printf("       -= APLIKASI MANAJEMEN PEGAWAI =-\n");
    do {
        selectMenu(&inputMenu);
        switch (inputMenu) {
            case 1:
                inputEmployee(&employees[countEmployee]);
                break;
            case 2:
                inputWorkingHour();
                break;
            case 3:
                viewPayslip();
                break;
        }
    } while (inputMenu != 0);
    return 0;
}

void selectMenu(int *inputMenu)
{
    printf("\nMenu Aplikasi\n");
    printf("1. Entry Data Pegawai\n");
    printf("2. Entry Jam Kerja Harian\n");
    printf("3. Lihat Slip Gaji\n");
    printf("0. Keluar\n");
    do {
        printf("Masukkan pilihan (0-3) : ");
        scanf("%d", inputMenu);
        if (*inputMenu < 0 || *inputMenu > 3) {
            printf("Pilihan tidak valid.\n");
        }
    } while (*inputMenu < 0 || *inputMenu > 3);
}

Employee * findEmployee(int nip)
{
    for (int i=0; i<countEmployee; i++) {
        if (employees[i].nip == nip) {
            return &employees[i];
        }
    }
    return NULL;
}

void inputEmployee(Employee *employee)
{
    int categoryCount = sizeof(categories)/sizeof(Category);
    int inputCategory;
    int nip;
    printf("\nEntry Data Pegawai\n");
    Employee* emp = NULL;
    do {
        printf("Masukkan NIP : ");
        scanf("%d", &nip);
        emp = findEmployee(nip);
        if (emp != NULL) {
            printf("Error : NIP Telah digunakan\n");
        }
    } while (emp != NULL);
    employee->nip = nip;
    printf("Masukkan nama : ");
    scanf("%s", employee->name);
    printf("Masukkan alamat : ");
    scanf("%s", employee->address);
    printf("Masukkan no hp : ");
    scanf("%s", employee->phoneNumber);
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
    employee->category = &categories[inputCategory-1];
    countEmployee++;
    printf("Data Pegawai Berhasil Disimpan\n");
}

void inputWorkingHour()
{
    int nip, hour;
    printf("\nEntry Jam Kerja Harian\n");
    printf("Masukkan NIP : ");
    scanf("%d", &nip);
    Employee* emp = findEmployee(nip);
    if (emp == NULL) {
        printf("Error : NIP Tidak ditemukan\n");
    } else {
        printf("\nNama Pegawai : %s\n", emp->name);
        do {
            printf("Masukkan jam kerja harian : ");
            scanf("%d", &hour);
            if (hour<0 || hour>24) {
                printf("Error : jam kerja tidak valid\n");
            }
        } while (hour<0 || hour>24);
        emp->workingHour = hour;
        printf("Jam Kerja Pegawai Berhasil Disimpan\n");
    }
}

void viewPayslip()
{
    int nip;
    printf("\nLihat Slip Gaji Karyawan\n");
    printf("Masukkan NIP : ");
    scanf("%d", &nip);
    Employee* emp = findEmployee(nip);
    if (emp == NULL) {
        printf("Error : NIP Tidak ditemukan\n");
    } else {
        int overtimeFee = 0;
        int overtimeHour = (emp->workingHour - workingHourDaily) * workingDaysMonthly;
        if (overtimeHour > 0) {
            overtimeFee = overtimeHour * overtimeFeeHourly;
        }
        int totalSalary = emp->category->salary + overtimeFee;
        printf("\nNama Pegawai : %s\n", emp->name);
        printf("Kategori     : %s\n", emp->category->name);
        printf("No. Telp     : %s\n", emp->phoneNumber);
        printf("Alamat       : %s\n\n", emp->address);
        printf("-----------------------------------------\n");
        printf("|%-15s|%-12s|%-10s|\n", "Pendapatan", "Nilai", "Keterangan");
        printf("-----------------------------------------\n");
        printf("|%-15s|Rp. %8d|%-10s|\n", "Gaji Pokok", emp->category->salary, "");
        printf("|%-15s|Rp. %8d|%-6d Jam|\n", "Uang Lembur", overtimeFee, overtimeHour);
        printf("-----------------------------------------\n");
        printf("|%-15s|Rp. %19d|\n", "TOTAL GAJI", totalSalary);
        printf("-----------------------------------------\n");
    }
}