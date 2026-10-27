#include "Cafenea.hpp"

Cafenea::Cafenea(const std::string& numeCafenea, double fondInitial)
    : nume(numeCafenea), balansf(fondInitial) {}

int Cafenea::gasesteIndexIngredient(const std::string& denumire) const
{
    for (std::size_t i = 0; i < stocIngrediente.size(); ++i)
        if (stocIngrediente[i].getdenumire() == denumire)
            return static_cast<int>(i);
    return -1;
}

int Cafenea::gasesteIndexReteta(const std::string& denumire) const
{
    for (std::size_t i = 0; i < catalogR.size(); ++i)
        if (catalogR[i].getDenumire() == denumire)
            return static_cast<int>(i);
    return -1;
}

void Cafenea::adaugaIngredient(const Ingrediente& ing)
{
    stocIngrediente.push_back(ing);
}

void Cafenea::adaugaReteta(const Reteta& ret)
{
    catalogR.push_back(ret);
}

bool Cafenea::poatePrepara(const std::string& numeBautura) const
{
    int ir = gasesteIndexReteta(numeBautura);
    if (ir == -1)
        return false;

    const CReteta* comp = catalogR[ir].getComponente();
    int nrComp = catalogR[ir].getNumarComponente();

    for (int j = 0; j < nrComp; ++j)
    {
        int indexStoc = gasesteIndexIngredient(comp[j].getnume());
        if (indexStoc == -1 ||
            stocIngrediente[indexStoc].getcantitateDisponibila() < comp[j].getcantitate())
            return false;
    }
    return true;
}

bool Cafenea::proceseazaComanda(const std::string& numeBautura)
{
    if (!poatePrepara(numeBautura))
    {
        std::cout << "[EROARE] Nu se poate prepara '" << numeBautura
                  << "': stoc insuficient sau produs necunoscut.\n";
        return false;
    }

    int ir = gasesteIndexReteta(numeBautura);
    const CReteta* comp = catalogR[ir].getComponente();
    int nrComp = catalogR[ir].getNumarComponente();

    for (int j = 0; j < nrComp; ++j)
    {
        int indexStoc = gasesteIndexIngredient(comp[j].getnume());
        stocIngrediente[indexStoc].consuma(comp[j].getcantitate());
    }

    balansf += catalogR[ir].getPretVanzare();

    std::cout << "[COMANDA FINALIZATA] S-a preparat " << numeBautura
              << " | Incasat: " << catalogR[ir].getPretVanzare() << " Lei leuti\n";
    return true;
}

// Cumpara stoc: scade costul din balanta si adauga cantitatea in stoc
bool Cafenea::reaprovizioneaza(const std::string& denumireIngredient, double cantitate)
{
    int idx = gasesteIndexIngredient(denumireIngredient);
    if (idx == -1 || cantitate <= 0.0)
    {
        std::cout << "[EROARE] Ingredient necunoscut sau cantitate invalida.\n";
        return false;
    }

    double cost = cantitate * stocIngrediente[idx].getpretUnitate();
    if (cost > balansf)
    {
        std::cout << "[EROARE] Fonduri insuficiente (necesar: " << cost
                  << " Lei leuti, disponibil: " << balansf << ").\n";
        return false;
    }

    balansf -= cost;
    stocIngrediente[idx].adaugaStoc(cantitate);
    std::cout << "[REAPROVIZIONARE] +" << cantitate << " "
              << stocIngrediente[idx].getunitateMasura() << " "
              << denumireIngredient << " | Cost: " << cost << " Lei leuti\n";
    return true;
}

void Cafenea::afiseazaRaportProfitabilitate() const
{
    std::cout << "\n---------- RAPORT RENTABILITATE CATALOG ----------\n";
    for (std::size_t i = 0; i < catalogR.size(); ++i)
    {
        double cost = catalogR[i].calculeazaCostProductie(stocIngrediente.data(),
                                                          static_cast<int>(stocIngrediente.size()));
        double pret = catalogR[i].getPretVanzare();
        double profitNet = pret - cost;
        double marja = (pret > 0.0) ? (profitNet / pret) * 100.0 : 0.0;

        std::cout << "- " << catalogR[i].getDenumire()
                  << " | Cost Productie: " << cost << " Lei leuti"
                  << " | Pret Vanzare: " << pret << " Lei leuti"
                  << " | Profit Net: " << profitNet << " Lei leuti"
                  << " (" << marja << "% marja)\n";
    }
    std::cout << "-----------------------------------\n";
}

std::ostream& operator<<(std::ostream& os, const Cafenea& c)
{
    os << "-----------------------------------\n"
       << "Cafenea: " << c.nume << " | Balanta: " << c.balansf << " Lei leuti\n"
       << "Stocuri Curente:\n";
    for (std::size_t i = 0; i < c.stocIngrediente.size(); ++i)
        os << "  * " << c.stocIngrediente[i] << "\n";   // operator<< din Ingrediente
    os << "Catalog:\n";
    for (std::size_t i = 0; i < c.catalogR.size(); ++i)
        os << "  - " << c.catalogR[i] << "\n";           // operator<< din Reteta
    os << "-----------------------------------";
    return os;
}
