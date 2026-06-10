#include "rotor.h"
#include <fstream>
#include <iostream>
#include <cctype>

using namespace std;

// ================= ROTOR CORE =================

void Rotor::step() {
    pos = (pos + 1) % 26;
}

bool Rotor::atNotch() const {
    return ('A' + pos) == notch;
}

int Rotor::forward(int x) const {
    int shiftedIn = (x + pos) % 26;
    int wiredOut = wiring[shiftedIn] - 'A';
    return (wiredOut - pos + 26) % 26;
}

int Rotor::backward(int x) const {
    int shiftedIn = (x + pos) % 26;

    for (int i = 0; i < 26; i++) {
        if (wiring[i] - 'A' == shiftedIn) {
            return (i - pos + 26) % 26;
        }
    }

    return x;
}

// ================= VALIDATION =================

bool isValidWiring(const string& wiring) {
    if (wiring.size() != 26) return false;

    bool used[26] = { false };

    for (char c : wiring) {
        if (c < 'A' || c > 'Z') return false;
        int idx = c - 'A';
        if (used[idx]) return false;
        used[idx] = true;
    }

    return true;
}

// ================= FILES =================

bool loadRotor(const string& file, Rotor& r) {
    ifstream f(file);
    if (!f) return false;

    string wiringLine;
    string notchLine;

    if (!getline(f, wiringLine)) return false;

    for (char& c : wiringLine) c = toupper(static_cast<unsigned char>(c));

    if (!isValidWiring(wiringLine)) return false;

    r.wiring = wiringLine;
    r.pos = 0;
    r.notch = 'Z';

    if (getline(f, notchLine)) {
        if (!notchLine.empty()) {
            char c = toupper(static_cast<unsigned char>(notchLine[0]));
            if (c < 'A' || c > 'Z') return false;
            r.notch = c;
        }
    }

    return true;
}

bool saveRotor(const string& file, const Rotor& r) {
    ofstream f(file);
    if (!f) return false;

    f << r.wiring << "\n";
    f << r.notch << "\n";

    return f.good();
}

// ================= TEXT UTILS =================

string clean(const string& s) {
    string r;

    for (char c : s) {
        unsigned char uc = static_cast<unsigned char>(c);
        c = toupper(uc);

        if (c >= 'A' && c <= 'Z') {
            r += c;
        }
    }

    return r;
}

string groupFive(const string& s) {
    string out;

    for (size_t i = 0; i < s.size(); i++) {
        if (i > 0 && i % 5 == 0) out += ' ';
        out += s[i];
    }

    return out;
}

// ================= EDIT ROTOR =================

void editRotor(Rotor& r, const string& file) {
    string newWiring;
    string notchInput;

    cout << "Nueva permutacion (26 letras A-Z): ";
    cin >> newWiring;

    for (char& c : newWiring) c = toupper(static_cast<unsigned char>(c));

    if (!isValidWiring(newWiring)) {
        cout << "[ERROR] Permutacion invalida: deben ser 26 letras unicas A-Z\n";
        return;
    }

    cout << "Notch (1 letra A-Z, vacio = Z): ";
    cin >> notchInput;

    char newNotch = 'Z';
    if (!notchInput.empty()) {
        newNotch = toupper(static_cast<unsigned char>(notchInput[0]));
        if (newNotch < 'A' || newNotch > 'Z') {
            cout << "[ERROR] Notch invalido\n";
            return;
        }
    }

    r.wiring = newWiring;
    r.notch = newNotch;
    r.pos = 0;

    if (!saveRotor(file, r)) {
        cout << "[ERROR] No se pudo guardar " << file << "\n";
        return;
    }

    cout << "[OK] Rotor actualizado y guardado en " << file << "\n";
}