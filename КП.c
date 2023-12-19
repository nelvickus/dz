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
        printf("Данные успешно загружены из файла.\n");
    }
    else if (file == NULL) {
        printf("Ошибка: Не удается открыть файл для записи.\n");
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
        printf("Ошибка: Не удается открыть файл для чтения.\n");
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
        printf("Нет данных для печати.\n");
    }
    else {
        printf("%-15s %-15s %-10s %-15s %-10s\n", "Разработчик", "Год выпуска", "Версия", "Название", "Цена");
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

// Функция сравнения для сортировки по названию
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

    printf("Введите имя файла: ");
    scanf("%s", filename);

    while (1) {
        printf("\n---------- Меню ----------\n");
        printf("1. Загрузка данных из файла\n");
        printf("2. Вывести данные\n");
        printf("3. Поиск записи\n");
        printf("4. Сортировка записей\n");
        printf("5. Сохранить данные в файл\n");
        printf("6. Добавить новую запись\n");
        printf("0. Выход\n");
        printf("Введите свой выбор: ");
        scanf("%d", &choice);
        switch (choice) {
        case 0:
            break;
        case 1:
            data = readDataFromFile(&numRecords, filename);
            if (data != NULL) {
                printf("Данные успешно загружены из файла.\n");
            }
            break;
        case 2:
            if (data == NULL || numRecords == 0) {
                printf("Нет данных для печати.\n");
            }
            else {
                displayData(data, numRecords);
            }
            break;
        case 3:
        { int searchChoice;
        printf("Выберите критерий поиска:\n");
        printf("1. Разработчик\n");
        printf("2. Год выпуска\n");
        printf("3. Версия\n");
        printf("Введите свой выбор: ");
        scanf("%d", &searchChoice);

        struct OperatingSystem key = { "", 0, " ", " ", 0.f };
        if (searchChoice == 1) {
            printf("Введите разработчика: ");
            scanf("%s", key.developer);
        }
        else if (searchChoice == 2) {
            printf("Введите год выпуска: ");
            scanf("%d", &key.yearReleased);
        }
        else if (searchChoice == 3) {
            printf("Введите версию: ");
            scanf("%s", key.version);
        }

        struct OperatingSystem* foundRecords = searchData(data, numRecords, key);
        int numFoundRecords = 0;
        for (int i = 0; i < numRecords; i++) {
            if (foundRecords[i].yearReleased == 0) break;
            numFoundRecords++;
        }

        printf("Найдено записей: %d\n", numFoundRecords);
        displayData(foundRecords, numFoundRecords);}
        break;
        case 4:
            sort_select(data, numRecords);
            displayData(data, numRecords);
            break;
        default:
            printf("Неправильный выбор. Пожалуйста, повторите попытку.\n");
            break;
        case 5:
            if (data == NULL || numRecords == 0) {
                printf("Нет данных для сохранения.\n");
            }
            else {
                writeDataToFile(data, numRecords, filename);
                printf("Данные успешно сохранены в файл.\n");
            }
            break;
        case 6:
        { struct OperatingSystem newRecord;
        printf("Введите данные для новой записи:\n");
        printf("Разработчик: ");
        scanf("%s", newRecord.developer);
        printf("Год выпуска: ");
        scanf("%d", &newRecord.yearReleased);
        printf("Версия: ");
        scanf("%s", newRecord.version);
        printf("Название: ");
        scanf("%s", newRecord.name);
        printf("Цена: ");
        scanf("%f", &newRecord.price);
        addRecord(&data, &numRecords, newRecord);
        printf("Новая запись добавлена.\n");}
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
printf("Неправильный выбор. Пожалуйста, повторите попытку.\n");
*/
