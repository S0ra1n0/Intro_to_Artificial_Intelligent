#include<bits/stdc++.h>
using namespace std;

char c[10] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
int h[10] = {10, 8, 5, 7, 3, 6, 5, 3, 1, 0};
vector<vector<pair<char, int>>> linked(10);

void initialize() {
    for (int i = 0; i < 10; ++i) {
        switch (c[i]) {
            case 'A':
                linked[i].push_back(make_pair('B', 6));
                linked[i].push_back(make_pair('F', 3));
                break;
            case 'B':
                linked[i].push_back(make_pair('A', 6));
                linked[i].push_back(make_pair('C', 3));
                linked[i].push_back(make_pair('D', 2));
                break;
            case 'C':
                linked[i].push_back(make_pair('B', 3));
                linked[i].push_back(make_pair('D', 1));
                linked[i].push_back(make_pair('E', 5));
                break;
            case 'D':
                linked[i].push_back(make_pair('B', 2));
                linked[i].push_back(make_pair('C', 1));
                linked[i].push_back(make_pair('E', 8));
                break;
            case 'E':
                linked[i].push_back(make_pair('C', 5));
                linked[i].push_back(make_pair('D', 8));
                linked[i].push_back(make_pair('I', 5));
                linked[i].push_back(make_pair('J', 5));
                break;
            case 'F':
                linked[i].push_back(make_pair('A', 3));
                linked[i].push_back(make_pair('G', 1));
                linked[i].push_back(make_pair('H', 7));
                break;
            case 'G':
                linked[i].push_back(make_pair('F', 1));
                linked[i].push_back(make_pair('I', 3));
                break;
            case 'H':
                linked[i].push_back(make_pair('F', 7));
                linked[i].push_back(make_pair('I', 2));
                break;
            case 'I':
                linked[i].push_back(make_pair('E', 5));
                linked[i].push_back(make_pair('G', 3));
                linked[i].push_back(make_pair('H', 2));
                linked[i].push_back(make_pair('J', 3));
                break;
            case 'J':
                linked[i].push_back(make_pair('E', 5));
                linked[i].push_back(make_pair('I', 3));
                break;
        }
    }
}

int main() {
    initialize();
    //Choose (A) to start and (J) to end
    deque<pair<char, pair<int, int>>> q;
    //format of vector: ('A', ('A' - 'A', 0))
    q.push_back(make_pair('A', make_pair(0, 0)));
    int ans;
    vector<bool> visited(10, 0);
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
            for (int j = 0; j < 10; ++j) {if (c[j] == linked[posi][i].first) {tempposi = j; break;}}
            if (tempposi == 9) {
                nextposi = tempposi;
                nextchar = 'J';
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
    cout << "The cost-effective path from node(A) to (J) costs: " << ans;
}
