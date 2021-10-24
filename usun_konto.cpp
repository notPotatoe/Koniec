#include "projekt.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <cstdlib>

using namespace std;

void Projekt::usun_konto()
{
	Projekt pro;
	pro.deszyfr(pro.path_konta);
	string wiersz;
	fstream main, temp;
	int id;
	int linijka = 0;
	int liczba_linijek;
	int ile = 0;
    liczba_linijek = pro.liczba_linijki(pro.path_konta);

	main.open(pro.path_konta, fstream::in);
	temp.open("Dane/temp.dat", fstream::out);

	cout << "Prosze podac ID konta do usuniecia: ";
	while (!(cin >> id)) {
		cout << "Zla wartosc" << endl;
		cout << "Prosze podac ID konta do usuniecia: ";
		cin.clear();
		cin.ignore(1000, '\n');
	}
	if (id == 1)
    {
while (getline(main, wiersz))
	{
        if (ile == 9)
		{
			temp << wiersz;
			if (linijka < liczba_linijek - 1)
			{
				temp << endl;
			}
		}
		else
		{
		    temp << "USUNIETE";
			ile++;
			if (linijka <= liczba_linijek - 2)
			{
				temp << endl;
			}
		}
		linijka++;
	}

    }
    else
    {
	while (getline(main, wiersz))
	{
        if (linijka / ((id * 9) - 9) != 1 || ile == 9)
		{
			temp << wiersz;
			if (linijka < liczba_linijek - 1)
			{
				temp << endl;
			}
		}
		else
		{
		    temp << "USUNIETE";
			ile++;
			if (linijka <= liczba_linijek - 2)
			{
				temp << endl;
			}
		}
		linijka++;
	}
    }
	main.close();
	temp.close();
	main.open(pro.path_konta, fstream::out);
	temp.open("Dane/temp.dat", fstream::in);
	linijka = 0;

	while (getline(temp, wiersz)) {

		if (linijka != liczba_linijek - 1)
		{
			main << wiersz << endl;
		}
		else
		{
			main << wiersz;
		}
		linijka++;
	}
	main.close();
	temp.close();
	temp.open("Dane/temp.dat", fstream::out);
	temp.close();
	pro.szyfr(pro.path_konta);
}
