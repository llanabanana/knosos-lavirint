#pragma once
#include "Polje.h"
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <algorithm>
#pragma once

#include "Polje.h"
#include "Robot.h"
#include "Minotaur.h"
#include <vector>
#include <utility>

/*
Klasa koja sadrzi metode za generisanje lavirinta.
Autor: Lana Mirkov
Poslednja izmena: 1.8.2025.
*/

class GeneratorLavirinta {
public:
    static Polje** generisi(unsigned int brojRedova, unsigned int brojKolona, unsigned int brojPredmeta,
        Polje& ulaz, Polje& izlaz, Robot& robot, Minotaur& minotaur, std::vector<std::pair<int,int>>& v);

private:
	// metode za proveru da postoji put od ulaza do izlaza
    static bool matricaJeValidna(Polje** matrica, unsigned int brojRedova, unsigned int brojKolona, Polje ulaz, Polje izlaz);
    static bool floodFill(Polje** matrica, unsigned int brojRedova, unsigned int brojKolona, int row, int col, std::vector<std::vector<bool>>& visited, char target);
};
