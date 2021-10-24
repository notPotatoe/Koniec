#include <iostream>
#include <string>
#include <cstdlib>

class Projekt
{
public:
    std::string path_konta = "Dane/konta.dat";
    std::string path_his = "Dane/historia.dat";
    void szyfr(std::string path);
    void deszyfr(std::string path);
    void debug();
    void debug2();
    int liczba_linijki(std::string path);
    const std::string czas();

    void start();
    void nowe_konto();
    void edit_konto();
    void usun_konto();
    void t_balans();
    void historia();
};
