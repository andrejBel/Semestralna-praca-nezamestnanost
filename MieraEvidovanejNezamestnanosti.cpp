#include "MieraEvidovanejNezamestnanosti.h"

MieraEvidovanejNezamestnanosti::MieraEvidovanejNezamestnanosti(int rok, double percentaSpolu, double percentaMuzi, double percentaZeny):
	rok_(rok),
	percentaSpolu_(percentaSpolu),
	percentaMuzi_(percentaMuzi),
	percentaZeny_(percentaZeny)
{
}

int MieraEvidovanejNezamestnanosti::getRok() const
{
	return rok_;
}

double MieraEvidovanejNezamestnanosti::getPercentaSpolu() const
{
	return percentaSpolu_;
}

double MieraEvidovanejNezamestnanosti::getPercentaMuzi() const
{
	return percentaMuzi_;
}

double MieraEvidovanejNezamestnanosti::getPercentaZeny() const
{
	return percentaZeny_;
}

