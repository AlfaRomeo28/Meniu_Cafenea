#include <iostream>
#include <cassert>
#include <cmath>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <cstdio>

#include "Cafenea.hpp"
#include "Client.hpp"
#include "Comanda.hpp"
#include "CReteta.hpp"
#include "Ingrediente.hpp"
#include "IstoricVanzari.hpp"
#include "LinieComanda.hpp"
#include "Reteta.hpp"

namespace TestSuite
{
    static bool aproapeEgal(double a, double b, double eps = 0.001)
    {
        return std::fabs(a - b) < eps;
    }

    void test01_IngredienteConstructoriSiGetteri()
    {
        std::cout << "[TEST 01] Ingrediente constructori si getteri...\n";
        Ingrediente cafea("Cafea Boabe", 500.0, "g", 0.12);
        assert(cafea.getdenumire() == "Cafea Boabe");
        assert(aproapeEgal(cafea.getcantitateDisponibila(), 500.0));
        assert(cafea.getunitateMasura() == "g");
        assert(aproapeEgal(cafea.getpretUnitate(), 0.12));
    }

    void test02_IngredienteConsumSiStoc()
    {
        std::cout << "[TEST 02] Ingrediente operatii stoc si consum...\n";
        Ingrediente lapte("Lapte", 1000.0, "ml", 0.01);
        lapte.adaugaStoc(500.0);
        assert(aproapeEgal(lapte.getcantitateDisponibila(), 1500.0));

        bool consumReusit = lapte.consuma(300.0);
        assert(consumReusit);
        assert(aproapeEgal(lapte.getcantitateDisponibila(), 1200.0));

        bool consumExcesiv = lapte.consuma(5000.0);
        assert(!consumExcesiv);
        assert(aproapeEgal(lapte.getcantitateDisponibila(), 1200.0));
    }

    void test03_IngredienteConsumLimitaExacta()
    {
        std::cout << "[TEST 03] Ingrediente consum limita exacta...\n";
        Ingrediente zahar("Zahar", 100.0, "g", 0.05);
        bool consumTot = zahar.consuma(100.0);
        assert(consumTot);
        assert(aproapeEgal(zahar.getcantitateDisponibila(), 0.0));

        bool consumPeZero = zahar.consuma(0.01);
        assert(!consumPeZero);
    }

    void test04_IngredienteAfisareStream()
    {
        std::cout << "[TEST 04] Ingrediente afisare stream...\n";
        Ingrediente vanilie("Sirop Vanilie", 250.0, "ml", 0.08);
        std::ostringstream ss;
        ss << vanilie;
        assert(ss.str().find("Sirop Vanilie") != std::string::npos);
        assert(!ss.str().empty());
    }

    void test05_CRetetaConstructoriSiGetteri()
    {
        std::cout << "[TEST 05] CReteta constructori si getteri...\n";
        CReteta cr("Lapte Integral", 150.0);
        assert(cr.getnume() == "Lapte Integral");
        assert(aproapeEgal(cr.getcantitate(), 150.0));
    }

    void test06_CRetetaCopiereSiAtribuire()
    {
        std::cout << "[TEST 06] CReteta copiere si atribuire...\n";
        CReteta compOriginal("Apa Fierbinte", 120.0);
        CReteta compCopie = compOriginal;
        assert(compCopie.getnume() == "Apa Fierbinte");
        assert(aproapeEgal(compCopie.getcantitate(), 120.0));

        CReteta compAtribuit;
        compAtribuit = compOriginal;
        assert(compAtribuit.getnume() == "Apa Fierbinte");
        assert(aproapeEgal(compAtribuit.getcantitate(), 120.0));
    }

    void test07_CRetetaAfisareStream()
    {
        std::cout << "[TEST 07] CReteta afisare stream...\n";
        CReteta comp("Ciocolata", 35.0);
        std::ostringstream ss;
        ss << comp;
        assert(ss.str().find("Ciocolata") != std::string::npos);
    }

    void test08_RetetaConstructoriSiGetteri()
    {
        std::cout << "[TEST 08] Reteta constructori si inspectare componente...\n";
        const CReteta comp[2] = { CReteta("Cafea Boabe", 18.0), CReteta("Lapte Integral", 150.0) };
        Reteta cappuccino("Cappuccino", 16.0, comp, 2);

        assert(cappuccino.getDenumire() == "Cappuccino");
        assert(aproapeEgal(cappuccino.getPretVanzare(), 16.0));
        assert(cappuccino.getNumarComponente() == 2);
        assert(cappuccino.getComponente() != nullptr);
        assert(cappuccino.getComponente()[0].getnume() == "Cafea Boabe");
    }

    void test09_RetetaRegulaCelorTreiCopiereAdanca()
    {
        std::cout << "[TEST 09] Reteta regula celor 3 si deep copy...\n";
        const CReteta comp[1] = { CReteta("Cafea Boabe", 18.0) };
        Reteta original("Espresso", 10.0, comp, 1);

        {
            Reteta copie = original;
            assert(copie.getNumarComponente() == 1);
            assert(copie.getDenumire() == "Espresso");
            assert(aproapeEgal(copie.getPretVanzare(), original.getPretVanzare()));
        }

        Reteta atribuita;
        atribuita = original;
        assert(atribuita.getNumarComponente() == 1);
        assert(atribuita.getDenumire() == "Espresso");
        assert(aproapeEgal(atribuita.getPretVanzare(), original.getPretVanzare()));

        const Reteta* ptrAtribuita = &atribuita;
        atribuita = *ptrAtribuita;
        assert(atribuita.getNumarComponente() == 1);
    }

    void test10_RetetaCostProductie()
    {
        std::cout << "[TEST 10] Reteta calcul cost productie...\n";
        const CReteta comp[2] = { CReteta("Cafea Boabe", 10.0), CReteta("Lapte", 100.0) };
        Reteta cafeaLapte("Cafea cu Lapte", 12.0, comp, 2);

        const Ingrediente stocMagazie[2] = {
            Ingrediente("Cafea Boabe", 100.0, "g", 0.10),
            Ingrediente("Lapte", 500.0, "ml", 0.02)
        };

        double cost = cafeaLapte.calculeazaCostProductie(stocMagazie, 2);
        assert(aproapeEgal(cost, 3.0));
    }

    void test11_RetetaAfisareStream()
    {
        std::cout << "[TEST 11] Reteta operator<< ...\n";
        const CReteta comp[1] = { CReteta("Apa", 200.0) };
        Reteta ceai("Ceai", 8.0, comp, 1);
        std::ostringstream ss;
        ss << ceai;
        assert(ss.str().find("Ceai") != std::string::npos);
    }

    void test12_LinieComandaConstructoriSiTotal()
    {
        std::cout << "[TEST 12] LinieComanda constructori si total...\n";
        LinieComanda linie("Espresso Dublu", 2, 12.5);
        assert(linie.getDenumire() == "Espresso Dublu");
        assert(linie.getCantitate() == 2);
        assert(aproapeEgal(linie.getPretUnitar(), 12.5));
        assert(aproapeEgal(linie.getTotal(), 25.0));
    }

    void test13_LinieComandaAdaugaCantitate()
    {
        std::cout << "[TEST 13] LinieComanda adaugaCantitate...\n";
        LinieComanda linie("Croissant", 1, 8.0);
        linie.adaugaCantitate(3);
        assert(linie.getCantitate() == 4);
        assert(aproapeEgal(linie.getTotal(), 32.0));
    }

    void test14_LinieComandaAfisareStream()
    {
        std::cout << "[TEST 14] LinieComanda operator<< ...\n";
        LinieComanda linie("Latte", 2, 15.0);
        std::ostringstream ss;
        ss << linie;
        assert(ss.str().find("Latte") != std::string::npos);
    }

    void test15_ComandaAdaugareLiniiSiCalculSubtotal()
    {
        std::cout << "[TEST 15] Comanda adaugare linii si subtotal...\n";
        Comanda cmd(101, "Mihai Eminescu");
        assert(cmd.getId() == 101);
        assert(cmd.getNumeClient() == "Mihai Eminescu");
        assert(cmd.getNumarProduse() == 0);

        cmd.adaugaLinie("Espresso", 10.0, 2);
        cmd.adaugaLinie("Cappuccino", 15.0, 1);

        assert(cmd.getNumarProduse() == 3);
        assert(aproapeEgal(cmd.getSubtotal(), 35.0));
        assert(aproapeEgal(cmd.getTotal(), 35.0));
    }

    void test16_ComandaCumulareLiniiIdentice()
    {
        std::cout << "[TEST 16] Comanda cumulare produse pe aceeasi linie...\n";
        Comanda cmd(102, "Ion Creanga");
        cmd.adaugaLinie("Espresso", 10.0, 1);
        cmd.adaugaLinie("Espresso", 10.0, 2);

        assert(cmd.getLinii().size() == 1);
        assert(cmd.getNumarProduse() == 3);
        assert(aproapeEgal(cmd.getTotal(), 30.0));
    }

    void test17_ComandaAplicareReducere()
    {
        std::cout << "[TEST 17] Comanda aplicare reducere procentuala...\n";
        Comanda cmd(103, "George Enescu");
        cmd.adaugaLinie("Vanilla Latte", 20.0, 2);

        cmd.aplicaReducere(10.0);
        assert(aproapeEgal(cmd.getReducere(), 10.0));
        assert(aproapeEgal(cmd.getValoareReducere(), 4.0));
        assert(aproapeEgal(cmd.getTotal(), 36.0));
    }

    void test18_ComandaAfisareBonStream()
    {
        std::cout << "[TEST 18] Comanda operator<< format bon...\n";
        Comanda cmd(104, "Aurel Vlaicu");
        cmd.adaugaLinie("Ceai Cald", 10.0, 1);
        std::ostringstream ss;
        ss << cmd;
        assert(ss.str().find("Aurel Vlaicu") != std::string::npos);
        assert(ss.str().find("Ceai Cald") != std::string::npos);
    }

    void test19_ClientConstructoriSiDateInitiale()
    {
        std::cout << "[TEST 19] Client constructori si stare initiala...\n";
        Client c1("Mircea Eliade");
        assert(c1.getNume() == "Mircea Eliade");
        assert(aproapeEgal(c1.getPuncte(), 0.0));
        assert(aproapeEgal(c1.getTotalCheltuit(), 0.0));
        assert(c1.getNumarComenzi() == 0);
        assert(c1.getNivel() == "Standard");
        assert(aproapeEgal(c1.getReducere(), 0.0));

        Client c2("Constantin Brancusi", 150.0, 1500.0, 12);
        assert(c2.getPuncte() > 0.0);
        assert(c2.getNumarComenzi() == 12);
    }

    void test20_ClientInregistrareComandaSiPuncte()
    {
        std::cout << "[TEST 20] Client inregistrare tranzactie...\n";
        Client c("Nichita Stanescu");
        c.inregistreazaComanda(100.0);
        assert(aproapeEgal(c.getTotalCheltuit(), 100.0));
        assert(c.getNumarComenzi() == 1);
        assert(c.getPuncte() > 0.0);
    }

    void test21_ClientAvansareNivelSiReducere()
    {
        std::cout << "[TEST 21] Client avansare nivel Argint si Aur...\n";
        Client c("Ana Aslan");
        c.inregistreazaComanda(300.0);
        c.inregistreazaComanda(800.0);
        double red = c.getReducere();
        assert(red == 0.0 || red == 5.0 || red == 10.0);
        std::string nivel = c.getNivel();
        assert(nivel == "Standard" || nivel == "Argint" || nivel == "Aur");
    }

    void test22_ClientAfisareStream()
    {
        std::cout << "[TEST 22] Client operator<< stream...\n";
        Client c("Tudor Arghezi");
        std::ostringstream ss;
        ss << c;
        assert(ss.str().find("Tudor Arghezi") != std::string::npos);
    }

    void test23_IstoricVanzariInregistrareSiStatistici()
    {
        std::cout << "[TEST 23] IstoricVanzari cumulare comenzi...\n";
        IstoricVanzari ist("Bobis_Bob_Caffe");
        assert(ist.getNumarComenzi() == 0);
        assert(aproapeEgal(ist.totalIncasari(), 0.0));

        Comanda cmd1(1, "Client A");
        cmd1.adaugaLinie("Espresso", 10.0, 2);
        ist.adaugaComanda(cmd1);

        Comanda cmd2(2, "Client A");
        cmd2.adaugaLinie("Cappuccino", 15.0, 1);
        ist.adaugaComanda(cmd2);

        assert(ist.getNumarComenzi() == 2);
        assert(aproapeEgal(ist.totalIncasari(), 35.0));
        assert(ist.numarComenziClient("Client A") == 2);
        assert(aproapeEgal(ist.totalClient("Client A"), 35.0));
        assert(aproapeEgal(ist.valoareMedieComanda(), 17.5));
    }

    void test24_IstoricVanzariGasesteComandaSiTop()
    {
        std::cout << "[TEST 24] IstoricVanzari regasire comenzi si clasament...\n";
        IstoricVanzari ist("TestShop");
        Comanda cmd(10, "Radu Tudoran");
        cmd.adaugaLinie("Vanilla Latte", 20.0, 3);
        ist.adaugaComanda(cmd);

        const Comanda* gasita = ist.gasesteComanda(10);
        assert(gasita != nullptr);
        assert(gasita->getId() == 10);

        const Comanda* inexistent = ist.gasesteComanda(999);
        assert(inexistent == nullptr);

        std::vector<std::pair<std::string, int> > top = ist.topProduse(5);
        assert(!top.empty());
        assert(top[0].first == "Vanilla Latte");
        assert(top[0].second == 3);
    }

    void test25_IstoricVanzariPersistentaFisier()
    {
        std::cout << "[TEST 25] IstoricVanzari export in fisier...\n";
        IstoricVanzari ist("ExportShop");
        Comanda cmd(1, "Test Persistenta");
        cmd.adaugaLinie("Espresso", 10.0, 1);
        ist.adaugaComanda(cmd);

        const std::string fisier = "test_istoric_temp.txt";
        bool salvat = ist.salveazaInFisier(fisier);
        assert(salvat);

        std::ifstream fin(fisier.c_str());
        assert(fin.is_open());
        fin.close();
        std::remove(fisier.c_str());
    }

    void test26_CafeneaIncarcareIngredienteSiStoc()
    {
        std::cout << "[TEST 26] Cafenea incarcare ingrediente si stoc...\n";
        Cafenea shop("Cafeneaua Mea", 1000.0);
        shop.adaugaIngredient(Ingrediente("Cafea Boabe", 300.0, "g", 0.15));
        shop.adaugaIngredient(Ingrediente("Lapte Integral", 1000.0, "ml", 0.01));

        bool reaprovizionat = shop.reaprovizioneaza("Cafea Boabe", 200.0);
        assert(reaprovizionat);

        bool reaprovizionatInexistent = shop.reaprovizioneaza("ScortisoaraInexistenta", 100.0);
        assert(!reaprovizionatInexistent);
    }

    void test27_CafeneaPoatePreparaSiCatalogRetete()
    {
        std::cout << "[TEST 27] Cafenea disponibilitate reteta vs stoc...\n";
        Cafenea shop("CatalogShop", 500.0);
        shop.adaugaIngredient(Ingrediente("Cafea Boabe", 36.0, "g", 0.15));

        const CReteta compEsp[1] = { CReteta("Cafea Boabe", 18.0) };
        shop.adaugaReteta(Reteta("Espresso", 10.0, compEsp, 1));

        assert(shop.poatePrepara("Espresso"));
        assert(!shop.poatePrepara("ProdusFantom"));
    }

    void test28_CafeneaFluxProceseazaComandaDirecta()
    {
        std::cout << "[TEST 28] Cafenea comanda directa rapida...\n";
        Cafenea shop("FastCoffee", 500.0);
        shop.adaugaIngredient(Ingrediente("Cafea Boabe", 36.0, "g", 0.15));

        const CReteta compEsp[1] = { CReteta("Cafea Boabe", 18.0) };
        shop.adaugaReteta(Reteta("Espresso", 10.0, compEsp, 1));

        bool cmd1 = shop.proceseazaComanda("Espresso");
        assert(cmd1);

        bool cmd2 = shop.proceseazaComanda("Espresso");
        assert(cmd2);

        bool cmd3 = shop.proceseazaComanda("Espresso");
        assert(!cmd3);
        assert(!shop.poatePrepara("Espresso"));
    }

    void test29_CafeneaPlaseazaComandaClientCompusa()
    {
        std::cout << "[TEST 29] Cafenea plaseaza comanda multipla client...\n";
        Cafenea shop("OrderShop", 1000.0);
        shop.adaugaIngredient(Ingrediente("Cafea Boabe", 500.0, "g", 0.15));
        shop.adaugaIngredient(Ingrediente("Lapte Integral", 1000.0, "ml", 0.01));

        const CReteta compEsp[1] = { CReteta("Cafea Boabe", 18.0) };
        shop.adaugaReteta(Reteta("Espresso", 10.0, compEsp, 1));

        const CReteta compCap[2] = { CReteta("Cafea Boabe", 18.0), CReteta("Lapte Integral", 150.0) };
        shop.adaugaReteta(Reteta("Cappuccino", 16.0, compCap, 2));

        Client client("Barbu Stefanescu Delavrancea");
        std::vector<std::string> lista;
        lista.push_back("Espresso");
        lista.push_back("Cappuccino");

        bool plasata = shop.plaseazaComanda(client, lista);
        assert(plasata);
        assert(client.getNumarComenzi() == 1);
        assert(client.getTotalCheltuit() > 0.0);
        assert(shop.getIstoric().getNumarComenzi() == 1);
    }

    void test30_CafeneaSalvareRaportSiAfisare()
    {
        std::cout << "[TEST 30] Cafenea rapoarte, afisare si fisiere...\n";
        Cafenea shop("ReportShop", 1000.0);
        shop.adaugaIngredient(Ingrediente("Cafea Boabe", 200.0, "g", 0.15));

        const CReteta c[1] = { CReteta("Cafea Boabe", 18.0) };
        shop.adaugaReteta(Reteta("Espresso", 10.0, c, 1));
        bool okCmd = shop.proceseazaComanda("Espresso");
        assert(okCmd);

        shop.afiseazaRaportProfitabilitate();
        shop.afiseazaIstoric();

        std::ostringstream ss;
        ss << shop;
        assert(ss.str().find("ReportShop") != std::string::npos);

        const std::string caleRaport = "test_raport_final.txt";
        bool salvat = shop.salveazaRaportVanzari(caleRaport);
        assert(salvat);

        std::ifstream fVerificare(caleRaport.c_str());
        assert(fVerificare.is_open());
        fVerificare.close();
        std::remove(caleRaport.c_str());
    }

    void test31_IngredienteConsumFinSiReumplereRepetata()
    {
        std::cout << "[TEST 31] Ingrediente consum fractional fin si reumpleri...\n";
        Ingrediente scortisoara("Pudra Scortisoara", 10.0, "g", 0.25);

        for (int pas = 0; pas < 50; ++pas)
        {
            bool ok = scortisoara.consuma(0.1);
            assert(ok);
        }
        assert(aproapeEgal(scortisoara.getcantitateDisponibila(), 5.0, 0.01));

        for (int adaugare = 0; adaugare < 10; ++adaugare)
        {
            scortisoara.adaugaStoc(0.5);
        }
        assert(aproapeEgal(scortisoara.getcantitateDisponibila(), 10.0, 0.01));
    }

    void test32_RetetaComplexaMultiComponente()
    {
        std::cout << "[TEST 32] Reteta cu 5 componente distincte...\n";
        const CReteta compMochaDeluxe[5] = {
            CReteta("Cafea Boabe", 20.0),
            CReteta("Lapte Integral", 160.0),
            CReteta("Sirop Ciocolata", 25.0),
            CReteta("Frisca Lichida", 30.0),
            CReteta("Pudra Cacao", 5.0)
        };

        Reteta mocha("Mocha Deluxe", 24.5, compMochaDeluxe, 5);
        assert(mocha.getDenumire() == "Mocha Deluxe");
        assert(mocha.getNumarComponente() == 5);
        assert(aproapeEgal(mocha.getPretVanzare(), 24.5));

        const CReteta* componenteExtrase = mocha.getComponente();
        assert(componenteExtrase != nullptr);
        assert(componenteExtrase[2].getnume() == "Sirop Ciocolata");
        assert(aproapeEgal(componenteExtrase[2].getcantitate(), 25.0));
    }

    void test33_LinieComandaOperatiiSuccesiveSiPrecizie()
    {
        std::cout << "[TEST 33] LinieComanda cumulare repetata si calcule...\n";
        LinieComanda linieProdus("Frappe Caramel", 1, 14.25);
        assert(aproapeEgal(linieProdus.getTotal(), 14.25));

        linieProdus.adaugaCantitate(2);
        assert(linieProdus.getCantitate() == 3);
        assert(aproapeEgal(linieProdus.getTotal(), 42.75));

        linieProdus.adaugaCantitate(7);
        assert(linieProdus.getCantitate() == 10);
        assert(aproapeEgal(linieProdus.getTotal(), 142.50));
    }

    void test34_ComandaReduceriSiValidariLinii()
    {
        std::cout << "[TEST 34] Comanda calcul reduceri maxime si zero...\n";
        Comanda cmdZero(200, "Client Test Reduceri");
        cmdZero.adaugaLinie("Espresso", 10.0, 1);
        cmdZero.aplicaReducere(0.0);
        assert(aproapeEgal(cmdZero.getValoareReducere(), 0.0));
        assert(aproapeEgal(cmdZero.getTotal(), 10.0));

        cmdZero.aplicaReducere(25.0);
        assert(aproapeEgal(cmdZero.getReducere(), 25.0));
        assert(aproapeEgal(cmdZero.getValoareReducere(), 2.5));
        assert(aproapeEgal(cmdZero.getTotal(), 7.5));
    }

    void test35_ClientEvolutieComenziSiTranzactiiMultiple()
    {
        std::cout << "[TEST 35] Client evolutie pe parcursul mai multor comenzi...\n";
        Client clientFidel("Spiru Haret");
        assert(clientFidel.getNumarComenzi() == 0);

        for (int i = 1; i <= 5; ++i)
        {
            clientFidel.inregistreazaComanda(50.0);
            assert(clientFidel.getNumarComenzi() == i);
        }
        assert(aproapeEgal(clientFidel.getTotalCheltuit(), 250.0));
        assert(clientFidel.getPuncte() > 0.0);
    }

    void test36_IstoricVanzariFiltrareSiTopExtins()
    {
        std::cout << "[TEST 36] IstoricVanzari analize de vanzare si top extins...\n";
        IstoricVanzari ist("Statistici_Cafenea");

        Comanda c1(1, "Client1");
        c1.adaugaLinie("Ceai Verde", 8.0, 4);
        c1.adaugaLinie("Briosa", 12.0, 2);
        ist.adaugaComanda(c1);

        Comanda c2(2, "Client2");
        c2.adaugaLinie("Ceai Verde", 8.0, 6);
        c2.adaugaLinie("Croissant", 10.0, 5);
        ist.adaugaComanda(c2);

        assert(ist.getNumarComenzi() == 2);
        std::vector<std::pair<std::string, int> > top = ist.topProduse(3);
        assert(!top.empty());
        assert(top[0].first == "Ceai Verde");
        assert(top[0].second == 10);
    }

    void test37_CafeneaEpuizareResurseSiBlocarePreparare()
    {
        std::cout << "[TEST 37] Cafenea epuizare precisa pe ingrediente comune...\n";
        Cafenea shopResurse("ResurseTest", 800.0);
        shopResurse.adaugaIngredient(Ingrediente("Cafea Boabe", 30.0, "g", 0.15));
        shopResurse.adaugaIngredient(Ingrediente("Lapte Integral", 150.0, "ml", 0.01));

        const CReteta cEsp[1] = { CReteta("Cafea Boabe", 18.0) };
        shopResurse.adaugaReteta(Reteta("Espresso", 9.0, cEsp, 1));

        const CReteta cCap[2] = { CReteta("Cafea Boabe", 18.0), CReteta("Lapte Integral", 150.0) };
        shopResurse.adaugaReteta(Reteta("Cappuccino", 15.0, cCap, 2));

        assert(shopResurse.poatePrepara("Cappuccino"));
        bool servitCap = shopResurse.proceseazaComanda("Cappuccino");
        assert(servitCap);

        assert(!shopResurse.poatePrepara("Cappuccino"));
        assert(!shopResurse.poatePrepara("Espresso"));

        bool comandaEsuata = shopResurse.proceseazaComanda("Espresso");
        assert(!comandaEsuata);
    }

    void test38_CafeneaGestionareMultipliClientiSimultan()
    {
        std::cout << "[TEST 38] Cafenea comenzi simultane pentru mai multi clienti...\n";
        Cafenea centralShop("CentralCoffee", 2500.0);
        centralShop.adaugaIngredient(Ingrediente("Cafea Boabe", 2000.0, "g", 0.10));
        centralShop.adaugaIngredient(Ingrediente("Lapte Integral", 5000.0, "ml", 0.01));

        const CReteta comp[2] = { CReteta("Cafea Boabe", 18.0), CReteta("Lapte Integral", 120.0) };
        centralShop.adaugaReteta(Reteta("Flat White", 15.0, comp, 2));

        Client client1("Alexandru Odobescu");
        Client client2("Camil Petrescu");

        std::vector<std::string> listaC1;
        listaC1.push_back("Flat White");
        listaC1.push_back("Flat White");

        std::vector<std::string> listaC2;
        listaC2.push_back("Flat White");

        bool okC1 = centralShop.plaseazaComanda(client1, listaC1);
        bool okC2 = centralShop.plaseazaComanda(client2, listaC2);
        assert(okC1);
        assert(okC2);

        assert(client1.getNumarComenzi() == 1);
        assert(client2.getNumarComenzi() == 1);
        assert(centralShop.getIstoric().getNumarComenzi() == 2);
    }

    void test39_CafeneaIncarcareFisierFormatSimulat()
    {
        std::cout << "[TEST 39] Cafenea import stoc din fisier extern simulat...\n";
        const std::string caleFisierTest = "stoc_mock_test.txt";
        std::ofstream fout(caleFisierTest.c_str());
        fout << "Cafea_Arabica 500.0 g 0.20\n";
        fout << "Lapte_Ovaz 1000.0 ml 0.02\n";
        fout << "Sirop_Alune 250.0 ml 0.06\n";
        fout.close();

        Cafenea testImportShop("ImportShop", 1200.0);
        int nrLiniiIncarcate = testImportShop.incarcaIngredienteDinFisier(caleFisierTest);
        assert(nrLiniiIncarcate >= 0);

        std::remove(caleFisierTest.c_str());
    }

    void test40_CafeneaIntegritateStareSiIstoricComplet()
    {
        std::cout << "[TEST 40] Cafenea validare stare globala si istoric...\n";
        Cafenea finalShop("FinalAuditShop", 1000.0);
        finalShop.adaugaIngredient(Ingrediente("Cafea Boabe", 300.0, "g", 0.10));

        const CReteta comp[1] = { CReteta("Cafea Boabe", 15.0) };
        finalShop.adaugaReteta(Reteta("Ristretto", 8.0, comp, 1));

        for (int k = 0; k < 5; ++k)
        {
            bool okRistretto = finalShop.proceseazaComanda("Ristretto");
            assert(okRistretto);
        }

        const IstoricVanzari& istoricFinal = finalShop.getIstoric();
        assert(istoricFinal.getNumarComenzi() == 5);
        assert(aproapeEgal(istoricFinal.totalIncasari(), 40.0));
        assert(aproapeEgal(istoricFinal.valoareMedieComanda(), 8.0));
    }

    void test41_IngredienteConsumPanaLaEpuizareTotala()
    {
        std::cout << "[TEST 41] Ingrediente cicluri repetate de golire si umplere...\n";
        Ingrediente cardamon("Cardamon Macinat", 50.0, "g", 0.40);
        assert(cardamon.getdenumire() == "Cardamon Macinat");

        for (int iteratie = 0; iteratie < 10; ++iteratie)
        {
            assert(aproapeEgal(cardamon.getcantitateDisponibila(), 50.0));
            bool okConsum = cardamon.consuma(50.0);
            assert(okConsum);
            assert(aproapeEgal(cardamon.getcantitateDisponibila(), 0.0));
            bool okConsumPeste = cardamon.consuma(1.0);
            assert(!okConsumPeste);

            cardamon.adaugaStoc(50.0);
        }
        assert(aproapeEgal(cardamon.getcantitateDisponibila(), 50.0));
    }

    void test42_CRetetaStresVectorSiComparatii()
    {
        std::cout << "[TEST 42] CReteta manipulare colectii mari...\n";
        std::vector<CReteta> colectieComponente;
        for (int i = 1; i <= 20; ++i)
        {
            std::ostringstream ssNume;
            ssNume << "IngredientCompus_" << i;
            colectieComponente.push_back(CReteta(ssNume.str(), static_cast<double>(i * 5)));
        }

        assert(colectieComponente.size() == 20);
        for (std::size_t idx = 0; idx < colectieComponente.size(); ++idx)
        {
            assert(colectieComponente[idx].getcantitate() > 0.0);
            std::ostringstream ssOut;
            ssOut << colectieComponente[idx];
            assert(!ssOut.str().empty());
        }
    }

    void test43_RetetaMultiplaCuSapteIngrediente()
    {
        std::cout << "[TEST 43] Reteta cu 7 componente si cost de productie...\n";
        const CReteta compSpecial[7] = {
            CReteta("Cafea Boabe", 22.0),
            CReteta("Lapte Soia", 180.0),
            CReteta("Sirop Fistic", 20.0),
            CReteta("Sirop Vanilie", 15.0),
            CReteta("Pudra Matcha", 5.0),
            CReteta("Frisca Vegana", 40.0),
            CReteta("Topping Ciocolata", 10.0)
        };

        Reteta monsterCoffee("Super Monster Blend", 32.0, compSpecial, 7);
        assert(monsterCoffee.getNumarComponente() == 7);
        assert(monsterCoffee.getDenumire() == "Super Monster Blend");
        assert(aproapeEgal(monsterCoffee.getPretVanzare(), 32.0));

        const Ingrediente magazie[7] = {
            Ingrediente("Cafea Boabe", 1000.0, "g", 0.15),
            Ingrediente("Lapte Soia", 2000.0, "ml", 0.02),
            Ingrediente("Sirop Fistic", 500.0, "ml", 0.08),
            Ingrediente("Sirop Vanilie", 500.0, "ml", 0.05),
            Ingrediente("Pudra Matcha", 200.0, "g", 0.30),
            Ingrediente("Frisca Vegana", 800.0, "g", 0.04),
            Ingrediente("Topping Ciocolata", 400.0, "g", 0.03)
        };

        double costProd = monsterCoffee.calculeazaCostProductie(magazie, 7);
        assert(costProd > 0.0);
        assert(costProd < monsterCoffee.getPretVanzare());
    }

    void test44_RetetaAutoAtribuireSiSecventeCopiere()
    {
        std::cout << "[TEST 44] Reteta lanturi de copiere si auto-atribuire multipla...\n";
        const CReteta c[2] = { CReteta("Boabe", 10.0), CReteta("Apa", 100.0) };
        Reteta r1("Americano Mare", 12.0, c, 2);
        Reteta r2("Dummy", 1.0, nullptr, 0);
        Reteta r3("Dummy2", 2.0, nullptr, 0);

        r3 = r2 = r1;
        assert(r2.getDenumire() == "Americano Mare");
        assert(r3.getDenumire() == "Americano Mare");
        assert(r2.getNumarComponente() == 2);
        assert(r3.getNumarComponente() == 2);

        const Reteta* ptrR3 = &r3;
        r3 = *ptrR3;
        assert(r3.getDenumire() == "Americano Mare");
        assert(r3.getNumarComponente() == 2);
    }

    void test45_LinieComandaCalculFinanciarValoriMari()
    {
        std::cout << "[TEST 45] LinieComanda volume comerciale mari...\n";
        LinieComanda linieEnGros("Pachet Cafea Boabe 1kg", 50, 85.50);
        assert(linieEnGros.getCantitate() == 50);
        assert(aproapeEgal(linieEnGros.getPretUnitar(), 85.50));
        assert(aproapeEgal(linieEnGros.getTotal(), 4275.0));

        linieEnGros.adaugaCantitate(50);
        assert(linieEnGros.getCantitate() == 100);
        assert(aproapeEgal(linieEnGros.getTotal(), 8550.0));
    }

    void test46_ComandaBonMareCuMulteProduseSiReducere()
    {
        std::cout << "[TEST 46] Comanda bon de restaurant cu multe linii...\n";
        Comanda comandaMasa(500, "Masa Protocol");

        for (int p = 1; p <= 15; ++p)
        {
            std::ostringstream prodStream;
            prodStream << "Bautura_Protocol_" << p;
            comandaMasa.adaugaLinie(prodStream.str(), 10.0 + p, 2);
        }

        assert(comandaMasa.getLinii().size() == 15);
        assert(comandaMasa.getNumarProduse() == 30);
        assert(comandaMasa.getSubtotal() > 0.0);

        comandaMasa.aplicaReducere(15.0);
        assert(aproapeEgal(comandaMasa.getReducere(), 15.0));
        double redAsteptata = comandaMasa.getSubtotal() * 0.15;
        assert(aproapeEgal(comandaMasa.getValoareReducere(), redAsteptata));
        assert(aproapeEgal(comandaMasa.getTotal(), comandaMasa.getSubtotal() - redAsteptata));
    }

    void test47_ClientTranzactiiSuccesiveSiPuncteAcumulate()
    {
        std::cout << "[TEST 47] Client acumulare continua pe 25 de tranzactii...\n";
        Client fidel("Ioan Slavici");
        assert(fidel.getNume() == "Ioan Slavici");

        double totalCumulat = 0.0;
        for (int comandaIdx = 1; comandaIdx <= 25; ++comandaIdx)
        {
            double suma = 20.0 + static_cast<double>(comandaIdx * 2);
            fidel.inregistreazaComanda(suma);
            totalCumulat += suma;
            assert(fidel.getNumarComenzi() == comandaIdx);
        }

        assert(aproapeEgal(fidel.getTotalCheltuit(), totalCumulat));
        assert(fidel.getPuncte() > 0.0);
        std::string nivelFinal = fidel.getNivel();
        assert(nivelFinal == "Standard" || nivelFinal == "Argint" || nivelFinal == "Aur");
    }

    void test48_IstoricVanzariVerificareStatisticiComplet()
    {
        std::cout << "[TEST 48] IstoricVanzari validari matematice pe incasari...\n";
        IstoricVanzari istoricAudit("Audit_Cafenea");

        double sumaAsteptataIncasari = 0.0;
        double sumaAsteptataReduceri = 0.0;

        for (int idCmd = 1; idCmd <= 10; ++idCmd)
        {
            Comanda cmd(idCmd, "Client Test");
            cmd.adaugaLinie("Espresso", 10.0, 1);
            if (idCmd % 2 == 0)
            {
                cmd.aplicaReducere(10.0);
                sumaAsteptataReduceri += 1.0;
                sumaAsteptataIncasari += 9.0;
            }
            else
            {
                sumaAsteptataIncasari += 10.0;
            }
            istoricAudit.adaugaComanda(cmd);
        }

        assert(istoricAudit.getNumarComenzi() == 10);
        assert(aproapeEgal(istoricAudit.totalIncasari(), sumaAsteptataIncasari));
        assert(aproapeEgal(istoricAudit.totalReduceri(), sumaAsteptataReduceri));
        assert(aproapeEgal(istoricAudit.valoareMedieComanda(), sumaAsteptataIncasari / 10.0));
    }

    void test49_CafeneaStresSuteDeComenziSiReaprovizionari()
    {
        std::cout << "[TEST 49] Cafenea rulaj masiv: 100 comenzi cu reaprovizionare...\n";
        Cafenea highTrafficShop("MegaDriveCoffee", 10000.0);

        highTrafficShop.adaugaIngredient(Ingrediente("Cafea Boabe", 1800.0, "g", 0.10));
        const CReteta comp[1] = { CReteta("Cafea Boabe", 18.0) };
        highTrafficShop.adaugaReteta(Reteta("Espresso", 10.0, comp, 1));

        for (int i = 0; i < 100; ++i)
        {
            assert(highTrafficShop.poatePrepara("Espresso"));
            bool servit = highTrafficShop.proceseazaComanda("Espresso");
            assert(servit);
        }

        assert(!highTrafficShop.poatePrepara("Espresso"));
        bool servitPeste = highTrafficShop.proceseazaComanda("Espresso");
        assert(!servitPeste);

        bool aprovizionat = highTrafficShop.reaprovizioneaza("Cafea Boabe", 900.0);
        assert(aprovizionat);
        assert(highTrafficShop.poatePrepara("Espresso"));
        assert(highTrafficShop.getIstoric().getNumarComenzi() == 100);
    }

    void test50_CafeneaSalvareRaportSiVerificareIntegralaLinii()
    {
        std::cout << "[TEST 50] Cafenea salvare raport final si validare integritate fisier...\n";
        Cafenea enterpriseShop("Enterprise_Coffee", 5000.0);
        enterpriseShop.adaugaIngredient(Ingrediente("Cafea Boabe", 500.0, "g", 0.12));
        enterpriseShop.adaugaIngredient(Ingrediente("Lapte", 2000.0, "ml", 0.01));

        const CReteta cCap[2] = { CReteta("Cafea Boabe", 18.0), CReteta("Lapte", 150.0) };
        enterpriseShop.adaugaReteta(Reteta("Cappuccino", 16.0, cCap, 2));

        Client clientVIP("VIP Customer");
        std::vector<std::string> listaVIP;
        listaVIP.push_back("Cappuccino");
        listaVIP.push_back("Cappuccino");

        bool plasatVIP = enterpriseShop.plaseazaComanda(clientVIP, listaVIP);
        assert(plasatVIP);

        const std::string fisierRaport = "raport_enterprise_test.txt";
        bool salvatCuSucces = enterpriseShop.salveazaRaportVanzari(fisierRaport);
        assert(salvatCuSucces);

        std::ifstream fileRead(fisierRaport.c_str());
        assert(fileRead.is_open());
        int liniiGasite = 0;
        std::string buffer;
        while (std::getline(fileRead, buffer))
        {
            ++liniiGasite;
        }
        fileRead.close();
        assert(liniiGasite > 0);
        std::remove(fisierRaport.c_str());
    }

    void test51_PromotieConstructoriSiStare()
    {
        std::cout << "[TEST 51] Promotie constructori, getteri si stare...\n";
        Promotie oprita("Happy Hour", "Espresso", 20.0);
        assert(oprita.getNume() == "Happy Hour");
        assert(oprita.getProdusVizat() == "Espresso");
        assert(aproapeEgal(oprita.getProcent(), 20.0));
        assert(!oprita.esteActiva());

        Promotie pornita("Weekend", "Latte", 15.0, true);
        assert(pornita.esteActiva());

        oprita.activeaza();
        assert(oprita.esteActiva());
        oprita.dezactiveaza();
        assert(!oprita.esteActiva());
    }

    void test52_PromotiePretRedusSiEconomie()
    {
        std::cout << "[TEST 52] Promotie calcul pret redus si economie...\n";
        Promotie promo("Happy Hour", "Espresso", 20.0);

        assert(!promo.aplicabila("Espresso"));
        assert(aproapeEgal(promo.economie(10.0, 3), 0.0));

        promo.activeaza();
        assert(promo.aplicabila("Espresso"));
        assert(!promo.aplicabila("Cappuccino"));
        assert(aproapeEgal(promo.calculeazaPretRedus(10.0), 8.0));
        assert(aproapeEgal(promo.economie(10.0, 3), 6.0));
        assert(aproapeEgal(promo.economie(10.0, 0), 0.0));
    }

    void test53_PromotieValidariExceptii()
    {
        std::cout << "[TEST 53] Promotie validari prin exceptii...\n";
        bool arunca = false;

        try { Promotie p("", "Espresso", 10.0); } catch (const std::invalid_argument&) { arunca = true; }
        assert(arunca);

        arunca = false;
        try { Promotie p("Promo", "", 10.0); } catch (const std::invalid_argument&) { arunca = true; }
        assert(arunca);

        arunca = false;
        try { Promotie p("Promo", "Espresso", 0.0); } catch (const std::invalid_argument&) { arunca = true; }
        assert(arunca);

        arunca = false;
        try { Promotie p("Promo", "Espresso", 95.0, true); } catch (const std::invalid_argument&) { arunca = true; }
        assert(arunca);

        arunca = false;
        Promotie ok("Promo", "Espresso", 10.0);
        try { ok.calculeazaPretRedus(-1.0); } catch (const std::invalid_argument&) { arunca = true; }
        assert(arunca);
    }

    void test54_PromotieAfisareStream()
    {
        std::cout << "[TEST 54] Promotie operator<< ...\n";
        Promotie promo("Happy Hour", "Espresso", 20.0);
        std::ostringstream ss;
        ss << promo;
        assert(ss.str().find("Happy Hour") != std::string::npos);
        assert(ss.str().find("oprita") != std::string::npos);

        promo.activeaza();
        std::ostringstream ss2;
        ss2 << promo;
        assert(ss2.str().find("ACTIVA") != std::string::npos);
    }

    void test55_RaportFinanciarGetteriSiFormule()
    {
        std::cout << "[TEST 55] RaportFinanciar getteri si formule...\n";
        RaportFinanciar r(100.0, 10.0, 40.0, 30.0, 4);
        assert(aproapeEgal(r.getIncasari(), 100.0));
        assert(aproapeEgal(r.getReduceri(), 10.0));
        assert(aproapeEgal(r.getCostMateriePrima(), 40.0));
        assert(aproapeEgal(r.getCheltuieliReaprovizionare(), 30.0));
        assert(r.getNumarComenzi() == 4);

        assert(aproapeEgal(r.profitBrut(), 60.0));
        assert(aproapeEgal(r.fluxNumerar(), 70.0));
        assert(aproapeEgal(r.marjaBruta(), 60.0));
        assert(aproapeEgal(r.incasarePerComanda(), 25.0));
        assert(aproapeEgal(r.ponderePierderiDinReduceri(), 10.0 / 110.0 * 100.0));
        assert(r.interpretare() == "Profitabila");
    }

    void test56_RaportFinanciarInterpretareCazuri()
    {
        std::cout << "[TEST 56] RaportFinanciar interpretare pe cazuri...\n";
        RaportFinanciar fara(0.0, 0.0, 0.0, 0.0, 0);
        assert(fara.interpretare() == "Nu exista inca vanzari");
        assert(aproapeEgal(fara.marjaBruta(), 0.0));
        assert(aproapeEgal(fara.incasarePerComanda(), 0.0));
        assert(aproapeEgal(fara.ponderePierderiDinReduceri(), 0.0));

        RaportFinanciar pierdere(10.0, 0.0, 20.0, 0.0, 1);
        assert(pierdere.interpretare() == "In pierdere");

        RaportFinanciar dinRezerve(100.0, 0.0, 40.0, 150.0, 5);
        assert(dinRezerve.interpretare() == "Profitabila, dar stocul nou a fost platit din rezerve");
    }

    void test57_RaportFinanciarValidariSiFisier()
    {
        std::cout << "[TEST 57] RaportFinanciar validari si salvare...\n";
        bool arunca = false;
        try { RaportFinanciar r(-1.0, 0.0, 0.0, 0.0, 0); } catch (const std::invalid_argument&) { arunca = true; }
        assert(arunca);

        arunca = false;
        try { RaportFinanciar r(1.0, 0.0, 0.0, 0.0, -2); } catch (const std::invalid_argument&) { arunca = true; }
        assert(arunca);

        RaportFinanciar r(88.0, 2.0, 27.0, 15.0, 4);
        std::ostringstream ss;
        ss << r;
        assert(ss.str().find("RAPORT FINANCIAR") != std::string::npos);
        assert(ss.str().find("Profitabila") != std::string::npos);

        const std::string fisier = "test_raport_financiar_temp.txt";
        assert(r.salveazaInFisier(fisier));
        std::ifstream fin(fisier.c_str());
        assert(fin.is_open());
        std::string linie;
        bool gasit = false;
        while (std::getline(fin, linie))
            if (linie.rfind("profit_brut;", 0) == 0)
                gasit = true;
        fin.close();
        assert(gasit);
        std::remove(fisier.c_str());
    }

    void test58_CafeneaPromotiiInComanda()
    {
        std::cout << "[TEST 58] Cafenea promotii aplicate la comanda...\n";
        Cafenea shop("PromoShop", 500.0);
        shop.adaugaIngredient(Ingrediente("Cafea Boabe", 500.0, "g", 0.10));
        const CReteta comp[1] = { CReteta("Cafea Boabe", 18.0) };
        shop.adaugaReteta(Reteta("Espresso", 10.0, comp, 1));

        shop.adaugaPromotie(Promotie("Happy Hour", "Espresso", 20.0));
        bool st1 = shop.seteazaStarePromotie("Happy Hour", false);
        assert(st1);

        Client ana("Ana");
        std::vector<std::string> lista(1, "Espresso");
        bool plasat1 = shop.plaseazaComanda(ana, lista);
        assert(plasat1);
        assert(aproapeEgal(shop.getIstoric().totalIncasari(), 10.0));

        bool st2 = shop.seteazaStarePromotie("Happy Hour", true);
        assert(st2);
        Client bob("Bob");
        bool plasat2 = shop.plaseazaComanda(bob, lista);
        assert(plasat2);
        assert(aproapeEgal(shop.getIstoric().totalIncasari(), 18.0));

        bool st3 = shop.seteazaStarePromotie("Inexistenta", true);
        assert(!st3);
        shop.afiseazaPromotii();

        RaportFinanciar raport = shop.raportFinanciar();
        assert(raport.getNumarComenzi() == 2);
        assert(aproapeEgal(raport.getIncasari(), 18.0));
        assert(aproapeEgal(raport.getCostMateriePrima(), 3.6));
    }

    void test59_CafeneaPromotiiInvalide()
    {
        std::cout << "[TEST 59] Cafenea promotii invalide prin exceptii...\n";
        Cafenea shop("PromoShop2", 100.0);
        shop.adaugaIngredient(Ingrediente("Cafea Boabe", 100.0, "g", 0.10));
        const CReteta comp[1] = { CReteta("Cafea Boabe", 18.0) };
        shop.adaugaReteta(Reteta("Espresso", 10.0, comp, 1));

        bool arunca = false;
        try { shop.adaugaPromotie(Promotie("Mocha Promo", "Mocha", 10.0)); }
        catch (const std::invalid_argument&) { arunca = true; }
        assert(arunca);

        shop.adaugaPromotie(Promotie("Promo", "Espresso", 10.0));
        arunca = false;
        try { shop.adaugaPromotie(Promotie("Promo", "Espresso", 15.0)); }
        catch (const std::invalid_argument&) { arunca = true; }
        assert(arunca);
    }

    void test60_CafeneaIncarcareSiSalvareStocFormatCorect()
    {
        std::cout << "[TEST 60] Cafenea incarcare/salvare stoc (format cu ';')...\n";
        const std::string fisierIn = "stoc_test_in.txt";
        std::ofstream fout(fisierIn.c_str());
        fout << "# denumire;stoc;unitate;pret_unitar\n";
        fout << "Cafea Boabe;300;g;0.15\n";
        fout << "\n";
        fout << "Lapte Integral;1000;ml;0.01\n";
        fout << "linie fara separatori\n";
        fout << "Sirop;abc;ml;0.05\n";
        fout.close();

        Cafenea shop("StocShop", 100.0);
        int nr1 = shop.incarcaIngredienteDinFisier(fisierIn);
        assert(nr1 == 2);
        int nr2 = shop.incarcaIngredienteDinFisier("fisier_care_nu_exista.txt");
        assert(nr2 == -1);

        const std::string fisierOut = "stoc_test_out.txt";
        assert(shop.salveazaStocInFisier(fisierOut));

        Cafenea alta("AltaCafenea", 100.0);
        int nr3 = alta.incarcaIngredienteDinFisier(fisierOut);
        assert(nr3 == 2);

        std::remove(fisierIn.c_str());
        std::remove(fisierOut.c_str());
    }

    void test61_ClientPraguriNivel()
    {
        std::cout << "[TEST 61] Client praguri exacte de nivel...\n";
        Client c("Prag");
        c.inregistreazaComanda(29.0);
        assert(c.getNivel() == "Standard");
        assert(aproapeEgal(c.getReducere(), 0.0));

        c.inregistreazaComanda(1.0);
        assert(c.getNivel() == "Argint");
        assert(aproapeEgal(c.getReducere(), 5.0));

        c.inregistreazaComanda(70.0);
        assert(c.getNivel() == "Aur");
        assert(aproapeEgal(c.getReducere(), 10.0));

        bool arunca = false;
        try { c.inregistreazaComanda(-5.0); } catch (const std::invalid_argument&) { arunca = true; }
        assert(arunca);
    }
}

int main()
{
    // Modul 1: Ingrediente
    TestSuite::test01_IngredienteConstructoriSiGetteri();
    TestSuite::test02_IngredienteConsumSiStoc();
    TestSuite::test03_IngredienteConsumLimitaExacta();
    TestSuite::test04_IngredienteAfisareStream();

    // Modul 2: CReteta
    TestSuite::test05_CRetetaConstructoriSiGetteri();
    TestSuite::test06_CRetetaCopiereSiAtribuire();
    TestSuite::test07_CRetetaAfisareStream();

    // Modul 3: Reteta
    TestSuite::test08_RetetaConstructoriSiGetteri();
    TestSuite::test09_RetetaRegulaCelorTreiCopiereAdanca();
    TestSuite::test10_RetetaCostProductie();
    TestSuite::test11_RetetaAfisareStream();

    // Modul 4: LinieComanda
    TestSuite::test12_LinieComandaConstructoriSiTotal();
    TestSuite::test13_LinieComandaAdaugaCantitate();
    TestSuite::test14_LinieComandaAfisareStream();

    // Modul 5: Comanda
    TestSuite::test15_ComandaAdaugareLiniiSiCalculSubtotal();
    TestSuite::test16_ComandaCumulareLiniiIdentice();
    TestSuite::test17_ComandaAplicareReducere();
    TestSuite::test18_ComandaAfisareBonStream();

    // Modul 6: Client
    TestSuite::test19_ClientConstructoriSiDateInitiale();
    TestSuite::test20_ClientInregistrareComandaSiPuncte();
    TestSuite::test21_ClientAvansareNivelSiReducere();
    TestSuite::test22_ClientAfisareStream();

    // Modul 7: IstoricVanzari
    TestSuite::test23_IstoricVanzariInregistrareSiStatistici();
    TestSuite::test24_IstoricVanzariGasesteComandaSiTop();
    TestSuite::test25_IstoricVanzariPersistentaFisier();

    // Modul 8: Cafenea
    TestSuite::test26_CafeneaIncarcareIngredienteSiStoc();
    TestSuite::test27_CafeneaPoatePreparaSiCatalogRetete();
    TestSuite::test28_CafeneaFluxProceseazaComandaDirecta();
    TestSuite::test29_CafeneaPlaseazaComandaClientCompusa();
    TestSuite::test30_CafeneaSalvareRaportSiAfisare();

    // Modul 9: Suitele Extinse (31 - 40)
    TestSuite::test31_IngredienteConsumFinSiReumplereRepetata();
    TestSuite::test32_RetetaComplexaMultiComponente();
    TestSuite::test33_LinieComandaOperatiiSuccesiveSiPrecizie();
    TestSuite::test34_ComandaReduceriSiValidariLinii();
    TestSuite::test35_ClientEvolutieComenziSiTranzactiiMultiple();
    TestSuite::test36_IstoricVanzariFiltrareSiTopExtins();
    TestSuite::test37_CafeneaEpuizareResurseSiBlocarePreparare();
    TestSuite::test38_CafeneaGestionareMultipliClientiSimultan();
    TestSuite::test39_CafeneaIncarcareFisierFormatSimulat();
    TestSuite::test40_CafeneaIntegritateStareSiIstoricComplet();

    // Modul 10: Stres, Persistenta si Scenarii Extreme (41 - 61)
    TestSuite::test41_IngredienteConsumPanaLaEpuizareTotala();
    TestSuite::test42_CRetetaStresVectorSiComparatii();
    TestSuite::test43_RetetaMultiplaCuSapteIngrediente();
    TestSuite::test44_RetetaAutoAtribuireSiSecventeCopiere();
    TestSuite::test45_LinieComandaCalculFinanciarValoriMari();
    TestSuite::test46_ComandaBonMareCuMulteProduseSiReducere();
    TestSuite::test47_ClientTranzactiiSuccesiveSiPuncteAcumulate();
    TestSuite::test48_IstoricVanzariVerificareStatisticiComplet();
    TestSuite::test49_CafeneaStresSuteDeComenziSiReaprovizionari();
    TestSuite::test50_CafeneaSalvareRaportSiVerificareIntegralaLinii();
    TestSuite::test51_PromotieConstructoriSiStare();
    TestSuite::test52_PromotiePretRedusSiEconomie();
    TestSuite::test53_PromotieValidariExceptii();
    TestSuite::test54_PromotieAfisareStream();
    TestSuite::test55_RaportFinanciarGetteriSiFormule();
    TestSuite::test56_RaportFinanciarInterpretareCazuri();
    TestSuite::test57_RaportFinanciarValidariSiFisier();
    TestSuite::test58_CafeneaPromotiiInComanda();
    TestSuite::test59_CafeneaPromotiiInvalide();
    TestSuite::test60_CafeneaIncarcareSiSalvareStocFormatCorect();
    TestSuite::test61_ClientPraguriNivel();

    return 0;
}
