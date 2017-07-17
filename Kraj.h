#pragma once
#include <string>
#include "structures\heap_monitor.h"
#include "Okres.h"
#include "structures\list\linked_list.h"
#include "structures\table\sorting\sort.h"
#include "structures\table\linked_table.h"

using namespace structures;
using namespace std;
class Kraj
{
private:
	string nazovKraja_;
	List<Okres *>* zoznamOkresov_;

public:
	Kraj(const string& nazovKraja);
	void pridajOkres(Okres * okres);
	void vypisOkresy();
	void vypisInformacieOOkresoch(int zaciatocnyRok, int koncovyRok);
	double getMieraEvidovanejNezamestnanostiVPercentach(int rok);
	int getDisponibilnyPocetUchadzacovOZamestnanie(int rok);
	double getPriemernyPocetEkonomickyAktivnehoObyvatelstva(int zaciatocnyRok, int koncovyRok);
	double getRozdielMieryEvidovanejNezamestnanostiPreMuzov(int zaciatocnyRok,int koncovyRok);
	double getRozdielMieryEvidovanejNezamestnanostiPreZeny(int zaciatocnyRok, int koncovyRok);
	double getPomerMedziDisponibilnymPoctomUchadzacovOZamestnanieAUchadzacovZAbsolventov(int zaciatocnyRok, int koncovyRok);
	const string& getNazovKraja() const;
	~Kraj();

	class KomparatorKrajMieraNezamestnanostiADisponibilnyPocetVzostupne: 
		public Comparator<string, Kraj*>
	{
	private:
		struct Sumy {
			double mieraEvidovanejNezamestnanostiKraja_;
			int disponibilnyPocetUchadzacovOZamestnanieKraja_;
			Sumy(double mieraEvidovanejNezamestnanostiKraja, int disponibilnyPocetUchadzacovOZamestnanieKraja):
				mieraEvidovanejNezamestnanostiKraja_(mieraEvidovanejNezamestnanostiKraja),
				disponibilnyPocetUchadzacovOZamestnanieKraja_(disponibilnyPocetUchadzacovOZamestnanieKraja)
			{}
		};

		Table<Kraj *, Sumy *>* sumy_;
		
	public:
		KomparatorKrajMieraNezamestnanostiADisponibilnyPocetVzostupne(Table<string, Kraj *>* kraje, int rok);

		virtual int compare(TableItem<string, Kraj*>& first, TableItem<string, Kraj*>& second) const override;
		virtual ~KomparatorKrajMieraNezamestnanostiADisponibilnyPocetVzostupne();
	};

	class KomparatorKrajMieraNezamestnanostiADisponibilnyPocetZostupne: 
		public KomparatorKrajMieraNezamestnanostiADisponibilnyPocetVzostupne 
	{
	public:
		KomparatorKrajMieraNezamestnanostiADisponibilnyPocetZostupne(Table<string, Kraj *>* kraje, int rok);

		virtual int compare(TableItem<string, Kraj*>& first, TableItem<string, Kraj*>& second) const override;

	};

};

