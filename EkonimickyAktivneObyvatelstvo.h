#pragma once
#include "structures\heap_monitor.h"
class EkonomickyAktivneObyvatelstvo
{
private:
	int rok_;
	int pocetMuzi_;
	int pocetZeny_;


public:
	EkonomickyAktivneObyvatelstvo(int rok, int pocetMuzi,int pocetZeny);
	
	int getRok() const;
	int getPocetSpolu() const;
	int getPocetMuzi() const;
	int getPocetZeny() const;

};