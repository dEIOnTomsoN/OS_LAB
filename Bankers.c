Certainly, here's a simplified implementation of the Banker's algorithm in C without the request and release functionalities:

```c
#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int available[MAX_RESOURCES];
int max[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];

int num_processes, num_resources;

bool isSafe() {
    bool finish[num_processes];
    int work[num_resources];

    for (int i = 0; i < num_resources; ++i)
        work[i] = available[i];

    for (int i = 0; i < num_processes; ++i)
        finish[i] = false;

    int count = 0;
    while (count < num_processes) {
        bool found = false;
        for (int i = 0; i < num_processes; ++i) {
            if (!finish[i]) {
                bool canFinish = true;
                for (int j = 0; j < num_resources; ++j) {
                    if (need[i][j] > work[j]) {
                        canFinish = false;
                        break;
                    }
                }
                if (canFinish) {
                    for (int j = 0; j < num_resources; ++j)
                        work[j] += allocation[i][j];
                    finish[i] = true;
                    found = true;
                    ++count;
                }
            }
        }
        if (!found)
            return false;
    }
    return true;
}

int main() {
    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);
    printf("Enter the number of resources: ");
    scanf("%d", &num_resources);

    printf("Enter the available resources:\n");
    for (int i = 0; i < num_resources; ++i)
        scanf("%d", &available[i]);

    printf("Enter the maximum demand of each process:\n");
    for (int i = 0; i < num_processes; ++i)
        for (int j = 0; j < num_resources; ++j)
            scanf("%d", &max[i][j]);

    printf("Enter the allocation of resources to each process:\n");
    for (int i = 0; i < num_processes; ++i)
        for (int j = 0; j < num_resources; ++j)
            scanf("%d", &allocation[i][j]);

    for (int i = 0; i < num_processes; ++i)
        for (int j = 0; j < num_resources; ++j)
            need[i][j] = max[i][j] - allocation[i][j];

    if (isSafe())
        printf("System is in safe state.\n");
    else
        printf("System is in unsafe state.\n");

    }