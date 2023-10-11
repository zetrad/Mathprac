#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_arabic(int ch) {
    if (ch >= 48 && ch <= 57) return 1;
    else return 0;
}

int is_latin(int ch) {
    if ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122)) return 1;
    else return 0;
}

int is_space(int ch) {
    if (ch == 32) return 1;
    else return 0;
}

void without_arabic(FILE* file, FILE* new_file) {
    char symbol = fgetc(file);
    while (symbol != EOF) {
        if (is_arabic((int)symbol) == 0) {
            fprintf(new_file, "%c", symbol);
        }
        symbol = fgetc(file);
    }
}

void latin_count(FILE* file, FILE* new_file) {
    char symbol = fgetc(file);
    int count = 0;
    while (symbol != EOF) {
        if (symbol == '\n') {
            fprintf(new_file, "%d\n", count);
            count = 0;
        }
        if (is_latin((int)symbol) == 1) count++;
        symbol = fgetc(file);
    }
    fprintf(new_file, "%d", count);
}

void another_symbol_count(FILE* file, FILE* new_file) {
    char symbol = fgetc(file);
    int count = 0;
    while (symbol != EOF) {
        if (symbol == '\n') {
            fprintf(new_file, "%d\n", count);
            count = 0;
        }
        if (is_latin((int)symbol) + is_arabic((int)symbol) + is_space((int)symbol)== 0) {count++;}
        symbol = fgetc(file);
    }
    fprintf(new_file, "%d", count);
}

void print_ascii(FILE* file, FILE* new_file) {
    char symbol = fgetc(file);
    while (symbol != EOF) {
        if (is_arabic((int)symbol) == 0) {
            if (symbol != '\n')
                fprintf(new_file, "%d", (int)symbol);
            else
                fprintf(new_file, "\n");
        }
        else fprintf(new_file, "%c", symbol);
        symbol = fgetc(file);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3 || argc > 4) {
        printf("Invalid amount of values\n");
        return 0;
    }
    FILE *file;
    FILE *new_file;
    char* name = argv[2], *new_name;
    if ((file = fopen(name, "r")) == NULL) {
        printf("Couldn't open the file");
        return 0;
    }

    if (argc == 3) {
        new_name = (char*)malloc(sizeof(char) * (5 + strlen(name)));
        if (new_name == NULL) printf("No memory\n");
        new_name[0] = 'o', new_name[1] = 'u', new_name[2] = 't', new_name[3] = '_', new_name[4 + strlen(name)] = '\0';
        for (int i = 4; i < 4 + strlen(name); i++) {
            new_name[i] = argv[2][i - 4];
        }

        new_file = fopen(new_name, "w");
        if (new_file == NULL) printf("Unable to create the file\n");
        free(new_name);
    }
    else {
        if (argv[1][1] == 'n')
        new_name = argv[3];
        else return 0;
    }
    switch (argv[1][1])
    {
        case 'd':
            without_arabic(file, new_file);
            return 0;
        case 'i':
            latin_count(file, new_file);
            return 0;
        case 's':
            another_symbol_count(file, new_file);
            return 0;
        case 'a':
            print_ascii(file, new_file);
            return 0;
        default: printf("ERROR");
    }
    fclose(file);
    fclose(new_file);
}