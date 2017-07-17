#pragma once

#include "sort.h"
#include "../unsorted_sequence_table.h"
#include "../../queue/explicit_queue.h"


namespace structures
{

	/// <summary> Triedenie Merge sort. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class MergeSort : public Sort<K, T>
	{
	public:
		/// <summary> Utriedi tabulku triedenim Merge sort. </summary>
		/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
		void sort(UnsortedSequenceTable<K, T>& table, const Comparator<K, T>& comparator) override;
	private:
		void join(int n, Queue<TableItem<K, T> *>* joinedQueue, Queue<TableItem<K, T> *>* dividedQueue1, Queue<TableItem<K, T> *>* dividedQueue2, const Comparator<K, T>& comparator);
		void divide(int n, Queue<TableItem<K, T> *>* joinedQueue, Queue<TableItem<K, T> *>* dividedQueue1, Queue<TableItem<K, T> *>* dividedQueue2);
	};



	template<typename K, typename T>
	inline void MergeSort<K, T>::sort(UnsortedSequenceTable<K, T>& table, const Comparator<K, T>& comparator)
	{
		Queue<TableItem<K, T> *>* joinedQueue = new ExplicitQueue<TableItem<K, T> *>();
		Queue<TableItem<K, T> *>* dividedQueue1 = new ExplicitQueue<TableItem<K, T> *>();
		Queue<TableItem<K, T> *>* dividedQueue2 = new ExplicitQueue<TableItem<K, T> *>();
		for (TableItem<K, T>* item : table)
		{
			joinedQueue->push(new TableItem<K, T>(*item));
		}
		int i = 1;
		int pocetPrvkov = table.size();
		while (i < pocetPrvkov)
		{
			divide(i, joinedQueue, dividedQueue1, dividedQueue2);
			join(i, joinedQueue, dividedQueue1, dividedQueue2, comparator);
			i *= 2;
		}
		divide(i, joinedQueue, dividedQueue1, dividedQueue2);
		join(i, joinedQueue, dividedQueue1, dividedQueue2, comparator);
		table.clear();
		while (joinedQueue->size())
		{
			TableItem<K, T>* pair = joinedQueue->pop();
			table.insert(pair->getKey(), pair->accessData(), false);
			delete pair;
		}
		delete joinedQueue;
		delete dividedQueue1;
		delete dividedQueue2;
	}

	template<typename K, typename T>
	inline void MergeSort<K, T>::join(int n, Queue<TableItem<K, T> *>* joinedQueue, Queue<TableItem<K, T> *>* dividedQueue1, Queue<TableItem<K, T> *>* dividedQueue2, const Comparator<K, T>& comparator)
	{
		int prvych(0);
		int druhych(0);
		TableItem<K, T>* par1;
		TableItem<K, T>* par2;
		do
		{
			if (prvych == 0 && druhych == 0)
			{
				prvych = n < static_cast<int>(dividedQueue1->size()) ? n : static_cast<int>(dividedQueue1->size());
				druhych = n < static_cast<int>(dividedQueue2->size()) ? n : static_cast<int>(dividedQueue2->size());
			}
			par1 = prvych > 0 ? dividedQueue1->peek() : 0;
			par2 = druhych > 0 ? dividedQueue2->peek() : 0;
			if (par1 && par2)
			{
				if (comparator.compare(*par1, *par2) < 0)
				{
					prvych--;
					joinedQueue->push(dividedQueue1->pop());
				}
				else
				{
					druhych--;
					joinedQueue->push(dividedQueue2->pop());
				}
			}
			else
			{
				if (par1)
				{
					prvych--;
					joinedQueue->push(dividedQueue1->pop());
				}
				else if (par2)
				{
					druhych--;
					joinedQueue->push(dividedQueue2->pop());
				}
			}
		} while (!dividedQueue1->isEmpty() || !dividedQueue2->isEmpty());
	}

	template<typename K, typename T>
	inline void MergeSort<K, T>::divide(int n, Queue<TableItem<K, T> *>* joinedQueue, Queue<TableItem<K, T> *>* dividedQueue1, Queue<TableItem<K, T> *>* dividedQueue2)
	{
		int pocet(0);
		bool prvy(true);
		while (joinedQueue->size())
		{
			if ((pocet % n) == 0)
			{
				pocet = 0;
				prvy = !prvy;
			}
			if (prvy)
			{
				dividedQueue1->push(joinedQueue->pop());
			}
			else
			{
				dividedQueue2->push(joinedQueue->pop());
			}
			pocet++;
		}
	}

}