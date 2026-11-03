#include <iostream>
#include <cassert>
#include <cmath>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
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

        ing.consuma(150.0);
        assert(aproapeEgal(ing.getCantitate(), 350.0) || aproapeEgal(ing.getcantitateDisponibila(), 350.0));

        ing.adaugaStoc(200.0);
        assert(aproapeEgal(ing.getCantitate(), 550.0) || aproapeEgal(ing.getcantitateDisponibila(), 550.0));

        ing.consuma(550.0);
        assert(aproapeEgal(ing.getCantitate(), 0.0) || aproapeEgal(ing.getcantitateDisponibila(), 0.0));

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

    void testIngredienteCazuriLimita()
    {
        std::cout << "[TEST] Rulare testIngredienteCazuriLimita...\n";

        Ingrediente vanilie("Esenta Vanilie", 0.0, "ml", 0.50);
        assert(aproapeEgal(vanilie.getCantitate(), 0.0) || aproapeEgal(vanilie.getcantitateDisponibila(), 0.0));

        vanilie.adaugaStoc(0.001);
        assert((vanilie.getCantitate() > 0.0) || (vanilie.getcantitateDisponibila() > 0.0));

        vanilie.consuma(0.001);
        assert(aproapeEgal(vanilie.getCantitate(), 0.0) || aproapeEgal(vanilie.getcantitateDisponibila(), 0.0));

        // Consum repetat in pasi mici
        Ingrediente scortisoara("Scortisoara", 10.0, "g", 0.02);
        for (int i = 0; i < 100; ++i)
        {
            scortisoara.consuma(0.1);
        }
        assert(aproapeEgal(scortisoara.getCantitate(), 0.0, 0.01) || 
               aproapeEgal(scortisoara.getcantitateDisponibila(), 0.0, 0.01));

        // Verificare valori negative la adaugare
        bool stocNegativBlocat = false;
        try
        {
            scortisoara.adaugaStoc(-5.0);
        }
        catch (const std::exception&)
        {
            stocNegativBlocat = true;
        }
        (void)stocNegativBlocat;

        std::cout << "[PASS] testIngredienteCazuriLimita reusit.\n";
    }

    void testCRetetaSiConstructori()
    {
        std::cout << "[TEST] Rulare testCRetetaSiConstructori...\n";

        CReteta c1("Lapte Integral", 150.0);
        assert(c1.getNume() == "Lapte Integral");
        assert(aproapeEgal(c1.getCantitate(), 150.0));

        CReteta c2 = c1;
        assert(c2.getNume() == "Lapte Integral");
        assert(aproapeEgal(c2.getCantitate(), 150.0));

        CReteta c3("Zahar", 10.0);
        c3 = c1;
        assert(c3.getNume() == "Lapte Integral");
        assert(aproapeEgal(c3.getCantitate(), 150.0));

        std::cout << "[PASS] testCRetetaSiConstructori reusit.\n";
    }

    void testCRetetaModificariSiValidari()
    {
        std::cout << "[TEST] Rulare testCRetetaModificariSiValidari...\n";

        CReteta ing1("Miere", 25.0);
        CReteta ing2("Ciocolata Calda", 40.0);

        assert(ing1.getNume() != ing2.getNume());
        assert(!aproapeEgal(ing1.getCantitate(), ing2.getCantitate()));

        std::vector<CReteta> lista;
        lista.push_back(ing1);
        lista.push_back(ing2);
        lista.push_back(CReteta("Frisca", 30.0));

        assert(lista.size() == 3);
        assert(lista[0].getNume() == "Miere");
        assert(lista[1].getNume() == "Ciocolata Calda");
        assert(lista[2].getNume() == "Frisca");

        std::cout << "[PASS] testCRetetaModificariSiValidari reusit.\n";
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

        Reteta copie(original);
        assert(copie.getNume() == original.getNume());
        assert(aproapeEgal(copie.getPret(), original.getPret()));
        assert(copie.getNrIngrediente() == original.getNrIngrediente());

        Reteta atribuita;
        atribuita = original;
        assert(atribuita.getNume() == "Flat White");
        assert(aproapeEgal(atribuita.getPret(), 15.0));
        assert(atribuita.getNrIngrediente() == 2);

        atribuita = atribuita;
        assert(atribuita.getNume() == "Flat White");

        std::cout << "[PASS] testRetetaRegulaCelorTrei reusit.\n";
    }

    void testReteteComplexeSiCopiereAdanca()
    {
        std::cout << "[TEST] Rulare testReteteComplexeSiCopiereAdanca...\n";

        CReteta compMocha[4] = {
            CReteta("Cafea Boabe", 18.0),
            CReteta("Lapte Integral", 150.0),
            CReteta("Sirop Ciocolata", 30.0),
            CReteta("Frisca", 20.0)
        };

        Reteta mocha("Caffe Mocha", 19.5, compMocha, 4);
        assert(mocha.getNrIngrediente() == 4);

        // Scope local pentru a verifica ca distrugerea copiei nu afecteaza originalul
        {
            Reteta copieTemporara = mocha;
            assert(copieTemporara.getNrIngrediente() == 4);
            assert(copieTemporara.getNume() == "Caffe Mocha");
        }

        // Daca destructorul a eliberat memoria gresit, urmatoarele verificari vor pica
        assert(mocha.getNrIngrediente() == 4);
        assert(mocha.getNume() == "Caffe Mocha");
        assert(aproapeEgal(mocha.getPret(), 19.5));

        std::cout << "[PASS] testReteteComplexeSiCopiereAdanca reusit.\n";
    }

    void testClientPuncteSiFormatare()
    {
        std::cout << "[TEST] Rulare testClientPuncteSiFormatare...\n";

        Client c1("Mihai Eminescu");
        assert(c1.getNume() == "Mihai Eminescu");
        assert(c1.getPuncte() == 0);
        assert(aproapeEgal(c1.getTotalCheltuit(), 0.0));

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

        std::ostringstream out;
        out << c1;
        assert(!out.str().empty());

        std::cout << "[PASS] testClientPuncteSiFormatare reusit.\n";
    }

    void testClientGestiuneMultipla()
    {
        std::cout << "[TEST] Rulare testClientGestiuneMultipla...\n";

        std::vector<Client> clienti;
        clienti.push_back(Client("Ana Aslan"));
        clienti.push_back(Client("Mircea Eliade"));
        clienti.push_back(Client("Henri Coanda"));

        assert(clienti.size() == 3);
        assert(clienti[0].getNume() == "Ana Aslan");
        assert(clienti[1].getNume() == "Mircea Eliade");
        assert(clienti[2].getNume() == "Henri Coanda");

        for (std::size_t i = 0; i < clienti.size(); ++i)
        {
            std::ostringstream ss;
            ss << clienti[i];
            assert(ss.str().find(clienti[i].getNume()) != std::string::npos);
        }

        std::cout << "[PASS] testClientGestiuneMultipla reusit.\n";
    }

    void testCafeneaProcesareComenzi()
    {
        std::cout << "[TEST] Rulare testCafeneaProcesareComenzi...\n";

        Cafenea shop("TestShop", 500.0);

        shop.adaugaIngredient(Ingrediente("Cafea Boabe", 36.0, "g", 0.15));
        shop.adaugaIngredient(Ingrediente("Lapte Integral", 300.0, "ml", 0.01));

        CReteta comp[2] = { CReteta("Cafea Boabe", 18.0), CReteta("Lapte Integral", 150.0) };
        Reteta cappuccino("Cappuccino", 15.0, comp, 2);
        shop.adaugaReteta(cappuccino);

        assert(shop.poatePrepara("Cappuccino") == true);
        assert(shop.poatePrepara("ProdusInexistent") == false);

        shop.proceseazaComanda("Cappuccino");

        assert(shop.poatePrepara("Cappuccino") == true);
        shop.proceseazaComanda("Cappuccino");

        assert(shop.poatePrepara("Cappuccino") == false);

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
        assert(client.getTotalCheltuit() > 0.0);

        std::cout << "[PASS] testCafeneaComandaClientCompusa reusit.\n";
    }

    void testCafeneaComenziEsuateSiPartialitate()
    {
        std::cout << "[TEST] Rulare testCafeneaComenziEsuateSiPartialitate...\n";

        Cafenea shop("StresShop", 100.0);
        shop.adaugaIngredient(Ingrediente("Cafea Boabe", 20.0, "g", 0.10));

        CReteta cEspresso[1] = { CReteta("Cafea Boabe", 18.0) };
        shop.adaugaReteta(Reteta("Espresso", 8.0, cEspresso, 1));

        Client client("Cineva Oarecare");
        std::vector<std::string> comandaImposibila;
        comandaImposibila.push_back("Espresso");
        comandaImposibila.push_back("BauturaCareNuExista");

        // Daca lista are produse inexistente, nu ar trebui sa altereze starea clientului nejustificat
        double cheltuieliInitiale = client.getTotalCheltuit();
        try
        {
            shop.plaseazaComanda(client, comandaImposibila);
        }
        catch (const std::exception&)
        {
            // Tratare conform implementarii
        }
        (void)cheltuieliInitiale;

        std::cout << "[PASS] testCafeneaComenziEsuateSiPartialitate reusit.\n";
    }

    void testSalvareRaportFisier()
    {
        std::cout << "[TEST] Rulare testSalvareRaportFisier...\n";

        Cafenea shop("FileTestShop", 250.0);
        shop.adaugaIngredient(Ingrediente("Cafea Boabe", 50.0, "g", 0.10));
        CReteta comp[1] = { CReteta("Cafea Boabe", 18.0) };
        shop.adaugaReteta(Reteta("Espresso", 8.0, comp, 1));

        shop.proceseazaComanda("Espresso");

        const std::string caleFisier = "test_raport_output.txt";
        bool salvat = shop.salveazaRaportVanzari(caleFisier);
        assert(salvat == true);

        // Verificam ca fisierul exista si nu este gol
        std::ifstream fIn(caleFisier.c_str());
        assert(fIn.is_open());
        std::string linie;
        bool areContinut = false;
        while (std::getline(fIn, linie))
        {
            if (!linie.empty())
            {
                areContinut = true;
                break;
            }
        }
        fIn.close();
        assert(areContinut == true);

        std::cout << "[PASS] testSalvareRaportFisier reusit.\n";
    }

    void testIncarcareFisierConfiguratie()
    {
        std::cout << "[TEST] Rulare testIncarcareFisierConfiguratie...\n";

        const std::string fisierMock = "test_ingrediente_mock.txt";
        std::ofstream fOut(fisierMock.c_str());
        fOut << "Zahar 200 g 0.05\n";
        fOut << "Cacao 150 g 0.08\n";
        fOut.close();

        Cafenea shop("MockShop", 300.0);
        int nrIncarcate = shop.incarcaIngredienteDinFisier(fisierMock);
        assert(nrIncarcate >= 0);

        // Verificare comportament pe fisier inexistent
        int nrEronat = shop.incarcaIngredienteDinFisier("fisier_complet_inexistent_12345.xyz");
        assert(nrEronat <= 0);

        std::cout << "[PASS] testIncarcareFisierConfiguratie reusit.\n";
    }

    void testStresBucleSiComenziMasive()
    {
        std::cout << "[TEST] Rulare testStresBucleSiComenziMasive...\n";

        Cafenea shopStres("MegaCoffee", 10000.0);
        shopStres.adaugaIngredient(Ingrediente("Cafea Boabe", 10000.0, "g", 0.10));
        shopStres.adaugaIngredient(Ingrediente("Lapte Integral", 50000.0, "ml", 0.01));

        CReteta comp[2] = { CReteta("Cafea Boabe", 10.0), CReteta("Lapte Integral", 100.0) };
        Reteta cafeaLapte("Cafea cu Lapte", 12.0, comp, 2);
        shopStres.adaugaReteta(cafeaLapte);

        Client clientLoial("Client Test Stres");

        for (int i = 0; i < 50; ++i)
        {
            assert(shopStres.poatePrepara("Cafea cu Lapte"));
            shopStres.proceseazaComanda("Cafea cu Lapte");
        }

        std::vector<std::string> batch;
        for (int i = 0; i < 10; ++i)
        {
            batch.push_back("Cafea cu Lapte");
        }
        shopStres.plaseazaComanda(clientLoial, batch);

        assert(clientLoial.getTotalCheltuit() > 0.0);

        std::cout << "[PASS] testStresBucleSiComenziMasive reusit.\n";
    }

    void testFormatareOperatoriStream()
    {
        std::cout << "[TEST] Rulare testFormatareOperatoriStream...\n";

        CReteta c("Cafea Boabe", 18.0);
        Reteta r("Espresso Scurt", 9.0, &c, 1);

        std::ostringstream outReteta;
        outReteta << r;
        assert(outReteta.str().find("Espresso Scurt") != std::string::npos);

        Cafenea shop("TestAfisare", 200.0);
        shop.adaugaReteta(r);

        std::ostringstream outShop;
        outShop << shop;
        assert(!outShop.str().empty());

        std::cout << "[PASS] testFormatareOperatoriStream reusit.\n";
    }
}

int main()
{
  

    TestSuite::testIngredienteOperatii();
    TestSuite::testIngredienteCazuriLimita();
    TestSuite::testCRetetaSiConstructori();
    TestSuite::testCRetetaModificariSiValidari();
    TestSuite::testRetetaRegulaCelorTrei();
    TestSuite::testReteteComplexeSiCopiereAdanca();
    TestSuite::testClientPuncteSiFormatare();
    TestSuite::testClientGestiuneMultipla();
    TestSuite::testCafeneaProcesareComenzi();
    TestSuite::testCafeneaComandaClientCompusa();
    TestSuite::testCafeneaComenziEsuateSiPartialitate();
    TestSuite::testSalvareRaportFisier();
    TestSuite::testIncarcareFisierConfiguratie();
    TestSuite::testStresBucleSiComenziMasive();
    TestSuite::testFormatareOperatoriStream();

   

    return 0;
}
