#include <bits/stdc++.h>
using namespace std;

int main() {
    float np, nf, i, j, x, sum = 0;
    cout << "Enter no of processes, no of frames" << endl;
    cin >> np >> nf;

    vector<float> pro(np), fra(nf, -1), pp(np);

    cout << "Enter no of frames required for each process" << endl;
    for (i = 0; i < np; i++) {
        cin >> pro[i];
        sum += pro[i];
    }

    int id = 0;
    for (i = 0; i < np; i++)
        pp[i] = ceil((pro[i] / sum) * nf);

    for (i = 0; i < np; i++) {
        if (id == nf)
            break;

        j = id + pp[i];
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
