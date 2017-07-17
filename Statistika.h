#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "structures\heap_monitor.h"

#include "structures\table\treap.h"
#include "structures\table\sorting\heap_sort.h"
#include "structures\table\unsorted_sequence_table.h"
#include "structures\table\sorting\merge_sort.h"
#include "Okres.h"
#include "Kraj.h"
using namespace structures;
using namespace std;


class Statistika
{
private:
	Table<string, Okres *>* okresy_;
	UnsortedSequenceTable<string, Okres *>* okresySortable_;
	Sort<string, Okres *>* sortPreOkresy_;
	Table<string, Kraj *>* kraje_;
	UnsortedSequenceTable<string, Kraj *>* krajeSortable_;
	Sort< string, Kraj *>* sortPreKraje_;

	void split(const string & text, char sep, vector<string>& tokens);

public:
	Statistika();
	bool nacitajUdaje();
	void vyhladajInformacieOOkrese(const string& nazov, int zaciatocnyRok, int koncovyRok);
	void utriedOkresyPodlaMieryNezamestnanostiAPoctuUchadzacovoZamestnanie(int rok, bool vzostupne);
	void vyhladajInformacieOKraji(const string& nazovKraja, int zaciatocnyRok, int koncovyRok);
	void utriedKrajePodlaMieryNezamestnanostiAPoctuUchadzacovoZamestnanie(int rok, bool vzostupne);
	void utriedOkresyPodlaPriemerneMesacnejMzdyZamestnancaVOdvetvi(int cisloOdvetvia, int zaciatocnyRok, int koncovyRok, bool vzostupne);
	void komplexnaStatistikaOkresov(int zaciatocnyRok, int koncovyRok);
	void komplexnaStatistikaKrajov(int zaciatocnyRok, int koncovyRok);
	void vypisKrajeAIchOkresy();
	~Statistika();
};

