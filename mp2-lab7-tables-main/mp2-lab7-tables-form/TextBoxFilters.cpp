using namespace System;
using namespace System::Windows::Forms;

#include "TextBoxFilters.h"

void TextBoxFilters::AllowOnlyOne(TextBox^ sender, KeyPressEventArgs^ e, char ch) {
	if (e->KeyChar == ch && sender->Text->IndexOf(ch) > -1)
	{
		e->Handled = true;
	}
}


void TextBoxFilters::NaturalNumber(Object^ sender, KeyPressEventArgs^ e)
{
	if (!Char::IsControl(e->KeyChar) && !Char::IsDigit(e->KeyChar))
	{
		e->Handled = true;
	}
}

void TextBoxFilters::NonNegativeDecimalNumber(Object^ sender, KeyPressEventArgs^ e)
{
	if (!Char::IsControl(e->KeyChar) && !Char::IsDigit(e->KeyChar) &&
		e->KeyChar != '.')
	{
		e->Handled = true;
	}

	AllowOnlyOne((TextBox^)sender, e, '.');
}

void TextBoxFilters::DecimalNumber(Object^ sender, KeyPressEventArgs^ e)
{
	if (!Char::IsControl(e->KeyChar) && !Char::IsDigit(e->KeyChar) &&
		e->KeyChar != '.' && e->KeyChar != '-')
	{
		e->Handled = true;
	}

	AllowOnlyOne((TextBox^)sender, e, '.');
	AllowOnlyOne((TextBox^)sender, e, '-');
}