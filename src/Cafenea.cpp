#include "Cafenea.hpp"

//dublează capacitatea tabloului de ingrediente când devine plin
void Cafenea::redimIngr()
{
    int capacN;
    if(capacitateIngrediente == 0)
    {
        capacN = 2;
    }
    else
    {
        capacN = capacitateIngrediente * 2;
    }
    Ingrediente* nou = new Ingrediente[capacN];
    for(int i = 0; i < nrIngrediente; ++i)
    {
        nou[i] = stocIngrediente[i];
    }
    delete[] stocIngrediente;
    stocIngrediente = nou;
    capacitateIngrediente = capacN;
}

//dublează capacitatea catalogului de rețete
void Cafenea::redimR()
{
    int capacN;
    if(capacitateR == 0)
    {
        capacN = 2;
    }
    else
    {
        capacN = capacitateR * 2;
    }
    Reteta* nou = new Reteta[capacN];
    for(int i = 0; i < nrR; ++i)
    {
        nou[i] = catalogR[i];
    }
    delete[] catalogR;
    catalogR = nou;
    capacitateR = capacN;
}

//cauta indexul unui ingredient după denumire; returnează -1 dacă nu există
int Cafenea::gasesteIndexIngredient(const std::string& denumire) const
{
    for(int i = 0; i < nrIngrediente; ++i)
    {
        if(stocIngrediente[i].getdenumire() == denumire)
        {
            return i;
        }
    }
    return -1;
}

Cafenea::Cafenea(const std::string& numeCafenea, double fondInitial)
    : nume(numeCafenea), balansf(fondInitial),
      stocIngrediente(nullptr), capacitateIngrediente(0), nrIngrediente(0),
      catalogR(nullptr), capacitateR(0), nrR(0)
{
}

//eliberare memorie alocata dinamic pt a evita memory leaks
Cafenea::~Cafenea()
{
    delete[] stocIngrediente;
    delete[] catalogR;
}

//adaugare ingrediente si retete
void Cafenea::adaugaIngredient(const Ingrediente& ing)
{
    if (nrIngrediente == capacitateIngrediente)
    {
        redimIngr();
    }
    stocIngrediente[nrIngrediente] = ing;
    nrIngrediente = nrIngrediente + 1;
}

void Cafenea::adaugaReteta(const Reteta& ret)
{
    if (nrR == capacitateR)
    {
        redimR();
    }
    catalogR[nrR] = ret;
    nrR = nrR + 1;
}

//verificare disponibilitate stoc
bool Cafenea::poatePrepara(const std::string& numeBautura) const
{
    for (int i = 0; i < nrR; ++i)
    {
        if (catalogR[i].getDenumire() == numeBautura)
        {
            const CReteta* componente = catalogR[i].getComponente();
            int nrComp = catalogR[i].getNumarComponente();

            // verifica fiecare ingredient cerut de reteta
            for (int j = 0; j < nrComp; ++j)
            {
                int indexStoc = gasesteIndexIngredient(componente[j].getnume());

                // Ingredientul nu exista deloc sau nu avem cantitate suficienta
                if (indexStoc == -1 || stocIngrediente[indexStoc].getcantitateDisponibila() < componente[j].getcantitate())
                {
                    return false;
                }
            }
            return true; // Toate ingredientele sunt disponibile
        }
    }
    return false; // Reteta nu a fost găsită în catalog
}

// Scade ingredientele folosite din stoc și incaseaza banii
bool Cafenea::proceseazaComanda(const std::string& numeBautura)
{
    if (!poatePrepara(numeBautura))
    {
        std::cout << "[EROARE] Nu se poate prepara '" << numeBautura << "': stoc insuficient sau produs necunoscut.\n";
        return false;
    }

    for (int i = 0; i < nrR; ++i)
    {
        if (catalogR[i].getDenumire() == numeBautura)
        {
            const CReteta* componente = catalogR[i].getComponente();
            int nrComp = catalogR[i].getNumarComponente();

            // Scadere ingrediente stoc
            for (int j = 0; j < nrComp; ++j)
            {
                int indexStoc = gasesteIndexIngredient(componente[j].getnume());
                stocIngrediente[indexStoc].consuma(componente[j].getcantitate());
            }

            // Adauga pretul produsului la balanta financiara
            balansf = balansf + catalogR[i].getPretVanzare();

            std::cout << "[COMANDA FINALIZATA] S-a preparat " << numeBautura
                      << " | Incasat: " << catalogR[i].getPretVanzare() << " Lei leuti\n";
            return true;
        }
    }
    return false;
}

//calcul costul materiei prime, marja de profit si procentul de rentabilitate
void Cafenea::afiseazaRaportProfitabilitate() const
{
    std::cout << "\n---------- RAPORT RENTABILITATE CATALOG ---------- \n";
    for (int i = 0; i < nrR; ++i)
    {
        double cost = catalogR[i].calculeazaCostProductie(stocIngrediente, nrIngrediente);
        double pret = catalogR[i].getPretVanzare();
        double profitNet = pret - cost;
        double marjaProcentuala = 0.0;

        if (pret > 0.0)
        {
            marjaProcentuala = (profitNet / pret) * 100.0;
        }

        std::cout << "- " << catalogR[i].getDenumire()
                  << " | Cost Productie: " << cost << " Lei leuti"
                  << " | Pret Vanzare: " << pret << " Lei leuti"
                  << " | Profit Net: " << profitNet << " Lei leuti"
                  << " (" << marjaProcentuala << "% marja)\n";
    }
    std::cout << "-----------------------------------\n";
}

std::ostream& operator<<(std::ostream& os, const Cafenea& c)
{
    os << "-----------------------------------\n"
       << "Cafenea: " << c.nume << " | Balanta: " << c.balansf << " Lei leuti\n"
       << "Stocuri Curente:\n";

    for (int i = 0; i < c.nrIngrediente; ++i)
    {
        os << "  * " << c.stocIngrediente[i] << "\n";
    }

    os << "-----------------------------------";
    return os;
}
