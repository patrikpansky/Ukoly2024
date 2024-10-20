//program bere informace ze souboru na plose s nazvem sifra.txt 
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
string caesarovasifra(string text, int posun) // Caesarova sifra
{
    string vysledek = "";
    for (char& i : text)
    {
        if (isalpha(i))
        {
            char pismeno = islower(i) ? 'a' : 'A';
            i = (i - pismeno + posun) % 26 + pismeno;
        }
        vysledek += i;
    }
    return vysledek;
}
string vigeneresifra(string text, string klic) // Vigenerova sifra
{
    string vysledek = "";
    int delkaklice = klic.length();
    int indexklice = 0;
    for (char& i : text)
    {
        if (isalpha(i))
        {
            char pismeno = islower(i) ? 'a' : 'A';
            char posun = islower(klic[indexklice % delkaklice]) ? 'a' : 'A';
            i = (i - pismeno + (klic[indexklice % delkaklice] - posun)) % 26 + pismeno;
            indexklice++;
        }
        vysledek += i;
    }
    return vysledek;
}
string xorsifra(string text, char klic) // XOR sifra
{
    string vysledek = "";
    for (char& i : text)
    {
        vysledek += i ^ klic;
    }
    return vysledek;
}
int main()
{
    string text;
    int volba;
    string nazev = "C:\\Users\\patri\\Desktop\\sifra.txt";  // Zadejte vlastní cestu
    ifstream soubor(nazev);
    if (!soubor.is_open())
    {
        cerr << "Nepodarilo se otevrit soubor" << endl;
        return 1;
    }
    string radek;
    while (getline(soubor, radek))
    {
        text += radek + "\n";
    }
    soubor.close();
    cout << "Puvodni text ze souboru:\n" << text << endl;
    cout << "Vyberte sifru:\n";
    cout << "1 - Caesarova sifra\n";
    cout << "2 - Vigenerova sifra\n";
    cout << "3 - XOR sifra\n";
    cout << "Vase volba: ";
    cin >> volba;
    string zasifrovanytext;
    if (volba == 1)
    {
        int posun;
        cout << "Zadejte hodnotu posunu: ";
        cin >> posun;
        zasifrovanytext = caesarovasifra(text, posun);
    }
    else if (volba == 2) 
    {
        string klic;
        cout << "Zadejte klic: ";
        cin >> klic;
        zasifrovanytext = vigeneresifra(text, klic);
    }
    else if (volba == 3) 
    {
        char klic;
        cout << "Zadejte jeden znak jako klic: ";
        cin >> klic;
        zasifrovanytext = xorsifra(text, klic);
    }
    else
    {
        cout << "Neplatna volba" << endl;
        return 1;
    }
    cout << "Zasifrovany text:\n" << zasifrovanytext << endl;
    return 0;
}
