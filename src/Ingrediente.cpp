#include "Ingrediente.hpp"

//constructorul implicit,practic aici setez starea initiala
Ingrediente::Ingrediente()
    : den(""), stocd(0.0), umas(""), pretunit(0.0)
{
}

//initializare parametrii
Ingrediente::Ingrediente(const std::string& denumire, double stoc, const std::string& unitate, double pret)
    : den(denumire), stocd(stoc), umas(unitate), pretunit(pret)
{
}

const std::string& Ingrediente::getdenumire() const
{
    return den;
}

double Ingrediente::getcantitateDisponibila() const
{
    return stocd;
}

double Ingrediente::getpretUnitate() const
{
    return pretunit;
}

const std::string& Ingrediente::getunitateMasura() const
{
    return umas;
}

void Ingrediente::consuma(double cantitate)
{
    if (cantitate <= stocd)
    {
        stocd = stocd - cantitate;
    }
}

void Ingrediente::adaugaStoc(double cantitate)
{
    stocd = stocd + cantitate;
}

//ofera acces la membri privati
std::ostream& operator<<(std::ostream& os, const Ingrediente& ing)
{
    os << ing.den << ": " << ing.stocd << " " << ing.umas
       << " cost/unitate: " << ing.pretunit << " Lei leuti";
    return os;
}
