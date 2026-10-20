#include <iostream>
#include <string>
#include "Ingrediente.hpp"
#include "CReteta.hpp"
#include "Reteta.hpp"
#include "Cafenea.hpp"

int main()
{
    Cafenea cafenea("Bobis_Bob_Caffe", 1000.0);

    //  stoc de ingrediente de baza
    Ingrediente ingCafea("Cafea Boabe", 300.0, "g", 0.15);
    Ingrediente ingLapte("Lapte Integral", 1000.0, "ml", 0.01);
    Ingrediente ingVanilie("Sirop Vanilie", 200.0, "ml", 0.05);

    // Apel demonstrativ pentru toate metodele clasei Ingrediente
    ingCafea.adaugaStoc(50.0);
    ingCafea.consuma(10.0);
    std::cout << "[Test getteri ingrediente] " << ingCafea.getdenumire() << " " 
              << ingCafea.getcantitateDisponibila() << " " 
              << ingCafea.getunitateMasura() << " " 
              << ingCafea.getpretUnitate() << "\n";

    cafenea.adaugaIngredient(ingCafea);
    cafenea.adaugaIngredient(ingLapte);
    cafenea.adaugaIngredient(ingVanilie);

    //  Creare retete
    CReteta compEspresso[1] =
    {
        CReteta("Cafea Boabe", 18.0)
    };
    // Test getteri CReteta
    std::cout << "[Test getteri CReteta] " << compEspresso[0].getnume() << " " 
              << compEspresso[0].getcantitate() << "\n";

    Reteta espresso("Espresso", 10.0, compEspresso, 1);

    CReteta compCappuccino[2] =
    {
        CReteta("Cafea Boabe", 18.0),
        CReteta("Lapte Integral", 150.0)
    };
    Reteta cappuccino("Cappuccino", 16.0, compCappuccino, 2);

    CReteta compVanillaLatte[3] =
    {
        CReteta("Cafea Boabe", 18.0),
        CReteta("Lapte Integral", 200.0),
        CReteta("Sirop Vanilie", 20.0)
    };
    Reteta vanillaLatte("Vanilla Latte", 20.0, compVanillaLatte, 3);

    Reteta copieTest = cappuccino;         // Copy Constructor
    Reteta copieAtribuita;
    copieAtribuita = espresso;

    // Test getteri Reteta
    std::cout << "[Test getteri Reteta] " << espresso.getDenumire() << " " 
              << espresso.getPretVanzare() << " comp: " 
              << espresso.getNumarComponente() << "\n";

    // inregistrare retete in catalogul cafenelei
    cafenea.adaugaReteta(espresso);
    cafenea.adaugaReteta(cappuccino);
    cafenea.adaugaReteta(vanillaLatte);

    int optiune = -1;
    char op2;

    while (optiune != 0)
    {
        std::cout << "\n========================================\n";
        std::cout << "        MENIU GESTIUNE CAFENEA         \n";
        std::cout << "========================================\n";
        std::cout << "1. Afiseaza starea cafenelei (stocuri si sold)\n";
        std::cout << "2. Comanda Espresso\n";
        std::cout << "3. Comanda Cappuccino\n";
        std::cout << "4. Comanda Vanilla Latte\n";
        std::cout << "5. Verifica disponibilitate bautura\n";
        std::cout << "6. Afiseaza raportul de rentabilitate si profit\n";
        std::cout << "0. Iesire\n";
        std::cout << "Alege o optiune: ";
        std::cin >> optiune;

        if (optiune == 1)
        {
            std::cout << "\n" << cafenea << "\n";
            std::cout << "Doriti sa continuati? : (Y/N)";
            std::cin >> op2;
            if (op2 == 'Y')
                continue;
            else if (op2 == 'N')
                break;
            else
            {
                std::cout << "Eroare!\n";
                break;
            }
        }
        else if (optiune == 2)
        {
            cafenea.proceseazaComanda("Espresso");
            std::cout << "Doriti sa continuati? : (Y/N)";
            std::cin >> op2;
            if (op2 == 'Y')
                continue;
            else if (op2 == 'N')
                break;
            else
            {
                std::cout << "Eroare!\n";
                break;
            }
        }
        else if (optiune == 3)
        {
            cafenea.proceseazaComanda("Cappuccino");
            std::cout << "Doriti sa continuati? : (Y/N)";
            std::cin >> op2;
            if (op2 == 'Y')
                continue;
            else if (op2 == 'N')
                break;
            else
            {
                std::cout << "Eroare!\n";
                break;
            }
        }
        else if (optiune == 4)
        {
            cafenea.proceseazaComanda("Vanilla Latte");
            std::cout << "Doriti sa continuati? : (Y/N)";
            std::cin >> op2;
            if (op2 == 'Y')
                continue;
            else if (op2 == 'N')
                break;
            else
            {
                std::cout << "Eroare!\n";
                break;
            }
        }
        else if (optiune == 5)
        {
            std::string numeProdus;
            std::cout << "Introdu numele exact al bauturii de verificat: ";
            std::cin >> numeProdus;

            if (cafenea.poatePrepara(numeProdus))
            {
                std::cout << "[INFO] Exista stoc suficient pentru '" << numeProdus << "'.\n";
                std::cout << "Doriti sa continuati? : (Y/N)";
                std::cin >> op2;
                if (op2 == 'Y')
                    continue;
                else if (op2 == 'N')
                    break;
                else
                {
                    std::cout << "Eroare!\n";
                    break;
                }
            }
            else
            {
                std::cout << "[ATENTIE] Nu se poate prepara '" << numeProdus << "' (stoc insuficient sau produs inexistent).\n";
            }
        }
        else if (optiune == 6)
        {
            cafenea.afiseazaRaportProfitabilitate();
            std::cout << "Doriti sa continuati? : (Y/N)";
            std::cin >> op2;
            if (op2 == 'Y')
                continue;
            else if (op2 == 'N')
                break;
            else
            {
                std::cout << "Eroare!\n";
                break;
            }
        }
        else if (optiune == 0)
        {
            std::cout << "\nInchidere aplicatie. La revedere!\n";
        }
        else
        {
            std::cout << "\nOptiune invalida! Incearca din nou.\n";
        }
    }

    return 0;
}
