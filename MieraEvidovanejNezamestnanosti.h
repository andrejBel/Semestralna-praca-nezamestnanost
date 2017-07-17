#pragma once
#include "structures\heap_monitor.h"

class MieraEvidovanejNezamestnanosti
{
private:
	int rok_;
	double percentaSpolu_;
	double percentaMuzi_;
	double percentaZeny_;

public:
	MieraEvidovanejNezamestnanosti(int rok, double percentaSpolu, double percentaMuzi, double percentaZeny);
	int getRok() const;
	double getPercentaSpolu() const;
	double getPercentaMuzi() const;
	double getPercentaZeny() const;
};

