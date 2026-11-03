#ifndef COMANDA_HPP
#define COMANDA_HPP

#include <iostream>
#include <string>
#include <vector>
#include "LinieComanda.hpp"

// O comanda finalizata: client + lista de linii + reducere aplicata
class Comanda
{
private:
    int id;
    std::string numeClient;
    std::vector<LinieComanda> linii;
    double reducereProcent;

    int gasesteLinie(const std::string& denumire) const;
public:
    Comanda(int idComanda, const std::string& client);

    void adaugaLinie(const std::string& denumire, double pretUnitar, int cantitate = 1);
    void aplicaReducere(double procent);

    int getId() const;
    const std::string& getNumeClient() const;
    const std::vector<LinieComanda>& getLinii() const;
    double getReducere() const;

    int getNumarProduse() const;
    double getSubtotal() const;
    double getValoareReducere() const;
    double getTotal() const;

    friend std::ostream& operator<<(std::ostream& os, const Comanda& c);
};

#endif
