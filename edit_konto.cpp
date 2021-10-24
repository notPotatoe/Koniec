#include "projekt.h"
#include <iostream>
#include <fstream>
#include <windows.h>
#include <list>
#include <vector>
#include <limits>
#include <cstdlib>

using namespace std;

//Globalne zmienne które nie powinny byc globalne
list <string> konta_global;
int liczba_linijek;

//Faktyczna podmiana danych w pliku konta
void zmiana_danych(int id, int opcja, string wartosc)
{
    Projekt pro;
    pro.deszyfr(pro.path_konta);
    fstream main(pro.path_konta, ios::out);
    list <string>::iterator it;
    string wiersz;

    it = konta_global.begin();
    int i = 0;

    for (string x : konta_global)
    {
        if (i == (id * 9) - opcja)
        {
            main << wartosc << endl;
            it++;
        }
        else
        {
            main << *it;
            if (i+1 != liczba_linijek)
            {
                main << endl;
            }
            it++;
        }
        i++;
    }
    //pro.szyfr();
}

list <string> pob_dane_konta(int id)
{
    Projekt pro;
    fstream plik(pro.path_konta, ios::in);
    list <string> konta;
    list <string> dane;
    list <string>::iterator it;
    string wiersz;
    //Pobiera wszystkie konta do listy konto
    while (getline(plik, wiersz))
    {
        konta.push_back(wiersz);
    }

    liczba_linijek = pro.liczba_linijki(pro.path_konta);

    konta_global = konta;
    plik.close();

    //Przesuwa pocz¹tek listy na pozycje konta z podanym ID
    it = konta.begin();
    advance(it, (id * 9) - 9);
    //Wrzuca szukane dane do osobnej listy
    for (int i = 0; i < 9; i++)
    {
        if (*it == "USUNIETE")
        {
            cout << "Konto nie istnieje lub Zostalo usuniete" << endl;
            system("PAUSE");
            system("CLS");
            pro.edit_konto();
        }
        else
        {
            dane.push_back(*it);
            it++;
        }
    }
    return dane;
}

void wys_dane_konta(list <string> dane)
{
    Projekt pro;
    pro.deszyfr(pro.path_konta);
    list <string>::iterator it = dane.begin();
    advance(it, 2);
    cout << "Imie: " << *it << endl;
    advance(it, 1);
    cout << "Nazwisko: " << *it << endl;
    advance(it, 1);
    cout << "Numer Telefonu: " << *it << endl;
    advance(it, 1);
    cout << "Data Urodzenia: " << *it << endl;
    advance(it, 1);
    cout << "PESEL: " << *it << endl;
    advance(it, 1);
    cout << "Stan Konta: " << *it << " PLN" << endl;
    advance(it, 1);
}


void Projekt::edit_konto()
{
    Projekt pro;
    int id, wybor;
    string nowa_wartosc;
    pro.deszyfr(pro.path_konta);
    pro.szyfr(pro.path_konta);
zle_id:
    cout << "Prosze podac ID konta" << endl;
    cout << "Twoj wybor: ";
    while (!(cin >> id)) {
        cout << "Zla wartosc" << endl;
        cout << "Twoj wybor: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    system("CLS");
    if (id == 0)
    {
        cout << "Konto o takim ID nie istnieje, sprobuj ponownie" << endl;
        system("PAUSE");
        system("CLS");
        goto zle_id;
    }
    else if (id < 0)
    {
    cout << "Konto o takim ID nie istnieje, sprobuj ponownie" << endl;
    system("PAUSE");
    system("CLS");
    goto zle_id;
    }
    else if ((id * 9) <= liczba_linijki(pro.path_konta))
    {
        cout << "Dane konta z ID " << id << ":" << endl << endl;
        wys_dane_konta(pob_dane_konta(id));

    }
    else
    {
        cout << "Konto o takim ID nie istnieje, sprobuj ponownie" << endl;
        system("PAUSE");
        system("CLS");
        goto zle_id;
    }
zla_opcja:
    cout << endl << "Jakie dane chcesz zmienic?" << endl << endl;
    cout << "1. Imie" << endl;
    cout << "2. Nazwisko" << endl;
    cout << "3. Numer Telefonu" << endl;
    cout << "4. Stan Konta" << endl << endl;
    cout << "Twoj wybor: ";
    while (!(cin >> wybor)) {
        cout << "Zla wartosc" << endl;
        cout << "Twoj wybor: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    system("CLS");
    switch (wybor)
    {
        case 1:
            cout << "Prosze podac nowe imie: ";
            cin >> nowa_wartosc;
            zmiana_danych(id, 7, nowa_wartosc);
            cout << "Gotowe" << endl;
            system("PAUSE");
            system("CLS");
            pro.szyfr(pro.path_konta);
            pro.start();
            break;
        case 2:
            cout << "Prosze podac nowe nazwisko: ";
            cin >> nowa_wartosc;
            zmiana_danych(id, 6, nowa_wartosc);
            cout << "Gotowe" << endl;
            system("PAUSE");
            system("CLS");
            pro.szyfr(pro.path_konta);
            pro.start();
            break;
        case 3:
            cout << "Prosze podac nowy numer telefonu: ";
            cin >> nowa_wartosc;
            zmiana_danych(id, 5, nowa_wartosc);
            cout << "Gotowe" << endl;
            system("PAUSE");
            system("CLS");
            pro.szyfr(pro.path_konta);
            pro.start();
            break;
        case 4:
            cout << "Prosze podac nowy stan konta: ";
            cin >> nowa_wartosc;
            zmiana_danych(id, 2, nowa_wartosc);
            cout << "Gotowe" << endl;
            system("PAUSE");
            system("CLS");
            pro.szyfr(pro.path_konta);
            pro.start();
            break;
        default:
            cout << "Nie prawidlowa opcja, sprobuj ponownie" << endl;
            system("PAUSE");
            system("CLS");
            goto zla_opcja;
    }
}
