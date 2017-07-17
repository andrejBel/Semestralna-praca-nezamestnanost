#pragma once

#include "array_list.h"

namespace structures
{

	template<typename T>
	class SortedArrayList : public ArrayList<T>
	{
	public:

		SortedArrayList();

		SortedArrayList(const SortedArrayList<T>& other);

		Structure* clone() const override;


		List<T>& operator=(const List<T>& other) override;

		SortedArrayList<T>& operator=(const SortedArrayList<T>& other);

		void add(const T& data) override;

		/// <summary> Odstrani prvy vyskyt prvku zo zoznamu. </summary>
		/// <param name = "data"> Odstranovany prvok. </param>
		/// <returns> true, ak sa podarilo prvok zo zoznamu odobrat, false inak. </returns>
		bool tryRemove(const T& data) override;

		/// <summary> Vrati index prveho vyskytu prvku v zozname. </summary>
		/// <param name = "data"> Prvok, ktoreho index sa hlada. </param>
		/// <returns> Index prveho vyskytu prvku v zozname, ak sa prvok v zozname nenachadza, vrati -1. </returns>
		int getIndexOf(const T& data) override;

	private:
		 int getIndexOfData(const T& data);

	};

	template<typename T>
	inline SortedArrayList<T>::SortedArrayList() :
		ArrayList<T>()
	{
	}

	template<typename T>
	inline SortedArrayList<T>::SortedArrayList(const SortedArrayList<T>& other):
		ArrayList(other)
	{
	}

	template<typename T>
	inline Structure * SortedArrayList<T>::clone() const
	{
		return new SortedArrayList(*this);
	}

	template<typename T>
	inline List<T>& SortedArrayList<T>::operator=(const List<T>& other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const SortedArrayList<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	inline SortedArrayList<T>& SortedArrayList<T>::operator=(const SortedArrayList<T>& other)
	{
		if (this != &other)
		{
			ArrayList<T>::operator=(other);
		}
		return *this;
	}

	template<typename T>
	inline void SortedArrayList<T>::add(const T & data)
	{
		ArrayList<T>::insert(data, getIndexOfData(data));
	}

	template<typename T>
	inline bool SortedArrayList<T>::tryRemove(const T & data)
	{
		int index = getIndexOf(data);
		if (index != -1)
		{
			ArrayList<T>::removeAt(index);
			return true;
		}
		return false;
	}

	template<typename T>
	inline int SortedArrayList<T>::getIndexOf(const T & data)
	{
		int index = getIndexOfData(data);
		if (index >= size()) 
		{
			return -1;
		}
		return (*((*this)[index]) == *data) ? index : -1;
	}

	template<typename T>
	inline int SortedArrayList<T>::getIndexOfData(const T & data)
	{
		int left = 0;
		int right = static_cast<int>(this->size());
		int middle = left + (right - left) / 2;
		T item;
		while (left < right)
		{
			middle = left + (right - left) / 2;
			item = (*this)[middle];
			if (*item == *data) 
			{
				return middle;
			}
			if (*item < *data)
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