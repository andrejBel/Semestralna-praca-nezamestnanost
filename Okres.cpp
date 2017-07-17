#include "Okres.h"
#include "structures\heap_monitor.h"

Okres::Okres(const string & nazovOkresu):
	nazovOkresu_(nazovOkresu),
	informacieOUchadzacochOZamestnanie_(new Array<UchadzaciOZamestnanie *>(Okres::pocetRokovPrePoctyZamestnancov)),
	informacieOMiereEvidovanejNezamestnanosti_(new Array<MieraEvidovanejNezamestnanosti *>(Okres::pocetRokovPrePoctyZamestnancov)),
	informacieOEkonomickyAktivnomObyvatelstve_(new Array<EkonomickyAktivneObyvatelstvo *>(Okres::pocetRokovPrePoctyZamestnancov)),
	informacieODisponibilnomPocteUchadzacovOZamestnanie_(new Array<DisponibilnyPocetUchadzacovOZamestnanie *>(Okres::pocetRokovPrePoctyZamestnancov)),
	statistikaOdvetvii_(new Array<Array<int>*>(Okres::pocetOdvetvii))
{
}

void Okres::pridajInformaciuOUchadzacochOZamestnanie(int rok, int pocetUchadzacovZoZP, int pocetUchadzacovAbsolventi, int pocetUchadzacovMladistvi, int pocetDlhodoboEvidovanychUchadzacov)
{
	if (Okres::overPlatnostRokaPrePoctyZamestnancov(rok))
	{
		int indexVPoli = rok - Okres::zaciatocnyRokPreUchadzacov;
		if ((*informacieOUchadzacochOZamestnanie_)[indexVPoli])
		{
			delete (*informacieOUchadzacochOZamestnanie_)[indexVPoli];
		}
		(*informacieOUchadzacochOZamestnanie_)[indexVPoli] = new UchadzaciOZamestnanie(rok, pocetUchadzacovZoZP, pocetUchadzacovAbsolventi, pocetUchadzacovMladistvi, pocetDlhodoboEvidovanychUchadzacov);
	}
}

void Okres::pridajInformaciuOMiereEvidovanejNezamestnanosti(int rok, double percentaSpolu, double percentaMuzi, double percentaZeny)
{
	if (Okres::overPlatnostRokaPrePoctyZamestnancov(rok))
	{
		int indexVPoli = rok - Okres::zaciatocnyRokPreUchadzacov;
		if ((*informacieOMiereEvidovanejNezamestnanosti_)[indexVPoli])
		{
			delete (*informacieOMiereEvidovanejNezamestnanosti_)[indexVPoli];
		}
		(*informacieOMiereEvidovanejNezamestnanosti_)[indexVPoli] = new MieraEvidovanejNezamestnanosti(rok, percentaSpolu, percentaMuzi, percentaZeny);
	}
}

void Okres::pridajInformaciuOEkonomickyAktivnomObyvatelstve(int rok, int pocetMuzi, int pocetZeny)
{
	if (Okres::overPlatnostRokaPrePoctyZamestnancov(rok))
	{
		int indexVPoli = rok - Okres::zaciatocnyRokPreUchadzacov;
		if ((*informacieOEkonomickyAktivnomObyvatelstve_)[indexVPoli])
		{
			delete (*informacieOEkonomickyAktivnomObyvatelstve_)[indexVPoli];
		}
		(*informacieOEkonomickyAktivnomObyvatelstve_)[indexVPoli] = new EkonomickyAktivneObyvatelstvo(rok, pocetMuzi, pocetZeny);
	}
}

void Okres::pridajInformaciuODisponibilnomPocteUchadzacovOZamestnanie(int rok, int pocetMuzi, int pocetZeny)
{
	if (Okres::overPlatnostRokaPrePoctyZamestnancov(rok))
	{
		int indexVPoli = rok - Okres::zaciatocnyRokPreUchadzacov;
		if ((*informacieODisponibilnomPocteUchadzacovOZamestnanie_)[indexVPoli])
		{
			delete (*informacieODisponibilnomPocteUchadzacovOZamestnanie_)[indexVPoli];
		}
		(*informacieODisponibilnomPocteUchadzacovOZamestnanie_)[indexVPoli] = new DisponibilnyPocetUchadzacovOZamestnanie(rok, pocetMuzi, pocetZeny);
	}
}

void Okres::pridajInformaciuOOdvetvii(int cisloOdvetvia, Array<int>* udaje)
{
	if (cisloOdvetvia >= 1 && cisloOdvetvia <= Okres::pocetOdvetvii && udaje)
	{
		if ((*statistikaOdvetvii_)[cisloOdvetvia - 1])
		{
			delete (*statistikaOdvetvii_)[cisloOdvetvia - 1];
		}
		(*statistikaOdvetvii_)[cisloOdvetvia - 1] = udaje;
	}
}


void Okres::vypisInformacieOUchadzacoch(int zaciatocnyRok, int koncovyRok) const
{
	if (!Okres::overPlatnostRokaPrePoctyZamestnancov(zaciatocnyRok) || !Okres::overPlatnostRokaPrePoctyZamestnancov(koncovyRok) || zaciatocnyRok > koncovyRok)
	{
		cout << "Nespravne zadane roky" << endl;
		return;
	}
	int pocetZdravotnePostihnutych(0);
	int pocetAbsolventov(0);
	int pocetMladistvych(0);
	int pocetDlhodoboEvidovanych(0);
	cout << "Okres " << nazovOkresu_ << ":" << endl;
	for (int i = zaciatocnyRok; i <= koncovyRok; i++)
	{
		UchadzaciOZamestnanie* uchadadzi = (*informacieOUchadzacochOZamestnanie_)[i - Okres::zaciatocnyRokPreUchadzacov];
		if (uchadadzi)
		{
			cout << "Rok: " << i << endl;
			pocetZdravotnePostihnutych += uchadadzi->getPocetUchadzacovZoZP();
			pocetAbsolventov += uchadadzi->getPocetUchadzacovAbsolventi();
			pocetMladistvych += uchadadzi->getPocetUchadzacovMladistvi();
			pocetDlhodoboEvidovanych += uchadadzi->getPocetDlhodoboEvidovanychUchadzacov();
			cout << "	Pocet uchadzacov z radu zdravotne postihnutych: " << pocetZdravotnePostihnutych << "\n";
			cout << "	Pocet uchadzacov z radu absolventov:            " << pocetAbsolventov << "\n";
			cout << "	Pocet uchadzacov z radu mladistvych:            " << pocetMladistvych << "\n";
			cout << "	Pocet uchadzacov z radu dlhodobo evidovanych:   " << pocetDlhodoboEvidovanych << "\n";
			pocetZdravotnePostihnutych = 0;
			pocetAbsolventov = 0;
			pocetMladistvych = 0;
			pocetDlhodoboEvidovanych = 0;
		}
	}
}

const UchadzaciOZamestnanie* Okres::getInformaciaOUchadzacochOZamestnanie(int rok) const
{
	if (Okres::overPlatnostRokaPrePoctyZamestnancov(rok))
	{
		return (*informacieOUchadzacochOZamestnanie_)[rok - Okres::zaciatocnyRokPreUchadzacov];
	}
	return 0;
}

const MieraEvidovanejNezamestnanosti * Okres::getInformaciaOMiereEvidovanejNezamestnanosti(int rok) const
{
	if (Okres::overPlatnostRokaPrePoctyZamestnancov(rok))
	{
		return (*informacieOMiereEvidovanejNezamestnanosti_)[rok - Okres::zaciatocnyRokPreUchadzacov];
	}
	return 0;
}

const DisponibilnyPocetUchadzacovOZamestnanie * Okres::getInformacieODisponibilnomPocteUchadzacovOZamestnanie(int rok) const
{
	if (Okres::overPlatnostRokaPrePoctyZamestnancov(rok))
	{
		return (*informacieODisponibilnomPocteUchadzacovOZamestnanie_)[rok - Okres::zaciatocnyRokPreUchadzacov];
	}
	return 0;
}

const EkonomickyAktivneObyvatelstvo * Okres::getInformacieOEkonomickyAktivnomObyvatelstve(int rok) const
{
	if (Okres::overPlatnostRokaPrePoctyZamestnancov(rok))
	{
		return (*informacieOEkonomickyAktivnomObyvatelstve_)[rok - Okres::zaciatocnyRokPreUchadzacov];
	}
	return 0;
}

const double Okres::getPriemernaMesacnaMzdaZamestnancaVOdvetviiZaObdobie(int cisloOdvetvia, int zaciatocnyRok, int koncovyRok)
{
	if (!Okres::overPlatnostRokaPreMzdyZamestnancov(zaciatocnyRok) || !Okres::overPlatnostRokaPreMzdyZamestnancov(koncovyRok) || zaciatocnyRok > koncovyRok)
	{
		cout << "Nespravne zadane roky!!!\n";
		return 0.0;
	}
	if (cisloOdvetvia <= 0 || cisloOdvetvia > Okres::pocetOdvetvii)
	{
		cout << "Nespravne obdobie!!!";
		return 0.0;
	}
	double sumaPriemernejMzdy(0);
	for (int i = zaciatocnyRok; i <= koncovyRok; i++)
	{
		sumaPriemernejMzdy += (*(*statistikaOdvetvii_)[cisloOdvetvia - 1])[i - Okres::zaciatocnyRokPreMzdy];
	}
	return sumaPriemernejMzdy / (koncovyRok - zaciatocnyRok + 1);
}

const double Okres::getPriemernyPocetEkonomickyAktivnehoObyvatelstva(int zaciatocnyRok, int koncovyRok)
{
	if (!Okres::overPlatnostRokaPrePoctyZamestnancov(zaciatocnyRok) || !Okres::overPlatnostRokaPrePoctyZamestnancov(koncovyRok) || zaciatocnyRok > koncovyRok)
	{
		cout << "Nespravne zadane roky" << endl;
		return 0.0;
	}
	double vysledok(0);
	for (int i = zaciatocnyRok; i <= koncovyRok; i++)
	{
		if ((*informacieOEkonomickyAktivnomObyvatelstve_)[i - Okres::zaciatocnyRokPreUchadzacov])
		{
			vysledok += (*informacieOEkonomickyAktivnomObyvatelstve_)[i - Okres::zaciatocnyRokPreUchadzacov]->getPocetSpolu();
		}
	}
	return vysledok / (koncovyRok - zaciatocnyRok + 1);
}

const double Okres::getRozdielMieryEvidovanejNezamestnanostiPreMuzov(int zaciatocnyRok, int koncovyRok)
{
	if (!Okres::overPlatnostRokaPrePoctyZamestnancov(zaciatocnyRok) || !Okres::overPlatnostRokaPrePoctyZamestnancov(koncovyRok) || zaciatocnyRok > koncovyRok)
	{
		cout << "Nespravne zadane roky" << endl;
		return 0.0;
	}
	double vysledok(0);
	
	if ((*informacieOMiereEvidovanejNezamestnanosti_)[zaciatocnyRok - Okres::zaciatocnyRokPreUchadzacov])
	{
		vysledok = (*informacieOMiereEvidovanejNezamestnanosti_)[zaciatocnyRok - Okres::zaciatocnyRokPreUchadzacov]->getPercentaMuzi();
	}
	if ((*informacieOMiereEvidovanejNezamestnanosti_)[koncovyRok - Okres::zaciatocnyRokPreUchadzacov])
	{
		vysledok -= (*informacieOMiereEvidovanejNezamestnanosti_)[koncovyRok - Okres::zaciatocnyRokPreUchadzacov]->getPercentaMuzi();
	}
	return vysledok;
}

const double Okres::getRozdielMieryEvidovanejNezamestnanostiPreZeny(int zaciatocnyRok, int koncovyRok)
{
	if (!Okres::overPlatnostRokaPrePoctyZamestnancov(zaciatocnyRok) || !Okres::overPlatnostRokaPrePoctyZamestnancov(koncovyRok) || zaciatocnyRok > koncovyRok)
	{
		cout << "Nespravne zadane roky" << endl;
		return 0.0;
	}
	double vysledok(0);
	if ((*informacieOMiereEvidovanejNezamestnanosti_)[zaciatocnyRok - Okres::zaciatocnyRokPreUchadzacov])
	{
		vysledok = (*informacieOMiereEvidovanejNezamestnanosti_)[zaciatocnyRok - Okres::zaciatocnyRokPreUchadzacov]->getPercentaZeny();
	}
	if ((*informacieOMiereEvidovanejNezamestnanosti_)[koncovyRok - Okres::zaciatocnyRokPreUchadzacov])
	{
		vysledok -= (*informacieOMiereEvidovanejNezamestnanosti_)[koncovyRok - Okres::zaciatocnyRokPreUchadzacov]->getPercentaZeny();
	}
	return vysledok;
}

const double Okres::getPomerMedziDisponibilnymPoctomUchadzacovOZamestnanieAUchadzacovZAbsolventov(int zaciatocnyRok, int koncovyRok)
{
	if (!Okres::overPlatnostRokaPrePoctyZamestnancov(zaciatocnyRok) || !Okres::overPlatnostRokaPrePoctyZamestnancov(koncovyRok) || zaciatocnyRok > koncovyRok)
	{
		cout << "Nespravne zadane roky" << endl;
		return 0.0;
	}
	double vysledok(0);
	for (int i = zaciatocnyRok; i <= koncovyRok; i++)
	{
		if ((*informacieODisponibilnomPocteUchadzacovOZamestnanie_)[i - Okres::zaciatocnyRokPreUchadzacov] && (*informacieOUchadzacochOZamestnanie_)[i - Okres::zaciatocnyRokPreUchadzacov])
		{
			if ((*informacieODisponibilnomPocteUchadzacovOZamestnanie_)[i - Okres::zaciatocnyRokPreUchadzacov]->getPocetSpolu() && (*informacieOUchadzacochOZamestnanie_)[i - Okres::zaciatocnyRokPreUchadzacov]->getPocetUchadzacovAbsolventi())
			{
				vysledok += (static_cast<double>((*informacieODisponibilnomPocteUchadzacovOZamestnanie_)[i - Okres::zaciatocnyRokPreUchadzacov]->getPocetSpolu()) / (*informacieOUchadzacochOZamestnanie_)[i - Okres::zaciatocnyRokPreUchadzacov]->getPocetUchadzacovAbsolventi());
			}
			else 
			{
				vysledok += 36;
			}
		}
	}
	return vysledok / (koncovyRok - zaciatocnyRok + 1);
}

const string & Okres::getNazov() const
{
	return nazovOkresu_;
}

bool Okres::overPlatnostRokaPrePoctyZamestnancov(int rok)
{
	return (rok >= Okres::zaciatocnyRokPreUchadzacov && rok < (Okres::zaciatocnyRokPreUchadzacov + Okres::pocetRokovPrePoctyZamestnancov) );
}

bool Okres::overPlatnostRokaPreMzdyZamestnancov(int rok)
{
	return (rok >= Okres::zaciatocnyRokPreMzdy && rok < (Okres::zaciatocnyRokPreMzdy + Okres::pocetRokovPreMzdyZamestnancov));
}

bool Okres::overPlatnostOdvetvia(int cisloOdvetvia)
{
	return (cisloOdvetvia > 0 && cisloOdvetvia <= Okres::pocetOdvetvii);
}

Okres::~Okres()
{
	int sizeOfArray = static_cast<int>(informacieOUchadzacochOZamestnanie_->size());
	for (int i = 0; i < sizeOfArray; i++)
	{
		if ((*informacieOUchadzacochOZamestnanie_)[i])
		{
			delete (*informacieOUchadzacochOZamestnanie_)[i];
			(*informacieOUchadzacochOZamestnanie_)[i] = 0;
		}
	}
	delete informacieOUchadzacochOZamestnanie_;
	informacieOUchadzacochOZamestnanie_ = 0;

	for (int i = 0; i < sizeOfArray; i++)
	{
		if ((*informacieOMiereEvidovanejNezamestnanosti_)[i])
		{
			delete (*informacieOMiereEvidovanejNezamestnanosti_)[i];
			(*informacieOMiereEvidovanejNezamestnanosti_)[i] = 0;
		}
	}
	delete informacieOMiereEvidovanejNezamestnanosti_;
	informacieOMiereEvidovanejNezamestnanosti_ = 0;

	for (int i = 0; i < sizeOfArray; i++)
	{
		if ((*informacieOEkonomickyAktivnomObyvatelstve_)[i])
		{
			delete (*informacieOEkonomickyAktivnomObyvatelstve_)[i];
			(*informacieOEkonomickyAktivnomObyvatelstve_)[i] = 0;
		}
	}
	delete informacieOEkonomickyAktivnomObyvatelstve_;
	informacieOEkonomickyAktivnomObyvatelstve_ = 0;

	for (int i = 0; i < sizeOfArray; i++)
	{
		if ((*informacieODisponibilnomPocteUchadzacovOZamestnanie_)[i])
		{
			delete (*informacieODisponibilnomPocteUchadzacovOZamestnanie_)[i];
			(*informacieODisponibilnomPocteUchadzacovOZamestnanie_)[i] = 0;
		}
	}
	delete informacieODisponibilnomPocteUchadzacovOZamestnanie_;
	informacieODisponibilnomPocteUchadzacovOZamestnanie_ = 0;

	for (int i = 0; i < Okres::pocetOdvetvii; i++)
	{
		delete (*statistikaOdvetvii_)[i];
		(*statistikaOdvetvii_)[i] = 0;
	}
	delete statistikaOdvetvii_;
	statistikaOdvetvii_ = 0;

}

int Okres::KomparatorOkresyMieraNezamestnanostiADisponibilnyPocetVzostupne::compare(TableItem<string, Okres*>& first, TableItem<string, Okres*>& second) const
{
	Okres* prvy = first.accessData();
	Okres* druhy = second.accessData();
	if (!prvy && !druhy)
	{
		cout << "Tu by som nemal skocit\n";
		return 0;
	}
	if (!prvy)
	{
		cout << "Tu by som nemal skocit\n";
		return -1;
	}
	if (!druhy)
	{
		cout << "Tu by som nemal skocit\n";
		return 1;
	}
	int indexVPoli = rok_ - Okres::zaciatocnyRokPreUchadzacov;
	if ((*prvy->informacieOMiereEvidovanejNezamestnanosti_)[indexVPoli]->getPercentaSpolu() < (*druhy->informacieOMiereEvidovanejNezamestnanosti_)[indexVPoli]->getPercentaSpolu())
	{
		return -1;
	}
	if ( (*prvy->informacieOMiereEvidovanejNezamestnanosti_)[indexVPoli]->getPercentaSpolu() > (*druhy->informacieOMiereEvidovanejNezamestnanosti_)[indexVPoli]->getPercentaSpolu() )
	{
		return 1;
	}
	if ( (*prvy->informacieODisponibilnomPocteUchadzacovOZamestnanie_)[indexVPoli]->getPocetSpolu() < (*druhy->informacieODisponibilnomPocteUchadzacovOZamestnanie_)[indexVPoli]->getPocetSpolu())
	{
		return -1;
	}
	if ((*prvy->informacieODisponibilnomPocteUchadzacovOZamestnanie_)[indexVPoli]->getPocetSpolu() > (*druhy->informacieODisponibilnomPocteUchadzacovOZamestnanie_)[indexVPoli]->getPocetSpolu())
	{
		return 1;
	}
	return 0;
}

int Okres::KomparatorOkresyMieraNezamestnanostiADisponibilnyPocetZostupne::compare(TableItem<string, Okres*>& first, TableItem<string, Okres*>& second) const
{
	return -1 * KomparatorOkresyMieraNezamestnanostiADisponibilnyPocetVzostupne::compare(first, second);
}


int Okres::KomparatorOkresyOdvetvieVzostupne::compare(TableItem<string, Okres*>& first, TableItem<string, Okres*>& second) const
{
	Okres* prvy = first.accessData();
	Okres* druhy = second.accessData();
	if (!prvy && !druhy)
	{
		cout << "Tu by som nemal skocit\n";
		return 0;
	}
	if (!prvy)
	{
		cout << "Tu by som nemal skocit\n";
		return -1;
	}
	if (!druhy)
	{
		cout << "Tu by som nemal skocit\n";
		return 1;
	}
	double prvyVyslednaMzda = prvy->getPriemernaMesacnaMzdaZamestnancaVOdvetviiZaObdobie(cisloOdvetvia_, zaciatocnyRok_, koncovyRok_);
	double druhyVyslednaMzda = druhy->getPriemernaMesacnaMzdaZamestnancaVOdvetviiZaObdobie(cisloOdvetvia_, zaciatocnyRok_, koncovyRok_);
	if (prvyVyslednaMzda < druhyVyslednaMzda)
	{
		return -1;
	}
	if (prvyVyslednaMzda > druhyVyslednaMzda)
	{
		return 1;
	}
	return 0;
}

int Okres::KomparatorOkresyOdvetvieZostupne::compare(TableItem<string, Okres*>& first, TableItem<string, Okres*>& second) const
{
	return -1 * KomparatorOkresyOdvetvieVzostupne::compare(first, second);
}
