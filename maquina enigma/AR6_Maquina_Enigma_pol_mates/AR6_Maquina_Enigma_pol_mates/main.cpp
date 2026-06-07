#include <iostream>
#include <string>
#include "enigma.h"

using namespace std;

int main() {
    Rotor r1, r2, r3;

    if (!loadRotor("Rotor1.txt", r1) ||
        !loadRotor("Rotor2.txt", r2) ||
        !loadRotor("Rotor3.txt", r3)) {
        cout << "[ERROR] No se pudieron cargar los rotores\n";
        return 1;
    }

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
            else cout << "[ERROR] Rotor invalido";

            continue;
        }

        string window;
        cout << "Ventana (ABC): ";
        cin >> window;

        if (window.size() != 3) {
            cout << "[ERROR] Debe ser 3 letras\n";
            continue;
        }

        r1.pos = window[0] - 'A';
        r2.pos = window[1] - 'A';
        r3.pos = window[2] - 'A';

        cin.ignore();

        string msg;
        cout << "Mensaje: ";
        getline(cin, msg);

        msg = clean(msg);

        r1.pos = window[0] - 'A';
        r2.pos = window[1] - 'A';
        r3.pos = window[2] - 'A';

        if (op == 1)
            cout << encryptText(msg, r1, r2, r3) << endl;
        else if (op == 2)
            cout << decryptText(msg, r1, r2, r3) << endl;
        else
            cout << "[ERROR] Opcion invalida\n";
    }

    return 0;
}
