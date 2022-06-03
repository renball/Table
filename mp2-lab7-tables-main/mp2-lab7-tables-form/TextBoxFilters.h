#pragma once

public class TextBoxFilters {

private:
	TextBoxFilters() {}
	static void AllowOnlyOne(System::Windows::Forms::TextBox^ sender,
		System::Windows::Forms::KeyPressEventArgs^ e, char ch);

public:
	static void NaturalNumber(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e);
	static void NonNegativeDecimalNumber(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e);
	static void DecimalNumber(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e);
};