#ifndef CRETETA_H
#define CRETETA_H

#include <iostream>
#include <string>

//  componenta a unei retete: un ingredient + cantitatea ceruta
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
