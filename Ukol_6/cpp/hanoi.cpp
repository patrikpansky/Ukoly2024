#include <iostream>
#include <vector>

using namespace std;

// Funkce pro zobrazení stavu věží
void zobrazVeze(const vector<vector<int>>& veze) {
    int maxVyska = 0;
    for (const auto& vez : veze) {
        maxVyska = max(maxVyska, static_cast<int>(vez.size()));
    }

    for (int i = maxVyska - 1; i >= 0; --i) {
        for (const auto& vez : veze) {
            if (i < static_cast<int>(vez.size())) {
                cout << vez[i] << "\t";
            }
            else {
                cout << "|\t";
            }
        }
        cout << endl;
    }
    cout << "---\t---\t---\n";
    cout << " A\t B\t C\n";
}

// Rekurzivní funkce pro řešení Hanoiských věží
void hanoi(int n, char z, char pomocny, char cil, vector<vector<int>>& veze) {
    if (n == 1) {
        int disk = veze[z - 'A'].back();
        veze[z - 'A'].pop_back();
        veze[cil - 'A'].push_back(disk);

        cout << "Přesuň disk " << disk << " z " << z << " na " << cil << endl;
        zobrazVeze(veze);
        return;
    }

    hanoi(n - 1, z, cil, pomocny, veze);
    hanoi(1, z, pomocny, cil, veze);
    hanoi(n - 1, pomocny, z, cil, veze);
}

int main() {
    int n;

    cout << "Zadejte počet disků: ";
    cin >> n;

    if (n <= 0) {
        cerr << "Počet disků musí být kladné číslo." << endl;
        return 1;
    }

    // Inicializace věží
    vector<vector<int>> veze(3);
    for (int i = n; i > 0; --i) {
        veze[0].push_back(i);
    }

    cout << "Počáteční stav věží:" << endl;
    zobrazVeze(veze);

    hanoi(n, 'A', 'B', 'C', veze);

    return 0;
}
