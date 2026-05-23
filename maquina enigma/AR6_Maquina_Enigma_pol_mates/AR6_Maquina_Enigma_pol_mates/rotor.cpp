#include "rotor.h"
#include <fstream>
#include <iostream>
using namespace std;

void Rotor::step() {
    pos = (pos + 1) % 26;
}

int Rotor::forward(int x) {
    return wiring[(x + pos) % 26] - 'A';
}

int Rotor::backward(int x) {
    x = (x + pos) % 26;

    for (int i = 0; i < 26; i++) {
        if (wiring[i] - 'A' == x)
            return i;
    }

    return x;
}

bool loadRotor(string file, Rotor& r) {
    ifstream f(file);
    if (!f) return false;

    getline(f, r.wiring);
    r.pos = 0;

    return r.wiring.size() == 26;
}

bool saveRotor(string file, const Rotor& r) {
    ofstream f(file);
    if (!f) return false;

    f << r.wiring << "\n";
    f << "Z\n";
    return true;
}

string clean(string s) {
    string r;
    for (char c : s) {
        c = toupper(c);
        if (c >= 'A' && c <= 'Z') r += c;
    }
    return r;
}

void editRotor(Rotor& r, const string& file) {
    string newWiring;

    cout << "Nueva permutacion (26 letras A-Z): ";
    cin >> newWiring;

    if (newWiring.size() != 26) {
        cout << "[ERROR] Debe tener 26 letras\n";
        return;
    }

    r.wiring = newWiring;
    r.pos = 0;

    cout << "[OK] Rotor actualizado\n";
}
