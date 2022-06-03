#include "Convertex.h"
#include <msclr\marshal_cppstd.h>

using namespace System;
using namespace System::Windows::Forms;

std::string Convertex::StringTo_string(System::String^ str)
{
	return msclr::interop::marshal_as<std::string>(str);
}

int Convertex::StringTo_int(System::String^ str)
{
	return std::stoi(msclr::interop::marshal_as<std::string>(str));
}

float Convertex::StringTo_float(System::String^ str)
{
	return std::stof(msclr::interop::marshal_as<std::string>(str));
}

double Convertex::StringTo_double(System::String^ str)
{
	return std::stod(msclr::interop::marshal_as<std::string>(str));
}

System::String^ Convertex::stringTo_String(std::string str)
{
	return msclr::interop::marshal_as<System::String^>(str);
}

System::String^ Convertex::intTo_String(int number)
{
	return Convertex::stringTo_String(std::to_string(number));
}

System::String^ Convertex::floatTo_String(float number)
{
	return Convertex::stringTo_String(std::to_string(number));
}

System::String^ Convertex::doubleTo_String(double number)
{
	return Convertex::stringTo_String(std::to_string(number));
}

std::string Convertex::Read_string(System::Windows::Forms::TextBox^ tb)
{
	return StringTo_string(tb->Text);
}

int Convertex::Read_int(System::Windows::Forms::TextBox^ tb)
{
	return Convertex::StringTo_int(tb->Text);
}

float Convertex::Read_float(System::Windows::Forms::TextBox^ tb)
{
	return Convertex::StringTo_float(tb->Text);
}

double Convertex::Read_double(System::Windows::Forms::TextBox^ tb)
{
	return Convertex::StringTo_double(tb->Text);
}