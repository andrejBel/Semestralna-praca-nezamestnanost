#pragma once

#include "table.h"
#include "linked_table.h"
#include "../array/array.h"
#include "../structure_iterator.h"
#include <stdexcept>
#include <cmath>
#include <iostream>

namespace structures
{

	/// <summary> Hashovacia tabulka. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class HashTable : public Table<K, T>
	{
	private:
		static const int DATA_ARRAY_SIZE = 100;
	public:
		/// <summary> Konstruktor. </summary>
		HashTable();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> HashTable, z ktorej sa prevezmu vlastnosti. </param>
		HashTable(const HashTable<K, T>& other);

		/// <summary> Destruktor. </summary>
		~HashTable();

		/// <summary> Operacia klonovania. Vytvori a vrati duplikat udajovej struktury. </summary>
		/// <returns> Ukazovatel na klon struktury. </returns>
		virtual Structure* clone() const;

		/// <summary> Vrati pocet prvkov v tabulke. </summary>
		/// <returns> Pocet prvkov v tabulke. </returns>
		size_t size() const override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Tabulka, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tato tabulka nachadza po priradeni. </returns>
		Table<K, T>& operator=(const Table<K, T>& other) override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Hashovacia tabulka, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tato tabulka nachadza po priradeni. </returns>
		virtual HashTable<K, T>& operator=(const HashTable<K, T>& other);

		/// <summary> Vrati adresou data s danym klucom. </summary>
		/// <param name = "key"> Kluc dat. </param>
		/// <returns> Adresa dat s danym klucom. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak kluc nepatri do tabulky. </exception>  
		T& operator[](const K key) override;

		/// <summary> Vrati hodnotou data s daynm klucom. </summary>
		/// <param name = "key"> Kluc dat. </param>
		/// <returns> Hodnota dat s danym klucom. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak kluc nepatri do zoznamu. </exception>  
		const T operator[](const K key) const override;

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

		/// <summary> Bezpecne ziska data s danym klucom. </summary>
		/// <param name = "key"> Kluc dat. </param>
		/// <param name = "data"> Najdene data (vystupny parameter). </param>
		/// <returns> true, ak sa podarilo najst a naplnit data s danym klucom, false inak. </returns>
		bool tryFind(const K& key, T& data) override;

		/// <summary> Zisti, ci tabulka obsahuje data s danym klucom. </summary>
		/// <param name = "key"> Kluc dat. </param>
		/// <returns> true, tabulka obsahuje dany kluc, false inak. </returns>
		bool containsKey(const K& key) override;

		/// <summary> Vymaze tabulku. </summary>
		void clear() override;

		/// <summary> Vrati skutocny iterator na zaciatok struktury </summary>
		/// <returns> Iterator na zaciatok struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<TableItem<K, T>*>* getBeginIterator() const override;

		/// <summary> Vrati skutocny iterator na koniec struktury </summary>
		/// <returns> Iterator na koniec struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<TableItem<K, T>*>* getEndIterator() const override;
	protected:
		/// <summary> Pole s datami. </summary>
		Array<Table<K, T>*>* data_;
		/// <summary> Pocet prvkov v binarnom vyhladavacom strome. </summary>
		size_t size_;
	private:
		/// <summary> Hashovacia funkcia zahashuje kluc na indexu v poli dat. </summary>
		/// <param name = "key"> Kluc dat. </param>
		/// <returns> Index do pola dat, ktory vznikol zahashovanim kluca. </returns>
		int hashFunction(const K& key) const;

	private:
		/// <summary> Iterator pre HashTable. </summary>
		class HashTableIterator : public Iterator<TableItem<K, T>*>
		{
		public:
			/// <summary> Konstruktor. </summary>
			/// <param name = "hashTable"> Hashovacia tabulka, cez ktoru iteruje. </param>
			/// <param name = "position"> Pozicia, na ktorej zacina. </param>
			HashTableIterator(const HashTable<K, T>* hashTable, int position);

			/// <summary> Destruktor. </summary>
			~HashTableIterator();

			/// <summary> Operator priradenia. Priradi do seba hodnotu druheho iteratora. </summary>
			/// <param name = "other"> Druhy iterator. </param>
			/// <returns> Vrati seba po priradeni. </returns>
			Iterator<TableItem<K, T>*>& operator= (const Iterator<TableItem<K, T>*>& other) override;

			/// <summary> Porovna sa s druhym iteratorom na nerovnost. </summary>
			/// <param name = "other"> Druhy iterator. </param>
			/// <returns> True, ak sa iteratory nerovnaju, false inak. </returns>
			bool operator!=(const Iterator<TableItem<K, T>*>& other) override;

			/// <summary> Vrati data, na ktore aktualne ukazuje iterator. </summary>
			/// <returns> Data, na ktore aktualne ukazuje iterator. </returns>
			TableItem<K, T>* const operator*() override;

			/// <summary> Posunie iterator na dalsi prvok v strukture. </summary>
			/// <returns> Iterator na dalsi prvok v strukture. </returns>
			/// <remarks> Zvycajne vrati seba. Ak vrati iny iterator, povodny bude automaticky zruseny. </remarks>
			Iterator<TableItem<K, T>*>& operator++() override;
		private:
			/// <summary> Hashovacia tabulka, cez ktoru iteruje. </summary>
			const HashTable<K, T>* hashTable_;
			/// <summary> Aktualna pozicia v poli v tabulke. </summary>
			int position_;
			/// <summary> Aktualmy iterator preplnovacej tabulky v poli. </summary>
			Iterator<TableItem<K, T>*>* iterCurr_;
			/// <summary> Koncovy iterator preplnovacej tabulky v poli. </summary>
			Iterator<TableItem<K, T>*>* iterLast_;

			/// <summary> 
			/// Zmeni hodnotu v atribute position_ na najblizsiu preplnovaciu tabulku v poli tabuliek. 
			/// Ak sa taka tabulka najde, nastavi iterCurr_ a iterLast_.
			/// </summary>
			void movePositionInArray();
		};
	};

	template<typename K, typename T>
	inline HashTable<K, T>::HashTable() :
		Table<K, T>(),
		data_(new Array<Table<K, T>*>(DATA_ARRAY_SIZE)),
		size_(0)
	{
	}

	template<typename K, typename T>
	inline HashTable<K, T>::HashTable(const HashTable<K, T>& other) :
		HashTable()
	{
		*this = other;
	}

	template<typename K, typename T>
	inline HashTable<K, T>::~HashTable()
	{
		clear();
		delete data_;
		data_ = 0;
	}

	template<typename K, typename T>
	inline Structure * HashTable<K, T>::clone() const
	{
		return new HashTable<K, T>(*this);
	}

	template<typename K, typename T>
	inline size_t HashTable<K, T>::size() const
	{
		return this->size_;
	}

	template<typename K, typename T>
	inline Table<K, T>& HashTable<K, T>::operator=(const Table<K, T>& other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const HashTable<K, T>&>(other);
		}
		return *this;
	}

	template<typename K, typename T>
	inline HashTable<K, T>& HashTable<K, T>::operator=(const HashTable<K, T>& other)
	{
		if (this != &other)
		{
			clear();
			for (int i = 0; i < HashTable<K, T>::DATA_ARRAY_SIZE; i++)
			{
				if ((*other.data_)[i])
				{
					(*data_)[i] = new LinkedTable<K, T>(dynamic_cast<const LinkedTable<K, T>&>(*((*other.data_)[i])));
				}
			}
			size_ = other.size_;
		}
		return *this;
	}

	template<typename K, typename T>
	inline T & HashTable<K, T>::operator[](const K key)
	{
		return (*((*data_)[hashFunction(key)]))[key];
	}

	template<typename K, typename T>
	inline const T HashTable<K, T>::operator[](const K key) const
	{
		return (*((*data_)[hashFunction(key)]))[key];
	}

	template<typename K, typename T>
	inline void HashTable<K, T>::insert(const K & key, const T & data, bool check)
	{
		int keyIndex = hashFunction(key);
		if (!(*data_)[keyIndex])
		{
			(*data_)[keyIndex] = new LinkedTable<K, T>();
		}
		(*data_)[keyIndex]->insert(key, data);
		size_++;
	}

	template<typename K, typename T>
	inline T HashTable<K, T>::remove(const K & key)
	{
		int keyIndex = hashFunction(key);
		if ((*data_)[keyIndex])
		{
			T data = (*data_)[keyIndex]->remove(key);
			size_--;
			return data;
		}
		else 
		{
			throw std::logic_error("Key is not in table");
		}
	}

	template<typename K, typename T>
	inline bool HashTable<K, T>::tryFind(const K & key, T & data)
	{
		int keyIndex = hashFunction(key);
		if ((*data_)[keyIndex])
		{
			return (*data_)[keyIndex]->tryFind(key, data);
		}
		return false;
	}

	template<typename K, typename T>
	inline bool HashTable<K, T>::containsKey(const K & key)
	{
		int keyIndex = hashFunction(key);
		if ((*data_)[keyIndex])
		{
			return (*data_)[keyIndex]->containsKey(key);
		}
		return false;
	}

	template<typename K, typename T>
	inline void HashTable<K, T>::clear()
	{
		for (int i = 0; i < HashTable<K, T>::DATA_ARRAY_SIZE; i++)
		{
			if ((*data_)[i])
			{
				delete (*data_)[i];
				(*data_)[i] = 0;
			}
		}
		size_ = 0;
	}

	template<typename K, typename T>
	inline Iterator<TableItem<K, T>*>* HashTable<K, T>::getBeginIterator() const
	{
		return new HashTableIterator(this, 0);
	}

	template<typename K, typename T>
	inline Iterator<TableItem<K, T>*>* HashTable<K, T>::getEndIterator() const
	{
		return new HashTableIterator(this, static_cast<int>(DATA_ARRAY_SIZE));
	}

	template<typename K, typename T>
	inline int HashTable<K, T>::hashFunction(const K & key) const
	{
		short sizeLong = sizeof(T) / sizeof(unsigned long);
		unsigned long * longPointer = (unsigned long *)&key;
		unsigned long sum(0);
		int i(0);
		for (i = 0; i < sizeLong; i++)
		{
			sum += longPointer[i];
		}
		if (!sizeLong)
		{
			short sizeLongLeft = sizeof(T) % sizeof(unsigned long);
			byte* whatIsLeft = (byte *)(longPointer + i);
			for (int i = 0; i < sizeLongLeft; i++)
			{
				sum += whatIsLeft[i];
			}
		}
		return sum % HashTable<K, T>::DATA_ARRAY_SIZE;
	}



	template<typename K, typename T>
	inline HashTable<K, T>::HashTableIterator::HashTableIterator(const HashTable<K, T>* hashTable, int position) :
		Iterator<TableItem<K, T>*>(),
		hashTable_(hashTable),
		position_(position),
		iterCurr_(nullptr),
		iterLast_(nullptr)
	{
		movePositionInArray();
	}

	template<typename K, typename T>
	inline HashTable<K, T>::HashTableIterator::~HashTableIterator()
	{
		delete iterCurr_;
		delete iterLast_;
		iterCurr_ = 0;
		iterLast_ = 0;
	}

	template<typename K, typename T>
	inline Iterator<TableItem<K, T>*>& HashTable<K, T>::HashTableIterator::operator=(const Iterator<TableItem<K, T>*>& other)
	{
		if (this != &other)
		{
			const HashTable<K, T>::HashTableIterator& otherTyped = dynamic_cast<const HashTable<K, T>::HashTableIterator&>(other);
			this->hashTable_ = otherTyped.hashTable_;
			position_ = otherTyped.position_;
			iterCurr_ = otherTyped.iterCurr_;
			iterLast_ = otherTyped.iterLast_;
		}
		return *this;
	}

	template<typename K, typename T>
	inline bool HashTable<K, T>::HashTableIterator::operator!=(const Iterator<TableItem<K, T>*>& other)
	{
		const HashTable<K, T>::HashTableIterator& otherTyped = dynamic_cast<const HashTable<K, T>::HashTableIterator&>(other);
		return (position_ ) != otherTyped.position_;
	}

	template<typename K, typename T>
	inline TableItem<K, T>* const HashTable<K, T>::HashTableIterator::operator*()
	{
		return *(*iterCurr_);
	}

	template<typename K, typename T>
	inline Iterator<TableItem<K, T>*>& HashTable<K, T>::HashTableIterator::operator++()
	{
		if (iterCurr_)
		{
			iterCurr_->operator++();
		}
		this->movePositionInArray();
		return *this;
	}

	template<typename K, typename T>
	inline void HashTable<K, T>::HashTableIterator::movePositionInArray()
	{
		const static int limit = this->hashTable_->DATA_ARRAY_SIZE;

		if (!iterCurr_ && !iterLast_)
		{
			while (position_ < limit)
			{
				if ((*hashTable_->data_)[position_])
				{
					iterCurr_ = (*hashTable_->data_)[position_]->getBeginIterator();
					iterLast_ = (*hashTable_->data_)[position_]->getEndIterator();
					break;
				}
				position_++;
			}
		}
		else if (!(*iterCurr_ != *iterLast_))
		{
			while ((position_) < limit)
			{
				position_++;
				if (position_ < limit) 
				{
					if ((*hashTable_->data_)[position_])
					{
						delete iterCurr_;
						delete iterLast_;
						iterCurr_ = (*hashTable_->data_)[position_]->getBeginIterator();
						iterLast_ = (*hashTable_->data_)[position_]->getEndIterator();
						break;
					}
				}
			}
		}

	}

}

