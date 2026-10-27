#ifndef INGREDIENTE_HPP
#define INGREDIENTE_HPP

#include <iostream>
#include <string>

class Ingrediente
{
private:
    std::string den;
    double stocd;
    std::string umas;
    double pretunit;
public:
    Ingrediente();
    Ingrediente(const std::string& denumire, double stoc, const std::string& unitate, double pret);

    const std::string& getdenumire() const;
    double getcantitateDisponibila() const;
    double getpretUnitate() const;
    const std::string& getunitateMasura() const;

    bool consuma(double cantitate);
    void adaugaStoc(double cantitate);

    friend std::ostream& operator<<(std::ostream& os, const Ingrediente& ing);
};

#endif

