#include "Promotie.hpp"
#include <stdexcept>

namespace
{
    const double REDUCERE_MAXIMA = 90.0;
}

// Aceleasi reguli sunt verificate de ambii constructori
void Promotie::valideaza() const
{
    if (nume.empty())
        throw std::invalid_argument("Numele promotiei nu poate fi gol.");
    if (produsVizat.empty())
        throw std::invalid_argument("Promotia trebuie sa vizeze un produs.");
    if (procent <= 0.0 || procent > REDUCERE_MAXIMA)
        throw std::invalid_argument("Reducerea promotiei trebuie sa fie intre 0 (exclusiv) si 90%.");
}

// Promotiile noi pornesc dezactivate, ca sa nu schimbe preturile din greseala
Promotie::Promotie(const std::string& numePromotie, const std::string& produs, double procentReducere)
    : nume(numePromotie), produsVizat(produs), procent(procentReducere), activa(false)
{
    valideaza();
}

Promotie::Promotie(const std::string& numePromotie, const std::string& produs, double procentReducere,
                   bool esteActiva)
    : nume(numePromotie), produsVizat(produs), procent(procentReducere), activa(esteActiva)
{
    valideaza();
}

const std::string& Promotie::getNume() const { return nume; }
const std::string& Promotie::getProdusVizat() const { return produsVizat; }
double Promotie::getProcent() const { return procent; }
bool Promotie::esteActiva() const { return activa; }

// Se aplica doar daca e activa si produsul coincide
bool Promotie::aplicabila(const std::string& produs) const
{
    return activa && produs == produsVizat;
}

double Promotie::calculeazaPretRedus(double pretInitial) const
{
    if (pretInitial < 0.0)
        throw std::invalid_argument("Pretul initial nu poate fi negativ.");
    return pretInitial * (1.0 - procent / 100.0);
}

// Cat economiseste clientul pe cantitatea data (0 daca promotia e oprita)
double Promotie::economie(double pretInitial, int cantitate) const
{
    if (!activa || cantitate <= 0)
        return 0.0;
    return cantitate * (pretInitial - calculeazaPretRedus(pretInitial));
}

void Promotie::activeaza()
{
    activa = true;
}

void Promotie::dezactiveaza()
{
    activa = false;
}

std::ostream& operator<<(std::ostream& os, const Promotie& p)
{
    os << p.nume << " | Produs: " << p.produsVizat << " | Reducere: " << p.procent << "%"
       << " | Stare: " << (p.activa ? "ACTIVA" : "oprita");
    return os;
}
