#include "EkonimickyAktivneObyvatelstvo.h"

EkonomickyAktivneObyvatelstvo::EkonomickyAktivneObyvatelstvo(int rok, int pocetMuzi, int pocetZeny):
	rok_(rok),
	pocetMuzi_(pocetMuzi),
	pocetZeny_(pocetZeny)
{
}

int EkonomickyAktivneObyvatelstvo::getRok() const
{
	return rok_;
}

int EkonomickyAktivneObyvatelstvo::getPocetSpolu() const
{
	return pocetMuzi_ + pocetZeny_;
}

int EkonomickyAktivneObyvatelstvo::getPocetMuzi() const
{
	return pocetMuzi_;
}

int EkonomickyAktivneObyvatelstvo::getPocetZeny() const
{
	return pocetZeny_;
}
