#pragma once
#include <string>

public class Convertex
{

private:
	Convertex() {}

public:
	/* Extensions for String^ */

	//Part 1
	static std::string StringTo_string(System::String^ str);
	static int StringTo_int(System::String^ str);
	static float StringTo_float(System::String^ str);
	static double StringTo_double(System::String^ str);

	//Part 2 (reversed conversions)
	static System::String^ stringTo_String(std::string str);
	static System::String^ intTo_String(int number);
	static System::String^ floatTo_String(float number);
	static System::String^ doubleTo_String(double number);

	/* Extensions for TextBox^ */

	static std::string Read_string(System::Windows::Forms::TextBox^ tb);
	static int Read_int(System::Windows::Forms::TextBox^ tb);
	static float Read_float(System::Windows::Forms::TextBox^ tb);
	static double Read_double(System::Windows::Forms::TextBox^ tb);
};