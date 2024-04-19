#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct {
    int pageNum;
    int referenceCount;
    bool isLoaded;
} Page;


void FIFO(int pages[], int numPages, int capacity);
void LRU(int pages[], int numPages, int capacity);
void LFU(int pages[], int numPages, int capacity);

int main() {
    int capacity, numPages;

    printf("Enter the capacity of the memory: ");
    scanf("%d", &capacity);

    printf("Enter the number of pages: ");
    scanf("%d", &numPages);

    int pages[numPages];

    printf("Enter the page reference sequence:\n");
    for (int i = 0; i < numPages; i++) {
        scanf("%d", &pages[i]);
    }

    printf("\nFIFO Page Replacement Algorithm:\n");
    FIFO(pages, numPages, capacity);

    printf("\nLRU Page Replacement Algorithm:\n");
    LRU(pages, numPages, capacity);

    printf("\nLFU Page Replacement Algorithm:\n");
    LFU(pages, numPages, capacity);

    return 0;
}

void FIFO(int pages[], int numPages, int capacity) {
    int frame[capacity], frameCount = 0, pageFaults = 0, frameIndex = 0;

    for (int i = 0; i < numPages; i++) {
        bool pageExists = false;

        for (int j = 0; j < frameCount; j++) {
            if (frame[j] == pages[i]) {
                pageExists = true;
                break;
            }
        }

        if (!pageExists) {
            if (frameCount < capacity) {
                frame[frameCount++] = pages[i];
            } else {
                frame[frameIndex++] = pages[i];
                frameIndex %= capacity;
            }
            pageFaults++;
        }
    }

    printf("Page Faults: %d\n", pageFaults);
}

void LRU(int pages[], int numPages, int capacity) {
    int frame[capacity], frameCount = 0, pageFaults = 0, counter = 0;
    int leastRecentlyUsed[capacity];

    for (int i = 0; i < capacity; i++) {
        leastRecentlyUsed[i] = -1;
    }

    for (int i = 0; i < numPages; i++) {
        bool pageExists = false;

        for (int j = 0; j < frameCount; j++) {
            if (frame[j] == pages[i]) {
                pageExists = true;
                leastRecentlyUsed[j] = counter++;
                break;
            }
        }

        if (!pageExists) {
            if (frameCount < capacity) {
                frame[frameCount++] = pages[i];
                leastRecentlyUsed[frameCount - 1] = counter++;
            } else {
                int index = 0, min = leastRecentlyUsed[0];
                for (int j = 1; j < capacity; j++) {
                    if (leastRecentlyUsed[j] < min) {
                        min = leastRecentlyUsed[j];
                        index = j;
                    }
                }
                frame[index] = pages[i];
                leastRecentlyUsed[index] = counter++;
            }
            pageFaults++;
        }
    }

    printf("Page Faults: %d\n", pageFaults);
}

void LFU(int pages[], int numPages, int capacity) {
    Page frame[capacity];
    int pageFaults = 0;

    for (int i = 0; i < capacity; i++) {
        frame[i].pageNum = -1;
        frame[i].referenceCount = 0;
        frame[i].isLoaded = false;
    }

    for (int i = 0; i < numPages; i++) {
        bool pageExists = false;

        for (int j = 0; j < capacity; j++) {
            if (frame[j].pageNum == pages[i]) {
                pageExists = true;
                frame[j].referenceCount++;
                break;
            }
        }

        if (!pageExists) {
            int minIndex = 0;
            for (int j = 1; j < capacity; j++) {
                if (frame[j].referenceCount < frame[minIndex].referenceCount) {
                    minIndex = j;
                }
            }
            frame[minIndex].pageNum = pages[i];
            frame[minIndex].referenceCount = 1;
            frame[minIndex].isLoaded = true;
            pageFaults++;
        }
    }

    printf("Page Faults: %d\n", pageFaults);
}
