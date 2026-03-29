// Robot.h
#pragma once

#include <string>
#include <map>
#include <utility>

/*
Klasa koja predstavlja robota tj igraca u igri.
Autor: Lana Mirkov
Poslednja izmena: 10.5.2025.
*/

class Robot {
private:
	std::pair<int, int> koordinate; // Par koordinaata (x, y) robota
	std::map<std::string, int> efekti; // mapa efekata robota, gde je ključ naziv efekta, a vrednost trajanje efekta u potezima

public:
    Robot();
    Robot(int x, int y);
    ~Robot();

	// Metode za upravljanje efektima
    void dodajEfekat(const std::string& efekat);
    bool aktivanEfekat(const std::string& efekat) const;
    void ukloniEfekat(const std::string& efekat);
    void smanjiTrajanjeSvihEfekata();
    int getTrajanjeEfekta(const std::string& efekat) const;

	// Metode za upravljanje koordinatama robota
    void setKoordinate(int x, int y);
    std::pair<int, int> getKoordinate() const;
};