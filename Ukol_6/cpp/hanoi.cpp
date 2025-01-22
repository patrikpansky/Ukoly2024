#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// Struktura pro reprezentaci tahu
struct Tah {
    int disk;
    char z;
    char na;
    vector<vector<int>> stavVezi; // Stav věží po provedení tahu
};

// Funkce pro provedení tahu
void provedTah(vector<vector<int>>& veze, Tah& tah) {
    int disk = veze[tah.z - 'A'].back();
    veze[tah.z - 'A'].pop_back();
    veze[tah.na - 'A'].push_back(disk);
    tah.disk = disk;
    tah.stavVezi = veze;
}

// Funkce pro řešení Hanoiských věží (rekurzivní algoritmus)
void hanoi(int n, char z, char pomocny, char cil, vector<vector<int>>& veze, vector<Tah>& tahy) {
    if (n == 1) {
        Tah tah = { 0, z, cil };
        provedTah(veze, tah);
        tahy.push_back(tah);
        return;
    }
    hanoi(n - 1, z, cil, pomocny, veze, tahy);
    Tah tah = { 0, z, cil };
    provedTah(veze, tah);
    tahy.push_back(tah);
    hanoi(n - 1, pomocny, z, cil, veze, tahy);
}

// Funkce pro zobrazení stavu věží v konzoli
void zobrazVeze(const vector<vector<int>>& veze) {
    int maxDisk = 0;
    for (const auto& vez : veze) {
        for (int disk : vez) {
            maxDisk = max(maxDisk, disk);
        }
    }

    int vyska = max(veze[0].size(), max(veze[1].size(), veze[2].size()));
    for (int i = vyska - 1; i >= 0; --i) {
        for (const auto& vez : veze) {
            if (i < vez.size()) {
                cout << setw(maxDisk) << string(vez[i], '=') << setw(maxDisk) << " ";
            }
            else {
                cout << setw(maxDisk * 2) << "| ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

#ifndef __TEST__
int main() {
    int n;
    cout << "Zadejte pocet disku: ";
    cin >> n;
    if (n <= 0) {
        cout << "Pocet disku musi byt kladne cislo." << endl;
        return 1;
    }

    vector<vector<int>> veze(3); // Tři věže A, B, C
    for (int i = n; i > 0; --i) {
        veze[0].push_back(i);
    }

    vector<Tah> tahy;
    hanoi(n, 'A', 'B', 'C', veze, tahy);

    // Zobrazení tahů a stavů věží
    for (const Tah& tah : tahy) {
        cout << "Presun disk " << tah.disk << " z koliku " << tah.z << " na kolik " << tah.na << endl;
        zobrazVeze(tah.stavVezi);
    }

    return 0;
}
#endif // __TEST__
