#include <bits/stdc++.h> 
using namespace std; 

void plot(const vector<int>& movements) {
    ofstream f("data.dat");
    for (int i = 0; i < movements.size(); ++i)
        f << movements[i] << " " << i << "\n";
    f.close();

    ofstream plt("plot.plt");
    plt << "plot 'data.dat' with linespoints\n";
    plt << "pause -1\n"; // keeps window open
    plt.close();
    system("gnuplot plot.plt");
}

void genReq(int n, vector<int>& req, int maxC) { 
    srand(time(0)); 
    while (n--) 
        req.push_back(rand() % (maxC + 1)); 
} 

int schedule(vector<int> req, int head, int dir, string algo) {
    int total = 0;
    vector<int> mv;
    req.push_back(head);
    sort(req.begin(), req.end());
    int i = find(req.begin(), req.end(), head) - req.begin();
    if (algo == "LOOK") {
        int j = i;
        while (dir ? j < req.size() : j >= 0) {
            mv.push_back(req[j]);
            dir ? j++ : j--;
        }
        j = dir ? i - 1 : i + 1;
        while (dir ? j >= 0 : j < req.size()) {
            mv.push_back(req[j]);
            dir ? j-- : j++;
        }
    }
    else if (algo == "C-LOOK") {
        int j = i;
        while (dir ? j < req.size() : j >= 0) {
            mv.push_back(req[j]);
            dir ? j++ : j--;
        }
        j = dir ? 0 : req.size() - 1;
        while (dir ? j < i : j > i) {
            mv.push_back(req[j]);
            dir ? j++ : j--;
        }
    }
    else if (algo == "C-SCAN") {
        if (req[0] != 0) 
            req.insert(req.begin(), 0);
        req.push_back(200);
        i = find(req.begin(), req.end(), head) - req.begin();
        int j = i;
        while (dir ? j < req.size() : j >= 0) {
            mv.push_back(req[j]);
            dir ? j++ : j--;
        }
        j = dir ? 0 : req.size() - 1;
        while (dir ? j < i : j > i) {
            mv.push_back(req[j]);
            dir ? j++ : j--;
        }
    }
    cout << "Head movements:\n" << mv[0] << " ";
    for (int i = 1; i < mv.size(); i++) {
        cout << mv[i] << " ";
        total += abs(mv[i] - mv[i - 1]);
    }
    cout << "\nTotal Head Movement: " << total << " Cylinders\n";
    plot(mv);
    return total;
}
 
int main() { 
    int n, head, ch, dir; 
    vector<int> req; 
    cout << "Enter number of disk requests: "; 
        cin >> n; 
    genReq(n, req, 200); 
    cout << "Generated disk requests: "; 
    for (int r : req) 
        cout << r << " "; 
    cout << "\nEnter initial head position: "; 
    cin >> head; 
    cout << "Choose Disk Scheduling Algorithm:\n1. LOOK\n2. CSCAN\n3. C-LOOK\n"; 
    cin >> ch; 
    cout << "Enter head movement direction (left = 0, right = 1): "; 
    cin >> dir; 
    string algo = ch == 1 ? "LOOK" : ch == 2 ? "C-SCAN" : ch == 3 ? "CLOOK" : ""; 
    if (algo == "") 
        return cout << "Invalid choice!\n", 0; 
    int total = schedule(req, head, dir, algo); 
    cout << "Total Head Movement: " << total << " Cylinders\n"; 
    return 0;
}
