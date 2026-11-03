#include "IstoricVanzari.hpp"
#include <algorithm>
#include <fstream>

namespace
{
    // criteriu de sortare: cantitate descrescatoare, apoi nume crescator
    bool maiBun(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b)
    {
        if (a.second != b.second)
            return a.second > b.second;
        return a.first < b.first;
    }
}

IstoricVanzari::IstoricVanzari(const std::string& cafenea) : denumireCafenea(cafenea) {}

void IstoricVanzari::adaugaComanda(const Comanda& cmd)
{
    comenzi.push_back(cmd);
}

int IstoricVanzari::getNumarComenzi() const
{
    return static_cast<int>(comenzi.size());
}

double IstoricVanzari::totalIncasari() const
{
    double suma = 0.0;
    for (std::size_t i = 0; i < comenzi.size(); ++i)
        suma += comenzi[i].getTotal();
    return suma;
}

double IstoricVanzari::totalReduceri() const
{
    double suma = 0.0;
    for (std::size_t i = 0; i < comenzi.size(); ++i)
        suma += comenzi[i].getValoareReducere();
    return suma;
}

double IstoricVanzari::valoareMedieComanda() const
{
    if (comenzi.empty())
        return 0.0;
    return totalIncasari() / comenzi.size();
}

int IstoricVanzari::numarComenziClient(const std::string& client) const
{
    int nr = 0;
    for (std::size_t i = 0; i < comenzi.size(); ++i)
        if (comenzi[i].getNumeClient() == client)
            ++nr;
    return nr;
}

double IstoricVanzari::totalClient(const std::string& client) const
{
    double suma = 0.0;
    for (std::size_t i = 0; i < comenzi.size(); ++i)
        if (comenzi[i].getNumeClient() == client)
            suma += comenzi[i].getTotal();
    return suma;
}

const Comanda* IstoricVanzari::gasesteComanda(int id) const
{
    for (std::size_t i = 0; i < comenzi.size(); ++i)
        if (comenzi[i].getId() == id)
            return &comenzi[i];
    return nullptr;
}

// produs -> cate bucati s-au vandut in total (map pastreaza cheile sortate)
std::map<std::string, int> IstoricVanzari::cantitatiVandute() const
{
    std::map<std::string, int> rezultat;
    for (std::size_t i = 0; i < comenzi.size(); ++i)
    {
        const std::vector<LinieComanda>& linii = comenzi[i].getLinii();
        for (std::size_t j = 0; j < linii.size(); ++j)
            rezultat[linii[j].getDenumire()] += linii[j].getCantitate();
    }
    return rezultat;
}

std::vector<std::pair<std::string, int> > IstoricVanzari::topProduse(std::size_t n) const
{
    std::map<std::string, int> cant = cantitatiVandute();
    std::vector<std::pair<std::string, int> > lista(cant.begin(), cant.end());
    std::sort(lista.begin(), lista.end(), maiBun);
    if (lista.size() > n)
        lista.resize(n);
    return lista;
}

bool IstoricVanzari::salveazaInFisier(const std::string& cale) const
{
    std::ofstream fisier(cale.c_str());
    if (!fisier.is_open())
        return false;

    fisier << "# Raport vanzari - " << denumireCafenea << "\n";
    fisier << "# id;client;produse;subtotal;reducere%;total\n";
    for (std::size_t i = 0; i < comenzi.size(); ++i)
    {
        fisier << comenzi[i].getId() << ";"
               << comenzi[i].getNumeClient() << ";"
               << comenzi[i].getNumarProduse() << ";"
               << comenzi[i].getSubtotal() << ";"
               << comenzi[i].getReducere() << ";"
               << comenzi[i].getTotal() << "\n";
    }
    fisier << "# Total incasari: " << totalIncasari() << " Lei leuti\n";
    fisier << "# Total reduceri acordate: " << totalReduceri() << " Lei leuti\n";
    return fisier.good();
}

std::ostream& operator<<(std::ostream& os, const IstoricVanzari& ist)
{
    os << "========== ISTORIC VANZARI - " << ist.denumireCafenea << " ==========\n";
    if (ist.comenzi.empty())
    {
        os << "Nu exista comenzi inregistrate.\n";
    }
    for (std::size_t i = 0; i < ist.comenzi.size(); ++i)
        os << ist.comenzi[i] << "\n";            // operator<< din Comanda

    os << "----------------------------------------\n"
       << "Comenzi: " << ist.getNumarComenzi()
       << " | Incasari: " << ist.totalIncasari() << " Lei leuti"
       << " | Reduceri acordate: " << ist.totalReduceri() << " Lei leuti"
       << " | Valoare medie/comanda: " << ist.valoareMedieComanda() << " Lei leuti\n";

    std::vector<std::pair<std::string, int> > top = ist.topProduse(3);
    if (!top.empty())
    {
        os << "Top produse:\n";
        for (std::size_t i = 0; i < top.size(); ++i)
            os << "  " << (i + 1) << ". " << top[i].first << " (" << top[i].second << " buc.)\n";
    }
    os << "========================================";
    return os;
}
