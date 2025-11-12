#include <stdio.h>
#include <string.h>

struct Directory {
    char dname[20];      // Directory name (like a user)
    char fname[10][20];  // Files in the directory
    int fcount;          // Number of files
} dir[10];

int dcount = 0; // Total directories

void createDirectory() {
    if (dcount >= 10) {
        printf("\nMaximum directories reached!\n");
        return;
    }

    printf("\nEnter directory name: ");
    scanf("%s", dir[dcount].dname);
    dir[dcount].fcount = 0;
    dcount++;
    printf("Directory created successfully.\n");
}

void createFile() {
    char dname[20], fname[20];
    printf("\nEnter directory name: ");
    scanf("%s", dname);

    for (int i = 0; i < dcount; i++) {
        if (strcmp(dname, dir[i].dname) == 0) {
            if (dir[i].fcount >= 10) {
                printf("Directory full!\n");
                return;
            }
            printf("Enter file name: ");
            scanf("%s", fname);
            strcpy(dir[i].fname[dir[i].fcount], fname);
            dir[i].fcount++;
            printf("File created successfully.\n");
            return;
        }
    }
    printf("Directory not found!\n");
}

void deleteFile() {
    char dname[20], fname[20];
    printf("\nEnter directory name: ");
    scanf("%s", dname);

    for (int i = 0; i < dcount; i++) {
        if (strcmp(dname, dir[i].dname) == 0) {
            printf("Enter file name to delete: ");
            scanf("%s", fname);
            for (int j = 0; j < dir[i].fcount; j++) {
                if (strcmp(fname, dir[i].fname[j]) == 0) {
                    for (int k = j; k < dir[i].fcount - 1; k++)
                        strcpy(dir[i].fname[k], dir[i].fname[k + 1]);
                    dir[i].fcount--;
                    printf("File deleted successfully.\n");
                    return;
                }
            }
            printf("File not found!\n");
            return;
        }
    }
    printf("Directory not found!\n");
}

void searchFile() {
    char dname[20], fname[20];
    printf("\nEnter directory name: ");
    scanf("%s", dname);

    for (int i = 0; i < dcount; i++) {
        if (strcmp(dname, dir[i].dname) == 0) {
            printf("Enter file name to search: ");
            scanf("%s", fname);
            for (int j = 0; j < dir[i].fcount; j++) {
                if (strcmp(fname, dir[i].fname[j]) == 0) {
                    printf("File found in directory '%s'.\n", dname);
                    return;
                }
            }
            printf("File not found!\n");
            return;
        }
    }
    printf("Directory not found!\n");
}

void display() {
    if (dcount == 0) {
        printf("\nNo directories available.\n");
        return;
    }

    printf("\n--- Two-Level Directory Structure ---\n");
    for (int i = 0; i < dcount; i++) {
        printf("\nDirectory: %s\n", dir[i].dname);
        if (dir[i].fcount == 0)
            printf("  (No files)\n");
        else
            for (int j = 0; j < dir[i].fcount; j++)
                printf("  %d. %s\n", j + 1, dir[i].fname[j]);
    }
}

int main() {
    int choice;

    printf("=== Two-Level Directory Simulation ===\n");
    while (1) {
        printf("\n1. Create Directory\n2. Create File\n3. Delete File\n4. Search File\n5. Display\n6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createDirectory(); break;
            case 2: createFile(); break;
            case 3: deleteFile(); break;
            case 4: searchFile(); break;
            case 5: display(); break;
            case 6: printf("Exiting...\n"); return 0;
            default: printf("Invalid choice!\n");
        }
    }
}

