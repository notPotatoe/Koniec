#include "projekt.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <string>
#include <windows.h>

using namespace std;

list <string> konta_plik;
list <string> nowe_dane;
int s_konta1, s_konta2;
int ilosc_linijek;

void dodaj_his(int id_1,int id_2,int money)
{
    Projekt pro;
    pro.deszyfr(pro.path_his);
    fstream plik(pro.path_his, ios::app);
    plik << pro.czas() << ": ";
    plik << "Konto z ID " << id_1 << " przelalo " << money << " PLN na konto z ID " << id_2 << endl;
    pro.szyfr(pro.path_his);
}

int correct_id(string text)
{
    int id;
    Projekt pro;
    pro.deszyfr(pro.path_konta);
    fstream plik(pro.path_konta, ios::in);
zle_id:
    cout << text << endl;
    cout << "Twoj wybor: ";
    while (!(cin >> id))
    {
        cout << "Zla wartosc" << endl;
        cout << "Twoj wybor: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    cout << endl;
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
    else if ((id * 9) <= pro.liczba_linijki(pro.path_konta) + 2)
    {
        return id;
    }
    else
    {
        cout << "Konto o takim ID nie istnieje, sprobuj ponownie" << endl;
        system("PAUSE");
        system("CLS");
        goto zle_id;
    }
    plik.close();
}

int czy_mozna_przelew(int id_1, int id_2, int money)
{
    Projekt pro;
    fstream plik(pro.path_konta, fstream::in);
    pro.deszyfr(pro.path_konta);
    list <string> konto_1;
    list <string> konto_2;
    list <string>::iterator it_1;
    list <string>::iterator it_2;
    string wiersz;

    //Pobiera wszystkie konta do listy konto_1
    while (getline(plik, wiersz))
    {
        konto_1.push_back(wiersz);
    }
    konto_2 = konto_1;
    konta_plik = konto_1;
    it_1 = konto_1.begin();
    it_2 = konto_2.begin();

    advance(it_1, (id_1 * 9) - 2);
    advance(it_2, (id_2 * 9) - 2);

    if (*it_1 == "USUNIETE")
    {
        return 3;
    }
    if (*it_2 == "USUNIETE")
    {
        return 4;
    }

    s_konta1 = stoi(*it_1);
    s_konta2 = stoi(*it_2);

    if (s_konta1 - money < 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    plik.close();
}

void przelew(int id_1, int id_2, int money)
{
    Projekt pro;
    pro.deszyfr(pro.path_konta);
    fstream plik;
    plik.open(pro.path_konta, fstream::out);
    list <string>::iterator it;
    list <string>::iterator it_2;
    string wiersz;
    int now_s_konta1, now_s_konta2;

    it = konta_plik.begin();
    int i = 0;

    now_s_konta1 = s_konta1 - money;
    now_s_konta2 = s_konta2 + money;

    //string str1 = to_string(now_s_konta1);
    //string str2 = to_string(now_s_konta2);

    stringstream ss;
    ss << now_s_konta1;
    string str1=ss.str();
    stringstream ss1;
    ss1 << now_s_konta2;
    string str2=ss1.str();

    for (string x : konta_plik)
    {

        if (i == (id_1 * 9) - 2)
        {
            nowe_dane.push_back(str1);
            it++;
        }
        else if (i == (id_2 * 9) - 2)
        {
            nowe_dane.push_back(str2);
            it++;
        }
        else
        {
            nowe_dane.push_back(*it);
            it++;
        }
        i++;
    }

    it_2 = nowe_dane.begin();
    i = 0;
    for (string x : nowe_dane)
    {
        plik << *it_2;
        *it_2++;
        i++;
    if (i != ilosc_linijek)
        {
            plik << endl;
        }
    }
    plik.close();
}

void Projekt::t_balans()
{
    Projekt pro;
    string text;
    int id_1, id_2, money;
    pro.deszyfr(pro.path_konta);
    pro.szyfr(pro.path_konta);
    ilosc_linijek = pro.liczba_linijki(pro.path_konta);
reset:
    text = "Prosze podac ID konta z ktorego zostana pobrane srodki";
    id_1 = correct_id(text);
reset_money:
    cout << "Prosze podac kwote przelewanych srodkow" << endl;
    cout << "Kwota: ";
    while (!(cin >> money)) {
        cout << "Zla wartosc" << endl;
        cout << "Kwota: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    if (money <= 0)
    {
        cout << "Wprowadzono bledna kwote, prosze sprobowac ponownie" << endl;
        system("PAUSE");
        system("CLS");
        cout << "Prosze podac ID konta z ktorego zostana pobrane srodki" << endl;
        cout << "Twoj wybor: " << id_1 << endl << endl;
        goto reset_money;
    }
    cout << endl;
reciever:
    text = "Prosze podac ID konta ktore otrzyma wyslane srodki";
    id_2 = correct_id(text);

    if (id_1 == id_2)
    {
        cout << "Nie mozesz przeniesc pieniedzy na to samo konto" << endl;
        system("PAUSE");
        system("CLS");
        goto reciever;
    }

    if (czy_mozna_przelew(id_1, id_2, money) == 1)
    {
        string czy_reset;
        cout << "Brak wystarczajacych srodkow do przelewu" << endl;
        cout << "Czy chcesz sprobowac ponownie?" << endl;
        cout << ("TAK/NIE: ");
        cin >> czy_reset;
        std::transform(czy_reset.begin(), czy_reset.end(), czy_reset.begin(),
            [](unsigned char c) { return std::tolower(c); });

        if (czy_reset == "tak")
        {
            system("CLS");
            goto reset;
        }
        else
        {
            system("CLS");
            pro.szyfr(pro.path_konta);
            pro.start();
        }
    }
    else if (czy_mozna_przelew(id_1, id_2, money) == 0)
    {
        przelew(id_1, id_2, money);
        dodaj_his(id_1, id_2, money);
        cout << "Gotowe" << endl;
        system("PAUSE");
        system("CLS");
        pro.szyfr(pro.path_konta);
        pro.start();
    }
    else if (czy_mozna_przelew(id_1, id_2, money) == 3)
    {
        cout << "Konto z ID " << id_1 << " zostalo usuniete lub nie istnieje, sprobuj ponownie" << endl;
        system("PAUSE");
        system("CLS");
        goto reset;
    }
    else if (czy_mozna_przelew(id_1, id_2, money) == 4)
    {
        cout << "Konto z ID " << id_2 << " zostalo usuniete lub nie istnieje, sprobuj ponownie" << endl;
        system("PAUSE");
        system("CLS");
        goto reset;
    }
}
