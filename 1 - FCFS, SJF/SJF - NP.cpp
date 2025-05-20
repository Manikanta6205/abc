#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cout << "Enter N value: ";
    cin >> n;

    vector<int> bt(n), at(n), ct(n), tat(n), wt(n), order, time;
    vector<bool> completed(n, false);

    cout << "Enter Burst Times: " << endl;
    for (int i = 0; i < n; i++)
        cin >> bt[i];

    cout << "Enter Arrival Times: " << endl;
    for (int i = 0; i < n; i++)
        cin >> at[i];

    int completed_count = 0, current_time = 0;

    while (completed_count < n) {
        int id = -1, min_bt = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (!completed[i] && at[i] <= current_time && bt[i] < min_bt) {
                min_bt = bt[i];
                id = i;
            }
        }

        if (id == -1) {
            current_time++;
            time.push_back(-1); // Idle time
            continue;
        }

        current_time += bt[id];
        ct[id] = current_time;
        tat[id] = ct[id] - at[id];
        wt[id] = tat[id] - bt[id];
        completed[id] = true;
        completed_count++;
        order.push_back(id);
        time.push_back(current_time);
    }

    cout << "Process\tArrival\tBurst\tWaiting\tTurnAround\tCompletion" << endl;
    for (int i = 0; i < n; i++) {
        cout << "P[" << i + 1 << "]\t" << at[i] << "\t" << bt[i] << "\t"
             << wt[i] << "\t" << tat[i] << "\t\t" << ct[i] << endl;
    }

    float total_wt = accumulate(wt.begin(), wt.end(), 0);
    float total_tat = accumulate(tat.begin(), tat.end(), 0);

    cout << "Average waiting time: " << total_wt / n << endl;
    cout << "Average turnaround time: " << total_tat / n << endl;

    cout << "Gantt Chart" << endl;
    for (int i = 0; i < order.size(); i++)
        cout << "----";
    cout << endl;

    for (auto id : order)
        cout << "| P" << id + 1 << " ";
    cout << "|" << endl;

    for (int i = 0; i < order.size(); i++)
        cout << "----";
    cout << endl;

    return 0;
}
