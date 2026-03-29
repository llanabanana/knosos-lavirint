#pragma once
#include "Robot.h"
#include <string>


/*
Klasa koja predstavlja sve vrste magicnih predmeta u igri.
Autor: Lana Mirkov
Poslednja izmena: 5.5.2025.
*/

class MagicniPredmet {
protected:
	std::string naziv;  // Naziv magicnog predmeta
public:
    MagicniPredmet(const std::string& name);
    MagicniPredmet();
    virtual ~MagicniPredmet();
    virtual void primeniEfekat(Robot& robot) {};

    std::string getRandomPredmet();
};

// Klase koje nasleđuju MagicniPredmet 
class Magla : public MagicniPredmet {
public:
    Magla();
    void primeniEfekat(Robot& robot) override;
};

class Mac : public MagicniPredmet {
public:
    Mac();
    void primeniEfekat(Robot& robot) override;
};

class Stit : public MagicniPredmet {
public:
    Stit();
    void primeniEfekat(Robot& robot) override;
};

class Cekic : public MagicniPredmet {
public:
    Cekic();
    void primeniEfekat(Robot& robot) override;
};
