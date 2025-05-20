#include <bits/stdc++.h>
using namespace std;

vector<int> blockSize, originalBlockSize, blockStatus;
vector<int> processSize, processAllocation;

void copyBlocks() {
    originalBlockSize = blockSize;
}

void resetBlocks() {
    blockSize = originalBlockSize;
    fill(blockStatus.begin(), blockStatus.end(), 0);
    fill(processAllocation.begin(), processAllocation.end(), -1);
}

void printBlockStatus() {
    cout << "\nCurrent Block Allocation:\n";
    for (int i = 0; i < blockSize.size(); i++) {
        cout << "Block " << i + 1 << ": ";
        if (blockStatus[i] == 1) {
            bool found = false;
            for (int j = 0; j < processAllocation.size(); j++) {
                if (processAllocation[j] == i) {
                    cout << "Process " << j + 1 << " allocated (" << blockSize[i] << " left)\n";
                    found = true;
                    break;
                }
            }
            if (!found)
                cout << "Filled (" << blockSize[i] << ")\n";
        } else {
            cout << "Free (" << blockSize[i] << ")\n";
        }
    }

    cout << "\nProcesses without allocated blocks:\n";
    for (int i = 0; i < processAllocation.size(); i++)
        if (processAllocation[i] == -1)
            cout << "Process " << i + 1 << ": " << processSize[i] << "\n";
}

void firstFit() {
    for (int i = 0; i < processSize.size(); i++) {
        for (int j = 0; j < blockSize.size(); j++) {
            if (blockStatus[j] == 0 && blockSize[j] >= processSize[i]) {
                processAllocation[i] = j;
                blockSize[j] -= processSize[i];
                blockStatus[j] = 1;
                break;
            }
        }
    }
}

void bestFit() {
    for (int i = 0; i < processSize.size(); i++) {
        int bestIndex = -1;
        for (int j = 0; j < blockSize.size(); j++) {
            if (blockStatus[j] == 0 && blockSize[j] >= processSize[i]) {
                if (bestIndex == -1 || blockSize[j] < blockSize[bestIndex]) {
                    bestIndex = j;
                }
            }
        }
        if (bestIndex != -1) {
            processAllocation[i] = bestIndex;
            blockSize[bestIndex] -= processSize[i];
            blockStatus[bestIndex] = 1;
        }
    }
}

void worstFit() {
    for (int i = 0; i < processSize.size(); i++) {
        int worstIndex = -1;
        for (int j = 0; j < blockSize.size(); j++) {
            if (blockStatus[j] == 0 && blockSize[j] >= processSize[i]) {
                if (worstIndex == -1 || blockSize[j] > blockSize[worstIndex]) {
                    worstIndex = j;
                }
            }
        }
        if (worstIndex != -1) {
            processAllocation[i] = worstIndex;
            blockSize[worstIndex] -= processSize[i];
            blockStatus[worstIndex] = 1;
        }
    }
}

int main() {
    srand(time(0));
    int blockCount, processCount;

    cout << "Enter number of memory blocks: ";
    cin >> blockCount;

    blockSize.resize(blockCount);
    blockStatus.resize(blockCount);

    for (int i = 0; i < blockCount; i++) {
        blockSize[i] = rand() % 50 + 10;
        blockStatus[i] = rand() % 2; // randomly assign block as filled or free
    }

    copyBlocks();

    cout << "\nGenerated Blocks:\n";
    for (int i = 0; i < blockCount; i++) {
        cout << "Block " << i + 1 << ": " << blockSize[i] 
             << " (Status: " << (blockStatus[i] == 0 ? "Free" : "Filled") << ")\n";
    }

    cout << "\nEnter number of processes: ";
    cin >> processCount;

    processSize.resize(processCount);
    processAllocation.resize(processCount, -1);

    for (int i = 0; i < processCount; i++)
        processSize[i] = rand() % 60 + 5;

    cout << "\nGenerated Processes:\n";
    for (int i = 0; i < processCount; i++)
        cout << "Process " << i + 1 << ": " << processSize[i] << "\n";

    int choice;
    do {
        cout << "\nMemory Allocation Strategies:\n";
        cout << "1. First Fit\n";
        cout << "2. Best Fit\n";
        cout << "3. Worst Fit\n";
        cout << "4. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        resetBlocks();
        // keep some blocks filled randomly again
        for (int i = 0; i < blockStatus.size(); i++) 
            if (rand() % 4 == 0) blockStatus[i] = 1;

        switch (choice) {
            case 1:
                firstFit();
                printBlockStatus();
                break;
            case 2:
                bestFit();
                printBlockStatus();
                break;
            case 3:
                worstFit();
                printBlockStatus();
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
