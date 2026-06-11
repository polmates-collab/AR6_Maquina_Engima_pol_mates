#include "rotor.h"
#include <fstream>
#include <iostream>
#include <cctype>

using namespace std;

// Avanza una posición
void Rotor::avanzar() {
    posicion = (posicion + 1) % 26;
}

// Comprueba si el rotor está en su notch
bool Rotor::estaEnNotch() const {
    return ('A' + posicion) == notch;
}

// Paso hacia delante por el rotor
int Rotor::adelante(int x) const {
    int entradaAjustada = (x + posicion) % 26;
    int salidaCableada = cableado[entradaAjustada] - 'A';
    return (salidaCableada - posicion + 26) % 26;
}

// Paso hacia atrás por el rotor
int Rotor::atras(int x) const {
    int entradaAjustada = (x + posicion) % 26;

    for (int i = 0; i < 26; i++) {
        if (cableado[i] - 'A' == entradaAjustada) {
            return (i - posicion + 26) % 26;
        }
    }

    return x;
}

// Comprueba que el cableado tenga 26 letras únicas A-Z
bool cableadoValido(const string& cableado) {
    if (cableado.size() != 26) return false;

    bool usadas[26] = { false };

    for (char c : cableado) {
        if (c < 'A' || c > 'Z') return false;

        int indice = c - 'A';
        if (usadas[indice]) return false;

        usadas[indice] = true;
    }

    return true;
}

// Carga rotor desde archivo
bool cargarRotor(const string& archivo, Rotor& r) {
    ifstream f(archivo);
    if (!f) return false;

    string lineaCableado;
    string lineaNotch;

    if (!getline(f, lineaCableado)) return false;

    for (char& c : lineaCableado) {
        c = toupper(static_cast<unsigned char>(c));
    }

    if (!cableadoValido(lineaCableado)) return false;

    r.cableado = lineaCableado;
    r.posicion = 0;
    r.notch = 'Z';

    if (getline(f, lineaNotch)) {
        if (!lineaNotch.empty()) {
            char c = toupper(static_cast<unsigned char>(lineaNotch[0]));
            if (c < 'A' || c > 'Z') return false;
            r.notch = c;
        }
    }

    return true;
}

// Guarda rotor en archivo
bool guardarRotor(const string& archivo, const Rotor& r) {
    ofstream f(archivo);
    if (!f) return false;

    f << r.cableado << "\n";
    f << r.notch << "\n";

    return f.good();
}

// Limpia el texto: pasa a mayúsculas y elimina lo que no sea A-Z
string limpiarTexto(const string& texto) {
    string resultado;

    for (char c : texto) {
        c = toupper(static_cast<unsigned char>(c));

        if (c >= 'A' && c <= 'Z') {
            resultado += c;
        }
    }

    return resultado;
}

// Separa el texto en grupos de 5 letras
string agruparDeCinco(const string& texto) {
    string salida;

    for (size_t i = 0; i < texto.size(); i++) {
        if (i > 0 && i % 5 == 0) {
            salida += ' ';
        }

        salida += texto[i];
    }

    return salida;
}

// Edita rotor desde teclado
void editarRotor(Rotor& r, const string& archivo) {
    string nuevoCableado;
    string entradaNotch;

    cout << "Nueva permutacion (26 letras A-Z): ";
    cin >> nuevoCableado;

    for (char& c : nuevoCableado) {
        c = toupper(static_cast<unsigned char>(c));
    }

    if (!cableadoValido(nuevoCableado)) {
        cout << "[ERROR] El cableado no es valido\n";
        return;
    }

    cout << "Notch (una letra A-Z, si no sabes pon Z): ";
    cin >> entradaNotch;

    char nuevoNotch = 'Z';

    if (!entradaNotch.empty()) {
        nuevoNotch = toupper(static_cast<unsigned char>(entradaNotch[0]));

        if (nuevoNotch < 'A' || nuevoNotch > 'Z') {
            cout << "[ERROR] El notch no es valido\n";
            return;
        }
    }

    r.cableado = nuevoCableado;
    r.notch = nuevoNotch;
    r.posicion = 0;

    if (!guardarRotor(archivo, r)) {
        cout << "[ERROR] No se pudo guardar el rotor en el archivo\n";
        return;
    }

    cout << "[OK] Rotor actualizado correctamente\n";
}