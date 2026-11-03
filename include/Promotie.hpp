#ifndef PROMOTIE_HPP
#define PROMOTIE_HPP

#include <iostream>
#include <string>

// O promotie pe un produs din catalog (ex: Happy Hour la Espresso, -20%)
class Promotie
{
private:
    std::string nume;
    std::string produsVizat;
    double procent;
    bool activa;

    void valideaza() const;
public:
    Promotie(const std::string& numePromotie, const std::string& produs, double procentReducere);
    Promotie(const std::string& numePromotie, const std::string& produs, double procentReducere,
             bool esteActiva);

    const std::string& getNume() const;
    const std::string& getProdusVizat() const;
    double getProcent() const;
    bool esteActiva() const;

    bool aplicabila(const std::string& produs) const;
    double calculeazaPretRedus(double pretInitial) const;
    double economie(double pretInitial, int cantitate) const;

    void activeaza();
    void dezactiveaza();

    friend std::ostream& operator<<(std::ostream& os, const Promotie& p);
};

#endif
