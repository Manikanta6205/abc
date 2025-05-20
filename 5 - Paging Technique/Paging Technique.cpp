#include <stdio.h>

int main() {
    int numberOfPages, pageSize, logicalAddress;
    int pageTable[100]; 

    printf("Enter number of pages (max 100): ");
    scanf("%d", &numberOfPages);

    printf("Enter page size (in bytes): ");
    scanf("%d", &pageSize);

    printf("Enter the frame number for each page (-1 if page not in memory):\n");
    for (int page = 0; page < numberOfPages; page++) {
        printf("Page %d -> Frame: ", page);
        scanf("%d", &pageTable[page]);
    }

    printf("Enter a logical address (0 - %d): ", (numberOfPages * pageSize) - 1);
    scanf("%d", &logicalAddress);

    int pageNumber = logicalAddress / pageSize;
    int offset = logicalAddress % pageSize;

    if (pageNumber >= numberOfPages) {
        printf("Invalid logical address! Page number %d is out of bounds.\n", pageNumber);
        return 1;
    }

    if (pageTable[pageNumber] == -1) {
        printf("Page fault! Page %d is not in memory.\n", pageNumber);
        return 1;
    }

    int frameNumber = pageTable[pageNumber];
    int physicalAddress = frameNumber * pageSize + offset;

    printf("\n--- Address Translation ---\n");
    printf("Logical Address: %d\n", logicalAddress);
    printf("Page Number: %d\n", pageNumber);
    printf("Offset: %d\n", offset);
    printf("Mapped to Frame: %d\n", frameNumber);
    printf("Physical Address: %d\n", physicalAddress);

    return 0;
}
