#ifndef CAFENEA_HPP
#define CAFENEA_HPP

#include <iostream>
#include <string>
#include "Ingrediente.hpp"
#include "Reteta.hpp"

class Cafenea
{
private:
    std::string nume;
    double balansf; //bani cafenelei
    //stoc ingrediente manual prin tablou dinamic
    Ingrediente* stocIngrediente;
    int capacitateIngrediente;
    int nrIngrediente;
    //catalog retete manual prin tablou dinamic
    Reteta* catalogR;
    int capacitateR;
    int nrR;
    //dublează capacitatea tabloului de ingrediente când devine plin
    void redimIngr();
    //dublează capacitatea catalogului de rețete
    void redimR();
    //cauta indexul unui ingredient după denumire; returnează -1 dacă nu există
    int gasesteIndexIngredient(const std::string& denumire) const;
public:
    Cafenea(const std::string& numeCafenea, double fondInitial);
    //eliberare memorie alocata dinamic pt a evita memory leaks
    ~Cafenea();
    //blocarea copierei clasei Cafenea pt ca nu avem nevoie de copii ale cafenelei
    Cafenea(const Cafenea&) = delete;
    Cafenea& operator=(const Cafenea&) = delete;
    //adaugare ingrediente si retete
    void adaugaIngredient(const Ingrediente& ing);
    void adaugaReteta(const Reteta& ret);
    //verificare disponibilitate stoc
    bool poatePrepara(const std::string& numeBautura) const;
    // Scade ingredientele folosite din stoc și incaseaza banii
    bool proceseazaComanda(const std::string& numeBautura);
    //calcul costul materiei prime, marja de profit si procentul de rentabilitate
    void afiseazaRaportProfitabilitate() const;
    friend std::ostream& operator<<(std::ostream& os, const Cafenea& c);
};

#endif
