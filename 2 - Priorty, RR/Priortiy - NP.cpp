#include <bits/stdc++.h>  
using namespace std;  
int main() {  
 int n;  
 cout << "Enter N value: "; cin >> n;  
 vector<int> bt(n), at(n), ct(n), tat(n), wt(n), pr(n), order, time;  
 vector<bool> completed(n, false);  
 cout << "Enter Burst Times: " << endl;  
 for (int i = 0; i < n; i++)  
     cin >> bt[i];  
 cout << "Enter Arrival Times: " << endl;  
 for (int i = 0; i < n; i++)  
     cin >> at[i];  
 cout << "Enter Priorities (Lower number = Higher priority): " << endl;  
 for (int i = 0; i < n; i++)  
     cin >> pr[i];  
 int completed_count = 0, current_time = 0;  
 while (completed_count < n) {  
     int id = -1, min_pr = INT_MAX;  
     for (int i = 0; i < n; i++) {  
         if (!completed[i] && at[i] <= current_time && pr[i] < min_pr) {  
             min_pr = pr[i];  
             id = i;  
         }  
     }  
     if (id == -1) {  
         current_time++;  
         time.push_back(-1);  
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
 cout << "Process\tArrival\tBurst\tPriority\tWaiting\tTurnAround\tCompletion" << endl;  
 for (int i = 0; i < n; i++) {  
     printf("P[%d]\t%d\t%d\t%d\t\t%d\t%d\t\t%d\n", 
         i + 1, at[i], bt[i], pr[i], wt[i], tat[i], ct[i]);  
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
 cout << "0";  
 for (int i = 0; i < time.size(); i++) {  
     if (time[i] != -1)  
         printf("%4d", time[i]);  
 }  
 cout << endl; 
return 0;
}
