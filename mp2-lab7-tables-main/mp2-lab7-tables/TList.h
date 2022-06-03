#pragma once
#include <iostream>
#include <sstream>
#include <string>

/* TListException - ����� ���������� ��� TList */

class TLException
{
private:
	std::string desc;

public:
	TLException(std::string _desc)
	{
		desc = _desc;
	}
	TLException(const TLException& e)
	{
		desc = e.desc;
	}

	friend std::ostream& operator<<(std::ostream& os, const TLException& e)
	{
		os << "Exception message: " << e.desc << '\n';
		return os;
	}
};

/* ...................... TNode ...................... */

template <class T>
struct TNode
{
	T value;
	TNode<T>* pNext;
};

/* ...................... TList ...................... */

template <class T>
class TList
{
protected:
	TNode<T>* pFirst;
	TNode<T>* pLast;
	//��� ���������� ��-�� � �������� ������ � ��������: [] -> [pPrev] -> [pCurr] -> []
	TNode<T>* pPrev;
	TNode<T>* pCurr;
	//pStop ����� ����� ��������� �� ������, ����� �� �����
	//������� ��� �������� �� ���. ������ � ����������
	TNode<T>* pStop;
	//������� ����� ������
	int length;

	virtual void Print(std::ostream& os) const;

public:
	TList();
	virtual ~TList();

	bool IsEmpty();
	bool IsNotEmpty();

	//���������� �������� � ������ ������
	virtual void InsFirst(T element);
	//���������� �������� � ����� ������
	void InsLast(T element);
	//���������� �������� � ������� ������� (����� �������) (������� ���������� �����������)
	void InsCurr(T element);

	//�������� ������� �������� ������
	virtual void DelFirst();
	//�������� �������� �������� ������ (������� ���������� ��������� �� ���)
	void DelCurr();

	//��������� �������� �������� ������
	TNode<T>* GetCurrNode();

	//������� � �������� ���������
	void Reset();
	//������� �����
	void GoNext();
	//�������� �� ���������� ���������� ����� ������
	bool IsEnd();
	bool IsNotEnd();

	std::string ToStr() const;

	friend std::ostream& operator<<(
		std::ostream& os,
		TList<T>& l)
	{
		l.Print(os);
		return os;
	}
};

template <class T>
void TList<T>::Print(std::ostream& os) const
{
	os << "[ ";
	TNode<T>* t = pFirst;

	while (t != pStop)
	{
		os << t->value << " ";
		t = t->pNext;
	}
	os << "]";
}

template <class T>
TList<T>::TList()
{
	pStop = nullptr;
	pFirst = pLast = pPrev = pCurr = pStop;
	length = 0;
}

template <class T>
TList<T>::~TList()
{
	while (pFirst != pStop)
	{
		TNode<T>* tmp = pFirst;
		pFirst = pFirst->pNext;
		delete tmp;
	}
}

template <class T>
bool TList<T>::IsEmpty()
{
	return pFirst == pStop;
}

template <class T>
bool TList<T>::IsNotEmpty()
{
	return pFirst != pStop;
}

template <class T>
void TList<T>::InsFirst(T element)
{
	TNode<T>* newNode = new TNode<T>();
	newNode->value = element;
	newNode->pNext = pFirst;
	pFirst = newNode;
	length++;
	if (length == 1)
		pLast = pFirst;
}

template <class T>
void TList<T>::InsLast(T element)
{
	if (length > 0)
	{
		TNode<T>* newNode = new TNode<T>();
		newNode->value = element;
		newNode->pNext = pStop;

		pLast->pNext = newNode;
		pLast = newNode;
		length++;
	}
	else
	{
		InsFirst(element);
	}
}

template <class T>
void TList<T>::InsCurr(T element)
{
	if (pCurr == pFirst)
	{
		InsFirst(element);
		pPrev = pFirst;
	}
	else if (pPrev == pLast)
	{
		InsLast(element);
		pPrev = pLast;
	}
	else
	{
		TNode<T>* newNode = new TNode<T>();
		newNode->value = element;

		newNode->pNext = pCurr;
		pPrev->pNext = newNode;
		pCurr = newNode;
		length++;
	}
}

template <class T>
void TList<T>::DelFirst()
{
	if (pFirst == pStop)
		throw TLException("Can't delete first element: it's a barrier");

	TNode<T>* tmp = pFirst;
	pFirst = pFirst->pNext;
	delete tmp;
	length--;
}

template <class T>
void TList<T>::DelCurr()
{
	if (pCurr == pStop)
		throw TLException("Can't delete current element: it's a barrier");

	if (pCurr == pFirst)
	{
		DelFirst();
		pPrev = pStop;
		pCurr = pFirst;
	}
	else
	{
		//��� �������� �������� ��������,
		//���� �� �������� ���������,
		//���������� �������� � pLast
		if (pCurr == pLast)
			pLast = pPrev;

		TNode<T>* tmp = pCurr;
		pCurr = pCurr->pNext;
		pPrev->pNext = pCurr;
		delete tmp;
		length--;
	}
}

template <class T>
TNode<T>* TList<T>::GetCurrNode()
{
	if (pCurr == pStop)
		throw TLException("Can't get current element: it's a barrier");
	return pCurr;
}

template <class T>
void TList<T>::Reset()
{
	pPrev = pStop;
	pCurr = pFirst;
}

template <class T>
void TList<T>::GoNext()
{
	pPrev = pCurr;
	pCurr = pCurr->pNext;
}

template <class T>
bool TList<T>::IsEnd()
{
	return pCurr == pStop;
}

template <class T>
bool TList<T>::IsNotEnd()
{
	return pCurr != pStop;
}

template <class T>
std::string TList<T>::ToStr() const
{
	std::stringstream ss;
	Print(ss);
	return ss.str();
}