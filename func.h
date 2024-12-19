#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#ifndef STRUCT_CONTAINER_H

#define STRUCT_CONTAINER_H
#include "struct.h"

typedef struct {
    Work* data;     // Массив для хранения элементов
    int top;       // Индекс верхнего элемента
    int capacity;  // Вместимость стека
} Stack;

Stack* create_stack(int capacity);
int get_size(Stack* stack);
Work get_element(Stack* stack, int index);
Work* get_top(Stack* stack);
Work* get_bottom(Stack* stack);
Work* get_next(Stack* stack, int index);
Work* get_prev(Stack* stack, int index);
void add_element(Stack* stack, int index, Work value);
void remove_element(Stack* stack, int index);
void swap_elements(Stack* stack, int index1, int index2);
Stack* array_to_stack(Work* array, int size);
Work* stack_to_array(Stack* stack);
void Sort_to_max(Stack* stack);
void Sort_to_min(Stack* stack);
void clear_stack(Stack* stack);
void writeStackToCSV(Stack* stack, const char* filename);
void saveStackToTXT(Stack* stack, const char* filename);
void print_stack(Stack* stack);
void readCSV(const char* filename, Stack* stack);
void input_cmd(Stack* stack, int count);





#endif