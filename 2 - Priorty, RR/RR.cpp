#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, i, j, ts;
    cout << "Enter n value :" << endl;
    cin >> n;

    vector<int> bt(n), tbt(n), at(n), order, time, tat(n), wt(n), id(n);
    
    cout << "Enter time slice value :" << endl;
    cin >> ts;

    cout << "Enter bt and at for all n processes:" << endl;
    for(i = 0; i < n; i++) {
        cin >> bt[i] >> at[i];
        id[i] = i;
    }

    // Sort by arrival timew
    for(i = 0; i < n; i++) {
        for(j = 1; j < n; j++) {
            if(at[j] < at[j-1]) {
                swap(at[j], at[j-1]);
                swap(bt[j], bt[j-1]);
                swap(id[j], id[j-1]);
            }
        }
    }

    tbt = bt;
    int com = 0, ct = 0;
    vector<bool> done(n, false);

    while(com < n)
    {
        bool executed = false;
        for(i = 0; i < n; i++)
        {
            if(at[i] <= ct && tbt[i] > 0)
            {
                order.push_back(id[i] + 1);
                time.push_back(ct);
                executed = true;

                if(tbt[i] > ts)
                {
                    ct += ts;
                    tbt[i] -= ts;
                }
                else
                {
                    ct += tbt[i];
                    tbt[i] = 0;
                    tat[id[i]] = ct - at[i];
                    wt[id[i]] = tat[id[i]] - bt[i];
                    com++;
                }
            }
        }

        if(!executed)
        {
            // CPU is idle
            order.push_back(-1);
            time.push_back(ct);
            ct++; // move clock forward by 1
        }
    }

    time.push_back(ct); // Final time

    // Sort id-wise for final output
    for(i = 0; i < n; i++) {
        for(j = 1; j < n; j++) {
            if(id[j] < id[j-1]) {
                swap(at[j], at[j-1]);
                swap(bt[j], bt[j-1]);
                swap(tat[j], tat[j-1]);
                swap(wt[j], wt[j-1]);
                swap(id[j], id[j-1]);
            }
        }
    }

    // Output
    cout << "bt ";
    for(auto x : bt) cout << x << " ";
    cout << "\nat  ";
    for(auto x : at) cout << x << " ";
    cout << "\nwt  ";
    for(auto x : wt) cout << x << " ";
    cout << "\ntat ";
    for(auto x : tat) cout << x << " ";
    cout << "\nid  ";
    for(auto x : id) cout << x + 1 << " ";
    
    cout << "\n\nGantt Chart (order): ";
    for(auto x : order)
        cout << (x == -1 ? -1 : x) << " ";

    cout << "\nTime Points: ";
    for(auto x : time)
        cout << x << " ";
    cout << endl;

    return 0;
}
