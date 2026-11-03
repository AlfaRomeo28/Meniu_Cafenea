#include "Cafenea.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>

Cafenea::Cafenea(const std::string& numeCafenea, double fondInitial)
    : nume(numeCafenea), balansf(fondInitial), istoric(numeCafenea), urmatorulIdComanda(1),
      cheltuieliReaprovizionare(0.0) {}

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

// aduna necesarul total de ingrediente: daca ingredientul exista deja in lista,
// ii creste cantitatea sau il adauga
void Cafenea::adaugaLaNecesar(std::vector<CReteta>& necesar, const CReteta& comp)
{
    for (std::size_t i = 0; i < necesar.size(); ++i)
    {
        if (necesar[i].getnume() == comp.getnume())
        {
            necesar[i] = CReteta(comp.getnume(), necesar[i].getcantitate() + comp.getcantitate());
            return;
        }
    }
    necesar.push_back(comp);
}


bool Cafenea::stocAcopera(const std::vector<CReteta>& necesar) const
{
    for (std::size_t i = 0; i < necesar.size(); ++i)
    {
        int idx = gasesteIndexIngredient(necesar[i].getnume());
        if (idx == -1 || stocIngrediente[idx].getcantitateDisponibila() < necesar[i].getcantitate())
            return false;
    }
    return true;
}

void Cafenea::adaugaIngredient(const Ingrediente& ing)
{
    stocIngrediente.push_back(ing);
}

void Cafenea::adaugaReteta(const Reteta& ret)
{
    catalogR.push_back(ret);
}


// returneaza cate ingrediente a incarcat, sau -1 daca fisierul nu poate fi deschis
int Cafenea::incarcaIngredienteDinFisier(const std::string& cale)
{
    std::ifstream fisier(cale.c_str());
    if (!fisier.is_open())
        return -1;

    int incarcate = 0;
    std::string linie;
    while (std::getline(fisier, linie))
    {
        if (!linie.empty() && linie[linie.size() - 1] == '\r')
            linie.erase(linie.size() - 1);
        if (linie.empty() || linie[0] == '#')
            continue;

        std::stringstream ss(linie);
        std::string den, stocText, unitate, pretText;
        if (!(std::getline(ss, den, ';') && std::getline(ss, stocText, ';') &&
              std::getline(ss, unitate, ';') && std::getline(ss, pretText, ';')))
        {
            std::cout << "[ATENTIE] Linie invalida ignorata: " << linie << "\n";
            continue;
        }

        try
        {
            double stoc = std::stod(stocText);
            double pret = std::stod(pretText);
            if (den.empty() || stoc < 0.0 || pret < 0.0)
                throw std::invalid_argument("valori invalide");
            adaugaIngredient(Ingrediente(den, stoc, unitate, pret));
            ++incarcate;
        }
        catch (const std::exception&)
        {
            std::cout << "[ATENTIE] Valori invalide, linie ignorata: " << linie << "\n";
        }
    }
    return incarcate;
}

bool Cafenea::poatePrepara(const std::string& numeBautura) const
{
    int ir = gasesteIndexReteta(numeBautura);
    if (ir == -1)
        return false;

    const CReteta* comp = catalogR[ir].getComponente();
    int nrComp = catalogR[ir].getNumarComponente();
    std::vector<CReteta> necesar(comp, comp + nrComp);
    return stocAcopera(necesar);
}

// Comanda simpla (un singur produs, client anonim); foloseste comanda completa
bool Cafenea::proceseazaComanda(const std::string& numeBautura)
{
    Client anonim("Client anonim");
    return plaseazaComanda(anonim, std::vector<std::string>(1, numeBautura));
}

//Comanda client completa
//  1) aduna necesarul total, 2) verifica stocul pentru tot, 3) scade ingredientele, 4) aplica reducerea de fidelitate, 5) incaseaza si inregistreaza
bool Cafenea::plaseazaComanda(Client& client, const std::vector<std::string>& produse)
{
    if (produse.empty())
    {
        std::cout << "[EROARE] Comanda nu contine niciun produs.\n";
        return false;
    }

    std::vector<CReteta> necesar;
    for (std::size_t i = 0; i < produse.size(); ++i)
    {
        int ir = gasesteIndexReteta(produse[i]);
        if (ir == -1)
        {
            std::cout << "[EROARE] Produs necunoscut: '" << produse[i] << "'. Comanda anulata.\n";
            return false;
        }
        const CReteta* comp = catalogR[ir].getComponente();
        for (int j = 0; j < catalogR[ir].getNumarComponente(); ++j)
            adaugaLaNecesar(necesar, comp[j]);
    }

    if (!stocAcopera(necesar))
    {
        std::cout << "[EROARE] Stoc insuficient pentru intreaga comanda. Comanda anulata.\n";
        return false;
    }

    for (std::size_t i = 0; i < necesar.size(); ++i)
        stocIngrediente[gasesteIndexIngredient(necesar[i].getnume())].consuma(necesar[i].getcantitate());

    Comanda cmd(urmatorulIdComanda, client.getNume());
    for (std::size_t i = 0; i < produse.size(); ++i)
    {
        double pret = catalogR[gasesteIndexReteta(produse[i])].getPretVanzare();
        int ip = gasesteIndexPromotie(produse[i]);
        if (ip != -1)
        {
            double pretRedus = promotii[ip].calculeazaPretRedus(pret);
            std::cout << "[PROMO] " << promotii[ip].getNume() << ": " << produse[i] << " "
                      << pret << " -> " << pretRedus << " Lei leuti\n";
            pret = pretRedus;
        }
        cmd.adaugaLinie(produse[i], pret);
    }

    cmd.aplicaReducere(client.getReducere());   // reducerea nivelului de la inceputul comenzii
    balansf += cmd.getTotal();
    client.inregistreazaComanda(cmd.getTotal());
    istoric.adaugaComanda(cmd);
    urmatorulIdComanda = urmatorulIdComanda + 1;

    std::cout << "[COMANDA FINALIZATA]\n" << cmd << "\n";
    return true;
}

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
    cheltuieliReaprovizionare += cost;
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

void Cafenea::afiseazaIstoric() const
{
    std::cout << "\n" << istoric << "\n";
}

bool Cafenea::salveazaRaportVanzari(const std::string& cale) const
{
    return istoric.salveazaInFisier(cale);
}

const IstoricVanzari& Cafenea::getIstoric() const
{
    return istoric;
}

std::ostream& operator<<(std::ostream& os, const Cafenea& c)
{
    os << "-----------------------------------\n"
       << "Cafenea: " << c.nume << " | Balanta: " << c.balansf << " Lei leuti"
       << " | Comenzi finalizate: " << c.istoric.getNumarComenzi() << "\n"
       << "Stocuri Curente:\n";
    for (std::size_t i = 0; i < c.stocIngrediente.size(); ++i)
        os << "  * " << c.stocIngrediente[i] << "\n";
    os << "Catalog:\n";
    for (std::size_t i = 0; i < c.catalogR.size(); ++i)
        os << "  - " << c.catalogR[i] << "\n";
    os << "-----------------------------------";
    return os;
}

// Intoarce promotia activa cu cea mai mare reducere pentru produs, sau -1
int Cafenea::gasesteIndexPromotie(const std::string& produs) const
{
    int best = -1;
    for (std::size_t i = 0; i < promotii.size(); ++i)
    {
        if (promotii[i].aplicabila(produs) &&
            (best == -1 || promotii[i].getProcent() > promotii[best].getProcent()))
            best = static_cast<int>(i);
    }
    return best;
}

int Cafenea::gasesteIndexPromotieNume(const std::string& numePromotie) const
{
    for (std::size_t i = 0; i < promotii.size(); ++i)
        if (promotii[i].getNume() == numePromotie)
            return static_cast<int>(i);
    return -1;
}

void Cafenea::adaugaPromotie(const Promotie& promo)
{
    if (gasesteIndexReteta(promo.getProdusVizat()) == -1)
        throw std::invalid_argument("Promotia vizeaza un produs inexistent: " + promo.getProdusVizat());
    if (gasesteIndexPromotieNume(promo.getNume()) != -1)
        throw std::invalid_argument("Exista deja o promotie cu numele: " + promo.getNume());
    promotii.push_back(promo);
}

bool Cafenea::seteazaStarePromotie(const std::string& numePromotie, bool activa)
{
    int idx = gasesteIndexPromotieNume(numePromotie);
    if (idx == -1)
        return false;
    if (activa)
        promotii[idx].activeaza();
    else
        promotii[idx].dezactiveaza();
    return true;
}

void Cafenea::afiseazaPromotii() const
{
    std::cout << "\n---------- PROMOTII ----------\n";
    if (promotii.empty())
        std::cout << "Nu exista promotii definite.\n";
    for (std::size_t i = 0; i < promotii.size(); ++i)
        std::cout << " * " << promotii[i] << "\n";
    std::cout << "------------------------------\n";
}

// Costul materiei prime pentru TOATE bauturile vandute pana acum:
// pentru fiecare produs, cantitate vanduta * costul de productie al retetei
double Cafenea::costMateriePrimaVanduta() const
{
    double total = 0.0;
    std::vector<std::pair<std::string, int> > vandute = istoric.topProduse(catalogR.size());
    for (std::size_t i = 0; i < vandute.size(); ++i)
    {
        int ir = gasesteIndexReteta(vandute[i].first);
        if (ir == -1)
            continue;
        double costUnitar = catalogR[ir].calculeazaCostProductie(stocIngrediente.data(),
                                                                 static_cast<int>(stocIngrediente.size()));
        total += vandute[i].second * costUnitar;
    }
    return total;
}

RaportFinanciar Cafenea::raportFinanciar() const
{
    return RaportFinanciar(istoric.totalIncasari(), istoric.totalReduceri(),
                           costMateriePrimaVanduta(), cheltuieliReaprovizionare,
                           istoric.getNumarComenzi());
}

void Cafenea::afiseazaRaportFinanciar() const
{
    std::cout << "\n" << raportFinanciar() << "\n";
}

// Scrie stocul curent in acelasi format pe care il citeste incarcaIngredienteDinFisier
bool Cafenea::salveazaStocInFisier(const std::string& cale) const
{
    std::ofstream fisier(cale.c_str());
    if (!fisier.is_open())
        return false;

    fisier << "# denumire;stoc;unitate;pret_unitar\n";
    for (std::size_t i = 0; i < stocIngrediente.size(); ++i)
    {
        fisier << stocIngrediente[i].getdenumire() << ";"
               << stocIngrediente[i].getcantitateDisponibila() << ";"
               << stocIngrediente[i].getunitateMasura() << ";"
               << stocIngrediente[i].getpretUnitate() << "\n";
    }
    return fisier.good();
}
