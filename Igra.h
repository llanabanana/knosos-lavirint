#pragma once
#include "Lavirint.h"
#include "MagicniPredmet.h"
#include "Fajl.h"

/*
Klasa koja omogucava tok i logiku igre.
Autor: Lana Mirkov
Poslednja izmena: 20.7.2025.
*/

class Igra {
private:
    Lavirint lavirint;
    bool krajIgre;

    bool pomerajRobota(char smer,  MagicniPredmet mp, Robot& robot, Minotaur& m);
    void pomerajMinotaura(Minotaur m, Robot r);

public:
    Igra(int redovi, int kolone, int predmeti);
    void pokreni();
};


