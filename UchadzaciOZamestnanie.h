#pragma once
#include <string>
#include <iostream>
#include "structures\heap_monitor.h"

using namespace std;
class UchadzaciOZamestnanie
{
private:
	int rok_;
	int pocetUchadzacovZoZP_;
	int pocetUchadzacovAbsolventi_;
	int pocetUchadzacovMladistvi_;
	int pocetDlhodoboEvidovanychUchadzacov_;
public:
	UchadzaciOZamestnanie(int rok,int pocetUchadzacovZoZP,int pocetUchadzacovAbsolventi,int pocetUchadzacovMladistvi,int pocetDlhodoboEvidovanychUchadzacov);
	int getRok() const;
	int getPocetUchadzacovZoZP() const;
	int getPocetUchadzacovAbsolventi() const;
	int getPocetUchadzacovMladistvi() const;
	int getPocetDlhodoboEvidovanychUchadzacov() const;
	string toString() const;

};

