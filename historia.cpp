#include "projekt.h"
#include <iostream>
#include <vector>
#include <list>
#include <fstream>
#include <windows.h>

using namespace std;

void Projekt::historia()
{
    Projekt pro;

    pro.deszyfr(pro.path_his);
    string wiersz;
	fstream plik(pro.path_his, ios::in);
	list <string> konto;

    while (getline(plik, wiersz))
    {
        konto.push_back(wiersz);
    }
	for (string x : konto)
		cout << x << endl;
    pro.szyfr(pro.path_his);
    cout << endl;
}
