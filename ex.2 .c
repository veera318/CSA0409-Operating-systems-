#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char buffer[1024];
    int source, destination, bytes_read;

    source = open("source.txt", O_RDONLY);
    if (source == -1) {
        perror("Failed to open source file");
        return 1;
    }

    destination = open("destination.txt", O_WRONLY | O_CREAT, 0644);
    if (destination == -1) {
        perror("Failed to open destination file");
        close(source);
        return 1;
    }

    while ((bytes_read = read(source, buffer, sizeof(buffer))) > 0) {
        write(destination, buffer, bytes_read);
    }

    close(source);
    close(destination);
    return 0;
}

