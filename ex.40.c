#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void print_permissions(struct stat fileStat) {

    printf("File Permissions: ");

    // File type
    printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");

    // Owner Permissions
    printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");

    // Group Permissions
    printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");

    // Others Permissions
    printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");

    printf("\n");
}

int main() {
    char filename[100];
    struct stat fileStat;

    printf("Enter file name: ");
    scanf("%s", filename);

    // Get file status
    if (stat(filename, &fileStat) < 0) {
        perror("Error retrieving file information");
        return 1;
    }

    // Print file type and permissions
    print_permissions(fileStat);

    // Print owner, group, others information
    printf("\nOwner ID  : %d", fileStat.st_uid);
    printf("\nGroup ID  : %d", fileStat.st_gid);

    printf("\nFile Size : %ld bytes", fileStat.st_size);

    // Print numeric (octal) permissions
    printf("\nOctal Permission: %o\n", fileStat.st_mode & 0777);

    return 0;
}

