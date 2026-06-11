#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "enigma.h"

using namespace std;

// Guarda texto en un archivo
bool guardarTexto(const string& archivo, const string& texto) {
    ofstream f(archivo);
    if (!f) return false;

    f << texto;
    return f.good();
}

// Comprueba que la ventana tenga 3 letras
bool ventanaValida(const string& ventana) {
    if (ventana.size() != 3) return false;

    for (char c : ventana) {
        if (c < 'A' || c > 'Z') return false;
    }

    return true;
}

int main() {
    Rotor r1, r2, r3;

    // Cargar rotores
    if (!cargarRotor("Rotor1.txt", r1)) {
        cout << "[ERROR] No se pudo cargar Rotor1.txt\n";
        return 1;
    }

    if (!cargarRotor("Rotor2.txt", r2)) {
        cout << "[ERROR] No se pudo cargar Rotor2.txt\n";
        return 1;
    }

    if (!cargarRotor("Rotor3.txt", r3)) {
        cout << "[ERROR] No se pudo cargar Rotor3.txt\n";
        return 1;
    }

    cout << "[OK] Rotores cargados correctamente\n";

    int opcion;

    while (true) {
        cout << "\n===== ENIGMA =====\n";
        cout << "1. Cifrar mensaje\n";
        cout << "2. Descifrar mensaje\n";
        cout << "3. Editar rotor\n";
        cout << "4. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        if (opcion == 4) {
            cout << "[OK] Programa terminado\n";
            break;
        }

        if (opcion == 3) {
            int numeroRotor;

            cout << "Que rotor quieres editar (1-3): ";
            cin >> numeroRotor;

            if (numeroRotor == 1) {
                editarRotor(r1, "Rotor1.txt");
            }
            else if (numeroRotor == 2) {
                editarRotor(r2, "Rotor2.txt");
            }
            else if (numeroRotor == 3) {
                editarRotor(r3, "Rotor3.txt");
            }
            else {
                cout << "[ERROR] Numero de rotor no valido\n";
            }

            continue;
        }

        if (opcion != 1 && opcion != 2) {
            cout << "[ERROR] Opcion no valida\n";
            continue;
        }

        string ventana;
        cout << "Ventana inicial (ABC): ";
        cin >> ventana;

        for (char& c : ventana) {
            c = toupper(static_cast<unsigned char>(c));
        }

        if (!ventanaValida(ventana)) {
            cout << "[ERROR] La ventana debe tener 3 letras\n";
            continue;
        }

        cin.ignore();

        string mensaje;
        cout << "Mensaje: ";
        getline(cin, mensaje);

        string textoLimpio = limpiarTexto(mensaje);

        if (!guardarTexto("Missatge.txt", textoLimpio)) {
            cout << "[ERROR] No se pudo guardar Missatge.txt\n";
            continue;
        }

        // Colocar los rotores en la posición inicial
        r1.posicion = ventana[0] - 'A';
        r2.posicion = ventana[1] - 'A';
        r3.posicion = ventana[2] - 'A';

        if (opcion == 1) {
            string cifrado = cifrarTexto(textoLimpio, r1, r2, r3);
            string cifradoAgrupado = agruparDeCinco(cifrado);

            if (!guardarTexto("Xifrat.txt", cifradoAgrupado)) {
                cout << "[ERROR] No se pudo guardar Xifrat.txt\n";
                continue;
            }

            cout << "[OK] Mensaje cifrado guardado en Xifrat.txt\n";
            cout << cifradoAgrupado << "\n";
        }
        else if (opcion == 2) {
            string descifrado = descifrarTexto(textoLimpio, r1, r2, r3);

            if (!guardarTexto("desxifrat.txt", descifrado)) {
                cout << "[ERROR] No se pudo guardar desxifrat.txt\n";
                continue;
            }

            cout << "[OK] Mensaje descifrado guardado en desxifrat.txt\n";
            cout << descifrado << "\n";
        }
    }

    return 0;
}