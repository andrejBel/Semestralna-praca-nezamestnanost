#pragma once

#include "sort.h"
#include "../unsorted_sequence_table.h"

namespace structures
{

	/// <summary> Triedenie Select sort. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class SelectSort : public Sort<K, T>
	{
	public:
		/// <summary> Utriedi tabulku triedenim Select sort. </summary>
		/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
		void sort(UnsortedSequenceTable<K, T>& table, const Comparator<K, T>& comparator) override;
	};

	template<typename K, typename T>
	inline void SelectSort<K, T>::sort(UnsortedSequenceTable<K, T>& table, const Comparator<K, T>& comparator)
	{
		int length = table.size();
		int minIndex(0);
		for (int i = 0; i < length -1; i++)
		{
			minIndex = i;
			for (int j = i + 1; j < length; j++)
			{
				if (comparator.compare(table.getItemAtIndex(j) ,table.getItemAtIndex(minIndex)) < 0)
				{
					minIndex = j;
				}
			}
			table.swap(i, minIndex);
		}

	}

}