#include "Statistika.h"
#include "structures\heap_monitor.h"
#include "structures\table\sorting\select_sort.h"
#include "structures\table\sorting\shell_sort.h"

using namespace std;

Statistika::Statistika() :
	okresy_(new Treap<string, Okres*>()),
	okresySortable_(new UnsortedSequenceTable<string, Okres *>()),
	sortPreOkresy_(new MergeSort<string, Okres *>()),
	kraje_(new Treap<string, Kraj*>()),
	krajeSortable_(new UnsortedSequenceTable<string, Kraj *>()),
	sortPreKraje_(new MergeSort<string, Kraj *>())
{
	cout << fixed;
	cout.precision(2);
}


bool Statistika::nacitajUdaje()
{
	if (!okresy_->size())
	{	
		string riadok;
		vector<string> tokeny;
		ifstream vstup("UchadzaciOZamestnanie.txt");
		if (vstup.is_open())
		{
			try
			{
				
				while (getline(vstup, riadok))
				{
					split(riadok, ';', tokeny);
					//cout << tokeny[0] << " " << tokeny[1] << endl; // v tokeny[0] je okres a v tokeny[1] je kraj
					Okres* okres(0);
					okresy_->tryFind(tokeny[0], okres);
					if (!okres)
					{
						okres = new Okres(tokeny[0]);
						okresy_->insert(tokeny[0], okres);
						okresySortable_->insert(tokeny[0], okres, false);
						Kraj * kraj(0);
						kraje_->tryFind(tokeny[1], kraj);
						if (!kraj)
						{
							kraj = new Kraj(tokeny[1]);
							kraje_->insert(tokeny[1], kraj);
							krajeSortable_->insert(tokeny[1], kraj, false);
						}
						kraj->pridajOkres(okres);
						int index(2);
						for (int rok = 2001; rok < 2017; rok++)
						{
							okres->pridajInformaciuOUchadzacochOZamestnanie(rok, stoi(tokeny[index]), stoi(tokeny[index + 1]), stoi(tokeny[index + 2]), stoi(tokeny[index + 3]));
							index += 4;
						}
					}
				}
				vstup.close();
			}
			catch (const std::exception&)
			{
				cout << "Chyba pri citani zo suboru!!!\n";
				return false;
			}
		}
		else
		{
			cout << "Nepodarilo sa otvorit subor!!!\n";
			return false;
		}	

		vstup.open("MieraEvidovanejNezamestnanosti.txt");
		if (vstup.is_open())
		{
			try
			{
				double percentaSpolu(0);
				double percentaMuzi(0);
				double percentaZeny(0);
				int pocetMuzi(0);
				int pocetZeny(0);
				while (getline(vstup, riadok))
				{
					Okres* okres(0);
					okresy_->tryFind(riadok, okres);
					
					int index(0);
					getline(vstup, riadok);
					split(riadok, ';', tokeny);
					for (int rok = 2001; rok < 2017; rok++)
					{
						if (tokeny[index].size())
						{
							percentaSpolu = stod(tokeny[index]);
						}
						else 
						{
							percentaSpolu = 0;
						}
						if (tokeny[index + 1].size())
						{
							percentaMuzi = stod(tokeny[index + 1]);
						}
						else
						{
							percentaMuzi = 0;
						}
						if (tokeny[index + 2].size())
						{
							percentaZeny = stod(tokeny[index + 2]);
						}
						else
						{
							percentaZeny = 0;
						}
						okres->pridajInformaciuOMiereEvidovanejNezamestnanosti(rok, percentaSpolu, percentaMuzi, percentaZeny);
						index += 3;
					}
					index = 0;

					getline(vstup, riadok);
					split(riadok, ';', tokeny);
					for (int rok = 2001; rok < 2017; rok++)
					{
						if (tokeny[index + 1].size())
						{
							pocetMuzi = stoi(tokeny[index + 1]);
						}
						else 
						{
							pocetMuzi = 0;
						}
						if (tokeny[index + 2].size())
						{
							pocetZeny = stoi(tokeny[index + 2]);
						}
						else
						{
							pocetZeny = 0;
						}
						okres->pridajInformaciuOEkonomickyAktivnomObyvatelstve(rok, pocetMuzi, pocetZeny);
						index += 3;
					}
					index = 0;

					getline(vstup, riadok);
					split(riadok, ';', tokeny);

					for (int rok = 2001; rok < 2017; rok++)
					{
						if (tokeny[index + 1].size())
						{
							pocetMuzi = stoi(tokeny[index + 1]);
						}
						else
						{
							pocetMuzi = 0;
						}
						if (tokeny[index + 2].size())
						{
							pocetZeny = stoi(tokeny[index + 2]);
						}
						else
						{
							pocetZeny = 0;
						}
						okres->pridajInformaciuODisponibilnomPocteUchadzacovOZamestnanie(rok, pocetMuzi, pocetZeny);
						index += 3;
					}					
				}
				vstup.close();
			}
			catch (const std::exception&)
			{
				cout << "Chyba pri citani zo suboru!!!\n";
				return false;
			}
		}
		else
		{
			cout << "Nepodarilo sa otvorit subor!!!\n";
			return false;
		}
		
		vstup.open("MzdyZamestnancovPodlaSK_NACE_Rev.2.txt");
		if (vstup.is_open())
		{
			try
			{
				while (getline(vstup, riadok))
				{
					Okres* okres = (*this->okresy_)[riadok];
					for (int pocetOdvetvii = 1; pocetOdvetvii < 22; pocetOdvetvii++)
					{
						getline(vstup, riadok);
						split(riadok, ';', tokeny);
						Array<int>* udaje = new Array<int>(7);
						okres->pridajInformaciuOOdvetvii(pocetOdvetvii, udaje);
						int indexVPoli(0);
						for (int i = 2; i < 21; i += 3)
						{
							(*udaje)[indexVPoli++] = stoi(tokeny[i]);
						}
					}
				}
				vstup.close();
			}
			catch (const std::exception&)
			{
				cout << "Chyba pri citani zo suboru!!!\n";
				return false;
			}
		}
		else
		{
			cout << "Nepodarilo sa otvorit subor!!!\n";
			return false;
		}

		cout << "Udaje boli uspesne nacitane\n";
		return true;
	}
	else 
	{
		cout << "Udaje uz boli nacitane\n";
		return false;
	}
}

void Statistika::vyhladajInformacieOOkrese(const string & nazov, int zaciatocnyRok, int koncovyRok)
{
	Okres* okres(0);
	okresy_->tryFind(nazov, okres);
	if (okres)
	{
		okres->vypisInformacieOUchadzacoch(zaciatocnyRok, koncovyRok);
	}
	else
	{
		cout << "Okres s nazvom: " << nazov << " sa nepodarilo najst!!!\n";
	}
}

void Statistika::utriedOkresyPodlaMieryNezamestnanostiAPoctuUchadzacovoZamestnanie(int rok, bool vzostupne)
{
	if (Okres::overPlatnostRokaPrePoctyZamestnancov(rok))
	{
		if (vzostupne)
		{
			Okres::KomparatorOkresyMieraNezamestnanostiADisponibilnyPocetVzostupne komparator(rok);
			sortPreOkresy_->sort(*okresySortable_, komparator);
		}
		else
		{
			Okres::KomparatorOkresyMieraNezamestnanostiADisponibilnyPocetZostupne komparator(rok);
			sortPreOkresy_->sort(*okresySortable_, komparator);
		}
		cout << "Po sortovani: ---------------------" << endl;
		for (auto var : *okresySortable_)
		{
			cout << var->accessData()->getNazov() << "-Miera evidovanej nezamestnanosti v %: " << var->accessData()->getInformaciaOMiereEvidovanejNezamestnanosti(rok)->getPercentaSpolu() << ", disponibilny pocet uchadzacov o zamestnanie: " << var->accessData()->getInformacieODisponibilnomPocteUchadzacovOZamestnanie(rok)->getPocetSpolu() << endl;
		}
		cout << "------------------------" << endl;
	}
	else 
	{
		cout << "Bol zadany nespravny rok!!!\n";
	}
}

void Statistika::vyhladajInformacieOKraji(const string & nazovKraja, int zaciatocnyRok, int koncovyRok)
{
	Kraj* kraj(0);
	kraje_->tryFind(nazovKraja, kraj);
	if (kraj)
	{
		kraj->vypisInformacieOOkresoch(zaciatocnyRok, koncovyRok);
	}
	else 
	{
		cout << "Kraj s menom " << nazovKraja << " sa nesasiel!!!\n";
	}
}

void Statistika::utriedKrajePodlaMieryNezamestnanostiAPoctuUchadzacovoZamestnanie(int rok, bool vzostupne)
{
	if (Okres::overPlatnostRokaPrePoctyZamestnancov(rok))
	{
		if (vzostupne)
		{
			Kraj::KomparatorKrajMieraNezamestnanostiADisponibilnyPocetVzostupne komparator(krajeSortable_, rok);
			sortPreKraje_->sort(*krajeSortable_, komparator);
		}
		else 
		{
			Kraj::KomparatorKrajMieraNezamestnanostiADisponibilnyPocetZostupne komparator(krajeSortable_, rok);
			sortPreKraje_->sort(*krajeSortable_, komparator);
		}
		cout << "Po sortovani: -----------------" << endl;
		for (auto var : *krajeSortable_)
		{
			cout << var->accessData()->getNazovKraja() << "- Miera evidovanej nezamestnanosti v %: " << var->accessData()->getMieraEvidovanejNezamestnanostiVPercentach(rok) << ", disponibilny pocet uchadzacov o zamestnanie: " << var->accessData()->getDisponibilnyPocetUchadzacovOZamestnanie(rok) << endl;
		}
		cout << "------------------------" << endl;
	}
	else 
	{
		cout << "Bol zadany nespravny rok\n";
	}
}

void Statistika::utriedOkresyPodlaPriemerneMesacnejMzdyZamestnancaVOdvetvi(int cisloOdvetvia, int zaciatocnyRok, int koncovyRok, bool vzostupne)
{
	if (Okres::overPlatnostRokaPreMzdyZamestnancov(zaciatocnyRok) && Okres::overPlatnostRokaPreMzdyZamestnancov(koncovyRok) && zaciatocnyRok <= koncovyRok)
	{
		if (!Okres::overPlatnostOdvetvia(cisloOdvetvia))
		{
			cout << "Nespravne cislo odvetvia!!!\n";
			return;
		}
		if (vzostupne)
		{
			Okres::KomparatorOkresyOdvetvieVzostupne komparator(cisloOdvetvia,zaciatocnyRok, koncovyRok);
			sortPreOkresy_->sort(*okresySortable_, komparator);
		}
		else
		{
			Okres::KomparatorOkresyOdvetvieZostupne komparator(cisloOdvetvia, zaciatocnyRok, koncovyRok);
			sortPreOkresy_->sort(*okresySortable_, komparator);
		}
		cout << "Po sortovani: ---------------------" << endl;
		for (auto var : *okresySortable_)
		{
			cout << var->accessData()->getNazov() << "- Priemerna nominalna mesacna mzda: " << var->accessData()->getPriemernaMesacnaMzdaZamestnancaVOdvetviiZaObdobie(cisloOdvetvia, zaciatocnyRok, koncovyRok) << endl;
		}
		cout << "------------------------" << endl;
	}
	else
	{
		cout << "Bol zadany nespravny rok!!!\n";
	}
}

void Statistika::komplexnaStatistikaOkresov(int zaciatocnyRok, int koncovyRok)
{
	if (!Okres::overPlatnostRokaPrePoctyZamestnancov(zaciatocnyRok) || !Okres::overPlatnostRokaPrePoctyZamestnancov(koncovyRok) || zaciatocnyRok > koncovyRok)
	{
		cout << "Nespravne zadane roky!!!" << endl;
		return;
	}
	if (okresy_->size())
	{
		Okres* najvacsiPocetEkonomickyAktivnehoObyvatelstva(0);
		Okres* najmensiPocetEkonomickyAktivnehoObyvatelstva(0);
		Okres* najvacsiPoklesMieryEvidovanejNezamestnanostiPreMuzov(0);
		Okres* najvacsiPoklesMieryEvidovanejNezamestnanostiPreZeny(0);
		Okres * najlepsiPomerMedziDisponibilnymPoctomUchadzacovoZamestnanieAAbsolventov(0);
		for (TableItem<string, Okres*>* okres: * okresy_)
		{
			najvacsiPocetEkonomickyAktivnehoObyvatelstva = okres->accessData();
			najmensiPocetEkonomickyAktivnehoObyvatelstva = okres->accessData();
			najvacsiPoklesMieryEvidovanejNezamestnanostiPreMuzov = okres->accessData();
			najvacsiPoklesMieryEvidovanejNezamestnanostiPreZeny = okres->accessData();
			najlepsiPomerMedziDisponibilnymPoctomUchadzacovoZamestnanieAAbsolventov = okres->accessData();
			if (okres->accessData())
			{
				break;
			}
		}
		for (auto okres : *okresy_)
		{
			if (okres->accessData()->getPriemernyPocetEkonomickyAktivnehoObyvatelstva(zaciatocnyRok, koncovyRok) < najmensiPocetEkonomickyAktivnehoObyvatelstva->getPriemernyPocetEkonomickyAktivnehoObyvatelstva(zaciatocnyRok, koncovyRok))
			{
				najmensiPocetEkonomickyAktivnehoObyvatelstva = okres->accessData();
			}
			if (okres->accessData()->getPriemernyPocetEkonomickyAktivnehoObyvatelstva(zaciatocnyRok, koncovyRok) > najvacsiPocetEkonomickyAktivnehoObyvatelstva->getPriemernyPocetEkonomickyAktivnehoObyvatelstva(zaciatocnyRok, koncovyRok))
			{
				najvacsiPocetEkonomickyAktivnehoObyvatelstva = okres->accessData();
			}
			if (okres->accessData()->getRozdielMieryEvidovanejNezamestnanostiPreMuzov(zaciatocnyRok, koncovyRok) > najvacsiPoklesMieryEvidovanejNezamestnanostiPreMuzov->getRozdielMieryEvidovanejNezamestnanostiPreMuzov(zaciatocnyRok, koncovyRok))
			{
				najvacsiPoklesMieryEvidovanejNezamestnanostiPreMuzov = okres->accessData();
			}
			if (okres->accessData()->getRozdielMieryEvidovanejNezamestnanostiPreZeny(zaciatocnyRok, koncovyRok) > najvacsiPoklesMieryEvidovanejNezamestnanostiPreZeny->getRozdielMieryEvidovanejNezamestnanostiPreZeny(zaciatocnyRok, koncovyRok))
			{
				najvacsiPoklesMieryEvidovanejNezamestnanostiPreZeny = okres->accessData();
			}
			if (okres->accessData()->getPomerMedziDisponibilnymPoctomUchadzacovOZamestnanieAUchadzacovZAbsolventov(zaciatocnyRok, koncovyRok) < najlepsiPomerMedziDisponibilnymPoctomUchadzacovoZamestnanieAAbsolventov->getPomerMedziDisponibilnymPoctomUchadzacovOZamestnanieAUchadzacovZAbsolventov(zaciatocnyRok, koncovyRok))
			{
				najlepsiPomerMedziDisponibilnymPoctomUchadzacovoZamestnanieAAbsolventov = okres->accessData();
			}
		}
		cout << "Statistika za obdobie od: " << zaciatocnyRok << " po " << koncovyRok << endl;
		cout << "Okres s najvacsim priemernym poctom ekonomicky aktivneho obyvatelstva je: " << najvacsiPocetEkonomickyAktivnehoObyvatelstva->getNazov() << ", priemer: " << najvacsiPocetEkonomickyAktivnehoObyvatelstva->getPriemernyPocetEkonomickyAktivnehoObyvatelstva(zaciatocnyRok, koncovyRok) << endl;
		cout << "Okres s najmensim priemernym poctom ekonomicky aktivneho obyvatelstva je: " << najmensiPocetEkonomickyAktivnehoObyvatelstva->getNazov() << ", priemer: " << najmensiPocetEkonomickyAktivnehoObyvatelstva->getPriemernyPocetEkonomickyAktivnehoObyvatelstva(zaciatocnyRok, koncovyRok) << endl;
		cout << "Okres s najvacsim poklesom miery nezamestnanosti muzov je: "
		 	 << najvacsiPoklesMieryEvidovanejNezamestnanostiPreMuzov->getNazov()
			 << ", na zaciatku sledovaneho obdobia: "
			 << najvacsiPoklesMieryEvidovanejNezamestnanostiPreMuzov->getInformaciaOMiereEvidovanejNezamestnanosti(zaciatocnyRok)->getPercentaMuzi()
			 << " %, na konci " << najvacsiPoklesMieryEvidovanejNezamestnanostiPreMuzov->getInformaciaOMiereEvidovanejNezamestnanosti(koncovyRok)->getPercentaMuzi()
			 << " %, rozdiel: " << najvacsiPoklesMieryEvidovanejNezamestnanostiPreMuzov->getRozdielMieryEvidovanejNezamestnanostiPreMuzov(zaciatocnyRok, koncovyRok) << " %" << endl;
		cout << "Okres s najvacsim poklesom miery nezamestnanosti zien je: "
			 << najvacsiPoklesMieryEvidovanejNezamestnanostiPreZeny->getNazov()
			 << ", na zaciatku sledovaneho obdobia: "
			 << najvacsiPoklesMieryEvidovanejNezamestnanostiPreZeny->getInformaciaOMiereEvidovanejNezamestnanosti(zaciatocnyRok)->getPercentaZeny()
			 << " %, na konci " << najvacsiPoklesMieryEvidovanejNezamestnanostiPreZeny->getInformaciaOMiereEvidovanejNezamestnanosti(koncovyRok)->getPercentaZeny()
			 << " %, rozdiel: " << najvacsiPoklesMieryEvidovanejNezamestnanostiPreZeny->getRozdielMieryEvidovanejNezamestnanostiPreZeny(zaciatocnyRok, koncovyRok) << " %" << endl;
		cout << "Okres s najlepsim pomerom medzi disponibilnym poctom uchadzacov o zamestnanie a poctom uchadzacov z radu absolventov je: "
			<< najlepsiPomerMedziDisponibilnymPoctomUchadzacovoZamestnanieAAbsolventov->getNazov()
			<< ", pomer je: " << najlepsiPomerMedziDisponibilnymPoctomUchadzacovoZamestnanieAAbsolventov->getPomerMedziDisponibilnymPoctomUchadzacovOZamestnanieAUchadzacovZAbsolventov(zaciatocnyRok, koncovyRok) << endl;
	}
	else 
	{
		cout << "Nemozno ziskat statistiky o okresoch, data neboli nacitane!!!\n";
	}	
}

void Statistika::komplexnaStatistikaKrajov(int zaciatocnyRok, int koncovyRok)
{	
	if (!Okres::overPlatnostRokaPrePoctyZamestnancov(zaciatocnyRok) || !Okres::overPlatnostRokaPrePoctyZamestnancov(koncovyRok) || zaciatocnyRok > koncovyRok)
	{
		cout << "Nespravne zadane roky!!!" << endl;
		return;
	}
	if (kraje_->size())
	{
		Kraj* najvacsiPocetEkonomickyAktivnehoObyvatelstva(0);
		Kraj* najmensiPocetEkonomickyAktivnehoObyvatelstva(0);
		Kraj* najvacsiPoklesMieryEvidovanejNezamestnanostiPreMuzov(0);
		Kraj* najvacsiPoklesMieryEvidovanejNezamestnanostiPreZeny(0);
		Kraj* najlepsiPomerMedziDisponibilnymPoctomUchadzacovoZamestnanieAAbsolventov(0);
		for (auto kraj : *kraje_) 
		{
			najvacsiPocetEkonomickyAktivnehoObyvatelstva = kraj->accessData();
			najmensiPocetEkonomickyAktivnehoObyvatelstva = kraj->accessData();
			najvacsiPoklesMieryEvidovanejNezamestnanostiPreMuzov = kraj->accessData();
			najvacsiPoklesMieryEvidovanejNezamestnanostiPreZeny = kraj->accessData();
			najlepsiPomerMedziDisponibilnymPoctomUchadzacovoZamestnanieAAbsolventov = kraj->accessData();
			if (kraj->accessData())
			{
				break;
			}
		}
		double priemernyPocetEkonomickyAktivnehoObyvatelstva(0);
		double najmensiPriemernyPocetEkonomickyAktivnehoObyvatelstva = najmensiPocetEkonomickyAktivnehoObyvatelstva->getPriemernyPocetEkonomickyAktivnehoObyvatelstva(zaciatocnyRok, koncovyRok);
		double najvacsiPriemernyPocetEkonomickyAktivnehoObyvatelstva = najvacsiPocetEkonomickyAktivnehoObyvatelstva->getPriemernyPocetEkonomickyAktivnehoObyvatelstva(zaciatocnyRok, koncovyRok);

		
		for (auto kraj : *kraje_)
		{
			priemernyPocetEkonomickyAktivnehoObyvatelstva = kraj->accessData()->getPriemernyPocetEkonomickyAktivnehoObyvatelstva(zaciatocnyRok, koncovyRok);
			
			
			if (priemernyPocetEkonomickyAktivnehoObyvatelstva < najmensiPriemernyPocetEkonomickyAktivnehoObyvatelstva)
			{
				najmensiPocetEkonomickyAktivnehoObyvatelstva = kraj->accessData();
				najmensiPriemernyPocetEkonomickyAktivnehoObyvatelstva = priemernyPocetEkonomickyAktivnehoObyvatelstva;
			}
			if (priemernyPocetEkonomickyAktivnehoObyvatelstva > najvacsiPriemernyPocetEkonomickyAktivnehoObyvatelstva)
			{
				najvacsiPocetEkonomickyAktivnehoObyvatelstva = kraj->accessData();
				najvacsiPriemernyPocetEkonomickyAktivnehoObyvatelstva = priemernyPocetEkonomickyAktivnehoObyvatelstva;
			}
			if (kraj->accessData()->getRozdielMieryEvidovanejNezamestnanostiPreMuzov(zaciatocnyRok, koncovyRok) > najvacsiPoklesMieryEvidovanejNezamestnanostiPreMuzov->getRozdielMieryEvidovanejNezamestnanostiPreMuzov(zaciatocnyRok, koncovyRok))
			{
				najvacsiPoklesMieryEvidovanejNezamestnanostiPreMuzov = kraj->accessData();
			}
			if (kraj->accessData()->getRozdielMieryEvidovanejNezamestnanostiPreZeny(zaciatocnyRok, koncovyRok) > najvacsiPoklesMieryEvidovanejNezamestnanostiPreZeny->getRozdielMieryEvidovanejNezamestnanostiPreZeny(zaciatocnyRok, koncovyRok))
			{
				najvacsiPoklesMieryEvidovanejNezamestnanostiPreZeny = kraj->accessData();
			}
			if (kraj->accessData()->getPomerMedziDisponibilnymPoctomUchadzacovOZamestnanieAUchadzacovZAbsolventov(zaciatocnyRok, koncovyRok) < najlepsiPomerMedziDisponibilnymPoctomUchadzacovoZamestnanieAAbsolventov->getPomerMedziDisponibilnymPoctomUchadzacovOZamestnanieAUchadzacovZAbsolventov(zaciatocnyRok, koncovyRok))
			{
				najlepsiPomerMedziDisponibilnymPoctomUchadzacovoZamestnanieAAbsolventov = kraj->accessData();
			}
		}
		cout << "Kraj s najvacsim priemernym poctom ekonomicky aktivneho obyvatelstva je: "
			 << najvacsiPocetEkonomickyAktivnehoObyvatelstva->getNazovKraja() << ", priemer: " << static_cast<double>(najvacsiPriemernyPocetEkonomickyAktivnehoObyvatelstva) << endl;
		cout << "Kraj s najmensim priemernym poctom ekonomicky aktivneho obyvatelstva je: "
			 << najmensiPocetEkonomickyAktivnehoObyvatelstva->getNazovKraja() << ", priemer: " << najmensiPriemernyPocetEkonomickyAktivnehoObyvatelstva << endl;
		cout << "Kraj s najvacsim poklesom miery nezamestnanosti muzov je: "
			 << najvacsiPoklesMieryEvidovanejNezamestnanostiPreMuzov->getNazovKraja()
			 << ", rozdiel: " << najvacsiPoklesMieryEvidovanejNezamestnanostiPreMuzov->getRozdielMieryEvidovanejNezamestnanostiPreMuzov(zaciatocnyRok, koncovyRok) << " %" << endl;
		cout << "Kraj s najvacsim poklesom miery nezamestnanosti zien je: "
			 << najvacsiPoklesMieryEvidovanejNezamestnanostiPreZeny->getNazovKraja()
			 << ", rozdiel: " << najvacsiPoklesMieryEvidovanejNezamestnanostiPreZeny->getRozdielMieryEvidovanejNezamestnanostiPreZeny(zaciatocnyRok, koncovyRok) << " %" << endl;
		cout << "Okres s najlepsim pomerom medzi disponibilnym poctom uchadzacov o zamestnanie a poctom uchadzacov z radu absolventov je: "
			 << najlepsiPomerMedziDisponibilnymPoctomUchadzacovoZamestnanieAAbsolventov->getNazovKraja()
			 << ", pomer je: " << najlepsiPomerMedziDisponibilnymPoctomUchadzacovoZamestnanieAAbsolventov->getPomerMedziDisponibilnymPoctomUchadzacovOZamestnanieAUchadzacovZAbsolventov(zaciatocnyRok, koncovyRok) << endl;
	}
	else
	{
		cout << "Nemozno ziskat statistiky o krajoch, data neboli nacitane!!!\n";
	}
}

void Statistika::vypisKrajeAIchOkresy()
{
	for (auto var : *kraje_)
	{
		cout << "Kraj: " << var->getKey() << endl;
		cout << "--------------------\n";
		var->accessData()->vypisOkresy();
		cout << "--------------------\n";
	}
}


Statistika::~Statistika()
{
	delete okresySortable_;
	okresySortable_ = 0;
	for (auto var: *okresy_)
	{
		delete var->accessData();
	}
	delete okresy_;
	okresy_ = 0;
	delete krajeSortable_;
	krajeSortable_ = 0;
	for (auto var : *kraje_)
	{
		delete var->accessData();
	}
	delete kraje_;
	kraje_ = 0;
	delete sortPreOkresy_;
	sortPreOkresy_ = 0;
	delete sortPreKraje_;
	sortPreKraje_ = 0;
}


void Statistika::split(const string & text, char sep, vector<string>& tokens)
{
	tokens.clear();
	std::size_t start = 0, end = 0;
	while ((end = text.find(sep, start)) != string::npos) {
		tokens.push_back(text.substr(start, end - start));
		start = end + 1;
	}
	tokens.push_back(text.substr(start));
}
