#include "Reteta.hpp"

void Reteta::copiazaComp(const CReteta* sursa, int dim)
{
    if (dim > 0 && sursa != nullptr)
    {
        nrcomp = dim;
        componente = new CReteta[dim];
        for (int i = 0; i < dim; ++i)
            componente[i] = sursa[i];
    }
    else
    {
        componente = nullptr;
        nrcomp = 0;
    }
}

Reteta::Reteta() : denBaut(""), pretV(0.0), componente(nullptr), nrcomp(0) {}

Reteta::Reteta(const std::string& denumire, double pret, const CReteta* comp, int nrComp)
    : denBaut(denumire), pretV(pret), componente(nullptr), nrcomp(0)
{
    copiazaComp(comp, nrComp);
}

Reteta::Reteta(const Reteta& other)
    : denBaut(other.denBaut), pretV(other.pretV), componente(nullptr), nrcomp(0)
{
    copiazaComp(other.componente, other.nrcomp);
}

Reteta& Reteta::operator=(const Reteta& other)
{
    if (this != &other)
    {
        delete[] componente;
        denBaut = other.denBaut;
        pretV = other.pretV;
        copiazaComp(other.componente, other.nrcomp);
    }
    return *this;
}

Reteta::~Reteta()
{
    delete[] componente;
}

const std::string& Reteta::getDenumire() const { return denBaut; }
double Reteta::getPretVanzare() const { return pretV; }
int Reteta::getNumarComponente() const { return nrcomp; }
const CReteta* Reteta::getComponente() const { return componente; }

double Reteta::calculeazaCostProductie(const Ingrediente* stoc, int nrIngrediente) const
{
    double costTotal = 0.0;
    for (int i = 0; i < nrcomp; ++i)
    {
        for (int j = 0; j < nrIngrediente; ++j)
        {
            if (stoc[j].getdenumire() == componente[i].getnume())
                costTotal += componente[i].getcantitate() * stoc[j].getpretUnitate();
        }
    }
    return costTotal;
}

std::ostream& operator<<(std::ostream& os, const Reteta& ret)
{
    os << "Produs: " << ret.denBaut << " | Pret: " << ret.pretV << " Lei leuti | Ingrediente: [";
    for (int i = 0; i < ret.nrcomp; ++i)
    {
        os << ret.componente[i];   // compunere de apeluri operator<<
        if (i < ret.nrcomp - 1)
            os << ", ";
    }
    os << "]";
    return os;
}
