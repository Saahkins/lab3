#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "struct.h"
#include "func.h"


// Функция создания стека
Stack* create_stack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->data = (Work*)malloc(capacity * sizeof(Work));
    return stack;
}

// Получение текущего размера стека
int get_size(Stack* stack) {
    return stack->top + 1;
}

// Получение элемента по индексу
Work get_element(Stack* stack, int index) {
    if (index < 0 || index > stack->top) {
        exit(EXIT_FAILURE);
    }
    return stack->data[index];
}

// Получение указателя на начало (верх стека)
Work* get_top(Stack* stack) {
    if (stack->top == -1) return NULL;
    return &stack->data[stack->top];
}

// Получение указателя на конец
Work* get_bottom(Stack* stack) {
    if (stack->top == -1) return NULL;
    return &stack->data[0];
}

// Получение следующего элемента от указателя
Work* get_next(Stack* stack, int index) {
    if (index + 1 < 0 || index >= stack->capacity) return NULL;
    return &stack->data[index + 1];
}

// Получение предыдущего элемента от указателя
Work* get_prev(Stack* stack, int index) {
    if (index <= 0) return NULL;
    return &stack->data[index - 1];
}

// Добавление элемента по индексу
void add_element(Stack* stack, int index, Work value) {
    if (index < 0 || index > stack->top + 1 || stack->top == stack->capacity - 1) {
        return;
    }
    for (int i = stack->top; i >= index; i--) {
        stack->data[i + 1] = stack->data[i];
    }
    stack->data[index] = value;
    stack->top++;
}

// Удаление элемента по индексу
void remove_element(Stack* stack, int index) {
    if (index < 0 || index > stack->top) {
        return;
    }

    for (int i = index; i < stack->top; i++) {
        stack->data[i] = stack->data[i + 1];
    }
    stack->top--;
}

// Замена двух элементов друг на друга
void swap_elements(Stack* stack, int index1, int index2) {
    if (index1 < 0 || index1 > stack->top || index2 < 0 || index2 > stack->top) {
        return;
    }
    Work temp = stack->data[index1];
    stack->data[index1] = stack->data[index2];
    stack->data[index2] = temp;
}

// Преобразование массива в стек
Stack* array_to_stack(Work* array, int size) {
    Stack* stack = create_stack(size);
    for (int i = 0; i < size; i++) {
        stack->data[i] = array[i];
        stack->top++;
    }
    return stack;
}

// Преобразование стека в массив
Work* stack_to_array(Stack* stack) {
    Work* array = (Work*)malloc((stack->top + 1) * sizeof(Work));
    for (int i = 0; i <= stack->top; i++) {
        array[i] = stack->data[i];
    }
    return array;
}   

//сортировка по возрастанию
void Sort_to_max(Stack* stack) {
    for (int i = 1; i < stack->top + 1; i++) {
        int loc = 0;
        for (int j = 0; j < i; j++) {
            if (stack->data[i].year > stack->data[j].year) {
                loc++;
            }
            else {
                break;
            }
        }
        Work t = stack->data[i];
        for (int j = i; j > loc; j--) {
            stack->data[j] = stack->data[j - 1];
        }
        stack->data[loc] = t;
    }
}

//сортировка по убыванию
void Sort_to_min(Stack* stack) {
    for (int i = 1; i < stack->top + 1; i++) {
        int loc = 0;
        for (int j = 0; j < i; j++) {
            if (stack->data[i].year < stack->data[j].year) {
                loc++;
            }
            else {
                break;
            }
        }
        Work t = stack->data[i];
        for (int j = i; j > loc; j--) {
            stack->data[j] = stack->data[j - 1];
        }
        stack->data[loc] = t;
    }
}

// Очистка стека
void clear_stack(Stack* stack) {
    free(stack->data);
    free(stack);
}

//генерация рандомной строки
void randomString(char* str, int length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ";
    for (int i = 0; i < length; i++) {
        str[i] = charset[rand() % (sizeof(charset) - 1)];
    }
    str[length] = '\0';
}

// Функция для генерации случайной работы
Work generateRandomWork() {
    Work work;
    randomString(work.title, rand() % 50 + 1);
    randomString(work.author_name, rand() % 50 + 1);
    randomString(work.initials, 3);
    randomString(work.journal_title, rand() % 50 + 1);
    work.year = rand() % 2023 + 1;
    work.journal = rand() % 100;
    work.flag = rand() % 2;
    work.page = rand() % 500 + 1;
    work.citation = rand() % 1000;
    return work;
}

//функция вывода в csv
void writeStackToCSV(Stack* stack, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Unable to open file!");
        return;
    }



    // Записываем данные стека
    for (int i = 0; i <= stack->top; i++) {
        Work* work = &stack->data[i];
        fprintf(file, "%s,%s,%s,%s,%d,%d,%d,%d,%d\n",
            work->title,
            work->author_name,
            work->initials,
            work->journal_title,
            work->year,
            work->journal,
            work->flag,
            work->page,
            work->citation);
    }

    fclose(file);
}

//вывод в txt
void saveStackToTXT(Stack* stack, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        perror("Ошибка открытии файла");
        return;
    }
    int n = stack->top;
    for (int i = 0; i <= n; i++) {
        Work work = stack->data[i];
        fprintf(file, "Title: %s\n", work.title);
        fprintf(file, "Author: %s\n", work.author_name);
        fprintf(file, "Initials: %s\n", work.initials);
        fprintf(file, "Journal Title: %s\n", work.journal_title);
        fprintf(file, "Year: %d\n", work.year);
        fprintf(file, "Journal: %d\n", work.journal);
        fprintf(file, "Flag: %d\n", work.flag);
        fprintf(file, "Page: %d\n", work.page);
        fprintf(file, "Citation: %d\n", work.citation);
    }

    fclose(file);
}


//вывод в консоль
void print_stack(Stack* stack) {
    if (stack->top == -1) {
        printf("Стек пуст.\n");
        return;
    }

    printf("Данные стека:\n");
    for (int i = stack->top; i >= 0; i--) {
        Work work = stack->data[i];
        printf("Название: %s\n", work.title);
        printf("Автор: %s\n", work.author_name);
        printf("Инициалы: %s\n", work.initials);
        printf("Название журнала: %s\n", work.journal_title);
        printf("Год: %d\n", work.year);
        printf("Журнал: %d\n", work.journal);
        printf("РИНЦ: %d\n", work.flag);
        printf("Страница: %d\n", work.page);
        printf("Цитирование: %d\n", work.citation);
    }
}

//считывание данных из csv
void readCSV(const char* filename, Stack* stack) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Ошибка открытия файла");
        return;
    }

    char line[512];
    int i = stack->top;
    while (fgets(line, sizeof(line), file)) {
        Work work;
        char* token = strtok(line, ",");

        // Считывание данных из строки
        strncpy(work.title, token, sizeof(work.title));
        token = strtok(NULL, ",");
        strncpy(work.author_name, token, sizeof(work.author_name));
        token = strtok(NULL, ",");
        strncpy(work.initials, token, sizeof(work.initials));
        token = strtok(NULL, ",");
        strncpy(work.journal_title, token, sizeof(work.journal_title));
        token = strtok(NULL, ",");
        work.year = atoi(token);
        token = strtok(NULL, ",");
        work.journal = atoi(token);
        token = strtok(NULL, ",");
        work.flag = atoi(token);
        token = strtok(NULL, ",");
        work.page = atoi(token);
        token = strtok(NULL, ",");
        work.citation = atoi(token);

        i++;
        add_element(stack, i, work);
    }

    fclose(file);
}


void input_cmd(Stack* stack, int count) {
    for (int i = 0; i < count; i++) {
        stack->top++;
        printf("Title: ");
        scanf("%s", &stack->data[stack->top].title);
        printf("Name: ");
        scanf("%s", &stack->data[stack->top].author_name);
        printf("Initials: ");
        scanf("%s", &stack->data[stack->top].initials);
        printf("Journel Title: ");
        scanf("%s", &stack->data[stack->top].journal_title);
        printf("Year: ");
        scanf("%d", &stack->data[stack->top].year);
        printf("Journal: ");
        scanf("%d", &stack->data[stack->top].journal);
        char a[3];
        printf("RINC: ");
        scanf("%s", &a);
        if (a[0] == 'y' && a[1] == 'e' && a[2] == 's') {
            stack->data[stack->top].flag = true;
        }
        else {
            stack->data[stack->top].flag = false;
        }
        printf("Page: ");
        scanf("%d", &stack->data[stack->top].page);
        printf("Citiation: ");
        scanf("%d", &stack->data[stack->top].citation);
    }
}

//проверка расширения
int check_file_extension(const char* filename) {
    const char* dot = strrchr(filename, '.');
    if (strcmp(dot, ".csv") == 0) {
        return 1;
    }
    else if (strcmp(dot, ".txt") == 0) {
        return 2;
    }
    else {
        printf("Некорректное расширение файла");
    }
}

