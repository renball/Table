#pragma once
#include "THashTable.h"
#include "TList.h"

class TListHashTable : public THashTable
{
private:
	//Массив списков
	TList<TRecord>** arr;
	//Его размер
	int size;

	//currPos содержит номер списка
	int currPos;
	//pCurr - указатель на элемент в этом списке
	TNode<TRecord>* pCurr;

public:
	TListHashTable(int _size = 10);
	~TListHashTable();

	bool IsFull() const override;

	bool Find(TKey key) override;
	bool Insert(TRecord rec) override;
	bool Delete(TKey key) override;

	void Reset() override;
	void GoNext() override;
	bool IsEnd() override;

	TKey GetCurrentKey() const override;
	TValue GetCurrentVal() const override;
};

TListHashTable::TListHashTable(int _size)
{
	size = _size;

	arr = new TList<TRecord>*[size]();
	for (int i = 0; i < size; i++)
		arr[i] = new TList<TRecord>();

	currPos = 0;
	pCurr = nullptr;
}

TListHashTable::~TListHashTable()
{
	for (int i = 0; i < size; i++)
		delete arr[i];
	delete[] arr;
}

bool TListHashTable::IsFull() const
{
	//Если есть возможность выделить память, то таблица пока не полна.
	try
	{
		TNode<TRecord>* newNode = new TNode<TRecord>();
		delete newNode;
		return false;
	}
	catch (...)
	{
		return true;
	}
}

bool TListHashTable::Find(TKey key)
{
	currPos = HashFunc(key) % size;
	pCurr = nullptr;

	for (arr[currPos]->Reset(); !arr[currPos]->IsEnd(); arr[currPos]->GoNext())
	{
		Eff++;
		TNode<TRecord>* cn = arr[currPos]->GetCurrNode();
		if (cn->value.key == key)
		{
			pCurr = cn;
			return true;
		}
	}
	return false;
}

bool TListHashTable::Insert(TRecord rec)
{
	if (IsFull())
		throw "No more space in table";
	if (Find(rec.key))
		return false;
	arr[currPos]->InsLast(rec);
	DataCount++;
	Eff++;
	return true;
}

bool TListHashTable::Delete(TKey key)
{
	if (!Find(key))
		return false;
	arr[currPos]->DelCurr();
	DataCount--;
	Eff++;
	return true;
}

void TListHashTable::Reset()
{
	if (DataCount == 0)
	{
		currPos = -1;
		pCurr = nullptr;
		return;
	}

	for (currPos = 0; currPos < size; currPos++)
		if (arr[currPos]->IsNotEmpty())
			break;
	//pCurr установим в начало этого списка
	arr[currPos]->Reset();
	pCurr = arr[currPos]->GetCurrNode();
}

void TListHashTable::GoNext()
{
	if (arr[currPos]->GetCurrNode()->pNext != nullptr)
		arr[currPos]->GoNext();
	else
	{
		for (currPos++; currPos < size; currPos++)
			if (arr[currPos]->IsNotEmpty())
				break;

		//Выход за пределы диапазона - обход закончен
		if(currPos == size)
		{
			pCurr = nullptr;
			return;
		}
		//Продолжим обход с начала найденного списка
		arr[currPos]->Reset();
	}

	pCurr = arr[currPos]->GetCurrNode();
}

bool TListHashTable::IsEnd()
{
	return (pCurr == nullptr);
}

TKey TListHashTable::GetCurrentKey() const
{
	return pCurr->value.key;
}

TValue TListHashTable::GetCurrentVal() const
{
	return pCurr->value.val;
}