#include "UchadzaciOZamestnanie.h"
#include "structures\heap_monitor.h"

UchadzaciOZamestnanie::UchadzaciOZamestnanie(int rok, int pocetUchadzacovZoZP, int pocetUchadzacovAbsolventi, int pocetUchadzacovMladistvi, int pocetDlhodoboEvidovanychUchadzacov) :
	rok_(rok),
	pocetUchadzacovZoZP_(pocetUchadzacovZoZP),
	pocetUchadzacovAbsolventi_(pocetUchadzacovAbsolventi),
	pocetUchadzacovMladistvi_(pocetUchadzacovMladistvi),
	pocetDlhodoboEvidovanychUchadzacov_(pocetDlhodoboEvidovanychUchadzacov)
{
}

int UchadzaciOZamestnanie::getRok() const
{
	return rok_;
}

int UchadzaciOZamestnanie::getPocetUchadzacovZoZP() const
{
	return pocetUchadzacovZoZP_;
}

int UchadzaciOZamestnanie::getPocetUchadzacovAbsolventi() const
{
	return pocetUchadzacovAbsolventi_;
}

int UchadzaciOZamestnanie::getPocetUchadzacovMladistvi() const
{
	return pocetUchadzacovMladistvi_;
}

int UchadzaciOZamestnanie::getPocetDlhodoboEvidovanychUchadzacov() const
{
	return pocetDlhodoboEvidovanychUchadzacov_;
}