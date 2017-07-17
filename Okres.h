#pragma once
#include <string>
#include "structures\heap_monitor.h"
#include "structures\array\array.h"
#include "UchadzaciOZamestnanie.h"
#include "MieraEvidovanejNezamestnanosti.h"
#include "EkonimickyAktivneObyvatelstvo.h"
#include "DisponibilnyPocetUchadzacovOZamestnanie.h"
#include "structures\table\sorting\sort.h"
#include "structures\table\linked_table.h"

using namespace structures;
using namespace std;

class Okres
{
private:
		
	static const int zaciatocnyRokPreUchadzacov = 2001;
	static const int pocetRokovPrePoctyZamestnancov = 16;
	static const int zaciatocnyRokPreMzdy = 2009;
	static const int pocetRokovPreMzdyZamestnancov = 7;
	static const int pocetOdvetvii = 21;
	Array<Array<int>*>* statistikaOdvetvii_;
	string nazovOkresu_;
	Array<UchadzaciOZamestnanie *>* informacieOUchadzacochOZamestnanie_;
	Array<MieraEvidovanejNezamestnanosti *>* informacieOMiereEvidovanejNezamestnanosti_;
	Array<EkonomickyAktivneObyvatelstvo *>* informacieOEkonomickyAktivnomObyvatelstve_;
	Array<DisponibilnyPocetUchadzacovOZamestnanie *>* informacieODisponibilnomPocteUchadzacovOZamestnanie_;


public:
	Okres(const string& nazovOkresu);
	void pridajInformaciuOUchadzacochOZamestnanie(int rok, int pocetUchadzacovZoZP, int pocetUchadzacovAbsolventi, int pocetUchadzacovMladistvi, int pocetDlhodoboEvidovanychUchadzacov);
	void pridajInformaciuOMiereEvidovanejNezamestnanosti(int rok, double percentaSpolu, double percentaMuzi, double percentaZeny);
	void pridajInformaciuOEkonomickyAktivnomObyvatelstve(int rok, int pocetMuzi, int pocetZeny);
	void pridajInformaciuODisponibilnomPocteUchadzacovOZamestnanie(int rok, int pocetMuzi, int pocetZeny);
	void pridajInformaciuOOdvetvii(int cisloOdvetvia, Array<int>* udaje);
	void vypisInformacieOUchadzacoch(int zaciatocnyRok, int koncovyRok) const;


	const UchadzaciOZamestnanie* getInformaciaOUchadzacochOZamestnanie(int rok) const;
	const MieraEvidovanejNezamestnanosti* getInformaciaOMiereEvidovanejNezamestnanosti(int rok) const;
	const DisponibilnyPocetUchadzacovOZamestnanie* getInformacieODisponibilnomPocteUchadzacovOZamestnanie(int rok) const;
	const EkonomickyAktivneObyvatelstvo* getInformacieOEkonomickyAktivnomObyvatelstve(int rok) const;
	const double getPriemernaMesacnaMzdaZamestnancaVOdvetviiZaObdobie(int cisloOdvetvia, int zaciatocnyRok, int koncovyRok);
	const double getPriemernyPocetEkonomickyAktivnehoObyvatelstva(int zaciatocnyRok, int koncovyRok);
	const double getRozdielMieryEvidovanejNezamestnanostiPreMuzov(int zaciatocnyRok, int koncovyRok);
	const double getRozdielMieryEvidovanejNezamestnanostiPreZeny(int zaciatocnyRok, int koncovyRok);
	const double getPomerMedziDisponibilnymPoctomUchadzacovOZamestnanieAUchadzacovZAbsolventov(int zaciatocnyRok, int koncovyRok);
	const string& getNazov() const;

	static bool overPlatnostRokaPrePoctyZamestnancov(int rok);
	static bool overPlatnostRokaPreMzdyZamestnancov(int rok);
	static bool overPlatnostOdvetvia(int cisloOdvetvia);
	~Okres();
	
	class KomparatorOkresyMieraNezamestnanostiADisponibilnyPocetVzostupne :
		public Comparator<string, Okres*> 
	{
	private:
		int rok_;
	public:
		KomparatorOkresyMieraNezamestnanostiADisponibilnyPocetVzostupne(int rok):
			rok_(rok)
		{}
		virtual int compare(TableItem<string, Okres*>& first, TableItem<string, Okres*>& second) const override;
	};

	class KomparatorOkresyMieraNezamestnanostiADisponibilnyPocetZostupne :
		public KomparatorOkresyMieraNezamestnanostiADisponibilnyPocetVzostupne
	{
	public:
		KomparatorOkresyMieraNezamestnanostiADisponibilnyPocetZostupne(int rok) :
			KomparatorOkresyMieraNezamestnanostiADisponibilnyPocetVzostupne(rok) 
		{}
		virtual int compare(TableItem<string, Okres*>& first, TableItem<string, Okres*>& second) const override;

	};

	class KomparatorOkresyOdvetvieVzostupne: public
	Comparator<string, Okres *>
	{
	public:
		KomparatorOkresyOdvetvieVzostupne(int cisloOdvetvia, int zaciatocnyRok, int koncovyRok) :
			cisloOdvetvia_(cisloOdvetvia),
			zaciatocnyRok_(zaciatocnyRok),
			koncovyRok_(koncovyRok)
		{}
		
	virtual int compare(TableItem<string, Okres*>& first, TableItem<string, Okres*>& second) const override;

	private:
		int cisloOdvetvia_;
		int zaciatocnyRok_;
		int koncovyRok_;
	};


	class KomparatorOkresyOdvetvieZostupne : public
		KomparatorOkresyOdvetvieVzostupne
	{
	public:
		KomparatorOkresyOdvetvieZostupne(int cisloOdvetvia, int zaciatocnyRok, int koncovyRok) :
			KomparatorOkresyOdvetvieVzostupne(cisloOdvetvia, zaciatocnyRok, koncovyRok) 
		{}
		virtual int compare(TableItem<string, Okres*>& first, TableItem<string, Okres*>& second) const override;
		
	};

};

