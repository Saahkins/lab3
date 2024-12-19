#ifndef STRUCT_RECORD_H
#define STRUCT_RECORD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>




typedef struct {
    char title[100];
    char author_name[100];
    char initials[100];
    char journal_title[100];
    int year;
    int journal;
    bool flag;
    int page;
    int citation;
}Work;

#endif