#include <iostream>
using namespace std;

// PROBLEM MIT #INCLUDE <VECTOR>
// Kapitel 2 fehlt: Auflistung der Gebaude + Materialien und Einzelpreis + Gesamtpreis

class CapycitySim {

public:
	int* flaecheErstellen(int laenge, int breite);

	bool kollidiert(int laengeGebaeude, int breiteGebaeude, int pos1, int pos2, int* flaeche, int laengeFlaeche, int breiteFlaeche);

	int* gebaudeAnlegen(int laengeGebaeude, int breiteGebaeude, int pos1, int pos2, int* flaeche, int laengeFlaeche, int gebaeudeCode);

	int* flaecheFreigeben(int flaechenLaenge, int flaechenBreite, int position1, int position2, int* flaeche, int laengeFlaeche);

	void print(int laengeFlaeche, int breiteFlaeche, int* flaeche);

	void printAuflistung();

};

int* CapycitySim::flaecheErstellen(int laenge, int breite) {
	int* flaeche = new int[laenge * breite] {0};
	return flaeche;
}

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

void CapycitySim::print(int laengeFlaeche, int breiteFlaeche, int* flaeche) {
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

void CapycitySim::printAuflistung()
{
	printf("Hallo");
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
	string label;
	Material* material;

public:
	Building() = default;
	Building(int gp, string l, Material* mat) : grundpreis(gp), label(l), material{ mat } {}
	int getGrundpreis() {
		return this->grundpreis;
	}
	string getLabel() {
		return this->label;
	}
	Material* getMat() {
		return this->material;

	}
};

class Wasserkraftwerk : public Building {
public:
	Wasserkraftwerk(int gp, string l, Material* mat) : Building(gp, l, mat) {};
};

class Windkraftwerk : public Building {
public:
	Windkraftwerk(int gp, string l, Material* mat) : Building(gp, l, mat) {};
};

class Solarpanel : public Building {
public:
	Solarpanel(int gp, string l, Material* mat) : Building(gp, l, mat) {};
};

int main() {

	CapycitySim* capycity = new CapycitySim();

	Holz h(30, "H");
	Metall m(50, "M");
	Kunststoff k(5, "K");


	Material* matWA = new Material[4]{ h, h, m, k };
	Material* matWI = new Material[4]{ h, m, m, k };
	Material* matSP = new Material[4]{ m, m, k, k };



	int laenge = 0, breite = 0, status = 0, artDesGebaeudes = 0, wieVieleGebaeude = 0;

	cout << "Geben Sie die Laenge des Baubereichs ein: \n";
	cin >> laenge;
	cout << "Geben Sie die Breite des Baubereichs ein: \n";
	cin >> breite;

	int* flaeche = capycity->flaecheErstellen(laenge, breite);

	int size = laenge * breite;
	Building* gebaeude = new Building[size];

	while (status != 5)
	{
		cout << "Menue: \n";
		cout << "Gebaeude setzen: (1) \n";
		cout << "Bereich loeschen: (2)\n";
		cout << "Bauplan ausgeben: (3) \n";
		cout << "Auflistung ausgeben: (4) \n";
		cout << "Programm beenden: (5)\n";
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

			if ((capycity->kollidiert(laengeGebaeude, breiteGebaeude, pos1, pos2, flaeche, laenge, breite)) == true) {
				cout << "Kollidiert mit vorhandenem Gebaeude! \n";
			}
			else if (artDesGebaeudes == 1) {
				Wasserkraftwerk wa(10000, "WA", matWA);
				gebaeude[wieVieleGebaeude] = wa;
				capycity->gebaudeAnlegen(laengeGebaeude, breiteGebaeude, pos1, pos2, flaeche, laenge, 1);
				wieVieleGebaeude++;
			}
			else if (artDesGebaeudes == 2) {
				Windkraftwerk wi(5000, "WI", matWI);
				gebaeude[wieVieleGebaeude] = wi;
				capycity->gebaudeAnlegen(laengeGebaeude, breiteGebaeude, pos1, pos2, flaeche, laenge, 2);
				wieVieleGebaeude++;
			}
			else if (artDesGebaeudes == 3) {
				Solarpanel sp(1000, "SP", matSP);
				gebaeude[wieVieleGebaeude] = sp;
				capycity->gebaudeAnlegen(laengeGebaeude, breiteGebaeude, pos1, pos2, flaeche, laenge, 3);
				wieVieleGebaeude++;
			}
			else {
				cout << "Diese Gebaeudeart gibt es nicht!";
			}

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

			capycity->flaecheFreigeben(flaechenLaenge, flaechenBreite, position1, position2, flaeche, laenge);

		}
		else if (status == 3)
		{
			capycity->print(laenge, breite, flaeche);
		}
		else if (status == 4) {

			int gesamtPreis = 0;

			cout << "Auflistung der Gebaeude: \n \n";

			for (int i = 0; i < wieVieleGebaeude; i++) {
				Material* gebaeudeMats = new Material[4]{};
				Building aktGebaeude = gebaeude[i];
				int gebaeudePreis = aktGebaeude.getGrundpreis();


				gebaeudeMats = aktGebaeude.getMat();
				for (int i2 = 0; i2 < 4; i2++) {
					gebaeudePreis += gebaeudeMats[i2].getPreis();

				}
				cout << "Gebaeude " << aktGebaeude.getLabel() << "\n";
				cout << "Grundpreis: " << aktGebaeude.getGrundpreis() << "\n";
				cout << "Benoetigtes Material: \n";
				for (int i2 = 0; i2 < 4; i2++) {
					if (i2 < 3) {
						cout << aktGebaeude.getMat()[i2].getLabel() << ", ";
					}
					else if (i2 < 4) {
						cout << aktGebaeude.getMat()[i2].getLabel();
					}
				}
				cout << "\n";
				cout << "Gesamtpreis: " << gebaeudePreis << "\n";

				gesamtPreis += gebaeudePreis;

				cout << "\n";

			}

			cout << "\n";
			cout << "Gesamtpreis der Bauflaeche: " << gesamtPreis << "\n \n";

		}
		else if (status == 5)
		{
			return 0;
		}
		else
		{
			cout << "False Auswahl!\n";
		}
	}
}






