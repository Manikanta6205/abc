#include <bits/stdc++.h> 
using namespace std; 

void printStatus(int i, const vector<int>& v, int flag, int page) { 
    cout << i + 1 << "   | "; 
    for (int j = 0; j < v.size(); j++)  
        cout << v[j] << " "; 
    cout << "  |  " << (flag ? "HIT" : "FAULT") << " |  " << page << endl;
}

void FIFO(int n, int c, const vector<int>& ve) 
{ 
    int a = 0, b = 0, l = 0; 
    vector<int> v(c, -1); 
    map<int, int> m; 
    for (int i = 0; i < n; i++) { 
        int flag = 0; 
        if (m[ve[i]] == 1) { 
            flag = 1; 
            a++; 
        } 
        else 
        { 
            m[ve[i]] = 1; 
            m[v[l]] = 0; 
            v[l] = ve[i]; 
            l = (l + 1) % c; 
            b++;
        } 
        printStatus(i, v, flag, ve[i]);
    } 
    cout << "HITS : " << a << "\nFAULTS : " << b << endl;
}

void LRU(int n, int c, const vector<int>& ve) { 
    int a = 0, b = 0; 
    vector<int> v; 
    map<int, int> m; 
    for (int i = 0; i < n; i++) { 
        int flag = 0; 
        if (m[ve[i]] == 1) { 
            flag = 1; 
            v.erase(find(v.begin(), v.end(), ve[i])); 
            v.push_back(ve[i]); 
            a++; 
        } 
        else 
        { 
            m[ve[i]] = 1;
            if (v.size() == c) { 
                m[v[0]] = 0; 
                v.erase(v.begin());
            } 
            v.push_back(ve[i]); 
            b++;
        } 
        printStatus(i, v, flag, ve[i]);
    } 
    cout << "HITS : " << a << "\nFAULTS : " << b << endl;
}

void Optimal(int n, int c, const vector<int>& ve) {
    vector<int> frames;
    int hits = 0, faults = 0;

    for (int i = 0; i < n; ++i) {
        int page = ve[i];
        bool isHit = false;

        // Check if page is already in frames
        for (int f = 0; f < frames.size(); ++f) {
            if (frames[f] == page) {
                isHit = true;
                hits++;
                break;
            }
        }

        if (!isHit) {
            faults++;
            if (frames.size() < c) {
                frames.push_back(page);
            } else {
                // Find the page to replace using Optimal logic
                int replaceIndex = -1, farthest = -1;
                for (int j = 0; j < c; ++j) {
                    int nextUse = -1;
                    for (int k = i + 1; k < n; ++k) {
                        if (ve[k] == frames[j]) {
                            nextUse = k;
                            break;
                        }
                    }
                    if (nextUse == -1) {
                        replaceIndex = j;
                        break;
                    }
                    if (nextUse > farthest) {
                        farthest = nextUse;
                        replaceIndex = j;
                    }
                }
                frames[replaceIndex] = page;
            }
        }

        printStatus(i, frames, isHit, page);
    }

    cout << "HITS : " << hits << "\nFAULTS : " << faults << endl;
}


int main() { 
    int n, c, choice; 
    vector<int> ve; 
    while (true) {
        cout << "\nPage Replacement Algorithms Menu\n"; 
        cout << "1. FIFO\n2. LRU\n3. Optimal\n4. Exit\nEnter your choice: "; 
        cin >> choice; 
        if (choice == 4) 
            break; 
        cout << "No of pages: "; 
        cin >> n; 
        ve.resize(n); 
        srand(time(0)); 
        for (int i = 0; i < n; i++) { 
            ve[i] = rand() % 11; 
        } 
        cout << "No of frames: "; 
        cin >> c; 
        switch (choice) { 
            case 1: 
                cout << "\nFIFO Algorithm:\n"; 
                FIFO(n, c, ve); 
                break; 
            case 2: 
                cout << "\nLRU Algorithm:\n"; 
                LRU(n, c, ve); 
                break; 
            case 3: 
                cout << "\nOptimal Algorithm:\n"; 
                Optimal(n, c, ve); 
                break; 
            default: 
                cout << "Invalid choice. Please try again.\n";}} 

	return 0;
}
