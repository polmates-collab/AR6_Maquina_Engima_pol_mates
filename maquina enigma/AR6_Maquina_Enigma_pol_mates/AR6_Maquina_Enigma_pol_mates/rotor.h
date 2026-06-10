#pragma once
#include <string>

struct Rotor {
    std::string wiring;
    char notch = 'Z';
    int pos = 0;

    void step();
    bool atNotch() const;
    int forward(int x) const;
    int backward(int x) const;
};

bool isValidWiring(const std::string& wiring);
bool loadRotor(const std::string& file, Rotor& r);
bool saveRotor(const std::string& file, const Rotor& r);

std::string clean(const std::string& s);
std::string groupFive(const std::string& s);

void editRotor(Rotor& r, const std::string& file);