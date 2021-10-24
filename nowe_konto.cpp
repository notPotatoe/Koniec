#include "projekt.h"
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <cstdlib>

using namespace std;

string imie, nazwisko, pesel, data_u;
int id, nr_tel;
int money = 0;

bool is_empty(fstream& pFile)
{
    return pFile.peek() == std::ifstream::traits_type::eof();
}

//Zwraca o jeden wiêkszy numer ID ni¿ ostatnio u¿yty w pliku konta.txt
int licz_id()
{
    Projekt pro;
    int aNumOfLines = 0;
    ifstream plik(pro.path_konta);

    string aLineStr;
    while (getline(plik, aLineStr))
    {
        if (!aLineStr.empty())
            aNumOfLines++;
    }

    id = aNumOfLines / 9;

    return id+1 ;
}

void podaj_dane()
{
    cout << "Podaj imie: ";
    cin >> imie;
    system("CLS");
    cout << "Podaj nazwisko: ";
    cin >> nazwisko;
    system("CLS");
    cout << "Podaj numer telefonu: ";
    cin >> nr_tel;
    system("CLS");
    cout << "Podaj date urodzenia (DD/MM/YYYY): ";
    cin >> data_u;
    system("CLS");
    cout << "Podaj PESEL: ";
    cin >> pesel;
    system("CLS");
}

void Projekt::nowe_konto()
{
    Projekt pro;
    pro.deszyfr(pro.path_konta);
    fstream konta;
    podaj_dane();
    konta.open(pro.path_konta, ios::app);
    konta.seekg(0, ios::end);
    if (konta.tellg() == 0)
        konta << licz_id() << endl;
    else
        konta << endl << licz_id() << endl;
    konta << "{" << endl;
    konta << imie << endl;
    konta << nazwisko << endl;
    konta << nr_tel << endl;
    konta << data_u << endl;
    konta << pesel << endl;
    konta << money << endl;
    konta << "}";
    konta.close();
    pro.szyfr(pro.path_konta);
    cout << "koniec" << endl;
}
