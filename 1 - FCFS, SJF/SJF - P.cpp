#include <bits/stdc++.h>
using namespace std;

struct Process {
    int id;
    int at, bt, rbt;
    int ct, wt, tat;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> p(n);
    vector<bool> isComp(n, false);
    vector<string> ganttChart;
    vector<int> ganttTimes;

    cout << "Enter Arrival Times:\n";
    for (int i = 0; i < n; i++) {
        cin >> p[i].at;
        p[i].id = i + 1;
    }

    cout << "Enter Burst Times:\n";
    for (int i = 0; i < n; i++) {
        cin >> p[i].bt;
        p[i].rbt = p[i].bt;
    }

    int start = 0, comp = 0;

    while (comp < n) {
        int sj = -1;
        int minbt = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= start && !isComp[i] && p[i].rbt > 0 && p[i].rbt < minbt) {
                minbt = p[i].rbt;
                sj = i;
            }
        }

        if (sj != -1) {
            if (ganttChart.empty() || ganttChart.back() != "P" + to_string(p[sj].id)) {
                ganttChart.push_back("P" + to_string(p[sj].id));
                ganttTimes.push_back(start);
            }
            start++;
            p[sj].rbt--;
            if (p[sj].rbt == 0) {
                p[sj].ct = start;
                p[sj].tat = p[sj].ct - p[sj].at;
                p[sj].wt = p[sj].tat - p[sj].bt;
                isComp[sj] = true;
                comp++;
            }
        } else {
            if (ganttChart.empty() || ganttChart.back() != "ID") {
                ganttChart.push_back("ID");
                ganttTimes.push_back(start);
            }
            start++;
        }
    }

    ganttTimes.push_back(start); // Final time

    // Output process info
    cout << "\nProcess\tArrival\tBurst\tWaiting\tTurnaround\tCompletion\n";
    for (const auto& proc : p) {
        cout << "P[" << proc.id << "]\t" << proc.at << "\t" << proc.bt << "\t"
             << proc.wt << "\t" << proc.tat << "\t\t" << proc.ct << "\n";
    }

    // Calculate averages
    float totalWT = 0, totalTAT = 0;
    for (const auto& proc : p) {
        totalWT += proc.wt;
        totalTAT += proc.tat;
    }

    cout << "\nAverage Waiting Time: " << fixed << setprecision(2) << totalWT / n << "\n";
    cout << "Average Turnaround Time: " << fixed << setprecision(2) << totalTAT / n << "\n";

    // Print Gantt Chart
    cout << "\nGantt Chart:\n";
    for (size_t i = 0; i < ganttChart.size(); i++) cout << "------";
    cout << "\n| ";
    for (const auto& label : ganttChart) cout << label << " | ";
    cout << "\n";
    for (size_t i = 0; i < ganttChart.size(); i++) cout << "------";
    cout << "\n";
    for (int t : ganttTimes) cout << t << "\t";
    cout << "\n";

	return 0;
}
