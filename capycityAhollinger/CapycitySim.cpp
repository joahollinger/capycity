#include <execution>
#include <algorithm>
#include <vector>
#include <map>
#include <iostream>
using namespace std;


class CapycitySim {

public:

	bool kollidiert(int laengeGebaeude, int breiteGebaeude, int pos1, int pos2, int* flaeche, int laengeFlaeche, int breiteFlaeche);

	int* gebaudeAnlegen(int laengeGebaeude, int breiteGebaeude, int pos1, int pos2, int* flaeche, int laengeFlaeche, int gebaeudeCode);

	int* flaecheFreigeben(int flaechenLaenge, int flaechenBreite, int position1, int position2, int* flaeche, int laengeFlaeche);



};



bool CapycitySim::kollidiert(int laengeGebaeude, int breiteGebaeude, int pos1, int pos2, int* flaeche, int laengeFlaeche, int breiteFlaeche) {
	bool kollidiert = false;

	if (pos1 >= laengeFlaeche || pos2 >= breiteFlaeche) {
		kollidiert = true;
	}
	else if (laengeGebaeude > laengeFlaeche || breiteGebaeude > breiteFlaeche) {
		kollidiert = true;
	}
	else {
		for (int restL = 0; restL < laengeGebaeude; ++restL) {
			for (int restB = 0; restB < breiteGebaeude; ++restB) {
				if (flaeche[(restB + pos2) * laengeFlaeche + (restL + pos1)] == 1 || flaeche[(restB + pos2) * laengeFlaeche + (restL + pos1)] == 2 || flaeche[(restB + pos2) * laengeFlaeche + (restL + pos1)] == 3) {
					kollidiert = true;
					break;
				}
				else if ((restB + pos2) * laengeFlaeche + (restL + pos1) > laengeFlaeche * breiteFlaeche) {
					kollidiert = true;
				}
				else {
					kollidiert = false;
				}
			}
		}
	}
	return kollidiert;
}

int* CapycitySim::gebaudeAnlegen(int laengeGebaeude, int breiteGebaeude, int pos1, int pos2, int* flaeche, int laengeFlaeche, int gebaeudeCode) {
	for (int restL = 0; restL < laengeGebaeude; ++restL) {
		for (int restB = 0; restB < breiteGebaeude; ++restB) {
			flaeche[(restB + pos2) * laengeFlaeche + (restL + pos1)] = { gebaeudeCode };
		}
	}
	return flaeche;
}

int* CapycitySim::flaecheFreigeben(int flaechenLaenge, int flaechenBreite, int position1, int position2, int* flaeche, int laengeFlaeche) {
	for (int restL = 0; restL < flaechenLaenge; ++restL) {
		for (int restB = 0; restB < flaechenBreite; ++restB) {
			flaeche[(restB + position2) * laengeFlaeche + (restL + position1)] = { 0 };
		}
	}
	return flaeche;
}




class Material {
private:
	int preis;
	string label;

public:
	Material() = default;
	Material(int pr, string l) :preis(pr), label(l) {}
	int getPreis() {
		return this->preis;
	}
	string getLabel() {
		return this->label;
	}
};

class Holz : public Material {
public:
	Holz(int pr, string l) :Material(pr, l) {};
};

class Metall : public Material {
public:
	Metall(int pr, string l) : Material(pr, l) {};
};

class Kunststoff : public Material {
public:
	Kunststoff(int pr, string l) : Material(pr, l) {};
};

class Building {
private:
	int grundpreis;
	int leistung;
	string label;
	map<string, int> material;

	/*
		Ich verwende Carlas Idee, da meiner Meinung nach die "Verwaltung der Materialien" als einfache map in der
		Building-Klasse vollkommend ausreichend ist. Eine separate Klasse hierfür, wäre meiner Meinung nach, für diesen
		"kleinen" Aspekt, etwas über das Ziel hinausgeschossen.Zudem mussten hierfür weniger Anpassungen getroffen werden.

	*/

public:
	Building() = default;
	Building(int gp, int mw, string l, map<string, int> mat) : grundpreis(gp), leistung(mw), label(l), material{ mat } {}
	int getGrundpreis() {
		return this->grundpreis;
	}
	int getLeistung() {
		return this->leistung;
	}
	string getLabel() {
		return this->label;
	}
	map<string, int> getMat() {
		return this->material;

	}
	int berechneGesamtPreis(int wieVieleGeaeude, Building gebaeude, Holz h, Metall m, Kunststoff k);
};

int Building::berechneGesamtPreis(int wieVieleGebaeude, Building aktGebaeude, Holz h, Metall m, Kunststoff k)
{
	int gesamtPreis = 0;


	for (int i = 0; i < wieVieleGebaeude; i++) {
		map<string, int> gebaeudeMats;
		int gebaeudePreis = aktGebaeude.getGrundpreis();


		gebaeudeMats = aktGebaeude.getMat();

		map<string, int>::iterator it = gebaeudeMats.begin();

		while (it != gebaeudeMats.end()) {
			if (it->first == "Holz") {
				gebaeudePreis += h.getPreis() * it->second;
			}
			else if (it->first == "Metall") {
				gebaeudePreis += m.getPreis() * it->second;
			}
			else if (it->first == "Kunststoff") {
				gebaeudePreis += k.getPreis() * it->second;
			}
			++it;
		}

		return gebaeudePreis;

	}

}

class Wasserkraftwerk : public Building {
public:
	Wasserkraftwerk(int gp, int mw, string l, map<string, int> mat) : Building(gp, mw, l, mat) {};
};

class Windkraftwerk : public Building {
public:
	Windkraftwerk(int gp, int mw, string l, map<string, int> mat) : Building(gp, mw, l, mat) {};
};

class Solarpanel : public Building {
public:
	Solarpanel(int gp, int mw, string l, map<string, int> mat) : Building(gp, mw, l, mat) {};
};

class BluePrint {
public:
	int* flaecheErstellen(int laenge, int breite);

	void print(int laengeFlaeche, int breiteFlaeche, int* flaeche);

	int berechneKennzahl(int flaechenEinheiten, int wieVieleGebaeude, int leistung, int preis);

};

int* BluePrint::flaecheErstellen(int laenge, int breite) {
	int* flaeche = new int[laenge * breite] {0};
	return flaeche;
}

void BluePrint::print(int laengeFlaeche, int breiteFlaeche, int* flaeche) {
	for (int tmp = 0; tmp < laengeFlaeche; tmp++)
	{
		for (int tmp2 = 0; tmp2 < breiteFlaeche; tmp2++)
		{
			if (flaeche[tmp2 * laengeFlaeche + tmp] == 0)
			{
				printf("|    |");
			}
			else if (flaeche[tmp2 * laengeFlaeche + tmp] == 1)
			{
				printf("| WA |");
			}
			else if (flaeche[tmp2 * laengeFlaeche + tmp] == 2)
			{
				printf("| WI |");
			}
			else if (flaeche[tmp2 * laengeFlaeche + tmp] == 3)
			{
				printf("| SP |");
			}
		}
		printf("\n");
		printf("\n");
	}
}

int BluePrint::berechneKennzahl(int flaechenEinheiten, int wieVieleGebaeude, int leistung, int preis)
{
	return (leistung / (preis * flaechenEinheiten));
}

int main() {

	CapycitySim* capycity = new CapycitySim();
	Building* capyBuilding = new Building();
	BluePrint* bluePrint = new BluePrint();
	map<int, int*> plaene;
	map<int, Building*> gebaeudeJePlan;
	map<int, int> kennzahlen;
	map<int, int> laengen;
	map<int, int> breiten;

	Holz h(30, "H");
	Metall m(50, "M");
	Kunststoff k(5, "K");


	map<string, int> matWA;
	matWA["Holz"] = 2;
	matWA["Metall"] = 1;
	matWA["Kunststoff"] = 1;

	map<string, int> matWI;
	matWI["Holz"] = 1;
	matWI["Metall"] = 2;
	matWI["Kunststoff"] = 1;

	map<string, int> matSP;
	matSP["Metall"] = 2;
	matSP["Kunststoff"] = 2;


	int laenge = 0, breite = 0, status = 0, artDesGebaeudes = 0, wieVieleGebaeude = 0, anzahlPlaene = 0;

	cout << "Geben Sie die Laenge des Baubereichs ein: \n";
	cin >> laenge;
	cout << "Geben Sie die Breite des Baubereichs ein: \n";
	cin >> breite;

	laengen[anzahlPlaene] = laenge;
	breiten[anzahlPlaene] = breite;

	int* flaeche = bluePrint->flaecheErstellen(laenge, breite);

	plaene[anzahlPlaene] = flaeche;

	int size = laenge * breite;
	Building* gebaeude = new Building[size];

	while (status != 7)
	{
		cout << "Menue: \n";
		cout << "Gebaeude setzen: (1) \n";
		cout << "Bereich loeschen: (2)\n";
		cout << "Bauplan ausgeben: (3) \n";
		cout << "Auflistung ausgeben: (4) \n";
		cout << "Neuen Plan erstellen: (5) \n";
		cout << "Alle Plaene ausgeben: (6) \n";
		cout << "Programm beenden: (7) \n";
		cin >> status;

		if (status == 1)
		{
			int laengeGebaeude, breiteGebaeude, pos1, pos2;

			cout << "Waehlen Sie die Art des Gebaeudes: \n";
			cout << "Wasserkraftwerk (1)\n";
			cout << "Windkraftwerk (2)\n";
			cout << "Solarpanele (3)\n";
			cin >> artDesGebaeudes;

			if (artDesGebaeudes != 1 && artDesGebaeudes != 2 && artDesGebaeudes != 3) {
				cout << "Diese Gebaeudeart gibt es nicht!";
				break;
			}

			cout << "Geben Sie die Laenge des Gebaeudes an: \n";
			cin >> laengeGebaeude;

			cout << "Geben Sie die Bereite des Gebaeudes an: \n";
			cin >> breiteGebaeude;

			cout << "Geben Sie die Gewuenschte Position ein: (In Koordinaten)\n";
			cout << "Position 1: \n";	//X
			cin >> pos1;

			cout << "Position 2: \n";	//Y
			cin >> pos2;

			if ((capycity->kollidiert(laengeGebaeude, breiteGebaeude, pos1, pos2, plaene[anzahlPlaene], laengen[anzahlPlaene], breiten[anzahlPlaene])) == true) {
				cout << "Kollidiert mit vorhandenem Gebaeude! \n";
			}
			else if (artDesGebaeudes == 1) {
				Wasserkraftwerk wa(10000, 56000000, "WA", matWA);
				gebaeude[wieVieleGebaeude] = wa;
				capycity->gebaudeAnlegen(laengeGebaeude, breiteGebaeude, pos1, pos2, plaene[anzahlPlaene], laengen[anzahlPlaene], 1);
				wieVieleGebaeude++;
				kennzahlen[anzahlPlaene] = bluePrint->berechneKennzahl((laenge * breite), wieVieleGebaeude, wa.getLeistung(), wa.berechneGesamtPreis(wieVieleGebaeude, wa, h, m, k));
			}
			else if (artDesGebaeudes == 2) {
				Windkraftwerk wi(5000, 15000000, "WI", matWI);
				gebaeude[wieVieleGebaeude] = wi;
				capycity->gebaudeAnlegen(laengeGebaeude, breiteGebaeude, pos1, pos2, plaene[anzahlPlaene], laengen[anzahlPlaene], 2);
				wieVieleGebaeude++;
				kennzahlen[anzahlPlaene] = bluePrint->berechneKennzahl((laenge * breite), wieVieleGebaeude, wi.getLeistung(), wi.berechneGesamtPreis(wieVieleGebaeude, wi, h, m, k));
			}
			else if (artDesGebaeudes == 3) {
				Solarpanel sp(1000, 5000000, "SP", matSP);
				gebaeude[wieVieleGebaeude] = sp;
				capycity->gebaudeAnlegen(laengeGebaeude, breiteGebaeude, pos1, pos2, plaene[anzahlPlaene], laengen[anzahlPlaene], 3);
				wieVieleGebaeude++;
				kennzahlen[anzahlPlaene] = bluePrint->berechneKennzahl((laenge * breite), wieVieleGebaeude, sp.getLeistung(), sp.berechneGesamtPreis(wieVieleGebaeude, sp, h, m, k));
			}
			else {
				cout << "Diese Gebaeudeart gibt es nicht!";
			}

			gebaeudeJePlan[anzahlPlaene] = gebaeude;

		}
		else if (status == 2)
		{
			int position1, position2, flaechenLaenge, flaechenBreite;

			cout << "Geben Sie die Position der zu verkleinernden Flaeche an: \n";
			cout << "Postion 1: \n";
			cin >> position1;
			cout << "Position 2: \n";
			cin >> position2;

			cout << "Geben Sie die neue Laenge der freizugebenden Flaeche ein : \n";
			cin >> flaechenLaenge;
			cout << "Geben Sie die neue Breite der freizugebenden Flaeche ein: \n";
			cin >> flaechenBreite;

			capycity->flaecheFreigeben(flaechenLaenge, flaechenBreite, position1, position2, plaene[anzahlPlaene], laengen[anzahlPlaene]);

		}
		else if (status == 3)
		{
			bluePrint->print(laengen[anzahlPlaene], breiten[anzahlPlaene], plaene[anzahlPlaene]);
		}
		else if (status == 4) {

			int gesamtPreis = 0, gesamteLeistung = 0;
			Building* gebaeudeVonAktuellemPlan = gebaeudeJePlan[anzahlPlaene];

			cout << "Auflistung der Gebaeude: \n \n";


			for (int i = 0; i < wieVieleGebaeude; i++) {

				map<string, int> gebaeudeMats;
				Building aktGebaeude = gebaeudeVonAktuellemPlan[i];
				int gebaeudePreis = aktGebaeude.getGrundpreis();

				if (aktGebaeude.getLabel() == "") {
					cout << "";
				}
				else {

					gebaeudeMats = aktGebaeude.getMat();

					map<string, int>::iterator it = gebaeudeMats.begin();

					cout << "Gebaeude " << aktGebaeude.getLabel() << "\n";
					cout << "Grundpreis: " << aktGebaeude.getGrundpreis() << "\n";
					cout << "Leistung: " << aktGebaeude.getLeistung() / 100000 << " MW " << "\n";
					cout << "Benoetigtes Material: \n";
					while (it != gebaeudeMats.end()) {
						cout << it->first << ": " << it->second << "\n";
						++it;
					}

					cout << "\n";
					cout << "Gesamtpreis: " << capyBuilding->berechneGesamtPreis(wieVieleGebaeude, aktGebaeude, h, m, k) << "\n";

					gesamtPreis += capyBuilding->berechneGesamtPreis(wieVieleGebaeude, aktGebaeude, h, m, k);
					gesamteLeistung += aktGebaeude.getLeistung();

					cout << "\n";
				}
			}


			cout << "\n";
			cout << "Gesamtpreis der Bauflaeche: " << gesamtPreis << "\n";

			if (gesamteLeistung == 0 || gesamtPreis == 0) {
				cout << "Kennzahl des Plans nicht berechenbar! \n\n";
			}
			else {
				cout << "Kennzahl dieses Plans: " << bluePrint->berechneKennzahl((laenge * breite), wieVieleGebaeude, gesamteLeistung, gesamtPreis) << "\n \n";
				kennzahlen[anzahlPlaene] = bluePrint->berechneKennzahl((laenge * breite), wieVieleGebaeude, gesamteLeistung, gesamtPreis);
			}
		}
		else if (status == 5)
		{
			int neueLaenge = 0, neueBreite = 0;

			cout << "Geben Sie die Laenge des Baubereichs ein: \n";
			cin >> neueLaenge;
			cout << "Geben Sie die Breite des Baubereichs ein: \n";
			cin >> neueBreite;

			int size = neueLaenge * neueBreite;
			Building* neueBuilding = new Building[size]{};
			gebaeude[anzahlPlaene] = {};

			int* neueFlaeche = bluePrint->flaecheErstellen(neueLaenge, neueBreite);

			anzahlPlaene++;

			laengen[anzahlPlaene] = neueLaenge;
			breiten[anzahlPlaene] = neueBreite;
			plaene[anzahlPlaene] = neueFlaeche;
			gebaeudeJePlan[anzahlPlaene] = neueBuilding;
		}
		else if (status == 6) {
			if (plaene.size() >= 2) {
				auto sortierungKennzahlen = [](map<int, int> knZl) ->vector<pair<int, int>> {
					vector<pair<int, int>> temp1;

					for (auto& i : knZl) {
						temp1.push_back(i);
					}

					sort(temp1.begin(), temp1.end(),
						[](const pair<int, int>& lhs, const pair<int, int>& rhs) {
							return lhs.second < rhs.second; });

					vector<pair<int, int>> result;

					for (auto& i2 : temp1) {
						result.push_back(i2);
					}

					return result;


				};


				vector<pair<int, int>> sortKennzahlen = sortierungKennzahlen(kennzahlen);

				for (auto i : sortKennzahlen) {
					bluePrint->print(laengen[i.first], breiten[i.first], plaene[i.first]);
					cout << "Kennzahl: " << i.second << "\n \n";
				}
			}
			else {
				cout << "Nur ein Plan vorhanden! \n";
			}
		}
		else if (status == 7) {
			return 0;
		}
		else
		{
			cout << "False Auswahl!\n";
		}
	}
}






