#ifndef LINIECOMANDA_HPP
#define LINIECOMANDA_HPP

#include <iostream>
#include <string>

// linia de pe bonul unei comenzi: produs, cantitate, pret unitar
class LinieComanda
{
private:
    std::string denumire;
    int cantitate;
    double pretUnitar;
public:
    LinieComanda(const std::string& denumireProdus, int cant, double pret);

    const std::string& getDenumire() const;
    int getCantitate() const;
    double getPretUnitar() const;
    double getTotal() const;

    void adaugaCantitate(int cant);

    friend std::ostream& operator<<(std::ostream& os, const LinieComanda& l);
};

#endif
