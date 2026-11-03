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
#include "Promotie.hpp"
#include "RaportFinanciar.hpp"
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
    std::vector<Promotie> promotii;
    double cheltuieliReaprovizionare;

    int gasesteIndexIngredient(const std::string& denumire) const;
    int gasesteIndexReteta(const std::string& denumire) const;
    int gasesteIndexPromotie(const std::string& produs) const;
    int gasesteIndexPromotieNume(const std::string& numePromotie) const;
    static void adaugaLaNecesar(std::vector<CReteta>& necesar, const CReteta& comp);
    bool stocAcopera(const std::vector<CReteta>& necesar) const;
    double costMateriePrimaVanduta() const;
public:
    Cafenea(const std::string& numeCafenea, double fondInitial);

    void adaugaIngredient(const Ingrediente& ing);
    void adaugaReteta(const Reteta& ret);
    void adaugaPromotie(const Promotie& promo);
    bool seteazaStarePromotie(const std::string& numePromotie, bool activa);
    int incarcaIngredienteDinFisier(const std::string& cale);

    bool poatePrepara(const std::string& numeBautura) const;
    bool proceseazaComanda(const std::string& numeBautura);
    bool plaseazaComanda(Client& client, const std::vector<std::string>& produse);
    bool reaprovizioneaza(const std::string& denumireIngredient, double cantitate);

    void afiseazaRaportProfitabilitate() const;
    void afiseazaIstoric() const;
    void afiseazaPromotii() const;
    void afiseazaRaportFinanciar() const;
    RaportFinanciar raportFinanciar() const;
    bool salveazaRaportVanzari(const std::string& cale) const;
    bool salveazaStocInFisier(const std::string& cale) const;
    const IstoricVanzari& getIstoric() const;

    friend std::ostream& operator<<(std::ostream& os, const Cafenea& c);
};

#endif
