#pragma once
#include "TTable.h"
#include "TStack.h"

struct TTreeNode
{
	TRecord rec;
	TTreeNode* pLeft, * pRight;

	TTreeNode(
		TRecord _rec,
		TTreeNode* _pLeft = nullptr,
		TTreeNode* _pRight = nullptr);
};

TTreeNode::TTreeNode(
	TRecord _rec,
	TTreeNode* _pLeft,
	TTreeNode* _pRight)
{
	rec = _rec;
	pLeft = _pLeft;
	pRight = _pRight;
}

class TTreeTable : public TTable
{
protected:
	//Указатель на корень
	TTreeNode* pRoot;
	TTreeNode* pPrev, * pCurr;

	TStack<TTreeNode*> st;

	int pos;
	void DelRecursively(TTreeNode* pDel);
	int level;
	void PrintRecursively(std::ostream& os, TTreeNode* tmp);

public:
	TTreeTable();
	~TTreeTable();

	bool IsFull() const override;

	bool Find(TKey key) override;
	bool Insert(TRecord rec) override;
	bool Delete(TKey key) override;

	void Reset() override;
	void GoNext() override;
	bool IsEnd() override;

	TKey GetCurrentKey() const override;
	TValue GetCurrentVal() const override;

	void Print(std::ostream& os = std::cout);
};

void TTreeTable::DelRecursively(TTreeNode* pDel)
{
	if (pDel != nullptr)
	{
		DelRecursively(pDel->pRight);
		DelRecursively(pDel->pLeft);
		delete pDel;
	}
}

void TTreeTable::PrintRecursively(std::ostream& os, TTreeNode* pNode)
{
	if (pNode != nullptr)
	{
		for (int i = 0; i < level; i++)
			os << " ";
		os << pNode->rec.key << '\n';
		level++;
		PrintRecursively(os, pNode->pLeft);
		PrintRecursively(os, pNode->pRight);
		level--;
	}
}
//Копирует обычный конструктор таблицы
TTreeTable::TTreeTable() : TTable()
{
	pRoot = pPrev = pCurr = nullptr;
	pos = 0;
	level = 0;
}

TTreeTable::~TTreeTable()
{
	DelRecursively(pRoot);
}

bool TTreeTable::IsFull() const
{
	try
	{
		TTreeNode* newNode = new TTreeNode(TRecord());
		delete newNode;
		return false;
	}
	catch (...)
	{
		return true;
	}
}

bool TTreeTable::Find(TKey key)
{
	pPrev = nullptr;
	pCurr = pRoot;

	while (pCurr != nullptr)
	{
		Eff++;
		if (pCurr->rec.key == key)
			return true;
		else if (key > pCurr->rec.key)
		{
			pPrev = pCurr;
			pCurr = pCurr->pRight;
		}
		else
		{
			pPrev = pCurr;
			pCurr = pCurr->pLeft;
		}
	}

	pCurr = pPrev;
	return false;
}

bool TTreeTable::Insert(TRecord rec)
{
	if (IsFull()) throw "Can't insert: no more space in table";
	if (Find(rec.key)) return false;

	TTreeNode* newNode = new TTreeNode(rec);

	if (pRoot == nullptr)
		pRoot = newNode;
	else if (rec.key > pCurr->rec.key)
		pCurr->pRight = newNode;
	else
		pCurr->pLeft = newNode;

	Eff++;
	DataCount++;
	return true;
}

bool TTreeTable::Delete(TKey key)
{
	if (!Find(key)) return false;
	TTreeNode* pDel = pCurr;

	//1. У удаляемой вершины либо один потомок слева, либо нет потомков
	if (pCurr->pRight == nullptr)
	{
		Eff++;
		//1.1. Удаляемая вершина - корень дерева (необходимо обновить корень)
		if (pPrev == nullptr)
			pRoot = pRoot->pLeft;
		//1.2. Удаляемая вершина - обычная вершина с одним потомком слева
		else
		{
			//1.2.1. Удаляемая вершина - потомок pPrev справа
			if (pCurr->rec.key > pPrev->rec.key)
				pPrev->pRight = pCurr->pLeft;
			//1.2.2. Удаляемая вершина - потомок pPrev слева
			else
				pPrev->pLeft = pCurr->pLeft;
		}
	}
	//2. У удаляемой вершины один потомок справа, или нет потомков
	else if (pCurr->pLeft == nullptr)
	{
		Eff++;
		//2.1. Удаляемая вершина - корень дерева (необходимо обновить корень)
		if (pPrev == nullptr)
			pRoot = pRoot->pRight;
		//2.2. Удаляемая вершина - обычная вершина с одним потомком справа
		else
		{
			//2.2.1. Удаляемая вершина - потомок pPrev справа
			if (pCurr->rec.key > pPrev->rec.key)
				pPrev->pRight = pCurr->pRight;
			//2.2.2. Удаляемая вершина - потомок pPrev слева
			else
				pPrev->pLeft = pCurr->pRight;
		}
	}
	//3. У удаляемого звена 2 потомка; удаляемым звеном становится другое звено;
	//его значение сохраняется в звено, которое планировалось удалить ранее, а оно само - удаляется.
	else
	{
		TTreeNode* tmp = pCurr->pLeft;

		//Сдвиг пары указателей (pPrev и tmp)
		//На один шаг влево
		pPrev = pCurr;
		//И до упора вправо
		while (tmp->pRight != nullptr)
		{
			Eff++;
			pPrev = tmp;
			tmp = tmp->pRight;
		}
		Eff++;

		//Запись в pCurr другой записи, собственное звено которой затем будет удалено
		pCurr->rec = tmp->rec;

		//У обновлённого pPrev tmp находится справа
		if (pPrev != pCurr)
			pPrev->pRight = tmp->pLeft;
		//У обновлённого pPrev tmp находится слева
		else
			pPrev->pLeft = tmp->pLeft;

		pDel = tmp;
	}

	delete pDel;
	DataCount--;
	return true;
}

//После установки через Reset этот минимальный элемент также будет и на вершине стека
void TTreeTable::Reset()
{
	st.Clear();
	pCurr = pRoot;

	//Идём влево до упора (к звену с минимальным ключом)
	while (pCurr != nullptr)
	{
		st.Push(pCurr);
		pCurr = pCurr->pLeft;
	}
	//Установка pCurr на это звено с минимальным ключом, если таблица не пуста
	//(если пуста, получается pRoot == nullptr, как и pCurr)
	if(IsNotEmpty())
		pCurr = st.Top();
	//Установка счётчика количества пройденных элементов на начало
	pos = 0;
}

//Переход от текущей вершины на 1 шаг вправо и до упора влево, если
//есть куда переходить. Иначе вершина извлекается из стека
void TTreeTable::GoNext()
{
	TTreeNode* node = st.Pop();
	if (pCurr->pRight != nullptr)
	{
		pCurr = pCurr->pRight;
		while (pCurr != nullptr)
		{
			st.Push(pCurr);
			pCurr = pCurr->pLeft;
		}
		pCurr = st.Top();
	}
	else
		if (st.IsEmpty())
			pCurr = node->pRight;
		else
			pCurr = st.Top();
	pos++;
}

bool TTreeTable::IsEnd()
{
	//Все элементы пройдены тогда, когда все элементы пройдены
	return (pos == DataCount);
}

TKey TTreeTable::GetCurrentKey() const
{
	return pCurr->rec.key;
}

TValue TTreeTable::GetCurrentVal() const
{
	return pCurr->rec.val;
}

void TTreeTable::Print(std::ostream& os)
{
	PrintRecursively(os, pRoot);
}