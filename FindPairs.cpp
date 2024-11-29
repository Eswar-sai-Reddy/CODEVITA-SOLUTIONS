#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

vector<pair<int, int>> normalizeShape(const vector<pair<int, int>>& vertices) {
    int n = vertices.size();
    vector<pair<int, int>> minRotation = vertices;

    for (int i = 0; i < n; ++i) {
        vector<pair<int, int>> rotated(vertices.begin() + i, vertices.end());
        rotated.insert(rotated.end(), vertices.begin(), vertices.begin() + i);

        if (rotated < minRotation) {
            minRotation = rotated;
        }
    }
    return minRotation;
}

vector<int> findMatchingPairs(const vector<vector<pair<int, int>>>& earrings) {
    map<vector<pair<int, int>>, vector<int>> normalizedShapes;

    for (int i = 0; i < earrings.size(); ++i) {
        vector<pair<int, int>> normalized = normalizeShape(earrings[i]);
        normalizedShapes[normalized].push_back(i + 1);
    }
https://telegram.me/PLACEMENTLELO

    for (const auto& entry : normalizedShapes) {
        if (entry.second.size() == 2) {
            return entry.second;
        }
    }
    return {};
}

int main() {
    int n;
    cin >> n;
    vector<vector<pair<int, int>>> earrings(n);

    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        vector<pair<int, int>> vertices(k);
        for (int j = 0; j < k; ++j) {
            cin >> vertices[j].first >> vertices[j].second;
        }
        earrings[i] = vertices;
    }

    vector<int> result = findMatchingPairs(earrings);
    if (!result.empty()) {
        cout << result[0] << " " << result[1] << endl;
    } else {
        cout << endl;
    }

    return 0;
}
