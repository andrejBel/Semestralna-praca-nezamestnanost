#pragma once


#include "tree.h"
#include <queue>

namespace structures
{
	/// <summary> Vrchol binarneho stromu. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych vo vrchole stromu. </typepram>
	template <typename T>
	class BinaryTreeNode : public TreeNode<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		/// <param name = "data"> Data, ktore uchovava. </param>
		BinaryTreeNode(T data);

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Vrchol binarneho stromu, z ktoreho sa prevezmu vlastnosti. </param>
		/// <remarks> Vytvori sa ako plytka kopia vrcholu other. </remarks>
		BinaryTreeNode(const BinaryTreeNode<T>& other);

		/// <summary> Destruktor. </summary>
		~BinaryTreeNode();

		/// <summary> Vytvori plytku kopiu vrchola (teda skopiruje iba data a smerniky na synov). </summary>
		/// <returns> Vystvorena plytka kopia vrcholu. </returns>
		TreeNode<T>* shallowCopy() override;

		/// <summary> Test, ci je list. </summary>
		/// <returns> true, ak je list, false inak. </returns>
		bool isLeaf() override;

		/// <summary> Spristupni syna vrcholu podla jeho pozicie v tomto vrchole. </summary>
		/// <param name = "order"> Poradie syna. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak neexistuje syn s takym poradim. </exception>
		/// <returns> Syn vrcholu. </returns>
		TreeNode<T>* getSon(int order) const override;

		/// <summary> Vlozi noveho syna vrcholu na dane miesto. </summary>
		/// <param name = "order"> Poradie syna. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak neexistuje syn s takym poradim. </exception>
		/// <remarks> Pouziva metodu replaceSon. </remarks>
		void insertSon(TreeNode<T>* son, int order) override;

		/// <summary> Nahradi syna vrcholu na danom mieste. </summary>
		/// <param name = "order"> Poradie syna. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak je poradie neplatne. </exception>
		/// <returns> Nahradeny syn vrcholu. </returns>
		/// <remarks> Vsetky smerniky zucastnenych vrcholov budu spravne nastavene. </remarks>
		TreeNode<T>* replaceSon(TreeNode<T>* son, int order) override;

		/// <summary> Odstrani syna na danom mieste. </summary>
		/// <param name = "order"> Poradie syna. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak neexistuje syn s takym poradim. </exception>
		/// <returns> Odstraneny syn vrcholu. </returns>
		/// <remarks> Pouziva metodu replaceSon s parametrom nullptr. </remarks>
		TreeNode<T>* removeSon(int order) override;

		/// <summary> Vrati stupen vrcholu. </summary>
		/// <returns> Vzdy K. </returns>
		int degree() override;

		/// <summary> Vrati pocet neNULLovych synov. </summary>
		/// <returns> Pocet neNULLovych synov. </returns>
		int numberOfSons();

		/// <summary> Getter otca. </summary>
		/// <returns> Otec. </returns>
		BinaryTreeNode<T>* getParent() const;

		/// <summary> Getter laveho syna. </summary>
		/// <returns> Lavy syn. </returns>
		BinaryTreeNode<T>* getLeftSon() const;

		/// <summary> Getter praveho syna. </summary>
		/// <returns> Pravy syn. </returns>
		BinaryTreeNode<T>* getRightSon() const;

		/// <summary> Setter laveho syna. </summary>
		/// <param name = "leftSon"> Novy lavy syn. </returns>
		/// <returns> Nahradeny lavy syn vrcholu. </returns>
		/// <remarks> Vsetky smerniky zucastnenych vrcholov budu spravne nastavene. </remarks>
		void setLeftSon(BinaryTreeNode<T>* leftSon);

		/// <summary> Setter praveho syna. </summary>
		/// <param name = "rightSon"> Novy pravy syn. </returns>
		/// <returns> Nahradeny pravy vrcholu. </returns>
		/// <remarks> Vsetky smerniky zucastnenych vrcholov budu spravne nastavene. </remarks>
		void setRightSon(BinaryTreeNode<T>* rightSon);

		/// <summary> Zameni laveho syna. </summary>
		/// <param name = "leftSon"> Novy lavy syn. </returns>
		/// <returns> Nahradeny lavy syn vrcholu. </returns>
		/// <remarks> Vsetky smerniky zucastnenych vrcholov budu spravne nastavene. </remarks>
		BinaryTreeNode<T>* changeLeftSon(BinaryTreeNode<T>* leftSon);

		/// <summary> Zameni praveho syna. </summary>
		/// <param name = "rightSon"> Novy pravy syn. </returns>
		/// <returns> Nahradeny pravy vrcholu. </returns>
		/// <remarks> Vsetky smerniky zucastnenych vrcholov budu spravne nastavene. </remarks>
		BinaryTreeNode<T>* changeRightSon(BinaryTreeNode<T>* rightSon);

		/// <summary> Zisti, ci je lavym synom svojho otca. </summary>
		/// <returns> true, ak je lavym synom svojho otca, false ak nema otca alebo nie je jeho lavym synom. </returns>
		bool isLeftSon() const;

		/// <summary> Zisti, ci je pravym synom svojho otca. </summary>
		/// <returns> true, ak je pravym synom svojho otca, false ak nema otca alebo nie je jeho pravym synom. </returns>
		bool isRightSon() const;

		/// <summary> Zisti, ci ma laveho syna. </summary>
		/// <returns> true, ma laveho syna, false inak. </returns>
		bool hasLeftSon() const;

		/// <summary> Zisti, ci ma praveho syna. </summary>
		/// <returns> true, ma praveho syna, false inak. </returns>
		bool hasRightSon() const;

	private:
		BinaryTreeNode<T>* leftSon_;
		BinaryTreeNode<T>* rightSon_;
	};

	/// <summary> Binary strom. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v strome. </typepram>
	template <typename T>
	class BinaryTree : public Tree<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		BinaryTree();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Binarny strom, z ktoreho sa prevezmu vlastnosti. </param>
		BinaryTree(const BinaryTree<T>& other);

		/// <summary> Operacia klonovania. Vytvori a vrati duplikat udajovej struktury. </summary>
		/// <returns> Ukazovatel na klon struktury. </returns>
		Structure* clone() const override;

		/// <summary> Vytvori a vrati instanciu vrcholu binarneho stromu. </summary>
		/// <returns> Vytvorena instancia vrcholu binarneho stromu. </returns>
		TreeNode<T>* createTreeNodeInstance() override;

		/// <summary> Vrati skutocny iterator na zaciatok struktury </summary>
		/// <returns> Iterator na zaciatok struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<T>* getBeginIterator() const override;

		/// <summary> Vrati skutocny iterator na koniec struktury </summary>
		/// <returns> Iterator na koniec struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<T>* getEndIterator() const override;
	public:
		class InOrderTreeIterator : public TreeIterator
		{
		public:
			/// <summary> Konstruktor. </summary>
			/// <param name = "startNode"> Vrchol podstromu, cez ktory ma iterovat. </param>
			InOrderTreeIterator(TreeNode<T>* const startNode);
		private:
			/// <summary> Zostavi do path_ prehliadku binarneho stromu v poradi inorder. </summary>
			/// <param name = "path"> Cesta stromom, ktoru zostavuje. </param>
			/// <param name = "current"> Aktualny spracovavany vrchol stromu. </param>
			void populatePath(TreeNode<T>* const current);
		};
	};

	template<typename T>
	inline BinaryTreeNode<T>::BinaryTreeNode(T data) :
		TreeNode<T>(data),
		leftSon_(0),
		rightSon_(0)
	{
	}

	template<typename T>
	inline BinaryTreeNode<T>::BinaryTreeNode(const BinaryTreeNode<T>& other) :
		TreeNode<T>(other),
		leftSon_(other.leftSon_),
		rightSon_(other.rightSon_)
	{
	}

	template<typename T>
	inline BinaryTreeNode<T>::~BinaryTreeNode()
	{
		delete leftSon_;
		leftSon_ = 0;
		delete rightSon_;
		rightSon_ = 0;
	}

	template<typename T>
	inline TreeNode<T>* BinaryTreeNode<T>::shallowCopy()
	{
		return new BinaryTreeNode(*this);
	}

	template<typename T>
	inline bool BinaryTreeNode<T>::isLeaf()
	{
		return leftSon_ == 0 && rightSon_ == 0;
	}

	template<typename T>
	inline TreeNode<T>* BinaryTreeNode<T>::getSon(int order) const
	{
		DSRoutines::rangeCheckExcept(order, 2, "Index out of range!");
		if (order == 0)
		{
			return leftSon_;
		}
		else
		{
			return rightSon_;
		}
	}

	template<typename T>
	inline void BinaryTreeNode<T>::insertSon(TreeNode<T>* son, int order)
	{
		replaceSon(son, order);
	}

	template<typename T>
	inline TreeNode<T>* BinaryTreeNode<T>::replaceSon(TreeNode<T>* son, int order)
	{
		DSRoutines::rangeCheckExcept(order, 2, "Index out of range!");
		if (order == 0)
		{
			return changeLeftSon(dynamic_cast<BinaryTreeNode<T> *>(son));
		}
		else
		{
			return changeRightSon(dynamic_cast<BinaryTreeNode<T> *>(son));
		}
	}

	template<typename T>
	inline TreeNode<T>* BinaryTreeNode<T>::removeSon(int order)
	{
		return replaceSon(0, order);
	}

	template<typename T>
	inline int BinaryTreeNode<T>::degree()
	{
		return 2;
	}

	template<typename T>
	inline int BinaryTreeNode<T>::numberOfSons()
	{
		if (leftSon_ && rightSon_)
		{
			return 2;
		}
		if (leftSon_ || rightSon_)
		{
			return 1;
		}
		return 0;
	}

	template<typename T>
	inline BinaryTreeNode<T>* BinaryTreeNode<T>::getParent() const
	{
		return dynamic_cast<BinaryTreeNode<T>*>(parent_);
	}

	template<typename T>
	inline BinaryTreeNode<T>* BinaryTreeNode<T>::getLeftSon() const
	{
		return leftSon_;
	}

	template<typename T>
	inline BinaryTreeNode<T>* BinaryTreeNode<T>::getRightSon() const
	{
		return rightSon_;
	}

	template<typename T>
	inline void BinaryTreeNode<T>::setLeftSon(BinaryTreeNode<T>* leftSon)
	{
		changeLeftSon(leftSon);
	}

	template<typename T>
	inline void BinaryTreeNode<T>::setRightSon(BinaryTreeNode<T>* rightSon)
	{
		changeRightSon(rightSon);
	}

	template<typename T>
	inline BinaryTreeNode<T>* BinaryTreeNode<T>::changeLeftSon(BinaryTreeNode<T>* leftSon)
	{
		BinaryTreeNode<T>* oldLeftSon = leftSon_;
		if (oldLeftSon)
		{
			oldLeftSon->resetParent();
		}
		leftSon_ = leftSon;
		if (leftSon_)
		{
			leftSon_->setParent(this);
		}
		return oldLeftSon;
	}

	template<typename T>
	inline BinaryTreeNode<T>* BinaryTreeNode<T>::changeRightSon(BinaryTreeNode<T>* rightSon)
	{
		BinaryTreeNode<T>* oldRightSon = rightSon_;
		if (oldRightSon)
		{
			oldRightSon->resetParent();
		}
		rightSon_ = rightSon;
		if (rightSon_)
		{
			rightSon_->setParent(this);
		}
		return oldRightSon;
	}

	template<typename T>
	inline bool BinaryTreeNode<T>::isLeftSon() const
	{
		if (!parent_)
		{
			return false;
		}
		return getParent()->getLeftSon() == this;
	}

	template<typename T>
	inline bool BinaryTreeNode<T>::isRightSon() const
	{
		if (!parent_)
		{
			return false;
		}
		return getParent()->getRightSon() == this;
	}

	template<typename T>
	inline bool BinaryTreeNode<T>::hasLeftSon() const
	{
		return leftSon_ != 0;
	}

	template<typename T>
	inline bool BinaryTreeNode<T>::hasRightSon() const
	{
		return rightSon_ != 0;
	}

	template<typename T>
	inline BinaryTree<T>::BinaryTree() :
		Tree<T>()
	{
	}

	template<typename T>
	inline BinaryTree<T>::BinaryTree(const BinaryTree<T>& other) :
		Tree<T>(other)
	{
	}

	template<typename T>
	inline Structure * BinaryTree<T>::clone() const
	{
		return new BinaryTree<T>(*this);
	}

	template<typename T>
	inline TreeNode<T>* BinaryTree<T>::createTreeNodeInstance()
	{
		T data = T();
		return new BinaryTreeNode<T>(data);
	}

	template<typename T>
	inline Iterator<T>* BinaryTree<T>::getBeginIterator() const
	{
		return new InOrderTreeIterator(root_);
	}

	template<typename T>
	inline Iterator<T>* BinaryTree<T>::getEndIterator() const
	{
		return new InOrderTreeIterator(nullptr);
	}

	template<typename T>
	inline BinaryTree<T>::InOrderTreeIterator::InOrderTreeIterator(TreeNode<T>* const startNode) :
		TreeIterator()
	{
		populatePath(startNode);
	}

	template<typename T>
	inline void BinaryTree<T>::InOrderTreeIterator::populatePath(TreeNode<T>* const current)
	{
		if (current)
		{
			BinaryTreeNode<T>* node = dynamic_cast<BinaryTreeNode<T> *>(current);
			populatePath(node->getLeftSon());
			path_->push(current);
			populatePath(node->getRightSon());
		}
	}

}

