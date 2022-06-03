#include <iostream>
#include <clocale>
#include <cmath>
#include "TSortTable.h"
#include "TArrayHashTable.h"
#include "TListHashTable.h"
#include "TTreeTable.h"
#include "randomizer.h"

using namespace std;

TTable* pTable;

//Заполнение таблицы рандомайзером
void CreateTable(TTable* table, int entriesCount, int keyMax)
{
	for (int i = 0; i < entriesCount; i++)
	{
		TKey randKey = Randomex::RandInt(0, keyMax);

		bool inserted = table->Insert(TRecord(randKey, "val_" + to_string(randKey*2)));
		if (!inserted) i--;
	}
}
//Вывод таблицы на экран
void PrintTable(TTable* table)
{
	//Для обычных таблиц
	if ((*pTable).IsNotEmpty())
		cout << (*pTable) << "\n";
	else
		cout << "Данная таблица пуста.\n\n";
	//Для дерева
	if (typeid(*table) == typeid(TTreeTable))
	{
		cout << "Древо:\n";
		((TTreeTable*)table)->Print();
	}
}

int main()
{
	setlocale(LC_ALL, "russian");
	Randomex::Init();

	while (true)
	{
		cout << "1  -  TScanTable (просматриваемая);\n";
		cout << "2  -  TSortTable (сортированная);\n";
		cout << "3  -  TSortTable (QuickSort);\n";
		cout << "4  -  TSortTable (SelectionSort);\n";
		cout << "5  -  TArrayHashTable (хэш-таблица на массиве);\n";
		cout << "6  -  TListHashTable (хэш-таблица на списке);\n";
		cout << "7  -  TTreeTable (тадлица в виде дерева);\n";

		int type;
		cout << "Выбор типа таблицы: ";
		cin >> type;

		int size = -1;

		if (type != 7)
		{
			cout << "Выбор размера таблицы: ";
			cin >> size;
		}

		int count;
		cout << "Число случайных записей (ключ-значение): ";
		cin >> count;

		int kmax;
		cout << "Диапазон возможных ключей от 0 до:";
		cin >> kmax;

		//Кнопки навигации
		switch (type)
		{
		case 1:
		{
			pTable = new TScanTable(size);
			CreateTable(pTable, count, kmax);
			break;
		}
		case 2:
		{
			pTable = new TSortTable(size);
			CreateTable(pTable, count, kmax);
			break;
		}
		case 3:
		{
			TScanTable* temp1 = new TScanTable(size);
			CreateTable(temp1, count, kmax);

			cout << "\nПервичная таблица: \n";
			cout << (*temp1) << "\n\n";

			T_SORTING_MODE = TSortingMode::QUICK_SORT;
			pTable = new TSortTable(*temp1);
			delete temp1;
			break;
		}
		case 4:
		{
			TScanTable* temp2 = new TScanTable(size);
			CreateTable(temp2, count, kmax);

			cout << "\nПервичная таблица: \n";
			cout << (*temp2) << "\n\n";

			T_SORTING_MODE = TSortingMode::SELECTION_SORT;
			pTable = new TSortTable(*temp2);
			delete temp2;
			break;
		}
		case 5:
		{
			int step;
			cout << "Шаг вторичного перемешивания: ";
			cin >> step;

			pTable = new TArrayHashTable(size, step);
			CreateTable(pTable, count, kmax);
			break;
		}
		case 6:
		{
			pTable = new TListHashTable(size);
			CreateTable(pTable, count, kmax);
			break;
		}
		case 7:
		{
			pTable = new TTreeTable();
			CreateTable(pTable, count, kmax);
			break;
		}
		}

		cout << "Эффективность генерации: " << pTable->GetEfficiency() << "\n\n";
		PrintTable(pTable);

		pTable->ClearEfficiency();

		while (true)
		{
			TKey key;
			cout << "Ввод нового ключа (-1 смена типа таблицы): ";
			cin >> key;
			cout << '\n';
			if (key == -1) break;

			cout << "1.Поиск этого ключа, 2.Добавление этого ключа, 3.Удаление этого ключа: ";
			int option;
			cin >> option;

			if (option == 1)
			{
				bool result = pTable->Find(key);

				if (result)
					cout << "Удалось найти элемент " << key << ". "
					<< "Эффективность: " << pTable->GetEfficiency() << "\n\n";
				else
					cout << "Не найден элемент " << key << ". "
					<< "Эффективность: " << pTable->GetEfficiency() << "\n\n";
				pTable->ClearEfficiency();
			}
			else if (option == 2)
			{
				bool result = false;

				try
				{
					result = pTable->Insert(
						TRecord(key, "val_" + to_string(key*2)));

					if (result)
					{
						cout << "Добавлено. Эффективность: "
							<< pTable->GetEfficiency() << "\n\n";
						cout << "Таблица:\n";
						PrintTable(pTable);
					}
					else
						cout << "Элемент с таким ключом уже есть в таблице. Эффективность: "
						<< pTable->GetEfficiency() << "\n\n";
				}
				catch (...)
				{
					cout << "Таблица переполнена.\n\n";
				}

				pTable->ClearEfficiency();
			}
			else if (option == 3)
			{
				bool result = pTable->Delete(key);

				if (result)
				{
					cout << "Элемент удалён. Эффективность: "
						<< pTable->GetEfficiency() << "\n\n";
					cout << "Таблица:\n";
					PrintTable(pTable);
				}
				else
					cout << "Элемент с таким ключом отсутствует. Эффективность: "
					<< pTable->GetEfficiency() << '\n';

				pTable->ClearEfficiency();
			}
		}
	}
}