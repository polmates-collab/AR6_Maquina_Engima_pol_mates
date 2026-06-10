#include "enigma.h"

char encryptChar(char c, Rotor& r1, Rotor& r2, Rotor& r3) {
    r1.step(); // Avanza el rotor 1

    int x = c - 'A'; // Convierte letra a número (A=0, B=1...)

    // Pasa por los rotores hacia adelante
    x = r1.forward(x);
    x = r2.forward(x);
    x = r3.forward(x);

    return char(x + 'A'); // Convierte número a letra
}

char decryptChar(char c, Rotor& r1, Rotor& r2, Rotor& r3) {
    r1.step(); // Avanza el rotor 1

    int x = c - 'A'; // Convierte letra a número

    // Pasa por los rotores hacia atrás
    x = r3.backward(x);
    x = r2.backward(x);
    x = r1.backward(x);

    return char(x + 'A'); // Convierte a letra otra vez
}

std::string encryptText(std::string msg, Rotor& r1, Rotor& r2, Rotor& r3) {
    std::string out; // Resultado final

    // Recorre cada letra del mensaje
    for (char c : msg)
        out += encryptChar(c, r1, r2, r3);

    return out;
}

std::string decryptText(std::string msg, Rotor& r1, Rotor& r2, Rotor& r3) {
    std::string out; // Resultado final

    // Recorre cada letra del mensaje
    for (char c : msg)
        out += decryptChar(c, r1, r2, r3);

    return out;
}