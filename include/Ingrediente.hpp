#ifndef INGREDIENTE_HPP
#define INGREDIENTE_HPP

#include <iostream>
#include <string>

//clasa pentru ingrediente
class Ingrediente
{
private:
    std::string den;
    double stocd;
    std::string umas;
    double pretunit;
public:
    Ingrediente(); //constructorul implicit,practic aici setez starea initiala
    Ingrediente(const std::string& denumire, double stoc, const std::string& unitate, double pret); //initializare parametrii
    const std::string& getdenumire() const;
    double getcantitateDisponibila() const;
    double getpretUnitate() const;
    const std::string& getunitateMasura() const;
    void consuma(double cantitate);
    void adaugaStoc(double cantitate);
    friend std::ostream& operator<<(std::ostream& os, const Ingrediente& ing); //ofera acces la membri privati
};

#endif
