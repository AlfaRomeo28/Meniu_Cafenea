#include "RaportFinanciar.hpp"
#include <fstream>
#include <stdexcept>

RaportFinanciar::RaportFinanciar(double incasariTotale, double reduceriAcordate, double costMaterii,
                                 double cheltuieliStoc, int comenzi)
    : incasari(incasariTotale), reduceri(reduceriAcordate), costMateriePrima(costMaterii),
      cheltuieliReaprovizionare(cheltuieliStoc), numarComenzi(comenzi)
{
    if (incasari < 0.0 || reduceri < 0.0 || costMateriePrima < 0.0 ||
        cheltuieliReaprovizionare < 0.0 || numarComenzi < 0)
        throw std::invalid_argument("Valorile raportului financiar nu pot fi negative.");
}

double RaportFinanciar::getIncasari() const { return incasari; }
double RaportFinanciar::getReduceri() const { return reduceri; }
double RaportFinanciar::getCostMateriePrima() const { return costMateriePrima; }
double RaportFinanciar::getCheltuieliReaprovizionare() const { return cheltuieliReaprovizionare; }
int RaportFinanciar::getNumarComenzi() const { return numarComenzi; }

// profit brut = ce am incasat - cat a costat materia prima din bauturile vandute
double RaportFinanciar::profitBrut() const
{
    return incasari - costMateriePrima;
}

// flux de numerar = ce am incasat - ce am cheltuit pe cumparat stoc nou
double RaportFinanciar::fluxNumerar() const
{
    return incasari - cheltuieliReaprovizionare;
}

double RaportFinanciar::marjaBruta() const
{
    if (incasari <= 0.0)
        return 0.0;
    return profitBrut() / incasari * 100.0;
}

double RaportFinanciar::incasarePerComanda() const
{
    if (numarComenzi == 0)
        return 0.0;
    return incasari / numarComenzi;
}

// Ce procent din venitul "pe hartie" s-a pierdut prin reduceri (fidelitate + promotii)
double RaportFinanciar::ponderePierderiDinReduceri() const
{
    double potential = incasari + reduceri;
    if (potential <= 0.0)
        return 0.0;
    return reduceri / potential * 100.0;
}

std::string RaportFinanciar::interpretare() const
{
    if (numarComenzi == 0)
        return "Nu exista inca vanzari";
    if (profitBrut() <= 0.0)
        return "In pierdere";
    if (fluxNumerar() < 0.0)
        return "Profitabila, dar stocul nou a fost platit din rezerve";
    return "Profitabila";
}

bool RaportFinanciar::salveazaInFisier(const std::string& cale) const
{
    std::ofstream fisier(cale.c_str());
    if (!fisier.is_open())
        return false;

    fisier << "# Raport financiar\n"
           << "comenzi;" << numarComenzi << "\n"
           << "incasari;" << incasari << "\n"
           << "reduceri;" << reduceri << "\n"
           << "cost_materie_prima;" << costMateriePrima << "\n"
           << "cheltuieli_reaprovizionare;" << cheltuieliReaprovizionare << "\n"
           << "profit_brut;" << profitBrut() << "\n"
           << "flux_numerar;" << fluxNumerar() << "\n"
           << "marja_bruta_procent;" << marjaBruta() << "\n";
    return fisier.good();
}

std::ostream& operator<<(std::ostream& os, const RaportFinanciar& r)
{
    os << "========== RAPORT FINANCIAR ==========\n"
       << "Comenzi finalizate:        " << r.numarComenzi << "\n"
       << "Incasari:                  " << r.incasari << " Lei leuti\n"
       << "Reduceri acordate:         " << r.reduceri << " Lei leuti ("
       << r.ponderePierderiDinReduceri() << "% din venitul potential)\n"
       << "Cost materie prima:        " << r.costMateriePrima << " Lei leuti\n"
       << "Cheltuieli reaprovizionare:" << " " << r.cheltuieliReaprovizionare << " Lei leuti\n"
       << "Profit brut:               " << r.profitBrut() << " Lei leuti (marja "
       << r.marjaBruta() << "%)\n"
       << "Flux de numerar:           " << r.fluxNumerar() << " Lei leuti\n"
       << "Incasare medie/comanda:    " << r.incasarePerComanda() << " Lei leuti\n"
       << "Situatie:                  " << r.interpretare() << "\n"
       << "======================================";
    return os;
}
