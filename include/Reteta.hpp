#ifndef RETETA_HPP
#define RETETA_HPP

#include <iostream>
#include <string>
#include "CReteta.hpp"
#include "Ingrediente.hpp"


class Reteta
{
private:
    std::string denBaut;
    double pretV;
    CReteta* componente;
    int nrcomp;

    void copiazaComp(const CReteta* sursa, int dim);
public:
    Reteta();
    Reteta(const std::string& denumire, double pret, const CReteta* comp, int nrComp);
    Reteta(const Reteta& other);
    Reteta& operator=(const Reteta& other);
    ~Reteta();

    const std::string& getDenumire() const;
    double getPretVanzare() const;
    int getNumarComponente() const;
    const CReteta* getComponente() const;

    double calculeazaCostProductie(const Ingrediente* stoc, int nrIngrediente) const;

    friend std::ostream& operator<<(std::ostream& os, const Reteta& ret);
};

#endif

