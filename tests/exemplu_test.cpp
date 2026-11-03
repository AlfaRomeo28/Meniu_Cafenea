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
        Ingrediente ingImplicit;
        (void)ingImplicit;

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
        assert(consumReusit == true);
        assert(aproapeEgal(lapte.getcantitateDisponibila(), 1200.0));

        bool consumExcesiv = lapte.consuma(5000.0);
        assert(consumExcesiv == false);
        assert(aproapeEgal(lapte.getcantitateDisponibila(), 1200.0));
    }

    void test03_IngredienteConsumLimitaExacta()
    {
        std::cout << "[TEST 03] Ingrediente consum limita exacta...\n";
        Ingrediente zahar("Zahar", 100.0, "g", 0.05);
        bool consumTot = zahar.consuma(100.0);
        assert(consumTot == true);
        assert(aproapeEgal(zahar.getcantitateDisponibila(), 0.0));

        bool consumPeZero = zahar.consuma(0.01);
        assert(consumPeZero == false);
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
        CReteta crDefault;
        (void)crDefault;

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
        CReteta comp[2] = { CReteta("Cafea Boabe", 18.0), CReteta("Lapte Integral", 150.0) };
        Reteta cappuccino("Cappuccino", 16.0, comp, 2);

        assert(cappuccino.getDenumire() == "Cappuccino");
        assert(aproapeEgal(cappuccino.getPretVanzare(), 16.0));
        assert(cappuccino.getNumarComponente() == 2);
        assert(cappuccino.getComponente() != NULL);
        assert(cappuccino.getComponente()[0].getnume() == "Cafea Boabe");
    }

    void test09_RetetaRegulaCelorTreiCopiereAdanca()
    {
        std::cout << "[TEST 09] Reteta regula celor 3 si deep copy...\n";
        CReteta comp[1] = { CReteta("Cafea Boabe", 18.0) };
        Reteta original("Espresso", 10.0, comp, 1);

        {
            Reteta copie = original;
            assert(copie.getNumarComponente() == 1);
            assert(copie.getDenumire() == "Espresso");
            assert(copie.getComponente() != original.getComponente());
        }

        Reteta atribuita;
        atribuita = original;
        assert(atribuita.getNumarComponente() == 1);
        assert(atribuita.getDenumire() == "Espresso");
        assert(atribuita.getComponente() != original.getComponente());

        atribuita = atribuita; // auto-atribuire
        assert(atribuita.getNumarComponente() == 1);
    }

    void test10_RetetaCostProductie()
    {
        std::cout << "[TEST 10] Reteta calcul cost productie...\n";
        CReteta comp[2] = { CReteta("Cafea Boabe", 10.0), CReteta("Lapte", 100.0) };
        Reteta cafeaLapte("Cafea cu Lapte", 12.0, comp, 2);

        Ingrediente stocMagazie[2] = {
            Ingrediente("Cafea Boabe", 100.0, "g", 0.10), // 10g * 0.10 = 1.00
            Ingrediente("Lapte", 500.0, "ml", 0.02)        // 100ml * 0.02 = 2.00
        };

        double cost = cafeaLapte.calculeazaCostProductie(stocMagazie, 2);
        assert(aproapeEgal(cost, 3.0));
    }

    void test11_RetetaAfisareStream()
    {
        std::cout << "[TEST 11] Reteta operator<< ...\n";
        CReteta comp[1] = { CReteta("Apa", 200.0) };
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
        cmd.adaugaLinie("Vanilla Latte", 20.0, 2); // 40.0 subtotal

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
        assert(gasita != NULL);
        assert(gasita->getId() == 10);

        const Comanda* inexistent = ist.gasesteComanda(999);
        assert(inexistent == NULL);

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
        assert(salvat == true);

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
        assert(reaprovizionat == true);

        bool reaprovizionatInexistent = shop.reaprovizioneaza("ScortisoaraInexistenta", 100.0);
        assert(reaprovizionatInexistent == false);
    }

    void test27_CafeneaPoatePreparaSiCatalogRetete()
    {
        std::cout << "[TEST 27] Cafenea disponibilitate reteta vs stoc...\n";
        Cafenea shop("CatalogShop", 500.0);
        shop.adaugaIngredient(Ingrediente("Cafea Boabe", 36.0, "g", 0.15));

        CReteta compEsp[1] = { CReteta("Cafea Boabe", 18.0) };
        shop.adaugaReteta(Reteta("Espresso", 10.0, compEsp, 1));

        assert(shop.poatePrepara("Espresso") == true);
        assert(shop.poatePrepara("ProdusFantom") == false);
    }

    void test28_CafeneaFluxProceseazaComandaDirecta()
    {
        std::cout << "[TEST 28] Cafenea comanda directa rapida...\n";
        Cafenea shop("FastCoffee", 500.0);
        shop.adaugaIngredient(Ingrediente("Cafea Boabe", 36.0, "g", 0.15));

        CReteta compEsp[1] = { CReteta("Cafea Boabe", 18.0) };
        shop.adaugaReteta(Reteta("Espresso", 10.0, compEsp, 1));

        bool cmd1 = shop.proceseazaComanda("Espresso");
        assert(cmd1 == true);

        bool cmd2 = shop.proceseazaComanda("Espresso");
        assert(cmd2 == true);

        // Al treilea esueaza fiindca s-au terminat cei 36g de cafea
        bool cmd3 = shop.proceseazaComanda("Espresso");
        assert(cmd3 == false);
        assert(shop.poatePrepara("Espresso") == false);
    }

    void test29_CafeneaPlaseazaComandaClientCompusa()
    {
        std::cout << "[TEST 29] Cafenea plaseaza comanda multipla client...\n";
        Cafenea shop("OrderShop", 1000.0);
        shop.adaugaIngredient(Ingrediente("Cafea Boabe", 500.0, "g", 0.15));
        shop.adaugaIngredient(Ingrediente("Lapte Integral", 1000.0, "ml", 0.01));

        CReteta compEsp[1] = { CReteta("Cafea Boabe", 18.0) };
        shop.adaugaReteta(Reteta("Espresso", 10.0, compEsp, 1));

        CReteta compCap[2] = { CReteta("Cafea Boabe", 18.0), CReteta("Lapte Integral", 150.0) };
        shop.adaugaReteta(Reteta("Cappuccino", 16.0, compCap, 2));

        Client client("Barbu Stefanescu Delavrancea");
        std::vector<std::string> lista;
        lista.push_back("Espresso");
        lista.push_back("Cappuccino");

        bool plasata = shop.plaseazaComanda(client, lista);
        assert(plasata == true);
        assert(client.getNumarComenzi() == 1);
        assert(client.getTotalCheltuit() > 0.0);
        assert(shop.getIstoric().getNumarComenzi() == 1);
    }

    void test30_CafeneaSalvareRaportSiAfisare()
    {
        std::cout << "[TEST 30] Cafenea rapoarte, afisare si fisiere...\n";
        Cafenea shop("ReportShop", 1000.0);
        shop.adaugaIngredient(Ingrediente("Cafea Boabe", 200.0, "g", 0.15));

        CReteta c[1] = { CReteta("Cafea Boabe", 18.0) };
        shop.adaugaReteta(Reteta("Espresso", 10.0, c, 1));
        shop.proceseazaComanda("Espresso");

        shop.afiseazaRaportProfitabilitate();
        shop.afiseazaIstoric();

        std::ostringstream ss;
        ss << shop;
        assert(ss.str().find("ReportShop") != std::string::npos);

        const std::string caleRaport = "test_raport_final.txt";
        bool salvat = shop.salveazaRaportVanzari(caleRaport);
        assert(salvat == true);

        std::ifstream fVerificare(caleRaport.c_str());
        assert(fVerificare.is_open());
        fVerificare.close();
        std::remove(caleRaport.c_str());
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
    TestSuite::test24_IstoricVanzariGasesteComandaSiTop() ;
    TestSuite::test25_IstoricVanzariPersistentaFisier();

    // Modul 8: Cafenea
    TestSuite::test26_CafeneaIncarcareIngredienteSiStoc();
    TestSuite::test27_CafeneaPoatePreparaSiCatalogRetete();
    TestSuite::test28_CafeneaFluxProceseazaComandaDirecta();
    TestSuite::test29_CafeneaPlaseazaComandaClientCompusa();
    TestSuite::test30_CafeneaSalvareRaportSiAfisare();

  

    return 0;
}
