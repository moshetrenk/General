#pragma once
#include "areacodes.h"
#include <msclr\marshal_cppstd.h> 

using namespace msclr::interop;

namespace One {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	AreaCodes aOne;
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
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
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  inbox;
	protected:




	private: System::Windows::Forms::MenuStrip^  menuStrip1;




	private: System::Windows::Forms::TextBox^  outbox;
	private: System::Windows::Forms::ToolStripMenuItem^  cityToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  arToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  areaCodeToolStripMenuItem;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;









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
			this->inbox = (gcnew System::Windows::Forms::TextBox());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->cityToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->arToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->areaCodeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->outbox = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// inbox
			// 
			this->inbox->Location = System::Drawing::Point(187, 138);
			this->inbox->Name = L"inbox";
			this->inbox->Size = System::Drawing::Size(100, 20);
			this->inbox->TabIndex = 0;
			this->inbox->TextChanged += gcnew System::EventHandler(this, &MyForm::inbox_TextChanged);
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->cityToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(438, 36);
			this->menuStrip1->TabIndex = 5;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// cityToolStripMenuItem
			// 
			this->cityToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->toolStripMenuItem1,
					this->arToolStripMenuItem, this->areaCodeToolStripMenuItem
			});
			this->cityToolStripMenuItem->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15));
			this->cityToolStripMenuItem->Name = L"cityToolStripMenuItem";
			this->cityToolStripMenuItem->Size = System::Drawing::Size(157, 32);
			this->cityToolStripMenuItem->Text = L"Search Options";
			this->cityToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::cityToolStripMenuItem_Click);
			// 
			// toolStripMenuItem1
			// 
			this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
			this->toolStripMenuItem1->Size = System::Drawing::Size(175, 32);
			this->toolStripMenuItem1->Text = L"City";
			this->toolStripMenuItem1->Click += gcnew System::EventHandler(this, &MyForm::toolStripMenuItem1_Click);
			// 
			// arToolStripMenuItem
			// 
			this->arToolStripMenuItem->Name = L"arToolStripMenuItem";
			this->arToolStripMenuItem->Size = System::Drawing::Size(175, 32);
			this->arToolStripMenuItem->Text = L"State";
			this->arToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::arToolStripMenuItem_Click);
			// 
			// areaCodeToolStripMenuItem
			// 
			this->areaCodeToolStripMenuItem->Name = L"areaCodeToolStripMenuItem";
			this->areaCodeToolStripMenuItem->Size = System::Drawing::Size(175, 32);
			this->areaCodeToolStripMenuItem->Text = L"Area Code";
			this->areaCodeToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::areaCodeToolStripMenuItem_Click);
			// 
			// outbox
			// 
			this->outbox->Location = System::Drawing::Point(187, 199);
			this->outbox->Name = L"outbox";
			this->outbox->ReadOnly = true;
			this->outbox->Size = System::Drawing::Size(100, 20);
			this->outbox->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(47, 141);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(31, 13);
			this->label1->TabIndex = 6;
			this->label1->Text = L"Input";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(47, 202);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(39, 13);
			this->label2->TabIndex = 7;
			this->label2->Text = L"Output";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(22, 98);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(388, 13);
			this->label3->TabIndex = 8;
			this->label3->Text = L"Please enter an area code or city and then choose from the search options menu";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(438, 280);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->outbox);
			this->Controls->Add(this->inbox);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MyForm";
			this->Text = L"Phone Number ";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {


				 string acode = marshal_as<string>(inbox->Text);
				 String ^phoneNumberText = marshal_as<String ^>(aOne.getCity(acode));
				 outbox->Text = phoneNumberText;

				 //Int32::TryParse(inbox->Text, __)
				 //outbox->Text = sum.ToString ()
				 //MessageBox::Show("");
	}
	private: System::Void checkBox1_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void cityToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void comboBox1_SelectedIndexChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void toolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) {
				 string acode = marshal_as<string>(inbox->Text);
				 String ^phoneNumberText = marshal_as<String ^>(aOne.getCity(acode));
				 outbox->Text = phoneNumberText;
	}
	private: System::Void arToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 string acode = marshal_as<string>(inbox->Text);
				 String ^phoneNumberText = marshal_as<String ^>(aOne.getState(acode));
				 outbox->Text = phoneNumberText;
	}
	private: System::Void areaCodeToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
				 string acode = marshal_as<string>(inbox->Text);
				 aOne.sortByCity();
				 string *multmatches;
				 for (int a = 0; a < strlen(acode.c_str()); a++)
				 {//switches all the letters in the city's name to lowercase
					 acode[a] = tolower(acode[a]);
				 }
				 acode[0] = toupper(acode[0]); //switches the first to uppercase
				 for (int a = 0; a < strlen(acode.c_str()); a++)
				 {//verifies that if the city's name is two words then the first character
					 if (acode[a] == ' ')//of the second word is also uppercase
						 acode[a + 1] = toupper(acode[a + 1]);
				 }

				 int numMatches = aOne.sizeAllocator(acode);

				 if (numMatches)
				 {
					 multmatches = (aOne.findMultCity(acode, numMatches));

					 if (multmatches)
					 {
						 if (numMatches == 1)
						 {
							 String ^phoneNumberText = marshal_as<String ^>(aOne.binarySearch(acode, numMatches));
							 outbox->Text = phoneNumberText;
						 }
						 else
						 {
							 String ^phoneNumberText;
							 for (int i = 0; i < numMatches; i++)
							 {
								 phoneNumberText += marshal_as<String ^>(multmatches[i]);

								 if (i != numMatches - 1)
									 phoneNumberText += ", ";
							 }
							 outbox->Text = phoneNumberText;
						 }

						 delete[] multmatches;
					 }
					 else{
						 MessageBox::Show("Please choose a valid option");
					 }
				 }

	}
	private: System::Void inbox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
};
}
