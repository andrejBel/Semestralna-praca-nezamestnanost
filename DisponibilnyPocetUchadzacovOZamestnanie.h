#pragma once
#include "structures\heap_monitor.h"

class DisponibilnyPocetUchadzacovOZamestnanie
{
private:
	int rok_;
	int pocetMuzi_;
	int pocetZeny_;


public:
	DisponibilnyPocetUchadzacovOZamestnanie(int rok, int pocetMuzi, int pocetZeny);

	int getRok() const ;
	int getPocetSpolu() const;
	int getPocetMuzi() const;
	int getPocetZeny() const;

};

