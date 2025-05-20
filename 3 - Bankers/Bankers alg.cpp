#include <iostream>
#include <vector>
using namespace std;

void pm(const vector<vector<int>>& m, const string& n) {
    cout << n << " matrix:" << endl;
    for (const auto& r : m) {
        for (int v : r) cout << v << " ";
        cout << endl;
    }
}

void pv(const vector<int>& v, const string& n) {
    cout << n << " vector: [";
    for (size_t i = 0; i < v.size(); i++) {
        cout << v[i];
        if (i != v.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

bool safe(const vector<int>& nd, const vector<int>& av, int r) {
    for (int i = 0; i < r; i++) if (nd[i] > av[i]) return false;
    return true;
}

bool ba(vector<vector<int>>& mx, vector<vector<int>>& al, vector<int>& av, int n, int r) {
    vector<bool> f(n, false);
    vector<int> seq;
    int done = 0;
    vector<vector<int>> nd(n, vector<int>(r));

    cout << "\nNeed matrix:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < r; j++) {
            nd[i][j] = mx[i][j] - al[i][j];
            cout << nd[i][j] << " ";
        }
        cout << endl;
    }

    while (done < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!f[i] && safe(nd[i], av, r)) {
                for (int j = 0; j < r; j++) av[j] += al[i][j];
                seq.push_back(i);
                f[i] = true;
                done++;
                found = true;
            }
        }
        if (!found) return false;
    }

    cout << "\nSafe sequence: ";
    for (int i = 0; i < seq.size(); i++) {
        cout << "P" << seq[i];
        if (i < seq.size() - 1) cout << " -> ";
    }
    cout << endl;
    return true;
}

int main() {
    int n, r;
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter number of resources: ";
    cin >> r;

    vector<int> inst(r);
    cout << "Enter instances for each resource:" << endl;
    for (int i = 0; i < r; i++) {
        cout << "Resource " << i << ": ";
        cin >> inst[i];
    }

    vector<vector<int>> mx(n, vector<int>(r));
    vector<vector<int>> al(n, vector<int>(r));
    vector<int> av(r);

    cout << "\nEnter the maximum resource matrix:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Process " << i << ": ";
        for (int j = 0; j < r; j++) {
            while (true) {
                cin >> mx[i][j];
                if (mx[i][j] <= inst[j]) break;
                cout << "Error: Value cannot exceed resource instance (" << inst[j] << "). Try again: ";
            }
        }
    }

    cout << "\nEnter the allocation matrix:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Process " << i << ": ";
        for (int j = 0; j < r; j++) {
            while (true) {
                cin >> al[i][j];
                if (al[i][j] <= mx[i][j]) break;
                cout << "Error: Allocation cannot exceed maximum (" << mx[i][j] << "). Try again: ";
            }
        }
    }

    for (int j = 0; j < r; j++) {
        int sum = 0;
        for (int i = 0; i < n; i++) sum += al[i][j];
        av[j] = inst[j] - sum;
    }

    pm(mx, "\nMax");
    pm(al, "Alloc");
    pv(av, "Avail");

    if (ba(mx, al, av, n, r)) {
        cout << "\nSystem is in a safe state." << endl;
    } else {
        cout << "\nSystem is in an unsafe state." << endl;
    }

    return 0;
}
