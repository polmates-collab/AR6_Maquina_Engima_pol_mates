#pragma once
#include "rotor.h"
#include <string>

void stepRotors(Rotor& r1, Rotor& r2, Rotor& r3);

char encryptChar(char c, Rotor& r1, Rotor& r2, Rotor& r3);
char decryptChar(char c, Rotor& r1, Rotor& r2, Rotor& r3);

std::string encryptText(const std::string& msg, Rotor& r1, Rotor& r2, Rotor& r3);
std::string decryptText(const std::string& msg, Rotor& r1, Rotor& r2, Rotor& r3);