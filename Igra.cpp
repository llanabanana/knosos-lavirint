#include "Igra.h"
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
using namespace std;
using std::cout;
/*
Modul koji sadrzi funkcije koje omogucavaju igranje igre.
Autor: Lana Mirkov
Poslednja izmena: 2.8.2025.
*/
Igra::Igra(int r, int k, int p) : lavirint(r, k, p), krajIgre(false) {}

bool Igra::pomerajRobota(char smer, MagicniPredmet magicniPredmet, Robot& robot, Minotaur& minotaur) {
	/*
	Funkcija koja pomera robota u lavirintu na osnovu unetog smera.
	Zavisno od tipa polja na koje robot staje, izvrsava se razlicita logika
    Parametri:
	smer - karakter koji predstavlja smer pomeranja robota ('w', 'a', 's', 'd')
	magicniPredmet - objekat klase MagicniPredmet koji sadrzi logiku za pronalazak i primenu magicnih predmeta
    */
    
    std::pair<int, int> pocetneKoordRobota = lavirint.getRobotKoordinate();
	std::vector<pair<int, int>> ivice = lavirint.getIvice();  // uzimamo ivice lavirinta
    auto stare = lavirint.getRobotKoordinate();
	auto nove = lavirint.pronadjiNovoPolje(stare.first, stare.second, smer);  // pronalazi novo polje na osnovu smera
	if (nove.first == -1) return false;  // ako uneti smer nije validan, vrati false

    char tip = lavirint[nove.first][nove.second].getTip();  
	// Implemetiramo logiku zavisno od tipa polja na koje robot staje
    switch (tip) {
    case '#':
        if (!robot.aktivanEfekat("Cekic")) {
            cout << "Ne mozes proci kroz zid!" << endl;
            return false;
        }
        else {
			//proveirmo da li robot zeli da ide na ivicu lavirinta
			if (std::find(ivice.begin(), ivice.end(), std::make_pair(nove.first, nove.second)) != ivice.end()) {
				cout << "Ne mozes proci kroz ivicu lavirinta!" << endl;
				return false;
			}
            cout << "Prosao si kroz zid! Cekic iskoriscen." << endl;
            lavirint.setPraznoPolje(stare.first, stare.second);
            lavirint[nove.first][nove.second].setTip('R');
            robot.setKoordinate(nove.first, nove.second);
            robot.ukloniEfekat("Cekic");
        }
        break;
    case 'U':
        cout << "Ne mozes se vratiti na ulaz!" << endl;
        return false;
    case 'I':
        cout << "Pobeda! Stigao si do izlaza!" << endl;
        lavirint.setPraznoPolje(stare.first, stare.second);
		lavirint.setRobotKoordinate(nove.first, nove.second);  // postavljamo robota na novo polje, da bi zapis na kraju igre izgledao odgovarajuce
        krajIgre = true;
        break;
    case ' ':
        lavirint.setPraznoPolje(stare.first, stare.second);
        lavirint.setRobotKoordinate(nove.first, nove.second);
        break;
    case 'M':
        if (robot.aktivanEfekat("Mac")) {
            cout << "Unistio si minotaura! Mac iskoriscen." << endl;
            lavirint.setPraznoPolje(pocetneKoordRobota.first, pocetneKoordRobota.second);
			minotaur.setUnisten(true);  
			minotaur.setKoordinate(-1, -1); // postavljamo minotaura van lavirinta
            lavirint[nove.first][nove.second].setTip('R');
            robot.setKoordinate(nove.first, nove.second);  
            robot.ukloniEfekat("Mac");
        }
        else if (robot.aktivanEfekat("Stit")) {
            cout << "Minotaur te nije pojeo! Stit iskoriscen." << endl;
            robot.ukloniEfekat("Stit");
        }
        else {
            cout << "Minotaur te je pojeo! Kraj igre!" << endl;
            lavirint.setPraznoPolje(pocetneKoordRobota.first, pocetneKoordRobota.second);
            krajIgre = true;
        }
        break;
    case 'P':
        cout << "Nasao si magicni predmet!" << endl;
        lavirint.setPraznoPolje(stare.first, stare.second);
        lavirint.setRobotKoordinate(nove.first, nove.second);

        {
            string naziv = magicniPredmet.getRandomPredmet();

            cout << "Predmet: " << naziv << endl;

            if (naziv == "Magla") { Magla magla; magla.primeniEfekat(robot); }
            else if (naziv == "Mac") { Mac mac; mac.primeniEfekat(robot); }
            else if (naziv == "Stit") { Stit stit; stit.primeniEfekat(robot); }
            else if (naziv == "Cekic") { Cekic cekic; cekic.primeniEfekat(robot); }
        }
        break;
    }

    return true;
}

void Igra::pomerajMinotaura(Minotaur minotaur, Robot robot) {
    /*
	Funkcija koja pomera minotaura u lavirintu.
	Minotaur se pomera nasumicno, osim ako je robot pored njega.
	Parametri:
	minotaur - objekat klase Minotaur koji predstavlja minotaura u lavirintu
	robot - objekat klase Robot koji predstavlja robota u lavirintu
    */
	
    std::pair<int, int> pocetneKoordRobota = lavirint.getRobotKoordinate();
    std::pair<int, int> pocetneKoordMinotaura = lavirint.getMinotaurKoordinate();
    if (!minotaur.isUnisten()) {
        std::pair<bool, std::pair<int, int>> potezMinotaura = minotaur.robotJePored(robot.getKoordinate(), pocetneKoordMinotaura);

        if (potezMinotaura.first) {
            //proveri da li robot moze da se odbrani
            if (robot.aktivanEfekat("Mac")) {
            cout << "Minotaur je pokusao da te napadne, ali si ga porazio!" << endl;
            cout << "MAC iskoriscen" << endl;
            robot.ukloniEfekat("Mac");
            minotaur.setUnisten(true);
            minotaur.setKoordinate(-1, -1);
            //setujemo prazno polje na minotaurove koordinate
            lavirint.setPraznoPolje(pocetneKoordMinotaura.first, pocetneKoordMinotaura.second);
        }
        else if (robot.aktivanEfekat("Stit")) {
            cout << "Minotaur je pokusao da te napadne, ali si se odbranio!" << endl;
            cout << "ŠTIT iskoriscen" << endl;
            robot.ukloniEfekat("Stit");
            //setujemo prazno polje na minotaurove koordinate

        }
        else {
                    cout << "Minotaur te je stigao!!!" << endl;
                    cout << "Kraj igre! Izgubio si!" << endl;
                    lavirint.setPraznoPolje(pocetneKoordMinotaura.first, pocetneKoordMinotaura.second);
                    lavirint.setMinotaurKoordinate(potezMinotaura.second.first, potezMinotaura.second.second);
                    minotaur.setKoordinate(potezMinotaura.second.first, potezMinotaura.second.second);
                    krajIgre = true;

                }
            }

            else {
                std::vector <char> smerovi = { 'a', 'w', 's', 'd' };
                while (true) {
                    int smer = rand() % 4;
                    std::pair<int, int> novo = lavirint.pronadjiNovoPolje(lavirint.getMinotaurKoordinate().first, lavirint.getMinotaurKoordinate().second, smerovi[smer]);
                    int x = novo.first;
                    int y = novo.second;
                    if (lavirint[x][y].getTip() == ' ' || lavirint[x][y].getTip() == 'P') {
                        lavirint.setPraznoPolje(lavirint.getMinotaurKoordinate().first, lavirint.getMinotaurKoordinate().second);
                        lavirint.setMinotaurKoordinate(x, y);
                        break;
                    }
                }
            }
        }
	}
   


void Igra::pokreni() {
    lavirint.prikaziLavirint();
	MagicniPredmet magicniPredmet;
    Minotaur minotaur = lavirint.getMinotaur();
	// igra traje dok se ne postigne uslov za kraj igre
    while (!krajIgre) {
		Robot& robot = lavirint.getRobot();
        cout << "Pomeri robota (WASD, Q za izlaz): ";
        char unos = _getch();
        unos = tolower(unos);

        if (unos == 'q') { 
            cout << "Izlaz iz igre." << endl; 
            break; 
        }

        pomerajRobota(unos, magicniPredmet, robot, minotaur);
		if (krajIgre){
			lavirint.prikaziLavirint();
            break;
		}
		cout << minotaur.isUnisten() << endl;
		// Proveravamo da li je minotaur unisten
        if (!minotaur.isUnisten()) {
            pomerajMinotaura(minotaur, robot);
        }

        cout << endl;
		if (robot.aktivanEfekat("Magla") && robot.getTrajanjeEfekta("Magla") > 0) {
			lavirint.prikaziMaglaLavirint();
		}
		else {
			lavirint.prikaziLavirint();
		}

        cout << "Aktivni efekti: ";
        if (robot.aktivanEfekat("Magla")) {
            cout << "Magla " << robot.getTrajanjeEfekta("Magla") << " ";
        }
        if (robot.aktivanEfekat("Mac")) {
            cout << "Mac " << robot.getTrajanjeEfekta("Mac") << " ";
        }
        if (robot.aktivanEfekat("Stit")) {
            cout << "Stit " << robot.getTrajanjeEfekta("Stit") << " ";
        }
        if (robot.aktivanEfekat("Cekic"))
        {
            cout << "Cekic " << robot.getTrajanjeEfekta("Cekic") << " ";
        }

        cout << endl;
        cout << endl;

    
        cout << endl;
    }
    cout << "Da li zelite da sacuvate igru? (y/n): ";
    char sacuvaj;
    sacuvaj = _getch();
    if (sacuvaj == 'y' || sacuvaj == 'Y') {
        cout << "Unesite ime fajla za cuvanje igre: ";
        string imeFajla;
        cin >> imeFajla;
        imeFajla = "data/" + imeFajla + ".txt"; // Dodajemo ekstenziju .txt
        Fajl fajl = Fajl();
        fajl.upisiUFajl(imeFajla, lavirint);
        cout << "Igra je sacuvana." << endl;
    }
    else {
        cout << "Igra nije sacuvana." << endl;
    }
}
