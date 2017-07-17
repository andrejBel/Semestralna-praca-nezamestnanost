#pragma once

#include "../list/array_list.h"
#include "sequence_table.h"

namespace structures
{

	/// <summary> Utriedena sekvencna tabulka. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class SortedSequenceTable : public SequenceTable<K, T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		SortedSequenceTable();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> SortedSequenceTable, z ktorej sa prevezmu vlastnosti. </param>
		SortedSequenceTable(const SortedSequenceTable<K, T>& other);

		/// <summary> Operacia klonovania. Vytvori a vrati duplikat udajovej struktury. </summary>
		/// <returns> Ukazovatel na klon struktury. </returns>
		Structure* clone() const override;

		/// <summary> Vlozi data s danym klucom do tabulky. </summary>
		/// <param name = "key"> Kluc vkladanych dat. </param>
		/// <param name = "data"> Vkladane data. </param>
		/// <exception cref="std::logic_error"> Vyhodena, ak tabulka uz obsahuje data s takymto klucom. </exception>  
		void insert(const K& key, const T& data, bool check = true) override;

		/// <summary> Odstrani z tabulky prvok s danym klucom. </summary>
		/// <param name = "key"> Kluc prvku. </param>
		/// <returns> Odstranene data. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak tabulka neobsahuje data s takymto klucom. </exception>  
		T remove(const K& key) override;

	protected:
		/// <summary> Najde prvok tabulky s danym klucom. </summary>
		/// <param name = "key"> Hladany kluc. </param>
		/// <returns> Prvok tabulky s danym klucom, ak neexistuje, vrati nullptr. </returns>
		TableItem<K, T>* findTableItem(const K& key) const override;
	private:
		/// <summary> Najde index prvku s danym klucom. Kontroluje rozsah [indexStart, indexEnd). Pracuje na principe bisekcie. </summary>
		/// <param name = "key"> Hladany kluc. </param>
		/// <param name = "indexStart"> Pociatocny index prehladavanej sekvencie. </param>
		/// <param name = "indexEnd"> Koncovy index prehladavanej sekvencie. </param>
		/// <param name = "found"> Vystupny parameter, ktory indikuje, ci sa kluc nasiel. </param>
		/// <returns> Index prvku s danym klucom. Ak sa kluc v tabulke nenachadza, vrati index, kde by sa mal prvok s takym klucom nachadzat. </returns>
		int indexOfKey(const K& key, int indexStart, int indexEnd, bool& found) const;
	};

	template<typename K, typename T>
	inline SortedSequenceTable<K, T>::SortedSequenceTable() :
		SequenceTable<K, T>(new ArrayList<TableItem<K, T>*>())
	{
		//dynamic_cast<ArrayList<TableItem<K, T>*> *>(list_)->trySetCapacity(1000000);
	}

	template<typename K, typename T>
	inline SortedSequenceTable<K, T>::SortedSequenceTable(const SortedSequenceTable<K, T>& other) :
		SortedSequenceTable()
	{
		*this = other;
	}

	template<typename K, typename T>
	inline Structure * SortedSequenceTable<K, T>::clone() const
	{
		return new SortedSequenceTable<K, T>(*this);
	}

	template<typename K, typename T>
	inline void SortedSequenceTable<K, T>::insert(const K & key, const T & data, bool check)
	{
		bool found(0);
		int keyIndex = indexOfKey(key, 0, list_->size(), found);
		if (found)
		{
			throw std::logic_error("Key is already in table");
		}
		list_->insert(new TableItem<K, T>(key, data), keyIndex);
	}

	template<typename K, typename T>
	inline T SortedSequenceTable<K, T>::remove(const K & key)
	{
		bool found(0);
		int keyIndex = indexOfKey(key, 0, list_->size(), found);
		if (found)
		{
			T data = (*list_)[keyIndex]->accessData();
			delete (*list_)[keyIndex];
			list_->removeAt(keyIndex);
			return data;
		}
		throw std::logic_error("Key is not in table");
	}

	template<typename K, typename T>
	inline TableItem<K, T>* SortedSequenceTable<K, T>::findTableItem(const K & key) const
	{
		bool found(0);
		int keyIndex = indexOfKey(key, 0, list_->size(), found);
		if (found)
		{
			return (*list_)[keyIndex];
		}
		return 0;
	}

	template<typename K, typename T>
	inline int SortedSequenceTable<K, T>::indexOfKey(const K & key, int indexStart, int indexEnd, bool & found) const
	{
		/*int left = indexstart;
		int right = indexend;
		int middle = (left + right) / 2;
		while (left < right)
		{
			middle = (left + right) / 2;
			k keyinmiddle = (*list_)[middle]->getkey();
			if (keyinmiddle == key)
			{
				found = true;
				break;
			}
			if (left == right) 
			{
				break;
			}
			if (keyinmiddle < key)
			{
				left = middle + 1;
			}
			else
			{
				right = middle;
			}
		}
		return left;*/

		int left = indexStart;
		int right = indexEnd;
		int middle(0);
		while (left < right)
		{
			middle = left + ((right - left) / 2);
			K keyInMiddle = (*list_)[middle]->getKey();
			if (keyInMiddle == key)
			{
				found = true;
				return middle;
				break;
			}
			if (left == right)
			{
				break;
			}
			if (keyInMiddle < key)
			{
				left = middle + 1;
			}
			else
			{
				right = middle;
			}
		}
		return left;
	}

}