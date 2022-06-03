#pragma once
#include "..\mp2-lab7-tables\TSortTable.h"
#include "..\mp2-lab7-tables\TArrayHashTable.h"
#include "..\mp2-lab7-tables\TListHashTable.h"
#include "..\mp2-lab7-tables\TBalTreeTable.h"
#include "..\mp2-lab7-tables\Ramdomex.h"
#include "TextBoxFilters.h"
#include "DataGridViewExtensions.h"
#include <fstream>

/*
Макс. размер - это size таблицы (для таблиц с размером)

Макс. ключ - это максимальный ключ при случайной генерации ключей
Случ. записей - число записей, которое будет случайно сгенерировано
*/

namespace mp2lab7tablesform {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class TablesForm : public System::Windows::Forms::Form
	{
	private:
		TTable* pTable;

	public:
		TablesForm(void)
		{
			InitializeComponent();
			dgvKeyValue->ColumnHeadersDefaultCellStyle->Font
				= (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			labelEff->Text = "0";
			folderBrowserDialog->Description = "Выберите папку для сохранения таблицы:";
			Randomex::Init();
		}

	protected:
		~TablesForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::DataGridView^ dgvKeyValue;

	private: System::Windows::Forms::GroupBox^ gbTableType;
	private: System::Windows::Forms::RadioButton^ rb6;

	private: System::Windows::Forms::RadioButton^ rb5;

	private: System::Windows::Forms::RadioButton^ rb4;

	private: System::Windows::Forms::RadioButton^ rb3;

	private: System::Windows::Forms::RadioButton^ rb2;

	private: System::Windows::Forms::RadioButton^ rb1;

	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Button^ btnCreateTable;
	private: System::Windows::Forms::NumericUpDown^ numberRecords;
	private: System::Windows::Forms::NumericUpDown^ numberMaxKey;

	private: System::Windows::Forms::TextBox^ tbKeyNumber;
	private: System::Windows::Forms::Button^ btnFind;
	private: System::Windows::Forms::Button^ btnAdd;
	private: System::Windows::Forms::Button^ btnDelete;

	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ labelEff;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Key;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Value;
	private: System::Windows::Forms::Button^ btnExport;
	private: System::Windows::Forms::FolderBrowserDialog^ folderBrowserDialog;
	private: System::Windows::Forms::NumericUpDown^ numberMaxSize;

	private: System::Windows::Forms::Label^ label5;

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle3 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle2 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(TablesForm::typeid));
			this->dgvKeyValue = (gcnew System::Windows::Forms::DataGridView());
			this->Key = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Value = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->gbTableType = (gcnew System::Windows::Forms::GroupBox());
			this->rb6 = (gcnew System::Windows::Forms::RadioButton());
			this->rb5 = (gcnew System::Windows::Forms::RadioButton());
			this->rb4 = (gcnew System::Windows::Forms::RadioButton());
			this->rb3 = (gcnew System::Windows::Forms::RadioButton());
			this->rb2 = (gcnew System::Windows::Forms::RadioButton());
			this->rb1 = (gcnew System::Windows::Forms::RadioButton());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->btnCreateTable = (gcnew System::Windows::Forms::Button());
			this->numberRecords = (gcnew System::Windows::Forms::NumericUpDown());
			this->numberMaxKey = (gcnew System::Windows::Forms::NumericUpDown());
			this->tbKeyNumber = (gcnew System::Windows::Forms::TextBox());
			this->btnFind = (gcnew System::Windows::Forms::Button());
			this->btnAdd = (gcnew System::Windows::Forms::Button());
			this->btnDelete = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->labelEff = (gcnew System::Windows::Forms::Label());
			this->btnExport = (gcnew System::Windows::Forms::Button());
			this->folderBrowserDialog = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->numberMaxSize = (gcnew System::Windows::Forms::NumericUpDown());
			this->label5 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvKeyValue))->BeginInit();
			this->gbTableType->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numberRecords))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numberMaxKey))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numberMaxSize))->BeginInit();
			this->SuspendLayout();
			// 
			// dgvKeyValue
			// 
			this->dgvKeyValue->AllowUserToAddRows = false;
			this->dgvKeyValue->AllowUserToDeleteRows = false;
			this->dgvKeyValue->AllowUserToResizeColumns = false;
			this->dgvKeyValue->AllowUserToResizeRows = false;
			this->dgvKeyValue->BackgroundColor = System::Drawing::Color::White;
			this->dgvKeyValue->ColumnHeadersHeight = 34;
			this->dgvKeyValue->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::DisableResizing;
			this->dgvKeyValue->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) { this->Key, this->Value });
			dataGridViewCellStyle3->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle3->BackColor = System::Drawing::SystemColors::Window;
			dataGridViewCellStyle3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			dataGridViewCellStyle3->ForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle3->SelectionBackColor = System::Drawing::SystemColors::Window;
			dataGridViewCellStyle3->SelectionForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle3->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->dgvKeyValue->DefaultCellStyle = dataGridViewCellStyle3;
			this->dgvKeyValue->EditMode = System::Windows::Forms::DataGridViewEditMode::EditProgrammatically;
			this->dgvKeyValue->GridColor = System::Drawing::Color::White;
			this->dgvKeyValue->Location = System::Drawing::Point(25, 26);
			this->dgvKeyValue->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->dgvKeyValue->MultiSelect = false;
			this->dgvKeyValue->Name = L"dgvKeyValue";
			this->dgvKeyValue->ReadOnly = true;
			this->dgvKeyValue->RowHeadersVisible = false;
			this->dgvKeyValue->RowHeadersWidth = 62;
			this->dgvKeyValue->RowHeadersWidthSizeMode = System::Windows::Forms::DataGridViewRowHeadersWidthSizeMode::DisableResizing;
			this->dgvKeyValue->RowTemplate->Height = 28;
			this->dgvKeyValue->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->dgvKeyValue->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->dgvKeyValue->Size = System::Drawing::Size(283, 474);
			this->dgvKeyValue->TabIndex = 0;
			// 
			// Key
			// 
			dataGridViewCellStyle1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Key->DefaultCellStyle = dataGridViewCellStyle1;
			this->Key->Frozen = true;
			this->Key->HeaderText = L"Ключ";
			this->Key->MaxInputLength = 20;
			this->Key->MinimumWidth = 8;
			this->Key->Name = L"Key";
			this->Key->ReadOnly = true;
			this->Key->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->Key->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->Key->Width = 120;
			// 
			// Value
			// 
			dataGridViewCellStyle2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Value->DefaultCellStyle = dataGridViewCellStyle2;
			this->Value->Frozen = true;
			this->Value->HeaderText = L"Значение";
			this->Value->MaxInputLength = 20;
			this->Value->MinimumWidth = 8;
			this->Value->Name = L"Value";
			this->Value->ReadOnly = true;
			this->Value->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->Value->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->Value->Width = 160;
			// 
			// gbTableType
			// 
			this->gbTableType->Controls->Add(this->rb6);
			this->gbTableType->Controls->Add(this->rb5);
			this->gbTableType->Controls->Add(this->rb4);
			this->gbTableType->Controls->Add(this->rb3);
			this->gbTableType->Controls->Add(this->rb2);
			this->gbTableType->Controls->Add(this->rb1);
			this->gbTableType->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->gbTableType->Location = System::Drawing::Point(343, 21);
			this->gbTableType->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->gbTableType->Name = L"gbTableType";
			this->gbTableType->Padding = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->gbTableType->Size = System::Drawing::Size(287, 259);
			this->gbTableType->TabIndex = 1;
			this->gbTableType->TabStop = false;
			this->gbTableType->Text = L"Тип таблицы";
			// 
			// rb6
			// 
			this->rb6->AutoSize = true;
			this->rb6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->rb6->Location = System::Drawing::Point(13, 216);
			this->rb6->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->rb6->Name = L"rb6";
			this->rb6->Size = System::Drawing::Size(178, 29);
			this->rb6->TabIndex = 5;
			this->rb6->Text = L"На АВЛ-дереве";
			this->rb6->UseVisualStyleBackColor = true;
			this->rb6->CheckedChanged += gcnew System::EventHandler(this, &TablesForm::rb_CheckedChanged);
			// 
			// rb5
			// 
			this->rb5->AutoSize = true;
			this->rb5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->rb5->Location = System::Drawing::Point(13, 180);
			this->rb5->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->rb5->Name = L"rb5";
			this->rb5->Size = System::Drawing::Size(131, 29);
			this->rb5->TabIndex = 4;
			this->rb5->Text = L"На дереве";
			this->rb5->UseVisualStyleBackColor = true;
			this->rb5->CheckedChanged += gcnew System::EventHandler(this, &TablesForm::rb_CheckedChanged);
			// 
			// rb4
			// 
			this->rb4->AutoSize = true;
			this->rb4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->rb4->Location = System::Drawing::Point(13, 143);
			this->rb4->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->rb4->Name = L"rb4";
			this->rb4->Size = System::Drawing::Size(257, 29);
			this->rb4->TabIndex = 3;
			this->rb4->Text = L"Хэш-таблица на списке";
			this->rb4->UseVisualStyleBackColor = true;
			this->rb4->CheckedChanged += gcnew System::EventHandler(this, &TablesForm::rb_CheckedChanged);
			// 
			// rb3
			// 
			this->rb3->AutoSize = true;
			this->rb3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->rb3->Location = System::Drawing::Point(13, 107);
			this->rb3->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->rb3->Name = L"rb3";
			this->rb3->Size = System::Drawing::Size(273, 29);
			this->rb3->TabIndex = 2;
			this->rb3->Text = L"Хэш-таблица на массиве";
			this->rb3->UseVisualStyleBackColor = true;
			this->rb3->CheckedChanged += gcnew System::EventHandler(this, &TablesForm::rb_CheckedChanged);
			// 
			// rb2
			// 
			this->rb2->AutoSize = true;
			this->rb2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->rb2->Location = System::Drawing::Point(13, 70);
			this->rb2->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->rb2->Name = L"rb2";
			this->rb2->Size = System::Drawing::Size(181, 29);
			this->rb2->TabIndex = 1;
			this->rb2->Text = L"Упорядоченная";
			this->rb2->UseVisualStyleBackColor = true;
			this->rb2->CheckedChanged += gcnew System::EventHandler(this, &TablesForm::rb_CheckedChanged);
			// 
			// rb1
			// 
			this->rb1->AutoSize = true;
			this->rb1->Checked = true;
			this->rb1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->rb1->Location = System::Drawing::Point(13, 34);
			this->rb1->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->rb1->Name = L"rb1";
			this->rb1->Size = System::Drawing::Size(202, 29);
			this->rb1->TabIndex = 0;
			this->rb1->TabStop = true;
			this->rb1->Text = L"Неупорядоченная";
			this->rb1->UseVisualStyleBackColor = true;
			this->rb1->CheckedChanged += gcnew System::EventHandler(this, &TablesForm::rb_CheckedChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(347, 381);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(148, 25);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Случ. записей:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(347, 339);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(122, 25);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Макс. ключ:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(659, 26);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(68, 25);
			this->label3->TabIndex = 4;
			this->label3->Text = L"Ключ:";
			// 
			// btnCreateTable
			// 
			this->btnCreateTable->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->btnCreateTable->Location = System::Drawing::Point(343, 432);
			this->btnCreateTable->Name = L"btnCreateTable";
			this->btnCreateTable->Size = System::Drawing::Size(287, 68);
			this->btnCreateTable->TabIndex = 6;
			this->btnCreateTable->Text = L"Создать таблицу";
			this->btnCreateTable->UseVisualStyleBackColor = true;
			this->btnCreateTable->Click += gcnew System::EventHandler(this, &TablesForm::btnCreateTable_Click);
			// 
			// numberRecords
			// 
			this->numberRecords->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->numberRecords->Location = System::Drawing::Point(495, 379);
			this->numberRecords->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100000, 0, 0, 0 });
			this->numberRecords->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numberRecords->Name = L"numberRecords";
			this->numberRecords->Size = System::Drawing::Size(134, 30);
			this->numberRecords->TabIndex = 7;
			this->numberRecords->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->numberRecords->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 15, 0, 0, 0 });
			this->numberRecords->ValueChanged += gcnew System::EventHandler(this, &TablesForm::number_ValueChanged);
			// 
			// numberMaxKey
			// 
			this->numberMaxKey->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->numberMaxKey->Location = System::Drawing::Point(495, 339);
			this->numberMaxKey->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000000, 0, 0, 0 });
			this->numberMaxKey->Name = L"numberMaxKey";
			this->numberMaxKey->Size = System::Drawing::Size(134, 30);
			this->numberMaxKey->TabIndex = 8;
			this->numberMaxKey->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->numberMaxKey->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 50, 0, 0, 0 });
			this->numberMaxKey->ValueChanged += gcnew System::EventHandler(this, &TablesForm::number_ValueChanged);
			// 
			// tbKeyNumber
			// 
			this->tbKeyNumber->Enabled = false;
			this->tbKeyNumber->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->tbKeyNumber->Location = System::Drawing::Point(733, 26);
			this->tbKeyNumber->MaxLength = 7;
			this->tbKeyNumber->Name = L"tbKeyNumber";
			this->tbKeyNumber->Size = System::Drawing::Size(110, 30);
			this->tbKeyNumber->TabIndex = 9;
			this->tbKeyNumber->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->tbKeyNumber->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &TablesForm::tbKeyNumber_KeyPress);
			// 
			// btnFind
			// 
			this->btnFind->Enabled = false;
			this->btnFind->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->btnFind->Location = System::Drawing::Point(663, 146);
			this->btnFind->Name = L"btnFind";
			this->btnFind->Size = System::Drawing::Size(180, 61);
			this->btnFind->TabIndex = 10;
			this->btnFind->Text = L"Найти";
			this->btnFind->UseVisualStyleBackColor = true;
			this->btnFind->Click += gcnew System::EventHandler(this, &TablesForm::btnFind_Click);
			// 
			// btnAdd
			// 
			this->btnAdd->Enabled = false;
			this->btnAdd->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->btnAdd->Location = System::Drawing::Point(663, 73);
			this->btnAdd->Name = L"btnAdd";
			this->btnAdd->Size = System::Drawing::Size(180, 61);
			this->btnAdd->TabIndex = 11;
			this->btnAdd->Text = L"Добавить";
			this->btnAdd->UseVisualStyleBackColor = true;
			this->btnAdd->Click += gcnew System::EventHandler(this, &TablesForm::btnAdd_Click);
			// 
			// btnDelete
			// 
			this->btnDelete->Enabled = false;
			this->btnDelete->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->btnDelete->Location = System::Drawing::Point(663, 219);
			this->btnDelete->Name = L"btnDelete";
			this->btnDelete->Size = System::Drawing::Size(180, 61);
			this->btnDelete->TabIndex = 12;
			this->btnDelete->Text = L"Удалить";
			this->btnDelete->UseVisualStyleBackColor = true;
			this->btnDelete->Click += gcnew System::EventHandler(this, &TablesForm::btnDelete_Click);
			// 
			// label4
			// 
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 11, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label4->Location = System::Drawing::Point(658, 325);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(198, 25);
			this->label4->TabIndex = 13;
			this->label4->Text = L"Эффективность:";
			this->label4->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// labelEff
			// 
			this->labelEff->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelEff->ForeColor = System::Drawing::Color::RoyalBlue;
			this->labelEff->Location = System::Drawing::Point(664, 362);
			this->labelEff->Name = L"labelEff";
			this->labelEff->Size = System::Drawing::Size(179, 25);
			this->labelEff->TabIndex = 14;
			this->labelEff->Text = L"777";
			this->labelEff->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// btnExport
			// 
			this->btnExport->Enabled = false;
			this->btnExport->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->btnExport->Location = System::Drawing::Point(663, 432);
			this->btnExport->Name = L"btnExport";
			this->btnExport->Size = System::Drawing::Size(180, 68);
			this->btnExport->TabIndex = 15;
			this->btnExport->Text = L"Экспорт";
			this->btnExport->UseVisualStyleBackColor = true;
			this->btnExport->Click += gcnew System::EventHandler(this, &TablesForm::buttonExport_Click);
			// 
			// numberMaxSize
			// 
			this->numberMaxSize->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->numberMaxSize->Location = System::Drawing::Point(495, 298);
			this->numberMaxSize->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 100000, 0, 0, 0 });
			this->numberMaxSize->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
			this->numberMaxSize->Name = L"numberMaxSize";
			this->numberMaxSize->Size = System::Drawing::Size(134, 30);
			this->numberMaxSize->TabIndex = 17;
			this->numberMaxSize->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->numberMaxSize->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 20, 0, 0, 0 });
			this->numberMaxSize->ValueChanged += gcnew System::EventHandler(this, &TablesForm::number_ValueChanged);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label5->Location = System::Drawing::Point(347, 300);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(145, 25);
			this->label5->TabIndex = 16;
			this->label5->Text = L"Макс. размер:";
			// 
			// TablesForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(10, 22);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(871, 526);
			this->Controls->Add(this->numberMaxSize);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->btnExport);
			this->Controls->Add(this->labelEff);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->btnDelete);
			this->Controls->Add(this->btnAdd);
			this->Controls->Add(this->btnFind);
			this->Controls->Add(this->tbKeyNumber);
			this->Controls->Add(this->numberMaxKey);
			this->Controls->Add(this->numberRecords);
			this->Controls->Add(this->btnCreateTable);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->gbTableType);
			this->Controls->Add(this->dgvKeyValue);
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->MaximizeBox = false;
			this->Name = L"TablesForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Таблицы";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dgvKeyValue))->EndInit();
			this->gbTableType->ResumeLayout(false);
			this->gbTableType->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numberRecords))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numberMaxKey))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numberMaxSize))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private:
		//Ограничение ввода:
		//Число ключей не может быть меньше, чем макс. число записей в таблице
		Void number_ValueChanged(Object^ sender, EventArgs^ e)
		{
			int nMaxSize = Convert::ToInt32(numberMaxSize->Value);
			int nMaxKey = Convert::ToInt32(numberMaxKey->Value);
			int nRandRecordsCnt = Convert::ToInt32(numberRecords->Value);

			if (rb5->Checked || rb6->Checked)
			{
				//Таблица предполагается на дереве (не имеет макс. размера)
			    //Если максимальный ключ не соответствует числу записей - он будет увеличен
				if (nMaxKey + 1 < nRandRecordsCnt)
					numberMaxKey->Value = (nRandRecordsCnt - 1);
				return;
			}

			//Таблица предполагается фиксированного размера (в случае с THashListTable - условно)
			//nMaxSize - макс. размер - главное число здесь.
			//Если максимальный ключ не соответствует макс. размеру - он будет увеличен
			if (nMaxKey + 1 < nMaxSize)
				numberMaxKey->Value = (nMaxSize - 1);
			//Если случайных записей планируется добавить более макс. размера,
			//то это также невозможно
			if (nRandRecordsCnt > nMaxSize)
				numberRecords->Value = nMaxSize;
		}
		Void tbKeyNumber_KeyPress(Object^ sender, KeyPressEventArgs^ e)
		{
			TextBoxFilters::NaturalNumber(sender, e);
		}

		void RefreshUITable()
		{
			dgvKeyValue->Rows->Clear();
			for (pTable->Reset(); !pTable->IsEnd(); pTable->GoNext())
			{
				AddRow(
					dgvKeyValue,
					std::to_string(pTable->GetCurrentKey()),
					pTable->GetCurrentVal()
				);
			}
		}

		//Создание таблицы по кнопке "Создать таблицу"
		Void btnCreateTable_Click(Object^ sender, EventArgs^ e)
		{
			int nMaxSize = Convert::ToInt32(numberMaxSize->Value);
			int nMaxKey = Convert::ToInt32(numberMaxKey->Value);
			int nRandRecordsCnt = Convert::ToInt32(numberRecords->Value);

			labelEff->Text = "0";
			number_ValueChanged(nullptr, nullptr);
			tbKeyNumber->Text = "";

			if (rb1->Checked)
			{
				pTable = new TScanTable(nMaxSize);
			}
			else if (rb2->Checked)
			{
				pTable = new TSortTable(nMaxSize);
			}
			else if (rb3->Checked)
			{
				//Тут взят шаг 1, чтобы не проверять на взаимную простоту
				pTable = new TArrayHashTable(nMaxSize, 1);
			}
			else if (rb4->Checked)
			{
				pTable = new TListHashTable(nMaxSize);
			}
			else if (rb5->Checked)
			{
				pTable = new TTreeTable();
			}
			else if (rb6->Checked)
			{
				//pTable = new TBalTreeTable();
			}

			if (pTable == nullptr) return;

			dgvKeyValue->Rows->Clear();
			//Заполнение новой таблицы случайными данными
			//с уникальными ключами
			for (int i = 0; i < nRandRecordsCnt; i++)
			{
				TKey randKey = Randomex::RandInt(0, nMaxKey);

				std::string randVal = "value" + std::to_string(randKey);
				bool result = pTable->Insert(TRecord(randKey, randVal));

				if (!result) i--;
			}
			labelEff->Text = Convertex::intTo_String(pTable->GetEfficiency());
			pTable->ClearEfficiency();

			RefreshUITable();

			//Включение доступности кнопок
			tbKeyNumber->Enabled = true;
			btnFind->Enabled = true;
			btnAdd->Enabled = true;
			btnDelete ->Enabled = true;
			btnExport->Enabled = true;
		}

		void ShowWarning(System::String^ text)
		{
			MessageBox::Show(
				text,
				"Сообщение",
				MessageBoxButtons::OK,
				MessageBoxIcon::Warning
			);
		}

		void ShowInfo(System::String^ text)
		{
			MessageBox::Show(
				text,
				"Сообщение",
				MessageBoxButtons::OK,
				MessageBoxIcon::Information
			);
		}
		
		bool CheckKey()
		{
			if (tbKeyNumber->Text->Length == 0)
			{
				ShowWarning("Ключ должен иметь корректное значение.");
				return false;
			}

			int nKey = Convertex::Read_int(tbKeyNumber);

			if (nKey > 1000000)
			{
				ShowWarning("Ключ должен иметь корректное значение.");
				return false;
			}
			return true;
		}

		Void btnFind_Click(System::Object^ sender, EventArgs^ e)
		{
			if (!CheckKey()) return;

			int key = Convertex::Read_int(tbKeyNumber);

			bool result = pTable->Find(key);
			labelEff->Text = Convertex::intTo_String(pTable->GetEfficiency());
			pTable->ClearEfficiency();

			if (result)
				ShowInfo("Элемент успешно найден.");
			else
				ShowInfo("Элемент не найден :(");
		}

		Void btnAdd_Click(Object^ sender, EventArgs^ e)
		{
			if (!CheckKey()) return;

			if (pTable->IsFull())
			{
				ShowInfo("Операция не удалась:\nтаблица уже полна.");
				return;
			}

			int key = Convertex::Read_int(tbKeyNumber);

			bool result = pTable->Insert(
				TRecord(key, "value" + std::to_string(key)));
			labelEff->Text = Convertex::intTo_String(pTable->GetEfficiency());
			pTable->ClearEfficiency();

			if (result)
			{
				RefreshUITable();
			}
			else
				ShowInfo("Операция не удалась:\n" +
					"элемент с таким ключом уже присутствует в таблице.");
		}

		Void btnDelete_Click(Object^ sender, EventArgs^ e)
		{
			if (!CheckKey()) return;

			int key = Convertex::Read_int(tbKeyNumber);

			bool result = pTable->Delete(key);
			labelEff->Text = Convertex::intTo_String(pTable->GetEfficiency());
			pTable->ClearEfficiency();

			if (result)
			{
				RefreshUITable();
			}
			else
				ShowInfo("Элемент с таким ключом не найден :(");
		}

		Void buttonExport_Click(Object^ sender, EventArgs^ e)
		{
			if (folderBrowserDialog->ShowDialog()
					== System::Windows::Forms::DialogResult::OK)
			{
				std::string fPath = Convertex::StringTo_string(
					folderBrowserDialog->SelectedPath) + "\\OutTable.txt";

				std::ofstream out;
				out.open(fPath);

				if (!out.is_open())
					ShowWarning("Не удалось экспортировать таблицу в файл. "
					+ "Попробуйте выбрать другую папку.");

				for (pTable->Reset(); !pTable->IsEnd(); pTable->GoNext())
					out << pTable->GetCurrentKey() << ": " <<
						pTable->GetCurrentVal() << "\n";

				if (typeid(*pTable) == typeid(TTreeTable)
					|| typeid(*pTable) == typeid(TBalTreeTable))
				{
					out << "\n";
					((TTreeTable*)pTable)->Print(out);
				}
				out.close();
			}
		}

		Void rb_CheckedChanged(Object^ sender, EventArgs^ e)
		{
			numberMaxSize->Enabled = !(rb5->Checked || rb6->Checked);
		}
};
}
