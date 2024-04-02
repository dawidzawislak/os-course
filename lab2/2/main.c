#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char** argv) {
    DIR* currDir = opendir(".");
    long long totalSize = 0;

    if (currDir == NULL) {
        printf("Nie można otworzyć katalogu!\n");
        return -1;
    }

    struct dirent *dirEntry;
    while ((dirEntry = readdir(currDir)) != NULL) {
        struct stat bufferStat;
        if (stat(dirEntry->d_name, &bufferStat) == -1) {
            printf("Błąd pobierania informacji o pliku\n");
            closedir(currDir);
            return -2;
        }

        if (!S_ISDIR(bufferStat.st_mode)) {
            printf("Rozmiar: %ld bytes \t| Nazwa pliku: %s\n", (long) bufferStat.st_size, dirEntry->d_name);
            totalSize += bufferStat.st_size;
        }
    }
    printf("Rozmiar wszystkich plików: %lld bytes\n", totalSize);

    closedir(currDir);

    return 0;
}