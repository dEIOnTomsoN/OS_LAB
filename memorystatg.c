#include <stdio.h>

void firstFit(int blockSize[], int m, int processSize[], int n) {
    int allocated[10];

    for (int i = 0; i < n; i++) {
        allocated[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocated[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }

    printf("\nProcess\t\tData Size\t\tAllocated\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t\t", i + 1, processSize[i]);
        if (allocated[i] == -1) {
            printf("Not allocated\n");
        } else {
            printf("%d\n", allocated[i] + 1);
        }
    }
}

void worstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[10];

    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int worstIndex = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIndex == -1 || blockSize[worstIndex] < blockSize[j]) {
                    worstIndex = j;
                }
            }
        }
        if (worstIndex != -1) {
            allocation[i] = worstIndex;
            blockSize[worstIndex] -= processSize[i];
        }
    }

    printf("\nProcess\t\tData Size\t\tAllocated\t\tFragments\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t\t", i + 1, processSize[i]);
        if (allocation[i] == -1) {
            printf("Not allocated\n");
        } else {
            printf("%d\t\t\t%d\n", allocation[i] + 1, blockSize[allocation[i]]);
        }
    }
}

void bestFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[10];

    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int bestIndex = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIndex == -1 || blockSize[bestIndex] > blockSize[j]) {
                    bestIndex = j;
                }
            }
        }

        if (bestIndex != -1) {
            allocation[i] = bestIndex;
            blockSize[bestIndex] -= processSize[i];
        }
    }

    printf("\nProcess\t\tData Size\t\tAllocated\t\tFragments\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t\t", i + 1, processSize[i]);
        if (allocation[i] == -1) {
            printf("Not allocated\n");
        } else {
            printf("%d\t\t\t%d\n", allocation[i] + 1, blockSize[allocation[i]]);
        }
    }
}

int main() {
    int m, n, blockSize[10], processSize[10];
    int choice;
do {
printf("\nChoose Allocation Algorithm:\n");
        printf("1. First Fit\n");
        printf("2. Worst Fit\n");
        printf("3. Best Fit\n");
        
        printf("En	ter your choice: ");
        scanf("%d", &choice);
    printf("Enter the number of Blocks: ");
    scanf("%d", &m);
    printf("Enter the Block sizes of each: ");
    for (int i = 0; i < m; i++) {
        scanf("%d", &blockSize[i]);
    }

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the Process size of each: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &processSize[i]);
    }

    
        

        switch (choice) {
            case 1:
                printf("\nFirst Fit:\n");
                firstFit(blockSize, m, processSize, n);
                break;
            case 2:
                printf("\nWorst Fit:\n");
                worstFit(blockSize, m, processSize, n);
                break;
            case 3:
                printf("\nBest Fit:\n");
                bestFit(blockSize, m, processSize, n);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }
    } while (choice != 4);

    return 0;
}

