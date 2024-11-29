#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>


using namespace std;

int dp(string& s, vector<string>& v, unordered_map<string, int>& memo) {
    
    if (memo.count(s)) return memo[s];

    int placementlelo = 0;

    for (auto& x : v) {
        size_t pos = s.find(x); 

        if (pos != string::npos) {
            string new_string = s.substr(0, pos) + s.substr(pos + x.size());
            placementlelo = max(placementlelo, 1 + dp(new_string, v, memo));
        }
    }

    return memo[s] = placementlelo;
}

int main() {
    int n;
    cin >> n;

    vector<string> substrings(n);
    for (int i = 0; i < n; ++i) {
        cin >> substrings[i];
    }


    string mainString;
    cin >> mainString;
    unordered_map<string, int> memo;

    cout << dp(mainString, substrings, memo);

    return 0;
}
