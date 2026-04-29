#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;

    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter number of resource types: ";
    cin >> m;

    vector<vector<int> > allocation(n, vector<int>(m));
    vector<vector<int> > maxNeed(n, vector<int>(m));
    vector<vector<int> > need(n, vector<int>(m));

    vector<int> available(m), work(m);
    vector<bool> finish(n, false);
    vector<int> safeSeq;

    cout << "\nEnter Allocation Matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> allocation[i][j];

    cout << "\nEnter Max Matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> maxNeed[i][j];

    cout << "\nEnter Available Resources:\n";
    for (int i = 0; i < m; i++) {
        cin >> available[i];
        work[i] = available[i];
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = maxNeed[i][j] - allocation[i][j];

    while ((int)safeSeq.size() < n) {
        bool found = false;

        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canRun = true;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canRun = false;
                        break;
                    }
                }

                if (canRun) {
                    for (int j = 0; j < m; j++)
                        work[j] += allocation[i][j];

                    safeSeq.push_back(i);
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            cout << "\nSystem is in UNSAFE state\n";
            return 0;
        }
    }

    cout << "\nSystem is in SAFE state\nSafe Sequence: ";
    for (int i = 0; i < n; i++) {
        cout << "P" << safeSeq[i];
        if (i != n - 1) cout << " -> ";
    }

    return 0;
}
