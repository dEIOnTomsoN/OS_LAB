#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define SHM_SIZE 1024

int main() {
    int shmid;
    key_t key;
    int *shm_ptr;
    pid_t pid;

    key = ftok(".", 's');

    shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    shm_ptr = (int *)shmat(shmid, NULL, 0);
    if ((int)shm_ptr == -1) {
        perror("shmat");
        exit(1);
    }

    pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(1);
    } else if (pid == 0) {
        for (int i = 0; i < SHM_SIZE/sizeof(int); i++) {
            shm_ptr[i] = i * i;
        }
    } else {
        wait(NULL);
        for (int i = 0; i < SHM_SIZE/sizeof(int); i++) {
            printf("%d\n", shm_ptr[i]);
        }
    }

    shmdt(shm_ptr);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
