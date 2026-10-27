#include <iostream>
#include <limits>
#include <string>
#include "Cafenea.hpp"

namespace
{
    void curataLinie()
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }


    bool continua()
    {
        char op;
        std::cout << "Doriti sa continuati? (Y/N): ";
        std::cin >> op;
        if (op == 'Y' || op == 'y')
            return true;
        if (op != 'N' && op != 'n')
            std::cout << "Eroare!\n";
        return false;
    }

    void afiseazaMeniu()
    {
        std::cout << "\n========================================\n"
                  << "        MENIU GESTIUNE CAFENEA         \n"
                  << "========================================\n"
                  << "1. Afiseaza starea cafenelei (stocuri, sold, catalog)\n"
                  << "2. Comanda Espresso\n"
                  << "3. Comanda Cappuccino\n"
                  << "4. Comanda Vanilla Latte\n"
                  << "5. Verifica disponibilitate bautura\n"
                  << "6. Afiseaza raportul de rentabilitate si profit\n"
                  << "7. Reaprovizioneaza un ingredient\n"
                  << "0. Iesire\n"
                  << "Alege o optiune: ";
    }
}

int main()
{
    Cafenea cafenea("Bobis_Bob_Caffe", 1300.0);

    cafenea.adaugaIngredient(Ingrediente("Cafea Boabe", 300.0, "g", 0.15));
    cafenea.adaugaIngredient(Ingrediente("Lapte Integral", 1000.0, "ml", 0.01));
    cafenea.adaugaIngredient(Ingrediente("Sirop Vanilie", 200.0, "ml", 0.05));

    CReteta compEspresso[1] = { CReteta("Cafea Boabe", 18.0) };
    Reteta espresso("Espresso", 10.0, compEspresso, 1);

    CReteta compCappuccino[2] = { CReteta("Cafea Boabe", 18.0), CReteta("Lapte Integral", 150.0) };
    Reteta cappuccino("Cappuccino", 16.0, compCappuccino, 2);

    CReteta compVanillaLatte[3] = { CReteta("Cafea Boabe", 18.0),
                                    CReteta("Lapte Integral", 200.0),
                                    CReteta("Sirop Vanilie", 20.0) };
    Reteta vanillaLatte("Vanilla Latte", 20.0, compVanillaLatte, 3);

    // constructor de copiere si operator=
    Reteta copieTest = cappuccino;
    Reteta copieAtribuita;
    copieAtribuita = espresso;
    std::cout << "Copie (ctor copiere): " << copieTest << "\n";
    std::cout << "Copie (operator=):    " << copieAtribuita << "\n";

    cafenea.adaugaReteta(espresso);
    cafenea.adaugaReteta(cappuccino);
    cafenea.adaugaReteta(vanillaLatte);

    int optiune = -1;
    while (optiune != 0)
    {
        afiseazaMeniu();
        if (!(std::cin >> optiune))
            break;
        curataLinie();

        switch (optiune)
        {
        case 1:
            std::cout << "\n" << cafenea << "\n";
            break;
        case 2:
            cafenea.proceseazaComanda("Espresso");
            break;
        case 3:
            cafenea.proceseazaComanda("Cappuccino");
            break;
        case 4:
            cafenea.proceseazaComanda("Vanilla Latte");
            break;
        case 5:
        {
            std::string numeProdus;
            std::cout << "Introdu numele exact al bauturii de verificat: ";
            std::getline(std::cin, numeProdus);
            if (cafenea.poatePrepara(numeProdus))
                std::cout << "[INFO] Exista stoc suficient pentru '" << numeProdus << "'.\n";
            else
                std::cout << "[ATENTIE] Nu se poate prepara '" << numeProdus
                          << "' (stoc insuficient sau produs inexistent).\n";
            break;
        }
        case 6:
            cafenea.afiseazaRaportProfitabilitate();
            break;
        case 7:
        {
            std::string ing;
            double cant;
            std::cout << "Ingredient: ";
            std::getline(std::cin, ing);
            std::cout << "Cantitate: ";
            std::cin >> cant;
            cafenea.reaprovizioneaza(ing, cant);
            break;
        }
        case 0:
            std::cout << "\nInchidere aplicatie. La revedere!\n";
            continue;
        default:
            std::cout << "\nOptiune invalida! Incearca din nou.\n";
            continue;
        }

        if (!continua())
            break;
    }
    return 0;
}
