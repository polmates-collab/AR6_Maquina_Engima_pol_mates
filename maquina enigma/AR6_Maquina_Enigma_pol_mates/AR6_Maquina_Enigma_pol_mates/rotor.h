#pragma once
#include <string>

// Estructura de un rotor
struct Rotor {
    std::string cableado;   // Permutación de 26 letras
    char notch = 'Z';       // Letra donde hace avanzar el siguiente rotor
    int posicion = 0;       // Posición actual del rotor

    void avanzar();
    bool estaEnNotch() const;
    int adelante(int x) const;
    int atras(int x) const;
};

// Comprueba si un cableado es válido
bool cableadoValido(const std::string& cableado);

// Carga y guarda un rotor en archivo
bool cargarRotor(const std::string& archivo, Rotor& r);
bool guardarRotor(const std::string& archivo, const Rotor& r);

// Limpia el texto: mayúsculas y solo A-Z
std::string limpiarTexto(const std::string& texto);

// Agrupa en bloques de 5 letras
std::string agruparDeCinco(const std::string& texto);

// Permite editar un rotor desde teclado
void editarRotor(Rotor& r, const std::string& archivo);