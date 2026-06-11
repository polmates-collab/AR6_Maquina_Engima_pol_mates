#pragma once
#include "rotor.h"
#include <string>

// Avanza los rotores
void avanzarRotores(Rotor& r1, Rotor& r2, Rotor& r3);

// Cifra y descifra una sola letra
char cifrarLetra(char c, Rotor& r1, Rotor& r2, Rotor& r3);
char descifrarLetra(char c, Rotor& r1, Rotor& r2, Rotor& r3);

// Cifra y descifra un texto entero
std::string cifrarTexto(const std::string& texto, Rotor& r1, Rotor& r2, Rotor& r3);
std::string descifrarTexto(const std::string& texto, Rotor& r1, Rotor& r2, Rotor& r3);