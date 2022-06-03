#pragma once
#include "TTable.h"

class TArrayTable : public TTable
{
protected:
	TRecord* arr;
	int size;
	//Текущий ключ
	int curr;

public:
	TArrayTable(int _size = 10);
	~TArrayTable();

	int GetSize() const;
	bool IsFull() const override;

	TKey GetCurrentKey() const override;
	TValue GetCurrentVal() const override;

	void Reset() override;
	void GoNext() override;
	bool IsEnd() override;
};

TArrayTable::TArrayTable(int _size)
{
	size = _size;
	arr = new TRecord[size];
	curr = -1;
}

TArrayTable::~TArrayTable()
{
	delete[] arr;
}

int TArrayTable::GetSize() const
{
	return size;
}

bool TArrayTable::IsFull() const
{
	return (DataCount == size);
}

TKey TArrayTable::GetCurrentKey() const
{
	return arr[curr].key;
}

TValue TArrayTable::GetCurrentVal() const
{
	return arr[curr].val;
}

void TArrayTable::Reset()
{
	curr = 0;
}

void TArrayTable::GoNext()
{
	curr++;
}

bool TArrayTable::IsEnd()
{
	return (curr == DataCount);
}