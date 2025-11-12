// single_level_directory.c
// Compile: gcc -o single_level_directory single_level_directory.c
// Run: ./single_level_directory

#include <stdio.h>
#include <string.h>

struct {
    char fname[20]; // file name
} dir[10]; // directory can hold 10 files

int count = 0; // number of files currently in directory

void createFile() {
    char name[20];
    if (count >= 10) {
        printf("\nDirectory is full! Cannot create more files.\n");
        return;
    }
    printf("Enter the name of the file to create: ");
    scanf("%s", name);

    // Check if file already exists
    for (int i = 0; i < count; i++) {
        if (strcmp(name, dir[i].fname) == 0) {
            printf("File '%s' already exists!\n", name);
            return;
        }
    }

    strcpy(dir[count].fname, name);
    count++;
    printf("File '%s' created successfully.\n", name);
}

void deleteFile() {
    char name[20];
    printf("Enter the name of the file to delete: ");
    scanf("%s", name);

    for (int i = 0; i < count; i++) {
        if (strcmp(name, dir[i].fname) == 0) {
            for (int j = i; j < count - 1; j++) {
                strcpy(dir[j].fname, dir[j + 1].fname);
            }
            count--;
            printf("File '%s' deleted successfully.\n", name);
            return;
        }
    }
    printf("File '%s' not found!\n", name);
}

void searchFile() {
    char name[20];
    printf("Enter the name of the file to search: ");
    scanf("%s", name);

    for (int i = 0; i < count; i++) {
        if (strcmp(name, dir[i].fname) == 0) {
            printf("File '%s' found at position %d.\n", name, i + 1);
            return;
        }
    }
    printf("File '%s' not found!\n", name);
}

void displayFiles() {
    if (count == 0) {
        printf("\nDirectory is empty.\n");
        return;
    }
    printf("\nFiles in the directory:\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s\n", i + 1, dir[i].fname);
    }
}

int main() {
    int choice;
    char dirname[20];

    printf("Enter the name of the directory: ");
    scanf("%s", dirname);
    printf("\nSingle-Level Directory Simulation for '%s'\n", dirname);

    while (1) {
        printf("\n---- MENU ----\n");
        printf("1. Create File\n");
        printf("2. Delete File\n");
        printf("3. Search File\n");
        printf("4. Display Files\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createFile(); break;
            case 2: deleteFile(); break;
            case 3: searchFile(); break;
            case 4: displayFiles(); break;
            case 5: 
                printf("\nExiting... Directory '%s' closed.\n", dirname);
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}

