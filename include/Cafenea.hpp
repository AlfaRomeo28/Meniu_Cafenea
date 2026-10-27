#ifndef CAFENEA_HPP
#define CAFENEA_HPP

#include <iostream>
#include <string>
#include <vector>
#include "Ingrediente.hpp"
#include "Reteta.hpp"

class Cafenea
{
private:
    std::string nume;
    double balansf;
    std::vector<Ingrediente> stocIngrediente;
    std::vector<Reteta> catalogR;

    int gasesteIndexIngredient(const std::string& denumire) const;
    int gasesteIndexReteta(const std::string& denumire) const;
public:
    Cafenea(const std::string& numeCafenea, double fondInitial);

    void adaugaIngredient(const Ingrediente& ing);
    void adaugaReteta(const Reteta& ret);

    bool poatePrepara(const std::string& numeBautura) const;
    bool proceseazaComanda(const std::string& numeBautura);
    bool reaprovizioneaza(const std::string& denumireIngredient, double cantitate);
    void afiseazaRaportProfitabilitate() const;

    friend std::ostream& operator<<(std::ostream& os, const Cafenea& c);
};

#endif
