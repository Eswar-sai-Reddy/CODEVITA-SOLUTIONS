#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> ids(n), costs(n);
    for (int i = 0; i < n; i++) cin >> ids[i];
    for (int i = 0; i < n; i++) cin >> costs[i];

    int budget;
    cin >> budget;

    int mfi = 0, mfw = 0;

    for (int i = 0; i < n; i++) {
        int buyCost = costs[i];
        int maxQty = budget / buyCost;

        if (maxQty > 0) {
            int cfi = 0;
            int cfw = 0;
            for (int j = 0; j < n; j++) {
                if (i != j && ids[i] % ids[j] == 0) {
                    cfi += maxQty;
                    cfw += costs[j] * maxQty;
                }
            }

            if (cfi > mfi || 
               (cfi == mfi && cfw > mfw)) {
                mfi = cfi;
                mfw = cfw;
            }
        }
    }

    cout << mfi << " " << mfw << endl;
    return 0;
}
