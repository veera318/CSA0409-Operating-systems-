#include <stdio.h>
#include <string.h>

int main() {
    char filename[50], pattern[50], line[200];
    FILE *fp;
    int line_num = 1, found = 0;

    // Get file name and pattern from user
    printf("Enter file name: ");
    scanf("%s", filename);

    printf("Enter pattern to search: ");
    scanf("%s", pattern);

    // Open file
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: Cannot open file.\n");
        return 1;
    }

    // Read file line by line
    while (fgets(line, sizeof(line), fp) != NULL) {
        if (strstr(line, pattern) != NULL) {
            printf("Line %d: %s", line_num, line);
            found = 1;
        }
        line_num++;
    }

    if (!found)
        printf("Pattern not found in file.\n");

    fclose(fp);
    return 0;
}

