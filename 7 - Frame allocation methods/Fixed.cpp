#include <bits/stdc++.h>
using namespace std;

int main() {
    int np, nf, i, j, x;
    cout << "Enter no of processes, no of frames" << endl;
    cin >> np >> nf;

    vector<int> pro(np), fra(nf, -1);

    cout << "Enter no of frames required for each process" << endl;
    for (i = 0; i < np; i++)
        cin >> pro[i];

    int fz = nf / np, id = 0;

    for (i = 0; i < np; i++) {
        if (id == nf)
            break;

        j = id + fz;
        for (id = id; id < min(j, nf); id++) {
            if (pro[i] > 0) {
                fra[id] = i + 1;
                pro[i]--;
            }
        }
    }

    cout << "frame allocation of processes :" << endl;
    for (i = 0; i < nf; i++) {
        if (fra[i] == -1)
            cout << "E ";
        else
            cout << "p" << fra[i] << " ";
    }

    cout << endl;
}
