#ifndef RAPORTFINANCIAR_HPP
#define RAPORTFINANCIAR_HPP

#include <iostream>
#include <string>

// Rezumat financiar al cafenelei, calculat din vanzari, costuri si cheltuieli de stoc
class RaportFinanciar
{
private:
    double incasari;
    double reduceri;
    double costMateriePrima;
    double cheltuieliReaprovizionare;
    int numarComenzi;
public:
    RaportFinanciar(double incasariTotale, double reduceriAcordate, double costMaterii,
                    double cheltuieliStoc, int comenzi);

    double getIncasari() const;
    double getReduceri() const;
    double getCostMateriePrima() const;
    double getCheltuieliReaprovizionare() const;
    int getNumarComenzi() const;

    double profitBrut() const;
    double fluxNumerar() const;
    double marjaBruta() const;
    double incasarePerComanda() const;
    double ponderePierderiDinReduceri() const;
    std::string interpretare() const;

    bool salveazaInFisier(const std::string& cale) const;

    friend std::ostream& operator<<(std::ostream& os, const RaportFinanciar& r);
};

#endif
