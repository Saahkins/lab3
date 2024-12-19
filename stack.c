#include "create_stack.c"
#include "stdio.h"





int main(int argc, char* argv[]) {
    Stack* stack = create_stack(50);
    char* file = NULL;
    char* file1 = NULL;
    int n = 0;
    int count = 0;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--generate") == 0 || strcmp(argv[i], "-g") == 0) {
            if (i + 1 < argc) {
                n = atoi(argv[i + 1]);
                i++;
            }
            for (int i = 0; i < n; i++) {
                Work a = generateRandomWork();
                add_element(stack, i, a);
            }
        }
        else if (strcmp(argv[i], "--type") == 0 || strcmp(argv[i], "-t") == 0) {
            if (strcmp(argv[i + 1], "=desc") == 0 || strcmp(argv[i + 1], "D") == 0) {
                Sort_to_min(stack);
            }
            else if (strcmp(argv[i + 1], "=asc") == 0 || strcmp(argv[i + 1], "A") == 0) {
                Sort_to_max(stack);
            }
            else {
                printf("A non-existent flag");
            }
        }
        else if (strcmp(argv[i], "--out") == 0 || strcmp(argv[i], "-o") == 0) {
            if (i + 1 < argc) {
                file = argv[i + 1];
            }
            int a = check_file_extension(file);
            if (a == 1) {
                writeStackToCSV(stack, file);
            }
            if (a == 2) {
                saveStackToTXT(stack, file);
            }
        }
        else if (strcmp(argv[i], "--in") == 0 || strcmp(argv[i], "-i") == 0) {
            if (i + 1 < argc) {
                file1 = argv[i + 1];
            }
            readCSV(file1, stack);
        }
        else if (strcmp(argv[i], "--print") == 0 || strcmp(argv[i], "-P") == 0) {
            if (i + 1 < argc){
                count = atoi(argv[i + 1]);
                i++;
            }
            input_cmd(stack, count);
        }
    }
    clear_stack(stack);
    return 0;
}