#pragma once
#include "Hotel.h"

namespace HotelManagement {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class RoomEditForm : public Form
    {
    public:
        RoomEditForm(void) {
            InitializeComponent();
            InitializeRoomTypes();
        }

        void SetMode(String^ mode, Room^ roomData) {
            this->mode = mode;

            if (mode == "Room") {
                this->Text = roomData == nullptr ? "Добавить номер" : "Редактировать номер";

                if (roomData != nullptr) {
                    txtRoomNumber->Text = roomData->RoomNumber.ToString();
                    cmbRoomType->SelectedItem = roomData->TypeString;
                    txtPrice->Text = roomData->PricePerDay.ToString();
                    txtCapacity->Text = roomData->Capacity.ToString();
                    txtDescription->Text = roomData->Description;
                    txtRoomNumber->ReadOnly = true;
                }
                else {
                    txtRoomNumber->ReadOnly = false;
                }

                ShowRoomControls();
            }
        }

        void SetModeForAdd(String^ mode) {
            this->mode = mode;

            if (mode == "Room") {
                this->Text = "Добавить номер";
                txtRoomNumber->ReadOnly = false;
                ShowRoomControls();
            }
        }

        property int RoomNumber{
            int get() { return Convert::ToInt32(txtRoomNumber->Text); }
        }

            property RoomType Type{
                RoomType get() {
                    String^ typeStr = cmbRoomType->SelectedItem->ToString();
                    if (typeStr == "Стандарт") return RoomType::Standard;
                    if (typeStr == "Комфорт") return RoomType::Comfort;
                    if (typeStr == "Люкс") return RoomType::Luxury;
                    return RoomType::Suite;
                }
        }

            property double PricePerDay{
                double get() { return Convert::ToDouble(txtPrice->Text); }
        }

            property int Capacity{
                int get() { return Convert::ToInt32(txtCapacity->Text); }
        }

            property String^ Description{
                String ^ get() { return txtDescription->Text; }
        }

    protected:
        ~RoomEditForm() {
            if (components) delete components;
        }

    private:
        String^ mode;
        System::ComponentModel::Container^ components;

        TextBox^ txtRoomNumber;
        TextBox^ txtPrice;
        TextBox^ txtCapacity;
        TextBox^ txtDescription;
        ComboBox^ cmbRoomType;
        Button^ btnSave;
        Label^ lblRoomNumber;
        Label^ lblRoomType;
        Label^ lblPrice;
        Label^ lblCapacity;
        Label^ lblDescription;
        Label^ lblRoomHint;     // Подсказка о номере комнаты
        Label^ lblPriceHint;    // Подсказка о максимальной цене

        void InitializeComponent(void) {
            this->components = gcnew System::ComponentModel::Container();
            this->txtRoomNumber = gcnew TextBox();
            this->txtPrice = gcnew TextBox();
            this->txtCapacity = gcnew TextBox();
            this->txtDescription = gcnew TextBox();
            this->cmbRoomType = gcnew ComboBox();
            this->btnSave = gcnew Button();
            this->lblRoomNumber = gcnew Label();
            this->lblRoomType = gcnew Label();
            this->lblPrice = gcnew Label();
            this->lblCapacity = gcnew Label();
            this->lblDescription = gcnew Label();
            this->lblRoomHint = gcnew Label();
            this->lblPriceHint = gcnew Label();

            this->SuspendLayout();

            // lblRoomNumber
            this->lblRoomNumber->Text = L"Номер комнаты:*";
            this->lblRoomNumber->Location = Drawing::Point(12, 15);
            this->lblRoomNumber->Size = Drawing::Size(100, 23);

            // txtRoomNumber
            this->txtRoomNumber->Location = Drawing::Point(120, 12);
            this->txtRoomNumber->Size = Drawing::Size(150, 20);
            this->txtRoomNumber->TextChanged += gcnew EventHandler(this, &RoomEditForm::txtRoomNumber_TextChanged);

            // lblRoomHint
            this->lblRoomHint->Text = L"Номер от 101 до 599";
            this->lblRoomHint->Location = Drawing::Point(120, 35);
            this->lblRoomHint->Size = Drawing::Size(200, 15);
            this->lblRoomHint->Font = gcnew Drawing::Font("Arial", 7);
            this->lblRoomHint->ForeColor = Drawing::Color::Gray;

            // lblRoomType
            this->lblRoomType->Text = L"Тип номера:";
            this->lblRoomType->Location = Drawing::Point(12, 55);
            this->lblRoomType->Size = Drawing::Size(100, 23);

            // cmbRoomType
            this->cmbRoomType->Location = Drawing::Point(120, 52);
            this->cmbRoomType->Size = Drawing::Size(150, 21);
            this->cmbRoomType->DropDownStyle = ComboBoxStyle::DropDownList;

            // lblPrice
            this->lblPrice->Text = L"Цена за сутки:*";
            this->lblPrice->Location = Drawing::Point(12, 85);
            this->lblPrice->Size = Drawing::Size(100, 23);

            // txtPrice
            this->txtPrice->Location = Drawing::Point(120, 82);
            this->txtPrice->Size = Drawing::Size(150, 20);
            this->txtPrice->TextChanged += gcnew EventHandler(this, &RoomEditForm::txtPrice_TextChanged);

            // lblPriceHint
            this->lblPriceHint->Text = L"Максимальная цена: 100 000 руб.";
            this->lblPriceHint->Location = Drawing::Point(120, 105);
            this->lblPriceHint->Size = Drawing::Size(200, 15);
            this->lblPriceHint->Font = gcnew Drawing::Font("Arial", 7);
            this->lblPriceHint->ForeColor = Drawing::Color::Gray;

            // lblCapacity
            this->lblCapacity->Text = L"Вместимость:*";
            this->lblCapacity->Location = Drawing::Point(12, 125);
            this->lblCapacity->Size = Drawing::Size(100, 23);

            // txtCapacity
            this->txtCapacity->Location = Drawing::Point(120, 122);
            this->txtCapacity->Size = Drawing::Size(150, 20);

            // lblDescription
            this->lblDescription->Text = L"Описание:";
            this->lblDescription->Location = Drawing::Point(12, 155);
            this->lblDescription->Size = Drawing::Size(100, 23);

            // txtDescription
            this->txtDescription->Location = Drawing::Point(120, 152);
            this->txtDescription->Size = Drawing::Size(250, 60);
            this->txtDescription->Multiline = true;

            // btnSave
            this->btnSave->Text = L"Сохранить";
            this->btnSave->Location = Drawing::Point(150, 230);
            this->btnSave->Size = Drawing::Size(100, 30);
            this->btnSave->Click += gcnew EventHandler(this, &RoomEditForm::btnSave_Click);

            // Form
            this->ClientSize = Drawing::Size(400, 290);
            this->Controls->Add(this->lblRoomNumber);
            this->Controls->Add(this->txtRoomNumber);
            this->Controls->Add(this->lblRoomHint);
            this->Controls->Add(this->lblRoomType);
            this->Controls->Add(this->cmbRoomType);
            this->Controls->Add(this->lblPrice);
            this->Controls->Add(this->txtPrice);
            this->Controls->Add(this->lblPriceHint);
            this->Controls->Add(this->lblCapacity);
            this->Controls->Add(this->txtCapacity);
            this->Controls->Add(this->lblDescription);
            this->Controls->Add(this->txtDescription);
            this->Controls->Add(this->btnSave);
            this->StartPosition = FormStartPosition::CenterParent;

            this->ResumeLayout(false);
            this->PerformLayout();
        }

        void InitializeRoomTypes() {
            cmbRoomType->Items->Add("Стандарт");
            cmbRoomType->Items->Add("Комфорт");
            cmbRoomType->Items->Add("Люкс");
            cmbRoomType->Items->Add("Апартаменты");
            cmbRoomType->SelectedIndex = 0;
        }

        void ShowRoomControls() {
            txtRoomNumber->Visible = true;
            cmbRoomType->Visible = true;
            txtPrice->Visible = true;
            txtCapacity->Visible = true;
            txtDescription->Visible = true;
            lblRoomNumber->Visible = true;
            lblRoomHint->Visible = true;
            lblRoomType->Visible = true;
            lblPrice->Visible = true;
            lblPriceHint->Visible = true;
            lblCapacity->Visible = true;
            lblDescription->Visible = true;
        }

        void txtRoomNumber_TextChanged(Object^ sender, EventArgs^ e) {
            if (!String::IsNullOrWhiteSpace(txtRoomNumber->Text)) {
                try {
                    int roomNum = Convert::ToInt32(txtRoomNumber->Text);
                    if (roomNum < 101) {
                        lblRoomHint->Text = L"Номер должен быть не менее 101!";
                        lblRoomHint->ForeColor = Drawing::Color::Orange;
                        btnSave->Enabled = false;
                    }
                    else if (roomNum > 599) {
                        lblRoomHint->Text = L"Номер не может превышать 599!";
                        lblRoomHint->ForeColor = Drawing::Color::Red;
                        btnSave->Enabled = false;
                    }
                    else {
                        lblRoomHint->Text = L"Номер корректен (101-599)";
                        lblRoomHint->ForeColor = Drawing::Color::Green;
                        // Проверяем цену, если она уже введена
                        if (!String::IsNullOrWhiteSpace(txtPrice->Text)) {
                            try {
                                double price = Convert::ToDouble(txtPrice->Text);
                                if (price > 0 && price <= 100000) {
                                    btnSave->Enabled = true;
                                }
                            }
                            catch (Exception^) {}
                        }
                        else {
                            btnSave->Enabled = true;
                        }
                    }
                }
                catch (Exception^) {
                    lblRoomHint->Text = L"Введите корректный номер!";
                    lblRoomHint->ForeColor = Drawing::Color::Red;
                    btnSave->Enabled = false;
                }
            }
            else {
                lblRoomHint->Text = L"Номер от 101 до 599";
                lblRoomHint->ForeColor = Drawing::Color::Gray;
                btnSave->Enabled = true;
            }
        }

        void txtPrice_TextChanged(Object^ sender, EventArgs^ e) {
            if (!String::IsNullOrWhiteSpace(txtPrice->Text)) {
                try {
                    double price = Convert::ToDouble(txtPrice->Text);
                    if (price > 100000) {
                        lblPriceHint->Text = L"Цена превышает максимальную (100 000 руб.)!";
                        lblPriceHint->ForeColor = Drawing::Color::Red;
                        btnSave->Enabled = false;
                    }
                    else if (price <= 0) {
                        lblPriceHint->Text = L"Цена должна быть положительным числом!";
                        lblPriceHint->ForeColor = Drawing::Color::Orange;
                        btnSave->Enabled = false;
                    }
                    else {
                        lblPriceHint->Text = L"Цена корректна (до 100 000 руб.)";
                        lblPriceHint->ForeColor = Drawing::Color::Green;
                        // Проверяем номер комнаты, если он уже введен
                        if (!String::IsNullOrWhiteSpace(txtRoomNumber->Text)) {
                            try {
                                int roomNum = Convert::ToInt32(txtRoomNumber->Text);
                                if (roomNum >= 101 && roomNum <= 599) {
                                    btnSave->Enabled = true;
                                }
                            }
                            catch (Exception^) {}
                        }
                        else {
                            btnSave->Enabled = true;
                        }
                    }
                }
                catch (Exception^) {
                    lblPriceHint->Text = L"Введите корректное число!";
                    lblPriceHint->ForeColor = Drawing::Color::Red;
                    btnSave->Enabled = false;
                }
            }
            else {
                lblPriceHint->Text = L"Максимальная цена: 100 000 руб.";
                lblPriceHint->ForeColor = Drawing::Color::Gray;
                btnSave->Enabled = true;
            }
        }

        void btnSave_Click(Object^ sender, EventArgs^ e) {
            // Проверка номера комнаты
            if (String::IsNullOrWhiteSpace(txtRoomNumber->Text)) {
                MessageBox::Show("Введите номер комнаты!", "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            int roomNum;
            if (!Int32::TryParse(txtRoomNumber->Text, roomNum)) {
                MessageBox::Show("Номер комнаты должен быть числом!", "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            if (roomNum < 101) {
                MessageBox::Show("Номер комнаты должен быть не менее 101!", "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            if (roomNum > 599) {
                MessageBox::Show("Номер комнаты не может превышать 599!", "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            // Проверка цены
            if (String::IsNullOrWhiteSpace(txtPrice->Text)) {
                MessageBox::Show("Введите цену за сутки!", "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            double price;
            if (!Double::TryParse(txtPrice->Text, price)) {
                MessageBox::Show("Цена должна быть числом!", "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            if (price < 499) {
                MessageBox::Show("Цена должна быть больше 500!", "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            // Проверка максимальной цены
            if (price > 100000) {
                MessageBox::Show("Цена не может превышать 100 000 рублей за сутки!",
                    "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            // Проверка вместимости
            if (String::IsNullOrWhiteSpace(txtCapacity->Text)) {
                MessageBox::Show("Введите вместимость номера!", "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            int capacity;
            if (!Int32::TryParse(txtCapacity->Text, capacity)) {
                MessageBox::Show("Вместимость должна быть числом!", "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            if (capacity <= 0) {
                MessageBox::Show("Вместимость должна быть положительным числом!", "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            if (capacity > 10) {
                MessageBox::Show("Вместимость не может превышать 10 человек!",
                    "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            this->DialogResult = System::Windows::Forms::DialogResult::OK;
            this->Close();
        }
    };
}