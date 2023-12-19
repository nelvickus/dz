#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_LENGTH 100

struct OperatingSystem {
    char developer[MAX_LENGTH];
    int yearReleased;
    char version[MAX_LENGTH];
    char name[MAX_LENGTH];
    float price;
};
void writeDataToFile(struct OperatingSystem* data, int numRecords, char* filename) {
    FILE* file = fopen(filename, "w");

    if (data != NULL) {
        printf("������ ������� ��������� �� �����.\n");
    }
    else if (file == NULL) {
        printf("������: �� ������� ������� ���� ��� ������.\n");
        return 0;
    }
    for (int i = 0; i < numRecords; i++) {
        fprintf(file, "%s %d %s %s %.2f\n", data[i].developer, data[i].yearReleased, data[i].version, data[i].name, data[i].price);
    }
    fclose(file);
}

struct OperatingSystem* readDataFromFile(int* numRecords, char* filename) {
    FILE* file = fopen(filename, "r");
    char symbol;
    *numRecords = 0;
    if (file == NULL) {
        printf("������: �� ������� ������� ���� ��� ������.\n");
        return NULL;
    }

    while (!feof(file))
    {
        fscanf(file, "%c", &symbol);
        if (symbol == '\n') *numRecords += 1;
    }
    *numRecords -= 1;
    struct OperatingSystem* data = (struct OperatingSystem*)malloc(*numRecords * sizeof(struct OperatingSystem));

    file = fopen(filename, "r");
    for (int i = 0; i < *numRecords; i++) {
        fscanf(file, "%s %d %s %s %f", data[i].developer, &data[i].yearReleased, data[i].version, data[i].name, &data[i].price);
    }

    fclose(file);
    return data;
}
void displayData(struct OperatingSystem* data, int numRecords) {
    if (data == NULL || numRecords == 0) {
        printf("��� ������ ��� ������.\n");
    }
    else {
        printf("%-15s %-15s %-10s %-15s %-10s\n", "�����������", "��� �������", "������", "��������", "����");
        for (int i = 0; i < numRecords; i++) {
            printf("%-15s %-15d %-10s %-15s %-10.2f\n", data[i].developer, data[i].yearReleased, data[i].version, data[i].name, data[i].price);
        }
    }
}
struct OperatingSystem* searchData(struct OperatingSystem* data, int numRecords, struct OperatingSystem key) {
    struct OperatingSystem* foundRecords = (struct OperatingSystem*)calloc(numRecords, sizeof(struct OperatingSystem));
    int count = 0;

    for (int i = 0; i < numRecords; i++) {
        if (strcmp(data[i].developer, key.developer) == 0) {
            foundRecords[count++] = data[i];
        }
        if (strcmp(data[i].version, key.version) == 0) {
            foundRecords[count++] = data[i];
        }
        if (data[i].yearReleased == key.yearReleased) {
            foundRecords[count++] = data[i];
        }
    }
    /*foundRecords[count].yearReleased = 0;*/
    return foundRecords;
}

void addRecord(struct OperatingSystem** data, int* numRecords, struct OperatingSystem newRecord) {
    (*numRecords)++;
    *data = (struct OperatingSystem*)realloc(*data, *numRecords * sizeof(struct OperatingSystem));
    (*data)[*numRecords - 1] = newRecord;
}

// ������� ��������� ��� ���������� �� ��������
int compareByName(const void* a, const void* b) {
    return strcmp(((struct OperatingSystem*)a)->name, ((struct OperatingSystem*)b)->name);
}

void sort_select(struct OperatingSystem* data, int numRecords) {
    qsort(data, numRecords, sizeof(struct OperatingSystem), compareByName);
}

int main() {
    setlocale(LC_ALL, "Russian");
    struct OperatingSystem* data = NULL;
    int numRecords = 0;
    int choice;
    char filename[MAX_LENGTH];
    int n = 0;

    printf("������� ��� �����: ");
    scanf("%s", filename);

    while (1) {
        printf("\n---------- ���� ----------\n");
        printf("1. �������� ������ �� �����\n");
        printf("2. ������� ������\n");
        printf("3. ����� ������\n");
        printf("4. ���������� �������\n");
        printf("5. ��������� ������ � ����\n");
        printf("6. �������� ����� ������\n");
        printf("0. �����\n");
        printf("������� ���� �����: ");
        scanf("%d", &choice);
        switch (choice) {
        case 0:
            break;
        case 1:
            data = readDataFromFile(&numRecords, filename);
            if (data != NULL) {
                printf("������ ������� ��������� �� �����.\n");
            }
            break;
        case 2:
            if (data == NULL || numRecords == 0) {
                printf("��� ������ ��� ������.\n");
            }
            else {
                displayData(data, numRecords);
            }
            break;
        case 3:
        { int searchChoice;
        printf("�������� �������� ������:\n");
        printf("1. �����������\n");
        printf("2. ��� �������\n");
        printf("3. ������\n");
        printf("������� ���� �����: ");
        scanf("%d", &searchChoice);

        struct OperatingSystem key = { "", 0, " ", " ", 0.f };
        if (searchChoice == 1) {
            printf("������� ������������: ");
            scanf("%s", key.developer);
        }
        else if (searchChoice == 2) {
            printf("������� ��� �������: ");
            scanf("%d", &key.yearReleased);
        }
        else if (searchChoice == 3) {
            printf("������� ������: ");
            scanf("%s", key.version);
        }

        struct OperatingSystem* foundRecords = searchData(data, numRecords, key);
        int numFoundRecords = 0;
        for (int i = 0; i < numRecords; i++) {
            if (foundRecords[i].yearReleased == 0) break;
            numFoundRecords++;
        }

        printf("������� �������: %d\n", numFoundRecords);
        displayData(foundRecords, numFoundRecords);}
        break;
        case 4:
            sort_select(data, numRecords);
            displayData(data, numRecords);
            break;
        default:
            printf("������������ �����. ����������, ��������� �������.\n");
            break;
        case 5:
            if (data == NULL || numRecords == 0) {
                printf("��� ������ ��� ����������.\n");
            }
            else {
                writeDataToFile(data, numRecords, filename);
                printf("������ ������� ��������� � ����.\n");
            }
            break;
        case 6:
        { struct OperatingSystem newRecord;
        printf("������� ������ ��� ����� ������:\n");
        printf("�����������: ");
        scanf("%s", newRecord.developer);
        printf("��� �������: ");
        scanf("%d", &newRecord.yearReleased);
        printf("������: ");
        scanf("%s", newRecord.version);
        printf("��������: ");
        scanf("%s", newRecord.name);
        printf("����: ");
        scanf("%f", &newRecord.price);
        addRecord(&data, &numRecords, newRecord);
        printf("����� ������ ���������.\n");}
        break;
        }

        if (choice == 0) {
            break;
        }
    }

    free(data);
    return 0;
} 

/*if (choice 0< && 5) {
printf("������������ �����. ����������, ��������� �������.\n");
*/
