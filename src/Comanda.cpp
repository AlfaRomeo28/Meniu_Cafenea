#include "Comanda.hpp"
#include <stdexcept>

Comanda::Comanda(int idComanda, const std::string& client)
    : id(idComanda), numeClient(client), reducereProcent(0.0)
{
    if (id <= 0)
        throw std::invalid_argument("Id-ul comenzii trebuie sa fie pozitiv.");
    if (numeClient.empty())
        throw std::invalid_argument("Comanda trebuie sa aiba un client.");
}

int Comanda::gasesteLinie(const std::string& denumire) const
{
    for (std::size_t i = 0; i < linii.size(); ++i)
        if (linii[i].getDenumire() == denumire)
            return static_cast<int>(i);
    return -1;
}

// Daca produsul exista deja pe bon, doar creste cantitatea
void Comanda::adaugaLinie(const std::string& denumire, double pretUnitar, int cantitate)
{
    int idx = gasesteLinie(denumire);
    if (idx == -1)
        linii.push_back(LinieComanda(denumire, cantitate, pretUnitar));
    else
        linii[idx].adaugaCantitate(cantitate);
}

void Comanda::aplicaReducere(double procent)
{
    if (procent < 0.0 || procent > 100.0)
        throw std::invalid_argument("Reducerea trebuie sa fie intre 0 si 100%.");
    reducereProcent = procent;
}

int Comanda::getId() const { return id; }
const std::string& Comanda::getNumeClient() const { return numeClient; }
const std::vector<LinieComanda>& Comanda::getLinii() const { return linii; }
double Comanda::getReducere() const { return reducereProcent; }

int Comanda::getNumarProduse() const
{
    int total = 0;
    for (std::size_t i = 0; i < linii.size(); ++i)
        total += linii[i].getCantitate();
    return total;
}

double Comanda::getSubtotal() const
{
    double suma = 0.0;
    for (std::size_t i = 0; i < linii.size(); ++i)
        suma += linii[i].getTotal();
    return suma;
}

double Comanda::getValoareReducere() const
{
    return getSubtotal() * reducereProcent / 100.0;
}

double Comanda::getTotal() const
{
    return getSubtotal() - getValoareReducere();
}

std::ostream& operator<<(std::ostream& os, const Comanda& c)
{
    os << "Comanda #" << c.id << " | Client: " << c.numeClient << "\n";
    for (std::size_t i = 0; i < c.linii.size(); ++i)
        os << "  - " << c.linii[i] << "\n";     // operator<< din LinieComanda
    os << "  Subtotal: " << c.getSubtotal()
       << " | Reducere: " << c.reducereProcent << "% (-" << c.getValoareReducere() << ")"
       << " | TOTAL: " << c.getTotal() << " Lei leuti";
    return os;
}
