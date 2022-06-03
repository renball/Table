#pragma once
#include <string>
#include "Convertex.h"

void AddRow(
	System::Windows::Forms::DataGridView^ dgv,
	...cli::array<System::String^>^ row)
{
	dgv->Rows->Add(row);
}

void AddRow(
	System::Windows::Forms::DataGridView^ dgv,
	std::string rowVal1, std::string rowVal2)
{
	AddRow(dgv, Convertex::stringTo_String(rowVal1),
		Convertex::stringTo_String(rowVal2));
}