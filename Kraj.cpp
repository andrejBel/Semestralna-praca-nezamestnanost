#include "Kraj.h"
#include "structures\heap_monitor.h"


Kraj::Kraj(const string & nazovKraja):
	nazovKraja_(nazovKraja),
	zoznamOkresov_(new LinkedList<Okres *>())
{
}

void Kraj::pridajOkres(Okres * okres)
{
	zoznamOkresov_->add(okres);
}

void Kraj::vypisOkresy()
{
	for (auto okres: *zoznamOkresov_)
	{
		cout << okres->getNazov() << endl;
	}
}

void Kraj::vypisInformacieOOkresoch(int zaciatocnyRok, int koncovyRok)
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
	cout << "Statistika kraja " << nazovKraja_ << " za roky " << zaciatocnyRok << " az " << koncovyRok << endl;
	const UchadzaciOZamestnanie* statistikaUchadzacov(0);
	for (int i = zaciatocnyRok; i <= koncovyRok; i++)
	{
		cout << "Rok: " << i << endl;
		for (auto okres : *zoznamOkresov_)
		{
			statistikaUchadzacov = okres->getInformaciaOUchadzacochOZamestnanie(i);
			if (statistikaUchadzacov)
			{
				pocetZdravotnePostihnutych += statistikaUchadzacov->getPocetUchadzacovZoZP();
				pocetAbsolventov += statistikaUchadzacov->getPocetUchadzacovAbsolventi();
				pocetMladistvych += statistikaUchadzacov->getPocetUchadzacovMladistvi();
				pocetDlhodoboEvidovanych += statistikaUchadzacov->getPocetDlhodoboEvidovanychUchadzacov();
			}
		}
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

double Kraj::getMieraEvidovanejNezamestnanostiVPercentach(int rok)
{
	int sumaDisponibilnehoPoctuUchadzacovOZamestnanie(0);
	int sumaEkonomickyAktivnehoObyvatelstva(0);
	for (auto okres: *zoznamOkresov_)
	{
		sumaDisponibilnehoPoctuUchadzacovOZamestnanie += okres->getInformacieODisponibilnomPocteUchadzacovOZamestnanie(rok)->getPocetSpolu();
		sumaEkonomickyAktivnehoObyvatelstva += okres->getInformacieOEkonomickyAktivnomObyvatelstve(rok)->getPocetSpolu();
	}
	return (sumaEkonomickyAktivnehoObyvatelstva == 0) ? 0 : ((static_cast<double>(sumaDisponibilnehoPoctuUchadzacovOZamestnanie) / static_cast<double>(sumaEkonomickyAktivnehoObyvatelstva )) ) * 100;
}

int Kraj::getDisponibilnyPocetUchadzacovOZamestnanie(int rok)
{
	int sumaDisponibilnehoPoctuUchadzacovOZamestnanie(0);
	for (auto okres : *zoznamOkresov_)
	{
		sumaDisponibilnehoPoctuUchadzacovOZamestnanie += okres->getInformacieODisponibilnomPocteUchadzacovOZamestnanie(rok)->getPocetSpolu();
	}
	return sumaDisponibilnehoPoctuUchadzacovOZamestnanie;
}

double Kraj::getPriemernyPocetEkonomickyAktivnehoObyvatelstva(int zaciatocnyRok, int koncovyRok)
{
	if (!Okres::overPlatnostRokaPrePoctyZamestnancov(zaciatocnyRok) || !Okres::overPlatnostRokaPrePoctyZamestnancov(koncovyRok) || zaciatocnyRok > koncovyRok)
	{
		cout << "Nespravne zadane roky" << endl;
		return 0.0;
	}
	double vysledok(0);
	for (int i = zaciatocnyRok; i <= koncovyRok; i++)
	{
		for (auto okres : *zoznamOkresov_)
		{
			vysledok += okres->getInformacieOEkonomickyAktivnomObyvatelstve(i)->getPocetSpolu();
		}
	}
	return vysledok / static_cast<double>((koncovyRok - zaciatocnyRok + 1));
}

double Kraj::getRozdielMieryEvidovanejNezamestnanostiPreMuzov(int zaciatocnyRok, int koncovyRok)
{
	if (!Okres::overPlatnostRokaPrePoctyZamestnancov(zaciatocnyRok) || !Okres::overPlatnostRokaPrePoctyZamestnancov(koncovyRok) || zaciatocnyRok > koncovyRok)
	{
		cout << "Nespravne zadane roky" << endl;
		return 0.0;
	}
	int sumaDisponibilnehoPoctuUchadzacovOZamestnanieZaciatocnyRok(0);
	int sumaEkonomickyAktivnehoObyvatelstvaZaciatocnyRok(0);
	int sumaDisponibilnehoPoctuUchadzacovOZamestnaniekoncovyRok(0);
	int sumaEkonomickyAktivnehoObyvatelstvaKoncovyRok(0);
	double podielZaciatocnyRok(0);
	double podielKoncovyRok(0);
	for (auto okres : *zoznamOkresov_)
	{
		sumaDisponibilnehoPoctuUchadzacovOZamestnanieZaciatocnyRok += okres->getInformacieODisponibilnomPocteUchadzacovOZamestnanie(zaciatocnyRok)->getPocetMuzi();
		sumaEkonomickyAktivnehoObyvatelstvaZaciatocnyRok += okres->getInformacieOEkonomickyAktivnomObyvatelstve(zaciatocnyRok)->getPocetMuzi();
		sumaDisponibilnehoPoctuUchadzacovOZamestnaniekoncovyRok += okres->getInformacieODisponibilnomPocteUchadzacovOZamestnanie(koncovyRok)->getPocetMuzi();
		sumaEkonomickyAktivnehoObyvatelstvaKoncovyRok += okres->getInformacieOEkonomickyAktivnomObyvatelstve(koncovyRok)->getPocetMuzi();
	}
	podielZaciatocnyRok = sumaEkonomickyAktivnehoObyvatelstvaZaciatocnyRok == 0 ? 0 : static_cast<double>(sumaDisponibilnehoPoctuUchadzacovOZamestnanieZaciatocnyRok) / static_cast<double>(sumaEkonomickyAktivnehoObyvatelstvaZaciatocnyRok);
	podielKoncovyRok = sumaEkonomickyAktivnehoObyvatelstvaKoncovyRok == 0 ? 0 : static_cast<double>(sumaDisponibilnehoPoctuUchadzacovOZamestnaniekoncovyRok) / static_cast<double>(sumaEkonomickyAktivnehoObyvatelstvaKoncovyRok);
	return (podielZaciatocnyRok - podielKoncovyRok) * 100;
}

double Kraj::getRozdielMieryEvidovanejNezamestnanostiPreZeny(int zaciatocnyRok, int koncovyRok)
{
	if (!Okres::overPlatnostRokaPrePoctyZamestnancov(zaciatocnyRok) || !Okres::overPlatnostRokaPrePoctyZamestnancov(koncovyRok) || zaciatocnyRok > koncovyRok)
	{
		cout << "Nespravne zadane roky" << endl;
		return 0.0;
	}
	int sumaDisponibilnehoPoctuUchadzacovOZamestnanieZaciatocnyRok(0);
	int sumaEkonomickyAktivnehoObyvatelstvaZaciatocnyRok(0);
	int sumaDisponibilnehoPoctuUchadzacovOZamestnaniekoncovyRok(0);
	int sumaEkonomickyAktivnehoObyvatelstvaKoncovyRok(0);
	double podielZaciatocnyRok(0);
	double podielKoncovyRok(0);
	for (auto okres : *zoznamOkresov_)
	{
		sumaDisponibilnehoPoctuUchadzacovOZamestnanieZaciatocnyRok += okres->getInformacieODisponibilnomPocteUchadzacovOZamestnanie(zaciatocnyRok)->getPocetZeny();
		sumaEkonomickyAktivnehoObyvatelstvaZaciatocnyRok += okres->getInformacieOEkonomickyAktivnomObyvatelstve(zaciatocnyRok)->getPocetZeny();
		sumaDisponibilnehoPoctuUchadzacovOZamestnaniekoncovyRok += okres->getInformacieODisponibilnomPocteUchadzacovOZamestnanie(koncovyRok)->getPocetZeny();
		sumaEkonomickyAktivnehoObyvatelstvaKoncovyRok += okres->getInformacieOEkonomickyAktivnomObyvatelstve(koncovyRok)->getPocetZeny();
	}
	podielZaciatocnyRok = sumaEkonomickyAktivnehoObyvatelstvaZaciatocnyRok == 0 ? 0 : static_cast<double>(sumaDisponibilnehoPoctuUchadzacovOZamestnanieZaciatocnyRok) / static_cast<double>(sumaEkonomickyAktivnehoObyvatelstvaZaciatocnyRok);
	podielKoncovyRok = sumaEkonomickyAktivnehoObyvatelstvaKoncovyRok == 0 ? 0 : static_cast<double>(sumaDisponibilnehoPoctuUchadzacovOZamestnaniekoncovyRok) / static_cast<double>(sumaEkonomickyAktivnehoObyvatelstvaKoncovyRok);
	return (podielZaciatocnyRok - podielKoncovyRok) * 100;

}

double Kraj::getPomerMedziDisponibilnymPoctomUchadzacovOZamestnanieAUchadzacovZAbsolventov(int zaciatocnyRok, int koncovyRok)
{
	if (!Okres::overPlatnostRokaPrePoctyZamestnancov(zaciatocnyRok) || !Okres::overPlatnostRokaPrePoctyZamestnancov(koncovyRok) || zaciatocnyRok > koncovyRok)
	{
		cout << "Nespravne zadane roky" << endl;
		return 0.0;
	}
	int disponibilnyPocetUchadzacov(0);
	int pocetUchadzacovZraduAbsolventov(0);
	double pomer(0);
	for (int i = zaciatocnyRok; i <= koncovyRok; i++)
	{
		for (auto okres : *zoznamOkresov_)
		{
			disponibilnyPocetUchadzacov += okres->getInformacieODisponibilnomPocteUchadzacovOZamestnanie(i)->getPocetSpolu();
			pocetUchadzacovZraduAbsolventov += okres->getInformaciaOUchadzacochOZamestnanie(i)->getPocetUchadzacovAbsolventi();
			
		}
		pomer += pocetUchadzacovZraduAbsolventov == 0 ? 0 : static_cast<double>(disponibilnyPocetUchadzacov) / static_cast<double>(pocetUchadzacovZraduAbsolventov);
		disponibilnyPocetUchadzacov = 0;
		pocetUchadzacovZraduAbsolventov = 0;
	}
	return pomer / (koncovyRok - zaciatocnyRok + 1);
}

const string & Kraj::getNazovKraja() const
{
	return nazovKraja_;
}

Kraj::~Kraj()
{
	delete zoznamOkresov_;
	zoznamOkresov_ = 0;
}

Kraj::KomparatorKrajMieraNezamestnanostiADisponibilnyPocetVzostupne::KomparatorKrajMieraNezamestnanostiADisponibilnyPocetVzostupne(Table<string, Kraj*>* kraje, int rok) :
	sumy_(new LinkedTable<Kraj *, Sumy *>())
{
	double mieraEvidovanejNezamestnanosti(0);
	int sumaDisponibilnehoPoctuZamestnancov(0);
	for (auto kraj : *kraje)
	{
		mieraEvidovanejNezamestnanosti = kraj->accessData()->getMieraEvidovanejNezamestnanostiVPercentach(rok);
		sumaDisponibilnehoPoctuZamestnancov = kraj->accessData()->getDisponibilnyPocetUchadzacovOZamestnanie(rok);
		sumy_->insert(kraj->accessData(), new Sumy(mieraEvidovanejNezamestnanosti, sumaDisponibilnehoPoctuZamestnancov));
	}
}

int Kraj::KomparatorKrajMieraNezamestnanostiADisponibilnyPocetVzostupne::compare(TableItem<string, Kraj*>& first, TableItem<string, Kraj*>& second) const
{
	Kraj* prvy = first.accessData();
	Kraj* druhy = second.accessData();
	if (!prvy && druhy)
	{
		return -1;
	}
	if (prvy && !druhy)
	{
		return 1;
	}
	if (!prvy && !druhy)
	{
		return 0;
	}
	if ((*sumy_)[prvy]->mieraEvidovanejNezamestnanostiKraja_ < (*sumy_)[druhy]->mieraEvidovanejNezamestnanostiKraja_)
	{
		return -1;
	}
	if ((*sumy_)[prvy]->mieraEvidovanejNezamestnanostiKraja_ > (*sumy_)[druhy]->mieraEvidovanejNezamestnanostiKraja_)
	{
		return 1;
	}
	if ((*sumy_)[prvy]->disponibilnyPocetUchadzacovOZamestnanieKraja_ < (*sumy_)[druhy]->disponibilnyPocetUchadzacovOZamestnanieKraja_)
	{
		return -1;
	}
	if ((*sumy_)[prvy]->disponibilnyPocetUchadzacovOZamestnanieKraja_ > (*sumy_)[druhy]->disponibilnyPocetUchadzacovOZamestnanieKraja_)
	{
		return 1;
	}
	return 0;
}

Kraj::KomparatorKrajMieraNezamestnanostiADisponibilnyPocetVzostupne::~KomparatorKrajMieraNezamestnanostiADisponibilnyPocetVzostupne()
{
	for (auto suma :*sumy_)
	{
		delete suma->accessData();
	}
	delete sumy_;
	sumy_ = 0;
}

Kraj::KomparatorKrajMieraNezamestnanostiADisponibilnyPocetZostupne::KomparatorKrajMieraNezamestnanostiADisponibilnyPocetZostupne(Table<string, Kraj*>* kraje, int rok):
	KomparatorKrajMieraNezamestnanostiADisponibilnyPocetVzostupne(kraje, rok)
{
}

int Kraj::KomparatorKrajMieraNezamestnanostiADisponibilnyPocetZostupne::compare(TableItem<string, Kraj*>& first, TableItem<string, Kraj*>& second) const
{
	return -1 * KomparatorKrajMieraNezamestnanostiADisponibilnyPocetVzostupne::compare(first, second);
}
