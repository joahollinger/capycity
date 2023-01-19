#include <iostream>
using namespace std;

int main() {


	int laenge = 0, breite = 0, status = 0, artDesGebaeudes = 0, wieVieleGebaeude = 0;

	cout << "Geben Sie die Laenge des Baubereichs ein: \n";
	cin >> laenge;
	cout << "Geben Sie die Breite des Baubereichs ein: \n";
	cin >> breite;

	int* flaeche = new int[laenge * breite] {0};

	while (status != 4)
	{
		cout << "Menue: \n";
		cout << "Gebaeude setzen: (1) \n";
		cout << "Bereich loeschen: (2)\n";
		cout << "Bauplan ausgeben: (3) \n";
		cout << "Programm beenden: (4)\n";
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

			bool kollidiert = false;

			if (pos1 >= laenge || pos2 >= breite) {
				kollidiert = true;
			}
			else if (laengeGebaeude > laenge || breiteGebaeude > breite) {
				kollidiert = true;
			}
			else {
				for (int restL = 0; restL < laengeGebaeude; ++restL) {
					for (int restB = 0; restB < breiteGebaeude; ++restB) {
						if (flaeche[(restB + pos2) * laenge + (restL + pos1)] == 1 || flaeche[(restB + pos2) * laenge + (restL + pos1)] == 2 || flaeche[(restB + pos2) * laenge + (restL + pos1)] == 3) {
							kollidiert = true;
							break;
						}
						else if ((restB + pos2) * laenge + (restL + pos1) > laenge * breite) {
							kollidiert = true;
						}
						else {
							kollidiert = false;
						}
					}
				}
			}
			
			if (artDesGebaeudes == 1) {
				for (int restL = 0; restL < laengeGebaeude; ++restL) {
					for (int restB = 0; restB < breiteGebaeude; ++restB) {
						flaeche[(restB + pos2) * laenge + (restL + pos1)] = { 1 };
					}
				}
			}
			else if (artDesGebaeudes == 2) {
				for (int restL = 0; restL < laengeGebaeude; ++restL) {
					for (int restB = 0; restB < breiteGebaeude; ++restB) {
						flaeche[(restB + pos2) * laenge + (restL + pos1)] = { 2 };
					}
				}
			}
			else if (artDesGebaeudes == 3) {
				for (int restL = 0; restL < laengeGebaeude; ++restL) {
					for (int restB = 0; restB < breiteGebaeude; ++restB) {
						flaeche[(restB + pos2) * laenge + (restL + pos1)] = { 3 };
					}
				}
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

			for (int restL = 0; restL < flaechenLaenge; ++restL) {
				for (int restB = 0; restB < flaechenBreite; ++restB) {
					flaeche[(restB + position2) * laenge + (restL + position1)] = { 0 };
				}
			}

		}
		else if (status == 3)
		{
			for (int tmp = 0; tmp < laenge; tmp++)
			{
				for (int tmp2 = 0; tmp2 < breite; tmp2++)
				{
					if (flaeche[tmp2 * laenge + tmp] == 0)
					{
						printf("|    |");
					}
					else if (flaeche[tmp2 * laenge + tmp] == 1)
					{
						printf("| WA |");
					}
					else if (flaeche[tmp2 * laenge + tmp] == 2)
					{
						printf("| WI |");
					}
					else if (flaeche[tmp2 * laenge + tmp] == 3)
					{
						printf("| SP |");
					}
				}
				printf("\n");
				printf("\n");
			}
		}
		else if (status == 4)
		{
			return 0;
		}
		else
		{
			cout << "False Auswahl!\n";
		}
	}
}






