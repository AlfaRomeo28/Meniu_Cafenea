#ifndef CRETETA_HPP
#define CRETETA_HPP

#include <iostream>
#include <string>

//  ingredient + cantitatea ceruta
class CReteta
{
private:
    std::string numeingre;
    double cantcer;
public:
    CReteta();
    CReteta(const std::string& nume, double cantitate);

    const std::string& getnume() const;
    double getcantitate() const;

    friend std::ostream& operator<<(std::ostream& os, const CReteta& cr);
};
#endif
