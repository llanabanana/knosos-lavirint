#include "Robot.h"
#include "Polje.h"
#include <iostream>

/*
Modul Robot sadrži funkcije za rad sa robotom u lavirintu.
Autor: Lana Mirkov
Poslednja izmena: 11.5.2025.
*/
Robot::Robot() : koordinate({ 0, 0 }) {}

Robot::Robot(int x, int y) : koordinate({ x, y }) {}

Robot::~Robot() {}

void Robot::dodajEfekat(const std::string& efekat) {
	// Dodaje efekat robota sa početnim trajanjem od 3 poteza
	if (efekti.find(efekat) != efekti.end()) {
		efekti[efekat] += 3;
	}
	else
		efekti[efekat] = 3;
}

void Robot::ukloniEfekat(const std::string& efekat) {
	// Uklanja efekat robota ako postoji
	if (efekti.find(efekat) != efekti.end()) {
		efekti.erase(efekat);
	}
}

void Robot::smanjiTrajanjeSvihEfekata() {
	// Smanjuje trajanje svih efekata robota za 1 potez
	for (auto it = efekti.begin(); it != efekti.end(); ) {
		it->second--;
		if (it->second == 0) {
			it = efekti.erase(it);
		}
		else {
			++it;
		}
	}
}

int Robot::getTrajanjeEfekta(const std::string& efekat) const {
	// Vraća trajanje efekta robota ako postoji, inače vraća 0
	if (efekti.find(efekat) != efekti.end()) {
		return efekti.at(efekat);
	}
	return 0;
}

bool Robot::aktivanEfekat(const std::string& efekat) const {
	return efekti.find(efekat) != efekti.end();
}

void Robot::setKoordinate(int x, int y) {
	koordinate = { x, y };
}
std::pair<int, int> Robot::getKoordinate() const {
	return koordinate;
}


