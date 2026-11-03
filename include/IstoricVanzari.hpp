#ifndef ISTORICVANZARI_HPP
#define ISTORICVANZARI_HPP

#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>
#include "Comanda.hpp"

// pastreaza toate comenzile finalizate si calculeaza statistici pe ele
class IstoricVanzari
{
private:
    std::string denumireCafenea;
    std::vector<Comanda> comenzi;

    std::map<std::string, int> cantitatiVandute() const;
public:
    explicit IstoricVanzari(const std::string& cafenea);

    void adaugaComanda(const Comanda& cmd);

    int getNumarComenzi() const;
    double totalIncasari() const;
    double totalReduceri() const;
    double valoareMedieComanda() const;
    int numarComenziClient(const std::string& client) const;
    double totalClient(const std::string& client) const;
    const Comanda* gasesteComanda(int id) const;
    std::vector<std::pair<std::string, int> > topProduse(std::size_t n) const;

    bool salveazaInFisier(const std::string& cale) const;

    friend std::ostream& operator<<(std::ostream& os, const IstoricVanzari& ist);
};

#endif
