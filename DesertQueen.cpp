#include <bits/stdc++.h>
using namespace std;

int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

bool isValid(int x, int y, int n, const vector<vector<char>>& grid) {
    return x >= 0 && x < n && y >= 0 && y < n && grid[x][y] != 'M';
}
int fMW(int n, const vector<vector<char>>& grid, pair<int, int> start, pair<int, int> end) {
    vector<vector<int>> placementlelo(n, vector<int>(n, INT_MAX)); 
    queue<pair<int, int>> q;
    

    q.push(start);
    placementlelo[start.first][start.second] = 0;

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        for (int d = 0; d < 4; d++) {
            int nx = x + dir[d][0];
            int ny = y + dir[d][1];

            if (isValid(nx, ny, n, grid)) {
                int cost = (grid[x][y] == 'T' && grid[nx][ny] == 'T') ? 0 : 1; 
                if (placementlelo[x][y] + cost < placementlelo[nx][ny]) {
                    placementlelo[nx][ny] = placementlelo[x][y] + cost;
                    q.push({nx, ny});
                }
            }
        }
    }

    return placementlelo[end.first][end.second];
}
int main() {
    int n;
    cin >> n;
    vector<vector<char>> grid(n, vector<char>(n));
    pair<int, int> start, end;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 'S') start = {i, j};
            if (grid[i][j] == 'E') end = {i, j};
        }
    }

    int result = fMW(n, grid, start, end);
    cout << result << endl;

    return 0;
}
