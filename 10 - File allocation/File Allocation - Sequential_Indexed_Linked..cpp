#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <utility>
using namespace std;

vector<vector<int> > v; 
int n, m; 


void initializeMemory() {
    cout << "Enter memory Grid dimension (rows and columns) : ";
    cin >> n >> m;
    v.assign(n, vector<int>(m));

    cout << "Grid Allocation" << endl;
    srand(time(0));
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            v[i][j] = rand() % 2;
            cout << v[i][j] << " ";
            if(v[i][j] == 1)
                v[i][j] = -1;
        }
        cout << endl;
    }
}

// Display the memory grid
void displayMemoryGrid() {
    cout << "\nFinal Memory Grid:" << endl;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(v[i][j] == -1)
                cout << "F ";
            else if(v[i][j] == 0)
                cout << "E ";
            else
                cout << v[i][j] << " ";
        }
        cout << endl;
    }
}

// Contiguous allocation method
void contiguousAllocation(vector<int>& pro) {
    for (int i = 1; i < pro.size(); i++) {
        int count = 0;
        vector<pair<int, int> > positions;

        for (int j = 0; j < n; j++) {
            for (int k = 0; k < m; k++) {
                if (v[j][k] == 0) {
                    positions.push_back({j, k});
                    count++;
                    if (count == pro[i]) break;
                } else {
                    positions.clear();
                    count = 0;
                }
            }
            if (count == pro[i]) break;
        }

        if (count == pro[i]) {
            for (int k = 0;k < positions.size();k++) {
                v[positions[k].first][positions[k].second] = i;
            }
        } else {
            cout << "Not enough contiguous memory for process " << i << " needing " << pro[i] << " blocks." << endl;
        }
    }
}

// Linked List allocation method
void linkedListAllocation(const vector<int>& pro) {
    for (int i = 1; i < pro.size(); i++) {
        int count = 0;
        vector<pair<int, int> > positions;

        for (int j = 0; j < n; j++) {
            for (int k = 0; k < m; k++) {
                if (v[j][k] == 0) {
                    positions.push_back({j, k});
                    count++;
                    if (count == pro[i]) break;
                }
            }
            if (count == pro[i]) break;
        }

        if (count == pro[i]) {
            for (int k = 0;k < positions.size();k++) {
                v[positions[k].first][positions[k].second] = i;
            }
        } else {
            cout << "Not enough memory for process " << i << " needing " << pro[i] << " blocks." << endl;
        }
    }
}

void indexedAllocation(vector<int>& pro) {
    int i, j, k;
    vector<pair<int, int> > vp;
    vector<pair<int, int> > positions;
    for(i = 1; i < pro.size(); i++) {
        pro[i]++;
    }
    for (i = 1; i <= pro.size() - 1; i++) {
        int count = 0;
        positions.clear();
        for (j = 0; j < n; j++) {
            for (k = 0; k < m; k++) {
                if (v[j][k] == 0) {
                    positions.push_back({j, k});
                    count++;
                    if (count == pro[i]) break;
                }
            }
            if (count == pro[i]) break;
        }
        if (count == pro[i]) {
            vp.push_back(positions[positions.size() - 1]);
            for (int idx = 0; idx < positions.size(); idx++) {
                v[positions[idx].first][positions[idx].second] = i;
            }
        } else {
            cout << "Not enough memory for process " << i << " needing " << pro[i] << " blocks." << endl;
            vp.push_back({-1, -1});
        }
    }

    cout << "INodes locations: " << endl;
    for(i = 0; i < vp.size(); i++) {
        cout << i + 1 << " : ";
        if (vp[i].first == -1) {
            cout << "No Space" << endl;
        } else {
            cout << vp[i].first << " " << vp[i].second << endl;
        }
    }
}

int main() {
    initializeMemory();

    int p;
    cout << "Enter number of processes: ";
    cin >> p;

    vector<int> pro(p + 1);
    cout << "Enter blocks required for each process:\n";
    for (int i = 1; i <= p; i++) {
        cout << "Process " << i << ": ";
        cin >> pro[i];
    }

    int choice;
    do {
        cout << "\n==== Memory Allocation Menu ====" << endl;
        cout << "1. Contiguous Allocation" << endl;
        cout << "2. Linked List Allocation" << endl;
        cout << "3. Indexed Allocation" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                contiguousAllocation(pro);
                displayMemoryGrid();
                break;
            case 2:
                linkedListAllocation(pro);
                displayMemoryGrid();
                break;
            case 3:
                indexedAllocation(pro);
                displayMemoryGrid();
                break;
            case 4:
                cout << "Exiting program..." << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 4);
    
    return 0;
}
