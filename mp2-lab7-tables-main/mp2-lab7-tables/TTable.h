#pragma once
#include <iostream>
#include <string>

//Ключ и значение
typedef int TKey;
typedef std::string TValue;

//Запись
struct TRecord
{
	TKey key;
	TValue val;

	TRecord(TKey _key = -1, TValue _val = "value-1")
	{
		key = _key;
		val = _val;
	}

	bool operator==(const TRecord& other) const
	{
		return (key == other.key);
	}

	bool operator!=(const TRecord& other) const
	{
		return (key != other.key);
	}
};

std::ostream& operator<<(std::ostream& os, const TRecord& tr)
{
	os << tr.key << ": " << tr.val;
	return os;
}

//Таблица 
class TTable
{
protected:
	//Счётчик числа записей
	int DataCount;
	//Счётчик эффективности 
	int Eff;
public:
	TTable();
	virtual ~TTable();

	int GetDataCount() const;
	int GetEfficiency() const;

	//Сброс счётчика эффективности
	void ClearEfficiency();

	//Проверки на пустоту
	bool IsEmpty();
	bool IsNotEmpty();

	//Проверка на заполненность
	virtual bool IsFull() const = 0;

	//Поиск записи
	virtual bool Find(TKey key) = 0;

	//Вставка новой записи в таблицу
	virtual bool Insert(TRecord rec) = 0;

	//Удаление записи из таблицы по ключу
	virtual bool Delete(TKey key) = 0;

	virtual void Reset() = 0;
	virtual void GoNext() = 0;
	virtual bool IsEnd() = 0;

	//Возвращает ключ текущей записи
	virtual TKey GetCurrentKey() const = 0;
	//Возвращает значение текущей записи
	virtual TValue GetCurrentVal() const = 0;

	//Вывод
	friend std::ostream& operator<<(std::ostream& os, TTable& t)
	{
		for (t.Reset(); !t.IsEnd(); t.GoNext())
			os << t.GetCurrentKey()
				<< " " << t.GetCurrentVal() << '\n';
		return os;
	}
};

TTable::TTable()
{
	DataCount = Eff = 0;
}

TTable::~TTable() { }

int TTable::GetDataCount() const
{
	return DataCount;
}

int TTable::GetEfficiency() const
{
	return Eff;
}

//Сброс счётчика эффективности операций
void TTable::ClearEfficiency()
{
	Eff = 0;
}

//Проверки таблицы на пустоту
bool TTable::IsEmpty()
{
	return (DataCount == 0);
}

bool TTable::IsNotEmpty()
{
	return (DataCount != 0);
}