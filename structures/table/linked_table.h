#pragma once

#include "../list/linked_list.h"
#include "sequence_table.h"

namespace structures
{

	/// <summary> Zretazena tabulka. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class LinkedTable : public SequenceTable<K, T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		LinkedTable();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> LinkedTable, z ktorej sa prevezmu vlastnosti. </param>
		LinkedTable(const LinkedTable<K, T>& other);

		/// <summary> Operacia klonovania. Vytvori a vrati duplikat udajovej struktury. </summary>
		/// <returns> Ukazovatel na klon struktury. </returns>
		Structure* clone() const override;

		/// <summary> Odstrani z tabulky prvok s danym klucom. </summary>
		/// <param name = "key"> Kluc prvku. </param>
		/// <returns> Odstranene data. </returns>
		/// <exception cref="std::logic_error"> Vyhodena, ak tabulka neobsahuje data s takymto klucom. </exception>  
		T remove(const K& key) override;

	};

	template<typename K, typename T>
	inline LinkedTable<K, T>::LinkedTable() :
		SequenceTable<K, T>(new LinkedList<TableItem<K, T>*>())
	{
	}

	template<typename K, typename T>
	inline LinkedTable<K, T>::LinkedTable(const LinkedTable<K, T>& other) :
		LinkedTable()
	{
		*this = other;
	}

	template<typename K, typename T>
	inline Structure * LinkedTable<K, T>::clone() const
	{
		return new LinkedTable<K, T>(*this);
	}

	template<typename K, typename T>
	inline T LinkedTable<K, T>::remove(const K & key)
	{
		int index = 0;
		TableItem<K, T>* forRemove(0);
		for (TableItem<K, T>* temp : *list_)
		{
			if (temp->getKey() == key)
			{
				forRemove = temp;
				break;
			}
			index++;
		}
		if (forRemove)
		{
			T data = forRemove->accessData();
			delete forRemove;
			list_->removeAt(index);
			return data;
		}
		throw std::logic_error("Key is not in table");
	}

}