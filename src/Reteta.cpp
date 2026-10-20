#include "Reteta.hpp"

void Reteta::compiazacomp(const CReteta* sursa, int dim)
{
    nrcomp = dim;
    if(dim > 0 && sursa != nullptr)
    {
        componente = new CReteta[dim];
        for(int i = 0; i < dim; ++i)
        {
            componente[i] = sursa[i];
        }
    }
    else
    {
        componente = nullptr;
        nrcomp = 0;
    }
}

Reteta::Reteta()
    : denBaut(""), pretV(0.0), componente(nullptr), nrcomp(0)
{
}

Reteta::Reteta(const std::string& denumire, double pret, const CReteta* comp, int nrComp)
    : denBaut(denumire), pretV(pret), componente(nullptr), nrcomp(0)
{
    compiazacomp(comp, nrComp);
}

Reteta::~Reteta()
{
    delete[] componente;
}

//Constructor de copiere (Copy Constructor)
Reteta::Reteta(const Reteta& other)
    : denBaut(other.denBaut), pretV(other.pretV), componente(nullptr), nrcomp(0)
{
    compiazacomp(other.componente, other.nrcomp);
}

// Operator= de copiere
Reteta& Reteta::operator=(const Reteta& other)
{
    // Verificare auto-atribuirea (ex: r = r)
    if (this != &other)
    {
        // Eliberare memoria curenta
        delete[] componente;

        // Copiere valorile simple
        denBaut = other.denBaut;
        pretV = other.pretV;

        // Realizare deep copy pentru tabloul dinamic
        compiazacomp(other.componente, other.nrcomp);
    }
    return *this;
}

const std::string& Reteta::getDenumire() const
{
    return denBaut;
}

double Reteta::getPretVanzare() const
{
    return pretV;
}

int Reteta::getNumarComponente() const
{
    return nrcomp;
}

const CReteta* Reteta::getComponente() const
{
    return componente;
}

//Calculeaza costul de productie al retetei.Parcurge ingredientele si le inmulteste cu pretul lor unitar din stoc
double Reteta::calculeazaCostProductie(const Ingrediente* stoc, int nrIngrediente) const
{
    double costTotal = 0.0;
    for (int i = 0; i < nrcomp; ++i)
    {
        for (int j = 0; j < nrIngrediente; ++j)
        {
            if (stoc[j].getdenumire() == componente[i].getnume())
            {
                costTotal = costTotal + componente[i].getcantitate() * stoc[j].getpretUnitate();
            }
        }
    }
    return costTotal;
}

std::ostream& operator<<(std::ostream& os, const Reteta& ret)
{
    os << "Produs: " << ret.denBaut << " | Pret: " << ret.pretV << " Lei leuti | Ingrediente: [";
    for (int i = 0; i < ret.nrcomp; ++i)
    {
        os << ret.componente[i]; // refoloseste operator<< din CReteta (compunere de afisari)
        if (i < ret.nrcomp - 1)
        {
            os << ", ";
        }
    }
    os << "]";
    return os;
}
