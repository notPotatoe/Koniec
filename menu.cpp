#include "projekt.h"
#include <iostream>
#include <windows.h>
#include <cstdlib>

void Projekt::start()
{
	Projekt pro;
	int wybor;

start:
	std::cout << "	======================================================================================================" << std::endl;
	std::cout << "				Witamy w systemie administrowania systemu bankowego" << std::endl;
	std::cout << "	======================================================================================================" << std::endl << std::endl;
	std::cout << "Prosze wybrac jedna z ponizszych opcji:" << std::endl;
	std::cout << "1. Dodaj nowe konto" << std::endl;
	std::cout << "2. Edytuj dane konta" << std::endl;
	std::cout << "3. Usun istniejace konto" << std::endl;
	std::cout << "4. Transferuj pieniadze na inne konto" << std::endl;
	std::cout << "5. Historia transferow" << std::endl;
	std::cout << "6. Wyjscie" << std::endl << std::endl;
	std::cout << "Wybrana opcja: ";
	while (!(std::cin >> wybor)) {
		std::cout << "Zla wartosc" << std::endl;
		std::cout << "Wybrana opcja: ";
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}
	switch (wybor){
		case 1:
			system("CLS");
			nowe_konto();
			system("PAUSE");
			system("CLS");
			goto start;
		case 2:
			system("CLS");
			edit_konto();
			system("PAUSE");
			system("CLS");
			goto start;
		case 3:
			system("CLS");
			usun_konto();
			system("PAUSE");
			system("CLS");
			goto start;
		case 4:
			system("CLS");
			t_balans();
			system("PAUSE");
			system("CLS");
			goto start;
		case 5:
			system("CLS");
			historia();
			system("PAUSE");
			system("CLS");
			goto start;
		case 6:
			break;
        case 8:
            system("CLS");
			debug2();
			system("PAUSE");
			system("CLS");
		case 9:
			system("CLS");
			debug();
			system("PAUSE");
			system("CLS");
        default:
            std::cout << "Taka opcja nie istnieje, sprobuj ponownie" << std::endl;
            system("PAUSE");
            system("CLS");
            goto start;
	}
}
