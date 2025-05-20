#include <bits/stdc++.h>
using namespace std;

struct Process {
    int id;
    int at, bt, rbt, priority;
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

    cout << "Enter Priorities (Lower number = Higher priority):\n";
    for (int i = 0; i < n; i++) {
        cin >> p[i].priority;
    }

    int current_time = 0, comp = 0;

    while (comp < n) {
        int hp = -1;
        int minPriority = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= current_time && !isComp[i] && p[i].rbt > 0) {
                if (p[i].priority < minPriority) {
                    minPriority = p[i].priority;
                    hp = i;
                }
            }
        }

        if (hp != -1) {
            if (ganttChart.empty() || ganttChart.back() != "P" + to_string(p[hp].id)) {
                ganttChart.push_back("P" + to_string(p[hp].id));
                ganttTimes.push_back(current_time);
            }

            current_time++;
            p[hp].rbt--;

            if (p[hp].rbt == 0) {
                p[hp].ct = current_time;
                p[hp].tat = p[hp].ct - p[hp].at;
                p[hp].wt = p[hp].tat - p[hp].bt;
                isComp[hp] = true;
                comp++;
            }
        } else {
            if (ganttChart.empty() || ganttChart.back() != "IDLE") {
                ganttChart.push_back("IDLE");
                ganttTimes.push_back(current_time);
            }
            current_time++;
        }
    }

    ganttTimes.push_back(current_time); // Final time

    // Output process info
    cout << "\nProcess\tArrival\tBurst\tPriority\tWaiting\tTurnaround\tCompletion\n";
    for (const auto& proc : p) {
        cout << "P[" << proc.id << "]\t" << proc.at << "\t" << proc.bt << "\t"
             << proc.priority << "\t\t" << proc.wt << "\t" << proc.tat << "\t\t" << proc.ct << "\n";
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
    for (int i = 0; i < ganttChart.size(); i++) cout << "------";
    cout << "\n| ";
    for (const auto& label : ganttChart) cout << label << " | ";
    cout << "\n";
    for (int i = 0; i < ganttChart.size(); i++) cout << "------";
    cout << "\n";
    for (int t : ganttTimes) cout << t << "\t";
    cout << "\n";

	return 0;
}