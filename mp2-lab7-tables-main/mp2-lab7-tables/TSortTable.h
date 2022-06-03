#pragma once
#include "TScanTable.h"

//��� ��������� ���� ����������
enum class TSortingMode { QUICK_SORT, SELECTION_SORT };
TSortingMode T_SORTING_MODE;

class TSortTable : public TScanTable
{
public:
	TSortTable(int _size = 10);
	TSortTable(TScanTable& st);

	bool Find(TKey key);
	bool Insert(TRecord rec);
	bool Delete(TKey key);

private:
	void QuickSort(int first, int last);
	void SelectionSort();
	void Sort();
};

TSortTable::TSortTable(int _size) : TScanTable(_size) { }

TSortTable::TSortTable(TScanTable& st) : TScanTable(st.GetSize())
{
	//����������� ���� ������� �� TScanTable
	DataCount = st.GetDataCount();
	int i;
	for (i = 0, st.Reset(); !st.IsEnd(); st.GoNext(), i++)
	{
		arr[i] = TRecord(st.GetCurrentKey(), st.GetCurrentVal());
		Eff++;
	}
	//���������� ��������� ������� �������
	Sort();
}
//�������� �����
bool TSortTable::Find(TKey key)
{
	int begin = 0, end = DataCount - 1;
	int mid;

	while (begin <= end)
	{
		Eff++;

		mid = (begin + end) / 2;

		//���� �����
		if (key < arr[mid].key)
			end = mid - 1;
		//���� ������
		else if (key > arr[mid].key)
			begin = mid + 1;
		//���� key == arr[mid].key
		else
		{
			//curr ������ ���� �����
			curr = mid;
			return true;
		}
	}
	curr = begin;
	return false;
}

bool TSortTable::Insert(TRecord rec)
{
	if (IsFull())
		throw "No more space";

	if (Find(rec.key))
		return false;

	//������� ������� �� ������� curr
	for (int i = DataCount - 1; i >= curr; i--)
	{
		//�������� ������
		Eff++;
		arr[i + 1] = arr[i];
	}
	//�������
	Eff++;
	arr[curr] = rec;
	DataCount++;
	return true;
}
//�������� �� curr �������� � Find
bool TSortTable::Delete(TKey key)
{
	if (Find(key))
	{
		for (int i = curr + 1; i <= DataCount - 1; i++)
		{
			//�������� ���� ����� �����
			Eff++;
			arr[i - 1] = arr[i];
		}
		DataCount--;
		return true;
	}
	else return false;
}

//������� ����������
void TSortTable::QuickSort(int first, int last)
{
	TKey midKey = arr[(first + last) / 2].key;

	int f = first, l = last;
	while (f < l)
	{
		while (arr[f].key < midKey)
		{
			f++;
			Eff++;
		}
		while (arr[l].key > midKey)
		{
			l--;
			Eff++;
		}

		if (f <= l)
		{
			std::swap(arr[f], arr[l]);
			f++; l--;
			Eff++;
		}
	}

	if (first < l)
		QuickSort(first, l);
	if (last > f)
		QuickSort(f, last);
}

//���������� ��������
void TSortTable::SelectionSort()
{
	int pos;

	for (int i = 0; i < DataCount; i++)
	{
		pos = i;
		
		for (int j = i; j < DataCount; j++)
		{
			Eff++;
			if (arr[j].key < arr[pos].key)
				pos = j;
		}
		std::swap(arr[pos], arr[i]);
		Eff++;
	}
}

void TSortTable::Sort()
{
	if (T_SORTING_MODE == TSortingMode::QUICK_SORT)
		QuickSort(0, DataCount - 1);
	else if (T_SORTING_MODE == TSortingMode::SELECTION_SORT)
		SelectionSort();
}