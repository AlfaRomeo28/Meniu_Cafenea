#include "Client.hpp"
#include <stdexcept>

namespace
{
    const double PRAG_ARGINT = 30.0;
    const double PRAG_AUR = 100.0;
}

Client::Client(const std::string& numeClient)
    : nume(numeClient), puncteFidelitate(0.0), totalCheltuit(0.0), numarComenzi(0)
{
    if (nume.empty())
        throw std::invalid_argument("Numele clientului nu poate fi gol.");
}

Client::Client(const std::string& numeClient, double puncte, double totalInitial, int comenzi)
    : nume(numeClient), puncteFidelitate(puncte), totalCheltuit(totalInitial), numarComenzi(comenzi)
{
    if (nume.empty())
        throw std::invalid_argument("Numele clientului nu poate fi gol.");
    if (puncte < 0.0 || totalInitial < 0.0 || comenzi < 0)
        throw std::invalid_argument("Valorile initiale ale clientului nu pot fi negative.");
}

const std::string& Client::getNume() const { return nume; }
double Client::getPuncte() const { return puncteFidelitate; }
double Client::getTotalCheltuit() const { return totalCheltuit; }
int Client::getNumarComenzi() const { return numarComenzi; }

int Client::indiceNivel() const
{
    if (puncteFidelitate >= PRAG_AUR)
        return 2;
    if (puncteFidelitate >= PRAG_ARGINT)
        return 1;
    return 0;
}

std::string Client::getNivel() const
{
    switch (indiceNivel())
    {
    case 2:
        return "Aur";
    case 1:
        return "Argint";
    default:
        return "Standard";
    }
}

double Client::getReducere() const
{
    switch (indiceNivel())
    {
    case 2:
        return 10.0;
    case 1:
        return 5.0;
    default:
        return 0.0;
    }
}

// 1 leu platit = 1 punct de fidelitate
void Client::inregistreazaComanda(double sumaPlatita)
{
    if (sumaPlatita < 0.0)
        throw std::invalid_argument("Suma platita nu poate fi negativa.");
    puncteFidelitate += sumaPlatita;
    totalCheltuit += sumaPlatita;
    numarComenzi = numarComenzi + 1;
}

std::ostream& operator<<(std::ostream& os, const Client& c)
{
    os << c.nume << " | Nivel: " << c.getNivel()
       << " (reducere " << c.getReducere() << "%)"
       << " | Puncte: " << c.puncteFidelitate
       << " | Comenzi: " << c.numarComenzi
       << " | Total cheltuit: " << c.totalCheltuit << " Lei leuti";
    return os;
}
