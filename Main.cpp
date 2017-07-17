#include "structures\heap_monitor.h"
#include "structures\table\sorted_sequence_table.h"
#include <string>
#include <iostream>
#include <fstream>
#include "Statistika.h"
#include <ctime>
//#include <vld.h>


void vypisHlavneMenu();
void vypisOdvetvia();
void nacitajCislo(int& cislo, string chybovaHlaska);

int main()
{
	initHeapMonitor();
	srand(static_cast<unsigned int>(time(0)));
	using namespace std;
	Statistika* statistika = new Statistika();
	if (!statistika->nacitajUdaje()) 
	{
		delete statistika;
		return -1;
	}
	string volba;
	string buffer1;
	string buffer2;
	string buffer3;
	int volbaCislo(0);
	do
	{
		vypisHlavneMenu();
		cout << "Volba: ";
		getline(cin, volba);
		try
		{
			volbaCislo = stoi(volba);
		}
		catch (exception&)
		{
			volbaCislo = -1;
		}
		switch (volbaCislo) 
		{
		case 0: 
		{
			cout << "Dovidenia!" << endl;
			break;
		}
		case 1: 
		{
			cout << "**Vyhladanie okresu na zaklade jeho nazvu a zobrazenie statistik o nom pre rozpatie rokov**\n";
			cout << "Zadajte nazov okresu:\n";
			getline(cin, buffer1);
			cout << "Zadajte zaciatocny rok, pre ktory chcete zobrazit statistiku:\n";
			int zaciatocnyRok(0);
			nacitajCislo(zaciatocnyRok, "Nespravne zadany rok! Zadajte ho prosim znova: \n");
			cout << "Zadajte koncovy rok, pre ktory chcete zobrazit statistiku:\n";
			int koncovyRok(0);
			nacitajCislo(koncovyRok, "Nespravne zadany rok! Zadajte ho prosim znova: \n");

			statistika->vyhladajInformacieOOkrese(buffer1, zaciatocnyRok, koncovyRok);
			break;
		}
		case 2:
		{
			cout << "**Zoradenie okresov v danom roku na zaklade spolocnych udajov pre muzov a zeny podla:\n"
			  	 << "	- miery evidovanej nezamestnanosti v %\n"
				 << "	- disponibilneho poctu uchadzacov o zamestnanie**\n";
			cout << "Zadajte rok, pre ktory sa maju okresy zotriedit\n";
			int rok(0);
			nacitajCislo(rok, "Nespravne zadany rok! Zadajte ho prosim znova: \n");
			cout << "Zelate si data zoradit vzostupne alebo vzostupne alebo zostupne?\n";
			cout << "v pre vzostupne, inak zostupne\n";
			getline(cin, buffer1);
			bool vzostupne(false);
			if (buffer1[0] == 'v' || buffer1[0] == 'V')
			{
				vzostupne = true;
			}
			statistika->utriedOkresyPodlaMieryNezamestnanostiAPoctuUchadzacovoZamestnanie(rok, vzostupne);
			break;
		}
		case 3:
		{
			cout << "**Vyhladanie okresov, ktore mali v danom rozpati rokov:\n"
				<< "	-najvacsi a najmensi priemerny pocet ekonomicky aktivneho obyvatelstva\n"
				<< "	-najvacsi pokles miery evidovanej nezamestnanosti osobitne pre muzov a pre zeny\n"
				<< "	-najlepsi pomer medzi disponibilnym poctom uchadzacov o zamestnanie a poctom uchadzacov z radov absolventov**\n";
			cout << "Zadajte zaciatocny rok, pre ktory chcete zobrazit statistiku:\n";
			int zaciatocnyRok(0);
			nacitajCislo(zaciatocnyRok, "Nespravne zadany rok! Zadajte ho prosim znova: \n");
			cout << "Zadajte koncovy rok, pre ktory chcete zobrazit statistiku:\n";
			int koncovyRok(0);
			nacitajCislo(koncovyRok, "Nespravne zadany rok! Zadajte ho prosim znova: \n");

			statistika->komplexnaStatistikaOkresov(zaciatocnyRok, koncovyRok);
			break;
		}
		case 4:
		{
			cout << "**Vyhladanie kraja na zaklade jeho nazvu a zobrazenie sumarnych statistik o nom pre rozpatie rokov**\n";
			cout << "Zadajte nazov kraja:\n";
			getline(cin, buffer1);
			cout << "Zadajte zaciatocny rok, pre ktory chcete zobrazit statistiku:\n";
			int zaciatocnyRok(0);
			nacitajCislo(zaciatocnyRok, "Nespravne zadany rok! Zadajte ho prosim znova: \n");
			cout << "Zadajte koncovy rok, pre ktory chcete zobrazit statistiku:\n";
			int koncovyRok(0);
			nacitajCislo(koncovyRok, "Nespravne zadany rok! Zadajte ho prosim znova: \n");

			statistika->vyhladajInformacieOKraji(buffer1, zaciatocnyRok, koncovyRok);
			break;
		}
		case 5:
		{
			cout << "**Zoradenie krajov v danom roku na zaklade spolocnych udajov pre muzov a zeny podla:\n"
				<< "	- miery evidovanej nezamestnanosti v %\n"
				<< "	- disponibilneho poctu uchadzacov o zamestnanie**\n";
			cout << "Zadajte rok, pre ktory sa maju kraje zotriedit\n";
			int rok(0);
			nacitajCislo(rok, "Nespravne zadany rok! Zadajte ho prosim znova:\n");
			cout << "Zelate si data zoradit vzostupne alebo vzostupne alebo zostupne?\n";
			cout << "v pre vzostupne, inak zostupne\n";
			getline(cin, buffer1);
			bool vzostupne(false);
			if (buffer1[0] == 'v' || buffer1[0] == 'V')
			{
				vzostupne = true;
			}
			statistika->utriedKrajePodlaMieryNezamestnanostiAPoctuUchadzacovoZamestnanie(rok, vzostupne);
			break;
		}
		case 6:
		{
			cout << "**Vyhladanie krajov, ktore mali v danom rozpati rokov:\n"
				<< "	-najvacsi a najmensi priemerny pocet ekonomicky aktivneho obyvatelstva\n"
				<< "	-najvacsi pokles miery evidovanej nezamestnanosti osobitne pre muzov a pre zeny\n"
				<< "	-najlepsi pomer medzi disponibilnym poctom uchadzacov o zamestnanie a poctom uchadzacov z radov absolventov**\n";
			cout << "Zadajte zaciatocny rok, pre ktory chcete zobrazit statistiku:\n";
			int zaciatocnyRok(0);
			nacitajCislo(zaciatocnyRok, "Nespravne zadany rok! Zadajte ho prosim znova:\n");
			cout << "Zadajte koncovy rok, pre ktory chcete zobrazit statistiku:\n";
			int koncovyRok(0);
			nacitajCislo(koncovyRok, "Nespravne zadany rok! Zadajte ho prosim znova:\n");
			statistika->komplexnaStatistikaKrajov(zaciatocnyRok, koncovyRok);
			break;
		}
		case 7:
		{
			cout << "Zoradenie okresov v danom rozpati rokov podla:\n"
				<< "	-priemernej nominalnej mesacnej mzdy zamestnanca v odvetvii\n**";
			cout << "Zadajte zaciatocny rok, pre ktory sa maju okresy zotriedit:\n";
			int zaciatocnyRok(0);
			nacitajCislo(zaciatocnyRok, "Nespravne zadany rok! Zadajte ho prosim znova: \n");
			cout << "Zadajte koncovy rok, pre ktory sa maju okresy zotriedit:\n";
			int koncovyRok(0);
			nacitajCislo(koncovyRok, "Nespravne zadany rok! Zadajte ho prosim znova: \n");
			cout << "Zelate si data zoradit vzostupne alebo vzostupne alebo zostupne?\n";
			cout << "v pre vzostupne, inak zostupne\n";
			getline(cin, buffer1);
			bool vzostupne(false);
			if (buffer1[0] == 'v' || buffer1[0] == 'V')
			{
				vzostupne = true;
			}
			cout << "Vyberte si odvetvie, podla ktoreho chcete data utriedit\n";
			vypisOdvetvia();
			int cisloOdvetvia(0);
			cout << "Cislo odvetvia\n";
			nacitajCislo(cisloOdvetvia, "Nespravne zadane odvetvie! Zadajte ho prosim znova: \n");
			statistika->utriedOkresyPodlaPriemerneMesacnejMzdyZamestnancaVOdvetvi(cisloOdvetvia, zaciatocnyRok, koncovyRok, vzostupne);
			break;
		}
		case 8: 
		{
			cout << "**Vypis krajov a ich okresov**\n";
			statistika->vypisKrajeAIchOkresy();
			break;
		}
		default: 
		{
			cout << "Bola zadana nespravna volba\n";
			break;
		}
		}

	} while (volbaCislo != 0);

	delete statistika;
	return 0;
}

void vypisHlavneMenu()
{
	system("pause");
	cout << "0 - Ukoncenie\n";
	cout << "1 - Vyhladanie okresu na zaklade jeho nazvu a zobrazenie statistik o nom\n";
	cout << "2 - Zoradenie okresov na zaklade spolocnych udajov pre zeny a muzov\n";
	cout << "3 - Najdenie okresu podla specifickych charakteristik\n";
	cout << "4 - Vyhladanie kraju na zaklade jeho nazvu a zobrazenie sumarnych statistik o nom\n";
	cout << "5 - Zoradenie krajov na zaklade spolocnych udajov pre zeny a muzov\n";
	cout << "6 - Najdenie kraju podla specifickych charakteristik\n";
	cout << "7 - Zoradenie okresov podla priemernej nominalnej mesacnej mzdy zamestnanca v odvetvii\n";
	cout << "8 - Vypis krajov a ich okresov\n";
}

void vypisOdvetvia()
{
	cout << "Odvetvia:\n";
	cout << "1 - Spolu\n";
	cout << "2 - Polnohospodarstvo,lesnictvo a rybolov\n";
	cout << "3 - Priemysel spolu\n";
	cout << "4 - Tazba a dobyvanie\n";
	cout << "5 - Priemyselna vyroba\n";
	cout << "6 - Dodavka elektriny, plynu, pary a studeneho vzduchu\n";
	cout << "7 - Dodavka vody;cistenie a odvod odpadovych vod, odpady a sluzby odstranovania odpadov\n";
	cout << "8 - Stavebnictvo\n";
	cout << "9 - Velkoobchod a maloobchod; oprava motorovych vozidiel a motocyklov\n";
	cout << "10 - Doprava a skladovanie\n";
	cout << "11 - Ubytovacie a stravovacie sluzby\n";
	cout << "12 - Informacie a komunikacia\n";
	cout << "13 - Financne a poistovacie cinnosti\n";
	cout << "14 - Cinnosti v oblasti nehnutelnosti\n";
	cout << "15 - Odborne, vedecke a technicke cinnosti\n";
	cout << "16 - Administrativne a podporne sluzby\n";
	cout << "17 - Verejna sprava a obrana; povinne socialne zabezpecenie\n";
	cout << "18 - Vzdelavanie\n";
	cout << "19 - Zdravotnictvo a socialna pomoc\n";
	cout << "20 - Umenie, zabava a rekreacia\n";
	cout << "21 - Ostatne cinnosti\n";
}

void nacitajCislo(int & cislo, string chybovaHlaska)
{
	string buffer;
	while (true)
	{
		try
		{
			getline(cin, buffer);
			cislo = stoi(buffer);
			break;
		}
		catch (const std::exception&)
		{
			cout << chybovaHlaska;
		}
	}
}





