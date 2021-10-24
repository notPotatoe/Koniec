#include "projekt.h"
#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <stdio.h>
#include <time.h>
#include <cstdlib>

using namespace std;

//Wrzucenie wszystkich danych do listy
/*
while (getline(plik, wiersz))
{
    konto.push_back(wiersz);
}

it = konto.begin();

for (string x : good_dane)
cout << x << endl;
*/

void Projekt::szyfr(string path)
{
    Projekt pro;
    char ch;
    string temp;
    if (path == "Dane/konta.dat")
        temp = "tmp";
    else if (path == "Dane/historia.dat")
        temp = "tmp2";

    fstream fps, fpt;
    fps.open(path, fstream::in);
    fpt.open(temp, fstream::out);
    while (fps >> noskipws >> ch)
    {
        ch = ch + 100;
        fpt << ch;
    }
    fps.close();
    fpt.close();
    fps.open(path, fstream::out);
    fpt.open(temp, fstream::in);
    while (fpt >> noskipws >> ch)
        fps << ch;
    fps.close();
    fpt.close();
}

void Projekt::deszyfr(string path)
{
    Projekt pro;
    char ch;
        string temp;
    if (path == "Dane/konta.dat")
        temp = "tmp";
    else if (path == "Dane/historia.dat")
        temp = "tmp2";
    fstream fps, fpt;
    fps.open(path, fstream::out);
    fpt.open(temp, fstream::in);
    while (fpt >> noskipws >> ch)
    {
        ch = ch - 100;
        fps << ch;
    }
    fps.close();
    fpt.close();
}

int Projekt::liczba_linijki(string path)
{
    Projekt pro;
    pro.deszyfr(path);
    int aNumOfLines = 0;
    ifstream plik(path);

    string aLineStr;
    while (getline(plik, aLineStr))
    {
        if (!aLineStr.empty())
            aNumOfLines++;
    }
    return aNumOfLines;

    plik.close();
}

//Podaje Faktyczna date i godzine wywolania
const string Projekt::czas()
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);

    return buf;
}
