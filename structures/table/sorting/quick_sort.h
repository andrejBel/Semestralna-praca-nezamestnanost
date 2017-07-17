#pragma once

#include "sort.h"
#include "../unsorted_sequence_table.h"
#include <cstdlib>

namespace structures
{

	/// <summary> Triedenie Quick sort. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class QuickSort : public Sort<K, T>
	{
	public:
		/// <summary> Utriedi tabulku triedenim Quick sort. </summary>
		/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
		void sort(UnsortedSequenceTable<K, T>& table, const Comparator<K, T>& comparator) override;
	private:

		void quickSort(UnsortedSequenceTable<K, T>& table, int min, int max, const Comparator<K, T>& comparator);

	};

	template<typename K, typename T>
	inline void QuickSort<K, T>::sort(UnsortedSequenceTable<K, T>& table, const Comparator<K, T>& comparator)
	{
		quickSort(table, 0, table.size() - 1, comparator);
	}

	template<typename K, typename T>
	inline void QuickSort<K, T>::quickSort(UnsortedSequenceTable<K, T>& table, int min, int max, const Comparator<K, T>& comparator)
	{
		TableItem<K,T>& pivot = table.getItemAtIndex((max + min) / 2);
		int left = min;
		int right = max;
		do
		{
			while (comparator.compare(table.getItemAtIndex(left), pivot) < 0)
			{
				left++;
			}
			while (comparator.compare(table.getItemAtIndex(right), pivot) > 0)
			{
				right--;
			}
			if (left <= right)
			{
				table.swap(left, right);
				left++;
				right--;
			}
		} while (left <= right);
		if (min < right)
		{
			quickSort(table, min, right, comparator);
		}
		if (left < max)
		{
			quickSort(table, left, max, comparator);
		}
	}

}