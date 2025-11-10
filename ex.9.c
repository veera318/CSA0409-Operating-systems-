#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

    key_t key = ftok("shmfile", 65);
    if (key == -1) {
        perror("ftok");
        exit(1);
    }

    int shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }
    char *str = (char*) shmat(shmid, NULL, 0);
    if (str == (char*) -1) {
        perror("shmat");
        exit(1);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    }
    else if (pid == 0) {
        sleep(1); 
        printf("Child reads: %s\n", str);
        sprintf(str, "Hello from Child!");
        printf("Child wrote new message to shared memory.\n");
    }
    else {
        sprintf(str, "Hello from Parent!");
        printf("Parent wrote message to shared memory.\n");
        wait(NULL);
        printf("Parent reads: %s\n", str);
        shmdt(str);
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}

