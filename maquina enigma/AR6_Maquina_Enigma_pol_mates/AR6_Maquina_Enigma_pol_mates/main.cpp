#include <iostream>
#include <fstream>
#include <string>
#include "enigma.h"

using namespace std;

bool saveTextFile(const string& file, const string& text) {
    ofstream f(file);
    if (!f) return false;
    f << text;
    return f.good();
}

bool validWindow(const string& window) {
    if (window.size() != 3) return false;

    for (char c : window) {
        if (c < 'A' || c > 'Z') return false;
    }

    return true;
}

int main() {
    Rotor r1, r2, r3;

    if (!loadRotor("Rotor1.txt", r1)) {
        cout << "[ERROR] No se pudo cargar Rotor1.txt o su permutacion es invalida\n";
        return 1;
    }

    if (!loadRotor("Rotor2.txt", r2)) {
        cout << "[ERROR] No se pudo cargar Rotor2.txt o su permutacion es invalida\n";
        return 1;
    }

    if (!loadRotor("Rotor3.txt", r3)) {
        cout << "[ERROR] No se pudo cargar Rotor3.txt o su permutacion es invalida\n";
        return 1;
    }

    cout << "[OK] Rotores cargados correctamente\n";

    int op;

    while (true) {
        cout << "\n===== ENIGMA =====\n";
        cout << "1. Cifrar mensaje\n";
        cout << "2. Descifrar mensaje\n";
        cout << "3. Editar rotor\n";
        cout << "4. Salir\n";
        cout << "Opcion: ";
        cin >> op;

        if (op == 4) {
            cout << "[OK] Saliendo...\n";
            break;
        }

        if (op == 3) {
            int id;
            cout << "Que rotor (1-3): ";
            cin >> id;

            if (id == 1) editRotor(r1, "Rotor1.txt");
            else if (id == 2) editRotor(r2, "Rotor2.txt");
            else if (id == 3) editRotor(r3, "Rotor3.txt");
            else cout << "[ERROR] Rotor invalido\n";

            continue;
        }

        if (op != 1 && op != 2) {
            cout << "[ERROR] Opcion invalida\n";
            continue;
        }

        string window;
        cout << "Ventana inicial (ABC): ";
        cin >> window;

        for (char& c : window) {
            c = toupper(static_cast<unsigned char>(c));
        }

        if (!validWindow(window)) {
            cout << "[ERROR] Debe ser una cadena de 3 letras entre A y Z\n";
            continue;
        }

        cin.ignore();

        string msg;
        cout << "Mensaje: ";
        getline(cin, msg);

        string cleaned = clean(msg);

        if (!saveTextFile("Missatge.txt", cleaned)) {
            cout << "[ERROR] No se pudo guardar Missatge.txt\n";
            continue;
        }

        r1.pos = window[0] - 'A';
        r2.pos = window[1] - 'A';
        r3.pos = window[2] - 'A';

        if (op == 1) {
            string encrypted = encryptText(cleaned, r1, r2, r3);
            string grouped = groupFive(encrypted);

            if (!saveTextFile("Xifrat.txt", grouped)) {
                cout << "[ERROR] No se pudo guardar Xifrat.txt\n";
                continue;
            }

            cout << "[OK] Missatge xifrat a Xifrat.txt ("
                << encrypted.size() << " lletres, "
                << (encrypted.size() + 4) / 5 << " grups de 5)\n";

            cout << grouped << "\n";
        }
        else if (op == 2) {
            string decrypted = decryptText(cleaned, r1, r2, r3);

            if (!saveTextFile("desxifrat.txt", decrypted)) {
                cout << "[ERROR] No se pudo guardar desxifrat.txt\n";
                continue;
            }

            cout << "[OK] Missatge desxifrat a desxifrat.txt ("
                << decrypted.size() << " lletres)\n";

            cout << decrypted << "\n";
        }
    }

    return 0;
}