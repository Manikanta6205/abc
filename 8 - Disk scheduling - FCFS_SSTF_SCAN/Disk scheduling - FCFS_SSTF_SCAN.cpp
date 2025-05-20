#include <bits/stdc++.h> 
using namespace std; 

void plotGraph(const vector<int>& movements) {
    ofstream f("data.dat");
    for (int i = 0; i < movements.size(); ++i)
        f << movements[i] << " " << i << "\n";
    f.close();

    ofstream plt("plot.plt");
    plt << "plot 'data.dat' with linespoints\n";
    plt << "pause -1\n"; // keeps window open
    plt.close();

    system("gnuplot plot.plt");
}

void generateRandomRequests(int n, vector<int>& requests, int maxCylinder) { 
    srand(time(0)); 
    for (int i = 0; i < n; i++) { 
        requests.push_back(rand() % (maxCylinder + 1));
    }
} 

int fcfs(vector<int>& requests, int head) { 
    int totalHeadMovement = 0;
    vector<int> movements(1,head); 
    for (int i = 0; i < requests.size(); i++) { 
        totalHeadMovement += abs(requests[i] - head); 
        head = requests[i]; 
        movements.push_back(head);
    }  
    plotGraph(movements); 
    return totalHeadMovement;
} 

int sstf(vector<int>& requests, int head) { 
    int totalHeadMovement = 0, n = requests.size(); 
    vector<int> visited(n, 0), movements(1,head); 
    for (int i = 0; i < n; i++) { 
        int minDist = INT_MAX, minIndex = -1; 
        for (int j = 0; j < n; j++) { 
            if (!visited[j] && abs(requests[j] - head) < minDist) { 
                minDist = abs(requests[j] - head); 
                minIndex = j;
            }
        } 
        visited[minIndex] = 1; 
        totalHeadMovement += minDist; 
        head = requests[minIndex]; 
        movements.push_back(head);
    } 
    plotGraph(movements); 
    return totalHeadMovement;
}

int scan(vector<int>& requests, int head, int diskSize, int direction) { 
    sort(requests.begin(), requests.end()); 
    int totalHeadMovement = 0, index = 0; 
    vector<int> movements(1,head); 
    for (int i = 0; i < requests.size(); i++) { 
        if (requests[i] > head) { 
            index = i; 
            break;
        }
    } 
    if (direction == 1) { 
        for (int i = index; i < requests.size(); i++) { 
            totalHeadMovement += abs(requests[i] - head); 
            head = requests[i]; 
            movements.push_back(head);
        } 
        totalHeadMovement += abs(diskSize - 1 - head); 
        head = diskSize - 1; 
        movements.push_back(head); 
        for (int i = index - 1; i >= 0; i--) { 
            totalHeadMovement += abs(requests[i] - head); 
            head = requests[i]; 
            movements.push_back(head);
        } 
    } else { 
        for (int i = index - 1; i >= 0; i--) { 
            totalHeadMovement += abs(requests[i] - head);
            head = requests[i]; 
            movements.push_back(head);
        } 
        totalHeadMovement += abs(head - 0); 
        head = 0; 
        movements.push_back(head); 
        for (int i = index; i < requests.size(); i++) { 
            totalHeadMovement += abs(requests[i] - head); 
            head = requests[i]; 
            movements.push_back(head);
        }
    } 
    plotGraph(movements); 
    return totalHeadMovement;
} 
int main() { 
    int n, head, choice; 
    cout << "Enter number of disk requests: "; 
    cin >> n; 
    vector<int> requests; 
    generateRandomRequests(n, requests, 199); 
    cout << "Generated disk requests: "; 
    for (int i = 0; i < n; i++)  
        cout << requests[i] << " "; 
    cout << endl; 
    cout << "Enter initial head position: "; 
    cin >> head; 
    cout << "Choose Disk Scheduling Algorithm:\n1. FCFS\n2. SSTF\n3. SCAN\n"; 
    cin >> choice; 
    int totalHeadMovement = 0; 
    switch (choice) { 
        case 1: totalHeadMovement = fcfs(requests, head); 
                break; 
        case 2: totalHeadMovement = sstf(requests, head); 
                break; 
        case 3: int direction; 
                cout << "Enter head movement direction (0 = left, 1 = right): "; 
                cin >> direction; 
                totalHeadMovement = scan(requests, head, 200, direction); 
                break; 
        default: cout << "Invalid choice!" << endl; 
                return 0;
    } 
    cout << "Total Head Movement: " << totalHeadMovement << " Cylinders" << endl; 
    return 0;
}
