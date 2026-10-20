#include <cassert>
#include "Ingrediente.hpp"

int main() {
    Ingrediente testIngr("Zahar", 100.0, "g", 0.05);
    assert(testIngr.getcantitateDisponibila() == 100.0);
    testIngr.consuma(20.0);
    assert(testIngr.getcantitateDisponibila() == 80.0);
    return 0;
}
