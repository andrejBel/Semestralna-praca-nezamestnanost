#pragma once

#include "sort.h"
#include "../unsorted_sequence_table.h"

namespace structures
{

	/// <summary> Triedenie Heap sort. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class HeapSort : public Sort<K, T>
	{
	public:
		/// <summary> Utriedi tabulku triedenim Heap sort. </summary>
		/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
		void sort(UnsortedSequenceTable<K, T>& table) override;
	};

	template<typename K, typename T>
	inline void HeapSort<K, T>::sort(UnsortedSequenceTable<K, T>& table)
	{
		int comparator;
		bool vymena(0);
		int length(table.size());
		int aktualny(0);
		int otec(0);
		for (int i = 1; i <= length - 1; i++)
		{
			aktualny = i;
			do
			{
				vymena = false;
				otec = (aktualny - 1) / 2;
				if (aktualny > 0 && table.getItemAtIndex(aktualny).getKey() > table.getItemAtIndex(otec).getKey() )
				{
					table.swap(aktualny, otec);
					aktualny = otec;
					vymena = true;
				}
			} while (vymena);
		}
		int lavy(0);
		int pravy(0);
		int max(0);
		for (int i = length - 1; i >= 1; i--)
		{
			table.swap(0, i);
			aktualny = 0;
			do
			{
				vymena = false;
				lavy = aktualny * 2 + 1;
				pravy = aktualny * 2 + 2;
				if (lavy < i && pravy < i)
				{
					max = table.getItemAtIndex(lavy).getKey() > table.getItemAtIndex(pravy).getKey() ? lavy : pravy;
				}
				else
				{
					max = lavy < i ? lavy : pravy;
				}
				if (max < i && table.getItemAtIndex(max).getKey() > table.getItemAtIndex(aktualny).getKey() )
				{
					table.swap(max, aktualny);
					aktualny = max;
					vymena = true;
				}
			} while (vymena);
		}
	}

}