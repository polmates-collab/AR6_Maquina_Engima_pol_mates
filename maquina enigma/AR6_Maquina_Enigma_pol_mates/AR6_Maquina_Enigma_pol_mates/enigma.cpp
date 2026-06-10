#include "enigma.h"

// ===== STEPPING =====

void stepRotors(Rotor& r1, Rotor& r2, Rotor& r3) {
    bool stepR2 = r1.atNotch();
    bool stepR3 = r2.atNotch();

    r1.step();

    if (stepR2) {
        r2.step();
    }

    if (stepR3) {
        r3.step();
    }
}

// ===== ROTOR CHAR =====

char encryptChar(char c, Rotor& r1, Rotor& r2, Rotor& r3) {
    stepRotors(r1, r2, r3);

    int x = c - 'A';

    x = r1.forward(x);
    x = r2.forward(x);
    x = r3.forward(x);

    return char(x + 'A');
}

char decryptChar(char c, Rotor& r1, Rotor& r2, Rotor& r3) {
    stepRotors(r1, r2, r3);

    int x = c - 'A';

    x = r3.backward(x);
    x = r2.backward(x);
    x = r1.backward(x);

    return char(x + 'A');
}

// ===== TEXT =====

std::string encryptText(const std::string& msg, Rotor& r1, Rotor& r2, Rotor& r3) {
    std::string out;

    for (char c : msg) {
        if (c >= 'A' && c <= 'Z') {
            out += encryptChar(c, r1, r2, r3);
        }
    }

    return out;
}

std::string decryptText(const std::string& msg, Rotor& r1, Rotor& r2, Rotor& r3) {
    std::string out;

    for (char c : msg) {
        if (c >= 'A' && c <= 'Z') {
            out += decryptChar(c, r1, r2, r3);
        }
    }

    return out;
}