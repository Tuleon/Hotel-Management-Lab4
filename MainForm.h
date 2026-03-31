#pragma once

#include "Hotel.h"
#include "AddForm.h"

namespace HotelApp {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::IO;

    public ref class MainForm : public Form {
    private:
        DataGridView^ grid;
        Button^ addBtn;
        Button^ delBtn;

        Hotel^ hotel;

    public:
        MainForm() {
            hotel = gcnew Hotel();

            grid = gcnew DataGridView();
            addBtn = gcnew Button();
            delBtn = gcnew Button();

            grid->Dock = DockStyle::Top;
            grid->Height = 200;
            grid->ColumnCount = 3;

            grid->Columns[0]->Name = "Название";
            grid->Columns[1]->Name = "Цена";
            grid->Columns[2]->Name = "Скидка";

            addBtn->Text = "Добавить";
            delBtn->Text = "Удалить";

            addBtn->Top = 210;
            delBtn->Top = 240;

            addBtn->Click += gcnew EventHandler(this, &MainForm::onAdd);
            delBtn->Click += gcnew EventHandler(this, &MainForm::onDelete);

            Controls->Add(grid);
            Controls->Add(addBtn);
            Controls->Add(delBtn);
        }

    private:
        void refreshGrid() {
            grid->Rows->Clear();

            for each (Room ^ r in hotel->rooms) {
                grid->Rows->Add(r->name, r->price, r->discount);
            }
        }

        void onAdd(Object^ sender, EventArgs^ e) {
            AddForm^ form = gcnew AddForm();

            if (form->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                hotel->addRoom(gcnew Room(
                    form->roomName,
                    form->price,
                    form->discount
                ));
                refreshGrid();
            }
        }

        void onDelete(Object^ sender, EventArgs^ e) {
            if (grid->SelectedRows->Count > 0) {
                int i = grid->SelectedRows[0]->Index;
                hotel->removeRoom(i);
                refreshGrid();
            }
        }

        

        
    private: System::Void InitializeComponent() {
        this->SuspendLayout();
        // 
        // MainForm
        // 
        this->ClientSize = System::Drawing::Size(282, 253);
        this->Name = L"MainForm";
        this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
        this->ResumeLayout(false);
    }
private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
    }
};

}