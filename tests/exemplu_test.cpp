#include <cassert>
#include "Ingrediente.hpp"
#include "LinieComanda.hpp"
#include "Client.hpp"
#include "Cafenea.hpp"
#include "IstoricVanzari.hpp"

int main() {

    Ingrediente testIngr("Zahar", 100.0, "g", 0.05);
    assert(testIngr.getcantitateDisponibila() == 100.0);
    testIngr.consuma(20.0);
    assert(testIngr.getcantitateDisponibila() == 80.0);

  
    LinieComanda linie("Espresso", 1, 10.0);
    assert(linie.getPretUnitar() == 10.0);

    
    Client client("Ion Popescu");
    (void)client.getPuncte();
    (void)client.getTotalCheltuit();

    
    Cafenea cafenea("Cafeneaua Mea", 500.0);
    const IstoricVanzari& istoric = cafenea.getIstoric();

  
    (void)istoric.numarComenziClient("Ion Popescu");
    (void)istoric.totalClient("Ion Popescu");
    (void)istoric.gasesteComanda(1);

    return 0;
}
