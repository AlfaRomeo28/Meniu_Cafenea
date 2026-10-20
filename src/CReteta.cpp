#include "CReteta.hpp"

CReteta::CReteta()
    : numeingre(""), cantcer(0.0)
{
}

CReteta::CReteta(const std::string& nume, double cantitate)
    : numeingre(nume), cantcer(cantitate)
{
}

const std::string& CReteta::getnume() const
{
    return numeingre;
}

double CReteta::getcantitate() const
{
    return cantcer;
}

//ofera acces la membri privati
std::ostream& operator<<(std::ostream& os, const CReteta& cr)
{
    os << cr.numeingre << " (" << cr.cantcer << ")";
    return os;
}
