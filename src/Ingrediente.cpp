#include "Ingrediente.hpp"

Ingrediente::Ingrediente() : den(""), stocd(0.0), umas(""), pretunit(0.0) {}

Ingrediente::Ingrediente(const std::string& denumire, double stoc, const std::string& unitate, double pret)
    : den(denumire), stocd(stoc), umas(unitate), pretunit(pret) {}

const std::string& Ingrediente::getdenumire() const { return den; }
double Ingrediente::getcantitateDisponibila() const { return stocd; }
double Ingrediente::getpretUnitate() const { return pretunit; }
const std::string& Ingrediente::getunitateMasura() const { return umas; }

bool Ingrediente::consuma(double cantitate)
{
    if (cantitate <= stocd)
    {
        stocd -= cantitate;
        return true;
    }
    return false;
}

void Ingrediente::adaugaStoc(double cantitate)
{
    if (cantitate > 0.0)
        stocd += cantitate;
}

std::ostream& operator<<(std::ostream& os, const Ingrediente& ing)
{
    os << ing.den << ": " << ing.stocd << " " << ing.umas
       << " cost/unitate: " << ing.pretunit << " Lei leuti";
    return os;
}
