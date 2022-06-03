#pragma once
#include "TArrayTable.h"

class TScanTable : public TArrayTable
{
public:
	TScanTable(int _size = 10);
	//������ �� �����
	bool Find(TKey key);
	//�������� ������
	bool Insert(TRecord rec);
	//������� �� �����
	bool Delete(TKey key);
};
//����������� scantable �������� ����������� ������� �� �������
TScanTable::TScanTable(int _size) : TArrayTable(_size) { }

bool TScanTable::Find(TKey key)
{
	for (int i = 0; i < DataCount; i++)
	{
		//������ �������� - ���� � �������������
		Eff++;
		if (arr[i].key == key)
		{
			//���� ����� - ��� ������� ������������� ���
			curr = i;
			return true;
		}
	}
	//���� ��� ��� �� ��� �� ����
	curr = DataCount;
	return false;
}

bool TScanTable::Insert(TRecord rec)
{
	//���� ������� ����� - �������� ������
	if (IsFull())
		throw "No more space";

	//���� ������ � ����� ������ ��� ����, �� �������� ������
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