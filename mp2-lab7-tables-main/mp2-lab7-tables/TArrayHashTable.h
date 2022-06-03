#pragma once
#include "THashTable.h"

class TArrayHashTable : public THashTable
{
private:
	TRecord Free, Deleted;
protected:
	TRecord* arr;
	int size;
	//Шаг при хэшировании
	int step;

	int curr;

public:
	TArrayHashTable(int _size = 10, int _step = 3);
	~TArrayHashTable();

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

TArrayHashTable::TArrayHashTable(int _size, int _step)
{
	size = _size;
	step = _step;
	arr = new TRecord[size];

	Free.key = -1;
	Deleted.key = -2;

	for (int i = 0; i < size; i++)
		arr[i] = Free;
}

TArrayHashTable::~TArrayHashTable()
{
	delete[] arr;
}

bool TArrayHashTable::IsFull() const
{
	return (DataCount == size);
}

bool TArrayHashTable::Find(TKey key)
{
	int fl = -1;
	int pos = HashFunc(key) % size;
	
	for (int i = 0; i < size; i++)
	{
		Eff++;
		//По значению хэш-функции сразу найдена строка с записью, имеющей ключ key
		if (arr[pos].key == key)
		{
			curr = pos;
			return true;
		}
		//Если строка содержит удалённую запись, то запоминаем для будущей вставки
		else if (arr[pos] == Deleted && fl == -1)
		{
			curr = pos;
			fl = 1;
		}

		else if (arr[pos] == Free)
		{
			//Строка оказалось пустой, значит можно будет использовать для последующего использования
			if (fl == -1)
				curr = pos;
			break;
		}

		pos = (pos + step) % size;
	}
	return false;
}

bool TArrayHashTable::Insert(TRecord rec)
{
	if (IsFull())
		throw "No more space in table";
	if (Find(rec.key))
		return false;
	arr[curr] = rec;
	DataCount++;
	Eff++;
	return true;
}

bool TArrayHashTable::Delete(TKey key)
{
	if (IsEmpty())
		return false;
	if (Find(key))
	{
		arr[curr] = Deleted;
		DataCount--;
		Eff++;
		return true;
	}
	return false;
}

void TArrayHashTable::Reset()
{
	for (curr = 0; curr < size; curr++)
		if (arr[curr] != Free && arr[curr] != Deleted)
			return;
}

void TArrayHashTable::GoNext()
{
	//Проход от текущей занятой строки до следующей занятой строки таблицы
	for (curr++; curr < size; curr++)
		if (arr[curr] != Free && arr[curr] != Deleted)
			return;
	//если мы дошли до конца таблицы и не нашли занятых строк, то curr будет == size
}

bool TArrayHashTable::IsEnd()
{
	//Проверка на достижение конца таблицы
	return (curr == size);
}

TKey TArrayHashTable::GetCurrentKey() const
{
	return arr[curr].key;
}

TValue TArrayHashTable::GetCurrentVal() const
{
	return arr[curr].val;
}