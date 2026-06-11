#include "enigma.h"

// Avanza los rotores antes de procesar una letra
void avanzarRotores(Rotor& r1, Rotor& r2, Rotor& r3) {
    bool moverR2 = r1.estaEnNotch();
    bool moverR3 = r2.estaEnNotch();

    r1.avanzar();

    if (moverR2) {
        r2.avanzar();
    }

    if (moverR3) {
        r3.avanzar();
    }
}

// Cifra una letra
char cifrarLetra(char c, Rotor& r1, Rotor& r2, Rotor& r3) {
    avanzarRotores(r1, r2, r3);

    int x = c - 'A';

    x = r1.adelante(x);
    x = r2.adelante(x);
    x = r3.adelante(x);

    return char(x + 'A');
}

// Descifra una letra
char descifrarLetra(char c, Rotor& r1, Rotor& r2, Rotor& r3) {
    avanzarRotores(r1, r2, r3);

    int x = c - 'A';

    x = r3.atras(x);
    x = r2.atras(x);
    x = r1.atras(x);

    return char(x + 'A');
}

// Cifra un texto completo
std::string cifrarTexto(const std::string& texto, Rotor& r1, Rotor& r2, Rotor& r3) {
    std::string salida;

    for (char c : texto) {
        if (c >= 'A' && c <= 'Z') {
            salida += cifrarLetra(c, r1, r2, r3);
        }
    }

    return salida;
}

// Descifra un texto completo
std::string descifrarTexto(const std::string& texto, Rotor& r1, Rotor& r2, Rotor& r3) {
    std::string salida;

    for (char c : texto) {
        if (c >= 'A' && c <= 'Z') {
            salida += descifrarLetra(c, r1, r2, r3);
        }
    }

    return salida;
}