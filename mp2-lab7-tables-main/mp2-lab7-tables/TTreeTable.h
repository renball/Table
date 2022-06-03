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
	//��������� �� ������
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
//�������� ������� ����������� �������
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

	//1. � ��������� ������� ���� ���� ������� �����, ���� ��� ��������
	if (pCurr->pRight == nullptr)
	{
		Eff++;
		//1.1. ��������� ������� - ������ ������ (���������� �������� ������)
		if (pPrev == nullptr)
			pRoot = pRoot->pLeft;
		//1.2. ��������� ������� - ������� ������� � ����� �������� �����
		else
		{
			//1.2.1. ��������� ������� - ������� pPrev ������
			if (pCurr->rec.key > pPrev->rec.key)
				pPrev->pRight = pCurr->pLeft;
			//1.2.2. ��������� ������� - ������� pPrev �����
			else
				pPrev->pLeft = pCurr->pLeft;
		}
	}
	//2. � ��������� ������� ���� ������� ������, ��� ��� ��������
	else if (pCurr->pLeft == nullptr)
	{
		Eff++;
		//2.1. ��������� ������� - ������ ������ (���������� �������� ������)
		if (pPrev == nullptr)
			pRoot = pRoot->pRight;
		//2.2. ��������� ������� - ������� ������� � ����� �������� ������
		else
		{
			//2.2.1. ��������� ������� - ������� pPrev ������
			if (pCurr->rec.key > pPrev->rec.key)
				pPrev->pRight = pCurr->pRight;
			//2.2.2. ��������� ������� - ������� pPrev �����
			else
				pPrev->pLeft = pCurr->pRight;
		}
	}
	//3. � ���������� ����� 2 �������; ��������� ������ ���������� ������ �����;
	//��� �������� ����������� � �����, ������� ������������� ������� �����, � ��� ���� - ���������.
	else
	{
		TTreeNode* tmp = pCurr->pLeft;

		//����� ���� ���������� (pPrev � tmp)
		//�� ���� ��� �����
		pPrev = pCurr;
		//� �� ����� ������
		while (tmp->pRight != nullptr)
		{
			Eff++;
			pPrev = tmp;
			tmp = tmp->pRight;
		}
		Eff++;

		//������ � pCurr ������ ������, ����������� ����� ������� ����� ����� �������
		pCurr->rec = tmp->rec;

		//� ����������� pPrev tmp ��������� ������
		if (pPrev != pCurr)
			pPrev->pRight = tmp->pLeft;
		//� ����������� pPrev tmp ��������� �����
		else
			pPrev->pLeft = tmp->pLeft;

		pDel = tmp;
	}

	delete pDel;
	DataCount--;
	return true;
}

//����� ��������� ����� Reset ���� ����������� ������� ����� ����� � �� ������� �����
void TTreeTable::Reset()
{
	st.Clear();
	pCurr = pRoot;

	//��� ����� �� ����� (� ����� � ����������� ������)
	while (pCurr != nullptr)
	{
		st.Push(pCurr);
		pCurr = pCurr->pLeft;
	}
	//��������� pCurr �� ��� ����� � ����������� ������, ���� ������� �� �����
	//(���� �����, ���������� pRoot == nullptr, ��� � pCurr)
	if(IsNotEmpty())
		pCurr = st.Top();
	//��������� �������� ���������� ���������� ��������� �� ������
	pos = 0;
}

//������� �� ������� ������� �� 1 ��� ������ � �� ����� �����, ����
//���� ���� ����������. ����� ������� ����������� �� �����
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
	//��� �������� �������� �����, ����� ��� �������� ��������
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