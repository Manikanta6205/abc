#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cout << "Enter 'N' value: ";
    cin >> n;

    int id[n], bt[n], at[n], ct[n], tat[n], wt[n];

    cout << "Enter burst time:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> bt[i];
    }

    cout << "Enter arrival time:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> at[i];
        id[i] = i + 1;
    }

    // Sort by arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (at[j] > at[j + 1]) {
                swap(bt[j], bt[j + 1]);
                swap(at[j], at[j + 1]);
                swap(id[j], id[j + 1]);
            }
        }
    }

    int sum = at[0];
    for (int i = 0; i < n; i++) {
        sum += bt[i];
        ct[i] = sum;
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        if (i < n - 1 && sum < at[i + 1])
            sum = at[i + 1];
    }

    cout << "Process\tArrival\tBurst\tWaiting\tTurnAround\tCompletion" << endl;
    for (int i = 0; i < n; i++) {
        cout << "P[" << id[i] << "]\t" << at[i] << "\t" << bt[i] << "\t"
             << wt[i] << "\t" << tat[i] << "\t\t" << ct[i] << endl;
    }

    int total_wt = 0, total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
    }

    cout << "Average waiting time: " << (float)total_wt / n << endl;
    cout << "Average turn around time: " << (float)total_tat / n << endl;

    cout << "Gantt Chart" << endl;
    for (int i = 0; i < n; i++)
        cout << "----";
    cout << endl;

    for (int i = 0; i < n; i++)
        cout << "| P" << id[i] << " ";
    cout << "|" << endl;

    for (int i = 0; i < n; i++)
        cout << "----";
    cout << endl;

    for (int i = 0; i < n; i++)
        cout << tat[i] << "\t";
    cout << endl;

    return 0;
}
