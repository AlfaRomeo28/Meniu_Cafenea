#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <string>

// client fidel al cafenelei: aduna puncte, iar nivelul lui da reducere
class Client
{
private:
    std::string nume;
    double puncteFidelitate;
    double totalCheltuit;
    int numarComenzi;

    int indiceNivel() const;   // 0 = Standard, 1 = Argint, 2 = Aur
public:
    explicit Client(const std::string& numeClient);
    Client(const std::string& numeClient, double puncte, double totalInitial, int comenzi);

    const std::string& getNume() const;
    double getPuncte() const;
    double getTotalCheltuit() const;
    int getNumarComenzi() const;

    std::string getNivel() const;
    double getReducere() const;                 // procent: 0, 5 sau 10
    void inregistreazaComanda(double sumaPlatita);

    friend std::ostream& operator<<(std::ostream& os, const Client& c);
};

#endif
