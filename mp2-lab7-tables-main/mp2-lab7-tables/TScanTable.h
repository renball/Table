#pragma once
#include "TArrayTable.h"

class TScanTable : public TArrayTable
{
public:
	TScanTable(int _size = 10);
	//Искать по ключу
	bool Find(TKey key);
	//Вставить запись
	bool Insert(TRecord rec);
	//Удалить по ключу
	bool Delete(TKey key);
};
//Конструктор scantable копирует конструктор таблицы на массиве
TScanTable::TScanTable(int _size) : TArrayTable(_size) { }

bool TScanTable::Find(TKey key)
{
	for (int i = 0; i < DataCount; i++)
	{
		//Каждое действие - плюс к эффективности
		Eff++;
		if (arr[i].key == key)
		{
			//Если нашли - как текущий устанавливаем его
			curr = i;
			return true;
		}
	}
	//Ключ там где он мог бы быть
	curr = DataCount;
	return false;
}

bool TScanTable::Insert(TRecord rec)
{
	//Если таблица полна - вставить некуда
	if (IsFull())
		throw "No more space";

	//Если запись с таким ключом уже есть, то вставить нельзя
	if (Find(rec.key))
		return false;

	arr[DataCount] = rec;
	DataCount++;

	Eff++;
	return true;
}

bool TScanTable::Delete(TKey key)
{
	if (Find(key))
	{
		arr[curr] = arr[DataCount - 1];
		DataCount--;
		Eff++;
		return true;
	}
	else return false;
}