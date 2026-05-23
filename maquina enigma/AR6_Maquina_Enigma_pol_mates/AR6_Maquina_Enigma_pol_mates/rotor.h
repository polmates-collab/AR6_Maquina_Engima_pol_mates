#pragma once
#include <string>

struct Rotor {
    std::string wiring;
    int pos = 0;

    void step();
    int forward(int x);
    int backward(int x);
};

bool loadRotor(std::string file, Rotor& r);
bool saveRotor(std::string file, const Rotor& r);

std::string clean(std::string s);
void editRotor(Rotor& r, const std::string& file);
