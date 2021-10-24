#include "Projekt.h"
#include <iostream>
#include <cstdlib>

using namespace std;

void Projekt::debug2()
{
	Projekt pro;
	int wybor;
	bool czy_szyfr = true;

start:
	cout << "1. Szyfruj plik historia.txt" << endl;
	cout << "2. Odszyfruj plik historia.txt" << endl;
	cout << "3. Exit" << endl;
	cout << "Twoj wybor: ";
	while (!(cin >> wybor)) {
		cout << "Zla wartosc" << endl;
		cout << "Twoj wybor: ";
		cin.clear();
		cin.ignore(1000, '\n');
	}
	switch (wybor)
	{
		case 1:
			szyfr(pro.path_his);
			czy_szyfr = true;
			system("PAUSE");
			system("CLS");
			goto start;
		case 2:
			deszyfr(pro.path_his);
			czy_szyfr = false;
			system("PAUSE");
			system("CLS");
			goto start;
		case 3:
			if (czy_szyfr)
			{
				system("CLS");
				start();
			}
			else
			{
				pro.szyfr(pro.path_his);
				system("CLS");
				start();
			}

	}

}
