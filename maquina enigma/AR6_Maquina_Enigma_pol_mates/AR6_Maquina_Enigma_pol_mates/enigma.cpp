#include "enigma.h"

char encryptChar(char c, Rotor& r1, Rotor& r2, Rotor& r3) {
    r1.step();

    int x = c - 'A';

    x = r1.forward(x);
    x = r2.forward(x);
    x = r3.forward(x);

    return char(x + 'A');
}

char decryptChar(char c, Rotor& r1, Rotor& r2, Rotor& r3) {
    r1.step();

    int x = c - 'A';

    x = r3.backward(x);
    x = r2.backward(x);
    x = r1.backward(x);

    return char(x + 'A');
}

std::string encryptText(std::string msg, Rotor& r1, Rotor& r2, Rotor& r3) {
    std::string out;

    for (char c : msg)
        out += encryptChar(c, r1, r2, r3);

    return out;
}

std::string decryptText(std::string msg, Rotor& r1, Rotor& r2, Rotor& r3) {
    std::string out;

    for (char c : msg)
        out += decryptChar(c, r1, r2, r3);

    return out;
}
