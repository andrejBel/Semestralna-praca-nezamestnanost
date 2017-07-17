#include "DisponibilnyPocetUchadzacovOZamestnanie.h"

DisponibilnyPocetUchadzacovOZamestnanie::DisponibilnyPocetUchadzacovOZamestnanie(int rok, int pocetMuzi, int pocetZeny) :
	rok_(rok),
	pocetMuzi_(pocetMuzi),
	pocetZeny_(pocetZeny)
{
}

int DisponibilnyPocetUchadzacovOZamestnanie::getRok() const
{
	return rok_;
}

int DisponibilnyPocetUchadzacovOZamestnanie::getPocetSpolu() const
{
	return pocetMuzi_ + pocetZeny_;
}

int DisponibilnyPocetUchadzacovOZamestnanie::getPocetMuzi() const
{
	return pocetMuzi_;
}

int DisponibilnyPocetUchadzacovOZamestnanie::getPocetZeny() const
{
	return pocetZeny_;
}
