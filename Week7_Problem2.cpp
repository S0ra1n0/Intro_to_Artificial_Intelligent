#include<bits/stdc++.h>
using namespace std;

char c[13] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M'};
int h[13] = {223, 222, 166, 192, 165, 136, 122, 111, 100, 60, 32, 102, 0};
vector<vector<pair<char, int>>> linked(13);

void initialize() {
    for (int i = 0; i < 13; ++i) {
        switch (c[i]) {
            case 'A':
                linked[i].push_back(make_pair('B', 36));
                linked[i].push_back(make_pair('C', 61));
                break;
            case 'B':
                linked[i].push_back(make_pair('A', 36));
                linked[i].push_back(make_pair('D', 31));
                break;
            case 'C':
                linked[i].push_back(make_pair('A', 61));
                linked[i].push_back(make_pair('D', 32));
                linked[i].push_back(make_pair('F', 31));
                linked[i].push_back(make_pair('L', 80));
                break;
            case 'D':
                linked[i].push_back(make_pair('B', 31));
                linked[i].push_back(make_pair('C', 32));
                linked[i].push_back(make_pair('E', 52));
                break;
            case 'E':
                linked[i].push_back(make_pair('D', 52));
                linked[i].push_back(make_pair('G', 43));
                break;
            case 'F':
                linked[i].push_back(make_pair('C', 31));
                linked[i].push_back(make_pair('J', 122));
                linked[i].push_back(make_pair('K', 112));
                break;
            case 'G':
                linked[i].push_back(make_pair('E', 43));
                linked[i].push_back(make_pair('H', 20));
                break;
            case 'H':
                linked[i].push_back(make_pair('G', 20));
                linked[i].push_back(make_pair('I', 40));
                break;
            case 'I':
                linked[i].push_back(make_pair('H', 40));
                linked[i].push_back(make_pair('J', 45));
                break;
            case 'J':
                linked[i].push_back(make_pair('F', 122));
                linked[i].push_back(make_pair('I', 45));
                linked[i].push_back(make_pair('K', 36));
                break;
            case 'K':
                linked[i].push_back(make_pair('F', 112));
                linked[i].push_back(make_pair('J', 36));
                linked[i].push_back(make_pair('M', 32));
                break;
            case 'L':
                linked[i].push_back(make_pair('C', 80));
                linked[i].push_back(make_pair('M', 102));
                break;
            case 'M':
                linked[i].push_back(make_pair('K', 32));
                linked[i].push_back(make_pair('L', 102));
                break;
        }
    }
}

int main() {
    initialize();
    //Choose (A) to start and (M) to end
    deque<pair<char, pair<int, int>>> q;
    //format of deque: ('A', ('A' - 'A', 0))
    q.push_back(make_pair('A', make_pair(0, 0)));
    int ans;
    vector<bool> visited(13, 0);
    visited[1] = 1;
    bool check = 0;
    cout << "A 0 0 (Start)" << "\n";
    while (!q.empty() && !check) {
        int mini = 1e9, posi = q[0].second.first;
        char cur = q[0].first;
        int dist = q[0].second.second;
        q.pop_front();
        int nextposi, nextdist;
        char nextchar;
        for (int i = 0; i < linked[posi].size(); ++i) {
            int tempposi;
            for (int j = 0; j < 13; ++j) {if (c[j] == linked[posi][i].first) {tempposi = j; break;}}
            if (tempposi == 12) {
                nextposi = tempposi;
                nextchar = 'M';
                nextdist = dist + linked[posi][i].second;
                check = 1;
                break;
            }
            if (!visited[tempposi]) {
                visited[tempposi] = 1;
                int temp = dist + linked[posi][i].second + h[tempposi];
                if (temp <= mini) {
                    nextchar = linked[posi][i].first;
                    nextdist = linked[posi][i].second;
                    nextposi = tempposi; 
                    mini = temp;
                }
            }
        }
        if (!check) {
            q.push_back(make_pair(nextchar, make_pair(nextposi, dist + nextdist)));
            cout << nextchar << " " << nextposi << " " << dist + nextdist << "\n";
        }
        else {
            ans = nextdist;
            cout << nextchar << " " << nextposi << " " << nextdist << " (End)\n";
        }
       
    }
    cout << "The cost-effective path from node(A) to (M) costs: " << ans;
}
