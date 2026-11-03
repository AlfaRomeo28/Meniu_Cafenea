#ifndef CAFENEA_HPP
#define CAFENEA_HPP

#include <iostream>
#include <string>
#include <vector>
#include "Client.hpp"
#include "Comanda.hpp"
#include "CReteta.hpp"
#include "IstoricVanzari.hpp"
#include "Ingrediente.hpp"
#include "Reteta.hpp"

class Cafenea
{
private:
    std::string nume;
    double balansf;
    std::vector<Ingrediente> stocIngrediente;
    std::vector<Reteta> catalogR;
    IstoricVanzari istoric;
    int urmatorulIdComanda;

    int gasesteIndexIngredient(const std::string& denumire) const;
    int gasesteIndexReteta(const std::string& denumire) const;
    static void adaugaLaNecesar(std::vector<CReteta>& necesar, const CReteta& comp);
    bool stocAcopera(const std::vector<CReteta>& necesar) const;
public:
    Cafenea(const std::string& numeCafenea, double fondInitial);

    void adaugaIngredient(const Ingrediente& ing);
    void adaugaReteta(const Reteta& ret);
    int incarcaIngredienteDinFisier(const std::string& cale);

    bool poatePrepara(const std::string& numeBautura) const;
    bool proceseazaComanda(const std::string& numeBautura);
    bool plaseazaComanda(Client& client, const std::vector<std::string>& produse);
    bool reaprovizioneaza(const std::string& denumireIngredient, double cantitate);

    void afiseazaRaportProfitabilitate() const;
    void afiseazaIstoric() const;
    bool salveazaRaportVanzari(const std::string& cale) const;
    const IstoricVanzari& getIstoric() const;

    friend std::ostream& operator<<(std::ostream& os, const Cafenea& c);
};

#endif
