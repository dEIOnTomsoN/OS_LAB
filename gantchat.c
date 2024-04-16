Here's the modified version of the program without comments:

```c
#include <stdio.h>

struct Process {
    int pid;
    int arrival;
    int burst;
};

void display_FCFS(struct Process processes[], int n) {
    int current_time = 0;
    printf("FCFS Gantt Chart:\n");
    printf("|");
    for (int i = 0; i < n; i++) {
        printf(" P%d |", processes[i].pid);
        current_time += processes[i].burst;
    }
    printf("\n");
    printf("0");
    for (int i = 0; i < n; i++) {
        printf("    %d", current_time);
    }
    printf("\n");
}

void display_SJF(struct Process processes[], int n) {
    int current_time = 0;
    printf("SJF Gantt Chart:\n");
    printf("|");
    for (int i = 0; i < n; i++) {
        printf(" P%d |", processes[i].pid);
        current_time += processes[i].burst;
    }
    printf("\n");
    printf("0");
    for (int i = 0; i < n; i++) {
        printf("    %d", current_time);
    }
    printf("\n");
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process *processes = (struct Process *)malloc(n * sizeof(struct Process));

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrival);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst);
        processes[i].pid = i + 1;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival > processes[j + 1].arrival) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    display_FCFS(processes, n);
    printf("\n");

    display_SJF(processes, n);
    printf("\n");

    free(processes);

    return 0;
}
```