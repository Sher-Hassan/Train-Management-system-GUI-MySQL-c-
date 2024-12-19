#pragma once
#include "DTRF.h"
#include "DTRR.h"
#include "ShowStations.h"
#include "EditStations.h"
#include "ShowRoutes.h"
#include "EditRoutes.h"
namespace TrainMS {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Menu
	/// </summary>
	public ref class Menu : public System::Windows::Forms::Form
	{
	public:
		Menu(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Menu()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ button1;

	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::Button^ button5;



	

	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button6;
	private: System::Windows::Forms::Button^ button7;




	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Century", 28.2F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(279, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(643, 55);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Train Management System";
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->Location = System::Drawing::Point(103, 121);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(384, 49);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Display Train Route (F)";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &Menu::button1_Click_1);
			// 
			// button3
			// 
			this->button3->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->button3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button3->Location = System::Drawing::Point(103, 214);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(384, 49);
			this->button3->TabIndex = 3;
			this->button3->Text = L"Show Stations";
			this->button3->UseVisualStyleBackColor = false;
			this->button3->Click += gcnew System::EventHandler(this, &Menu::button3_Click);
			// 
			// button4
			// 
			this->button4->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->button4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button4->Location = System::Drawing::Point(681, 214);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(384, 49);
			this->button4->TabIndex = 4;
			this->button4->Text = L"Edit Stations";
			this->button4->UseVisualStyleBackColor = false;
			this->button4->Click += gcnew System::EventHandler(this, &Menu::button4_Click);
			// 
			// button5
			// 
			this->button5->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->button5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button5->Location = System::Drawing::Point(103, 305);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(384, 49);
			this->button5->TabIndex = 5;
			this->button5->Text = L"Show Routes";
			this->button5->UseVisualStyleBackColor = false;
			this->button5->Click += gcnew System::EventHandler(this, &Menu::button5_Click);
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button2->Location = System::Drawing::Point(681, 121);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(385, 49);
			this->button2->TabIndex = 2;
			this->button2->Text = L"Display Train Route (R)";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &Menu::button2_Click);
			// 
			// button6
			// 
			this->button6->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->button6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button6->Location = System::Drawing::Point(682, 305);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(384, 49);
			this->button6->TabIndex = 6;
			this->button6->Text = L"Edit Routes";
			this->button6->UseVisualStyleBackColor = false;
			this->button6->Click += gcnew System::EventHandler(this, &Menu::button6_Click);
			// 
			// button7
			// 
			this->button7->BackColor = System::Drawing::SystemColors::ButtonFace;
			this->button7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button7->Location = System::Drawing::Point(402, 390);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(384, 49);
			this->button7->TabIndex = 7;
			this->button7->Text = L"EXIT";
			this->button7->UseVisualStyleBackColor = false;
			this->button7->Click += gcnew System::EventHandler(this, &Menu::button7_Click);
			// 
			// Menu
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1213, 490);
			this->Controls->Add(this->button7);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button5);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label1);
			this->Name = L"Menu";
			this->Text = L"Menu";
			this->Load += gcnew System::EventHandler(this, &Menu::Menu_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Menu_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	
	
    private: System::Void button1_Click_1(System::Object^ sender, System::EventArgs^ e) {
	DTRF^ dtrfForm = gcnew DTRF(); // Create an instance of DTRF
	dtrfForm->Show(); // Show the DTRF form
}
    private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	DTRR^ dtrrForm = gcnew DTRR(); // Create an instance of DTRR
	dtrrForm->Show(); // Show the DTRR form
}
    private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
	ShowStations^ showStationsForm = gcnew ShowStations(); // Create an instance of ShowStations
	showStationsForm->Show(); // Show the ShowStations form
}
	
    private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
	EditStations^ editStationsForm = gcnew EditStations(); // Create an instance of EditStations
	editStationsForm->Show(); // Show the EditStations form
}
	
    private: System::Void button5_Click(System::Object^ sender, System::EventArgs^ e) {
	ShowRoutes^ showRoutesForm = gcnew ShowRoutes(); // Create an instance of ShowRoutes
	showRoutesForm->Show(); // Show the ShowRoutes form
}
	
    private: System::Void button6_Click(System::Object^ sender, System::EventArgs^ e) {
	EditRoutes^ editRoutesForm = gcnew EditRoutes(); // Create an instance of EditRoutes
	editRoutesForm->Show(); // Show the EditRoutes form
}
	
    private: System::Void button7_Click(System::Object^ sender, System::EventArgs^ e) {
	Application::Exit(); // Exit the application
}
};
}




