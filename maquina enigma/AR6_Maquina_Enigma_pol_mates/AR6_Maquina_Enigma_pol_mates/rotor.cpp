#include "rotor.h"
#include <fstream>
#include <iostream>
using namespace std;

// Avanza la posición del rotor (de 0 a 25)
void Rotor::step() {
    pos = (pos + 1) % 26;
}

// Pasa la señal hacia adelante
int Rotor::forward(int x) {
    return wiring[(x + pos) % 26] - 'A';
}

// Pasa la señal hacia atrás (busca la letra original)
int Rotor::backward(int x) {
    x = (x + pos) % 26;

    // Busca qué posición da ese valor
    for (int i = 0; i < 26; i++) {
        if (wiring[i] - 'A' == x)
            return i;
    }

    return x; // Por seguridad (aunque no debería pasar)
}

// Carga un rotor desde archivo
bool loadRotor(string file, Rotor& r) {
    ifstream f(file);
    if (!f) return false; // Error al abrir

    getline(f, r.wiring); // Lee la configuración
    r.pos = 0; // Empieza en posición 0

    return r.wiring.size() == 26; // Comprueba que sea válido
}

// Guarda un rotor en archivo
bool saveRotor(string file, const Rotor& r) {
    ofstream f(file);
    if (!f) return false; // Error al abrir

    f << r.wiring << "\n";
    f << "Z\n"; // Línea extra (no muy importante)
    return true;
}

// Quita todo lo que no sean letras y pasa a mayúsculas
string clean(string s) {
    string r;
    for (char c : s) {
        c = toupper(c);
        if (c >= 'A' && c <= 'Z') r += c;
    }
    return r;
}

// Permite cambiar la configuración del rotor
void editRotor(Rotor& r, const string& file) {
    string newWiring;

    cout << "Nueva permutacion (26 letras A-Z): ";
    cin >> newWiring;

    // Comprueba que tenga 26 letras
    if (newWiring.size() != 26) {
        cout << "[ERROR] Debe tener 26 letras\n";
        return;
    }

    r.wiring = newWiring; // Guarda nueva configuración
    r.pos = 0; // Reinicia posición

    cout << "[OK] Rotor actualizado\n";
}