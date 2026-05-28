#pragma once
#include "rotor.h"
#include <string>

std::string encryptText(std::string msg, Rotor& r1, Rotor& r2, Rotor& r3);
std::string decryptText(std::string msg, Rotor& r1, Rotor& r2, Rotor& r3);

char encryptChar(char c, Rotor& r1, Rotor& r2, Rotor& r3);
char decryptChar(char c, Rotor& r1, Rotor& r2, Rotor& r3);
