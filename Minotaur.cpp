#include "Minotaur.h"
#include <iostream>
#include "Lavirint.h"
/*
Modul Minotaur sadrzi sve informacije o minotauru, kao i metode za rad sa minotaurom.
Autor: Lana Mirkov
Poslednja izmena: 25.2.2025.
*/
Minotaur::Minotaur() : koordinate({ 0, 0 }), unisten(false) {}

Minotaur::Minotaur(int x, int y) : koordinate({ x, y }) {}

Minotaur::~Minotaur() {}

void Minotaur::setKoordinate(int x, int y) {
	koordinate = { x, y };
}

std::pair<int, int> Minotaur::getKoordinate() const {
	return koordinate;
}

bool Minotaur::isUnisten() const {
	return unisten;
}

void Minotaur::setUnisten(bool status) {
	unisten = status;
}


std::pair <bool, std::pair<int, int>> Minotaur::robotJePored(std::pair<int, int> koordinateRobota, std::pair<int, int> trenutneKoordinate) {

	//proveri da li je robot pored minotaura
	//minotaur pogleda na sve 4 strane trazi robota

	//provera da li je robot pored minotaura
	if (koordinateRobota.first == trenutneKoordinate.first && koordinateRobota.second == trenutneKoordinate.second + 1) {
		//robot je desno od minotaura
		std::cout << "Robot je desno od minotaura" << std::endl;
		return { true, {trenutneKoordinate.first, trenutneKoordinate.second + 1} };

	}
	else if (koordinateRobota.first == trenutneKoordinate.first && koordinateRobota.second == trenutneKoordinate.second - 1) {
		//robot je levo od minotaura
		std::cout << "Robot je levo od minotaura" << std::endl;
		return { true, {trenutneKoordinate.first, trenutneKoordinate.second - 1} };
	}
	else if (koordinateRobota.first == trenutneKoordinate.first + 1 && koordinateRobota.second == trenutneKoordinate.second) {
		//robot je ispod minotaura
		std::cout << "Robot je ispod minotaura" << std::endl;
		return { true, {trenutneKoordinate.first + 1, trenutneKoordinate.second} };
	}
	else if (koordinateRobota.first == trenutneKoordinate.first - 1 && koordinateRobota.second == trenutneKoordinate.second) {
		//robot je iznad minotaura
		std::cout << "Robot je iznad minotaura" << std::endl;
		return { true, {trenutneKoordinate.first - 1, trenutneKoordinate.second} };
	}

	return { false, {0, 0} };
}