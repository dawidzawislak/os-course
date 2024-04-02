#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void reverseArray(char* array, int n) {
    for (int i = 0; i < n / 2; ++i) {
        char t = array[n-1-i];

        array[n-1-i] = array[i];
        array[i] = t;
    }
}

int reverse_1byte(const char* fileNameIn, const char* fileNameOut) {
    FILE* fin = fopen(fileNameIn, "r");
    FILE* fout = fopen(fileNameOut, "w");

    if (fin == NULL || fout == NULL) return -1;

    int i = -1;

    while (fseek(fin, i, SEEK_END) == 0) {
        char chr = fgetc(fin);
        fwrite(&chr, sizeof(char), 1, fout);
        --i;
    }

    fclose(fin);
    fclose(fout);

    return 0;
}

int reverse_1024byte(const char* fileNameIn, const char* fileNameOut) {
    FILE* fin = fopen(fileNameIn, "r");
    FILE* fout = fopen(fileNameOut, "w");

    if (fin == NULL || fout == NULL) return -1;

    int i = -1024;

    fseek(fin, 0, SEEK_END);
    size_t fileSize = ftell(fin);

    char* buffer = calloc(1024, sizeof(char));

    size_t bytesRead = 0;

    size_t to_read = 1024;

    fseek(fin, i, SEEK_END);

    int last = 0;

    while ((bytesRead = fread(buffer, sizeof(char), to_read, fin)) > 0) {
        reverseArray(buffer, bytesRead);
        size_t written = fwrite(buffer, sizeof(char), bytesRead, fout);

        if (written != bytesRead) {
            printf("ERROR writing to file!\n");
        }

        if (last == 1) break;
        else if (-i + 1024 > fileSize) {
            to_read = fileSize + i;
            fseek(fin, 0, SEEK_SET);
            last = 1;
        }
        else {
            i -= 1024;
            fseek(fin, i, SEEK_END);
        } 
    }

    free(buffer);

    fclose(fin);
    fclose(fout);

    return 0;
}

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

int main(int argc, char** argv) {

    const char* out1 = concat(argv[2], "1");
    const char* out2 = concat(argv[2], "1024");


    clock_t start = clock();
    reverse_1byte(argv[1], out1);
    double time_1byte = ((double)(clock() - start)) / CLOCKS_PER_SEC;
    start = clock();
    reverse_1024byte(argv[1], out2);
    double time_1024byte = ((double)(clock() - start)) / CLOCKS_PER_SEC;

    FILE* fout = fopen("pomiar_zad_2.txt", "w");

    fprintf(fout, "Czas wersji 1-bitowej: %f s\n", time_1byte);
    fprintf(fout, "Czas wersji 1024-bitowej: %f s\n", time_1024byte);

    fclose(fout);

    return 0;
}