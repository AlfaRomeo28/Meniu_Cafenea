#include <iostream>
#include <cassert>
#include <cmath>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include "Cafenea.hpp"

namespace TestSuite
{
    bool aproapeEgal(double a, double b, double eps = 0.001)
    {
        return std::fabs(a - b) < eps;
    }

    void testIngredienteOperatii()
    {
        std::cout << "[TEST] Rulare testIngredienteOperatii...\n";

        Ingrediente ing("Cafea Boabe", 500.0, "g", 0.12);
        assert(ing.getNume() == "Cafea Boabe");
        assert(aproapeEgal(ing.getCantitate(), 500.0) || aproapeEgal(ing.getcantitateDisponibila(), 500.0));
        assert(ing.getUnitateMasura() == "g");

        // Consum valid
        ing.consuma(150.0);
        assert(aproapeEgal(ing.getCantitate(), 350.0) || aproapeEgal(ing.getcantitateDisponibila(), 350.0));

        // Adaugare stoc
        ing.adaugaStoc(200.0);
        assert(aproapeEgal(ing.getCantitate(), 550.0) || aproapeEgal(ing.getcantitateDisponibila(), 550.0));

        // Consum pana la limita exacta
        ing.consuma(550.0);
        assert(aproapeEgal(ing.getCantitate(), 0.0) || aproapeEgal(ing.getcantitateDisponibila(), 0.0));

        // Test consum peste stoc (trebuie sa arunce exceptie)
        bool aAruncat = false;
        try
        {
            ing.consuma(1.0);
        }
        catch (const std::exception&)
        {
            aAruncat = true;
        }
        assert(aAruncat == true);

        std::cout << "[PASS] testIngredienteOperatii reusit.\n";
    }

    void testCRetetaSiConstructori()
    {
        std::cout << "[TEST] Rulare testCRetetaSiConstructori...\n";

        CReteta c1("Lapte Integral", 150.0);
        assert(c1.getNume() == "Lapte Integral");
        assert(aproapeEgal(c1.getCantitate(), 150.0));

        // Constructor copiere
        CReteta c2 = c1;
        assert(c2.getNume() == "Lapte Integral");
        assert(aproapeEgal(c2.getCantitate(), 150.0));

        // Operator de atribuire
        CReteta c3("Zahar", 10.0);
        c3 = c1;
        assert(c3.getNume() == "Lapte Integral");
        assert(aproapeEgal(c3.getCantitate(), 150.0));

        std::cout << "[PASS] testCRetetaSiConstructori reusit.\n";
    }

    void testRetetaRegulaCelorTrei()
    {
        std::cout << "[TEST] Rulare testRetetaRegulaCelorTrei...\n";

        CReteta ingredienteFlatWhite[2] = {
            CReteta("Cafea Boabe", 18.0),
            CReteta("Lapte Integral", 130.0)
        };

        Reteta original("Flat White", 15.0, ingredienteFlatWhite, 2);
        assert(original.getNume() == "Flat White");
        assert(aproapeEgal(original.getPret(), 15.0));
        assert(original.getNrIngrediente() == 2);

        // Test Constructor Copiere (Deep Copy)
        Reteta copie(original);
        assert(copie.getNume() == original.getNume());
        assert(aproapeEgal(copie.getPret(), original.getPret()));
        assert(copie.getNrIngrediente() == original.getNrIngrediente());

        // Test Operator= (Deep Copy)
        Reteta atribuita;
        atribuita = original;
        assert(atribuita.getNume() == "Flat White");
        assert(aproapeEgal(atribuita.getPret(), 15.0));
        assert(atribuita.getNrIngrediente() == 2);

        // Test auto-atribuire
        atribuita = atribuita;
        assert(atribuita.getNume() == "Flat White");

        std::cout << "[PASS] testRetetaRegulaCelorTrei reusit.\n";
    }

    void testClientPuncteSiFormatare()
    {
        std::cout << "[TEST] Rulare testClientPuncteSiFormatare...\n";

        Client c1("Mihai Eminescu");
        assert(c1.getNume() == "Mihai Eminescu");
        assert(c1.getPuncte() == 0);
        assert(aproapeEgal(c1.getTotalCheltuit(), 0.0));

        // Nume invalid (sir gol)
        bool numeGresit = false;
        try
        {
            Client cInvalid("");
        }
        catch (const std::invalid_argument&)
        {
            numeGresit = true;
        }
        assert(numeGresit == true);

        // Test flux stream
        std::ostringstream out;
        out << c1;
        assert(!out.str().empty());

        std::cout << "[PASS] testClientPuncteSiFormatare reusit.\n";
    }

    void testCafeneaProcesareComenzi()
    {
        std::cout << "[TEST] Rulare testCafeneaProcesareComenzi...\n";

        Cafenea shop("TestShop", 500.0);

        // Incarcam stoc initial minimal
        shop.adaugaIngredient(Ingrediente("Cafea Boabe", 36.0, "g", 0.15));
        shop.adaugaIngredient(Ingrediente("Lapte Integral", 300.0, "ml", 0.01));

        CReteta comp[2] = { CReteta("Cafea Boabe", 18.0), CReteta("Lapte Integral", 150.0) };
        Reteta cappuccino("Cappuccino", 15.0, comp, 2);
        shop.adaugaReteta(cappuccino);

        assert(shop.poatePrepara("Cappuccino") == true);
        assert(shop.poatePrepara("ProdusInexistent") == false);

        // Prima comanda reusita
        shop.proceseazaComanda("Cappuccino");

        // A doua comanda reusita (epuizeaza stocul exact: 36g cafea, 300ml lapte)
        assert(shop.poatePrepara("Cappuccino") == true);
        shop.proceseazaComanda("Cappuccino");

        // A treia comanda trebuie sa esueze din lipsa de stoc
        assert(shop.poatePrepara("Cappuccino") == false);

        // Reaprovizionare
        shop.reaprovizioneaza("Cafea Boabe", 100.0);
        shop.reaprovizioneaza("Lapte Integral", 500.0);
        assert(shop.poatePrepara("Cappuccino") == true);

        std::cout << "[PASS] testCafeneaProcesareComenzi reusit.\n";
    }

    void testCafeneaComandaClientCompusa()
    {
        std::cout << "[TEST] Rulare testCafeneaComandaClientCompusa...\n";

        Cafenea shop("TestClientShop", 1000.0);
        shop.adaugaIngredient(Ingrediente("Cafea Boabe", 500.0, "g", 0.10));
        shop.adaugaIngredient(Ingrediente("Lapte Integral", 1000.0, "ml", 0.01));
        shop.adaugaIngredient(Ingrediente("Sirop Vanilie", 100.0, "ml", 0.05));

        CReteta cEspresso[1] = { CReteta("Cafea Boabe", 18.0) };
        shop.adaugaReteta(Reteta("Espresso", 10.0, cEspresso, 1));

        CReteta cVanilla[3] = {
            CReteta("Cafea Boabe", 18.0),
            CReteta("Lapte Integral", 200.0),
            CReteta("Sirop Vanilie", 20.0)
        };
        shop.adaugaReteta(Reteta("Vanilla Latte", 20.0, cVanilla, 3));

        Client client("George Enescu");
        std::vector<std::string> listaProduse;
        listaProduse.push_back("Espresso");
        listaProduse.push_back("Vanilla Latte");

        shop.plaseazaComanda(client, listaProduse);

        // Clientul trebuie sa fi inregistrat cumparaturi
        assert(client.getTotalCheltuit() > 0.0);

        std::cout << "[PASS] testCafeneaComandaClientCompusa reusit.\n";
    }

    void testSalvareRaportFisier()
    {
        std::cout << "[TEST] Rulare testSalvareRaportFisier...\n";

        Cafenea shop("FileTestShop", 250.0);
        shop.adaugaIngredient(Ingrediente("Cafea Boabe", 50.0, "g", 0.10));
        CReteta comp[1] = { CReteta("Cafea Boabe", 18.0) };
        shop.adaugaReteta(Reteta("Espresso", 8.0, comp, 1));

        shop.proceseazaComanda("Espresso");

        bool salvat = shop.salveazaRaportVanzari("test_raport_output.txt");
        assert(salvat == true);

        std::cout << "[PASS] testSalvareRaportFisier reusit.\n";
    }
}
int main() {

    TestSuite::testIngredienteOperatii();
    TestSuite::testCRetetaSiConstructori();
    TestSuite::testRetetaRegulaCelorTrei();
    TestSuite::testClientPuncteSiFormatare();
    TestSuite::testCafeneaProcesareComenzi();
    TestSuite::testCafeneaComandaClientCompusa();
    TestSuite::testSalvareRaportFisier();
}
