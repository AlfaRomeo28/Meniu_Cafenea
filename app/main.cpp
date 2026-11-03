#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
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


    std::string taie(const std::string& text)
    {
        std::size_t inc = text.find_first_not_of(" \t\r");
        if (inc == std::string::npos)
            return "";
        std::size_t sf = text.find_last_not_of(" \t\r");
        return text.substr(inc, sf - inc + 1);
    }

    // "Espresso; Cappuccino" -> {"Espresso", "Cappuccino"}
    std::vector<std::string> imparteProduse(const std::string& linie)
    {
        std::vector<std::string> produse;
        std::stringstream ss(linie);
        std::string bucata;
        while (std::getline(ss, bucata, ';'))
        {
            bucata = taie(bucata);
            if (!bucata.empty())
                produse.push_back(bucata);
        }
        return produse;
    }

    // cauta clientul dupa nume; daca nu exista, il creeaza (poate arunca invalid_argument)
    Client& gasesteSauCreeazaClient(std::vector<Client>& clienti, const std::string& numeClient)
    {
        for (std::size_t i = 0; i < clienti.size(); ++i)
            if (clienti[i].getNume() == numeClient)
                return clienti[i];
        clienti.push_back(Client(numeClient));
        return clienti.back();
    }

    void incarcaStocInitial(Cafenea& cafenea)
    {
        int incarcate = cafenea.incarcaIngredienteDinFisier("ingrediente.txt");
        if (incarcate > 0)
        {
            std::cout << "[INFO] Am incarcat " << incarcate << " ingrediente din ingrediente.txt\n";
            return;
        }
        std::cout << "[INFO] ingrediente.txt lipseste sau e gol; folosesc stocul implicit.\n";
        cafenea.adaugaIngredient(Ingrediente("Cafea Boabe", 300.0, "g", 0.15));
        cafenea.adaugaIngredient(Ingrediente("Lapte Integral", 1000.0, "ml", 0.01));
        cafenea.adaugaIngredient(Ingrediente("Sirop Vanilie", 200.0, "ml", 0.05));
    }

    // submeniu pentru promotii: afisare, adaugare, activare, dezactivare
    void meniuPromotii(Cafenea& cafenea)
    {
        std::cout << "  1. Afiseaza promotiile\n"
                  << "  2. Adauga o promotie\n"
                  << "  3. Activeaza o promotie\n"
                  << "  4. Dezactiveaza o promotie\n"
                  << "  Alege: ";
        int sub = 0;
        std::cin >> sub;
        curataLinie();

        if (sub == 1)
        {
            cafenea.afiseazaPromotii();
        }
        else if (sub == 2)
        {
            std::string numePromo, produs;
            double procent = 0.0;
            std::cout << "Numele promotiei: ";
            std::getline(std::cin, numePromo);
            std::cout << "Produsul vizat: ";
            std::getline(std::cin, produs);
            std::cout << "Reducere (%): ";
            std::cin >> procent;
            curataLinie();

            cafenea.adaugaPromotie(Promotie(taie(numePromo), taie(produs), procent));
            std::cout << "[INFO] Promotie adaugata (oprita). Porneste-o din optiunea 3.\n";
        }
        else if (sub == 3 || sub == 4)
        {
            std::string numePromo;
            std::cout << "Numele promotiei: ";
            std::getline(std::cin, numePromo);
            if (cafenea.seteazaStarePromotie(taie(numePromo), sub == 3))
                std::cout << "[INFO] Promotia a fost " << (sub == 3 ? "activata" : "dezactivata") << ".\n";
            else
                std::cout << "[EROARE] Nu exista nicio promotie cu numele '" << numePromo << "'.\n";
        }
        else
        {
            std::cout << "Optiune invalida pentru promotii.\n";
        }
    }

    void afiseazaMeniu()
    {
        std::cout << "\n========================================\n"
                  << "        MENIU GESTIUNE CAFENEA         \n"
                  << "========================================\n"
                  << " 1. Afiseaza starea cafenelei (stocuri, sold, catalog)\n"
                  << " 2. Comanda Espresso\n"
                  << " 3. Comanda Cappuccino\n"
                  << " 4. Comanda Vanilla Latte\n"
                  << " 5. Verifica disponibilitate bautura\n"
                  << " 6. Afiseaza raportul de rentabilitate si profit\n"
                  << " 7. Reaprovizioneaza un ingredient\n"
                  << " 8. Comanda pentru un client (mai multe produse)\n"
                  << " 9. Afiseaza clientii si nivelurile de fidelitate\n"
                  << "10. Afiseaza istoricul vanzarilor\n"
                  << "11. Salveaza raportul de vanzari intr-un fisier\n"
                  << "12. Gestioneaza promotiile\n"
                  << "13. Afiseaza raportul financiar\n"
                  << "14. Salveaza raportul financiar intr-un fisier\n"
                  << "15. Salveaza stocul curent intr-un fisier\n"
                  << " 0. Iesire\n"
                  << "Alege o optiune: ";
    }
}

int main()
{
    Cafenea cafenea("Bobis_Bob_Caffe", 1000.0);
    incarcaStocInitial(cafenea);

    CReteta compEspresso[1] = { CReteta("Cafea Boabe", 18.0) };
    Reteta espresso("Espresso", 10.0, compEspresso, 1);

    CReteta compCappuccino[2] = { CReteta("Cafea Boabe", 18.0), CReteta("Lapte Integral", 150.0) };
    Reteta cappuccino("Cappuccino", 16.0, compCappuccino, 2);

    CReteta compVanillaLatte[3] = { CReteta("Cafea Boabe", 18.0),
                                    CReteta("Lapte Integral", 200.0),
                                    CReteta("Sirop Vanilie", 20.0) };
    Reteta vanillaLatte("Vanilla Latte", 20.0, compVanillaLatte, 3);

    //  constructor de copiere si operator=
    Reteta copieTest = cappuccino;
    Reteta copieAtribuita;
    copieAtribuita = espresso;
    std::cout << "Copie (ctor copiere): " << copieTest << "\n";
    std::cout << "Copie (operator=):    " << copieAtribuita << "\n";

    cafenea.adaugaReteta(espresso);
    cafenea.adaugaReteta(cappuccino);
    cafenea.adaugaReteta(vanillaLatte);

    // promotie definita din start, oprita; se porneste din meniu (optiunea 12)
    cafenea.adaugaPromotie(Promotie("Happy Hour Espresso", "Espresso", 20.0));

    std::vector<Client> clienti;

    int optiune = -1;
    while (optiune != 0)
    {
        afiseazaMeniu();
        if (!(std::cin >> optiune))
            break;
        curataLinie();

        try
        {
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
            case 8:
            {
                std::string numeClient, linieProduse;
                std::cout << "Numele clientului: ";
                std::getline(std::cin, numeClient);
                std::cout << "Produse (separate prin ';'): ";
                std::getline(std::cin, linieProduse);

                Client& client = gasesteSauCreeazaClient(clienti, taie(numeClient));
                cafenea.plaseazaComanda(client, imparteProduse(linieProduse));
                break;
            }
            case 9:
                if (clienti.empty())
                    std::cout << "Nu exista clienti inregistrati.\n";
                for (std::size_t i = 0; i < clienti.size(); ++i)
                    std::cout << " * " << clienti[i] << "\n";
                break;
            case 10:
                cafenea.afiseazaIstoric();
                break;
            case 11:
            {
                std::string cale;
                std::cout << "Numele fisierului de iesire: ";
                std::getline(std::cin, cale);
                if (cafenea.salveazaRaportVanzari(cale))
                    std::cout << "[INFO] Raport salvat in '" << cale << "'.\n";
                else
                    std::cout << "[EROARE] Nu am putut scrie fisierul '" << cale << "'.\n";
                break;
            }
            case 12:
                meniuPromotii(cafenea);
                break;
            case 13:
                cafenea.afiseazaRaportFinanciar();
                break;
            case 14:
            {
                std::string cale;
                std::cout << "Numele fisierului de iesire: ";
                std::getline(std::cin, cale);
                if (cafenea.raportFinanciar().salveazaInFisier(cale))
                    std::cout << "[INFO] Raport financiar salvat in '" << cale << "'.\n";
                else
                    std::cout << "[EROARE] Nu am putut scrie fisierul '" << cale << "'.\n";
                break;
            }
            case 15:
            {
                std::string cale;
                std::cout << "Numele fisierului pentru stoc: ";
                std::getline(std::cin, cale);
                if (cafenea.salveazaStocInFisier(cale))
                    std::cout << "[INFO] Stoc salvat in '" << cale << "'.\n";
                else
                    std::cout << "[EROARE] Nu am putut scrie fisierul '" << cale << "'.\n";
                break;
            }
            case 0:
                std::cout << "\nInchidere aplicatie. La revedere!\n";
                continue;
            default:
                std::cout << "\nOptiune invalida! Incearca din nou.\n";
                continue;
            }
        }
        catch (const std::exception& e)
        {
            std::cout << "[EXCEPTIE] " << e.what() << "\n";
        }

        if (!continua())
            break;
    }
    return 0;
}
