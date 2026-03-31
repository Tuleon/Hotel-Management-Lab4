#pragma once

namespace HotelApp {

    using namespace System;
    using namespace System::Windows::Forms;

    public ref class AddForm : public Form {
    public:
        TextBox^ nameBox;
        TextBox^ priceBox;
        TextBox^ discountBox;
        Button^ btn;

        String^ roomName;
        double price;
        double discount;

        AddForm() {
            this->Text = "Добавить";

            nameBox = gcnew TextBox();
            priceBox = gcnew TextBox();
            discountBox = gcnew TextBox();
            btn = gcnew Button();

            nameBox->Top = 10;
            priceBox->Top = 40;
            discountBox->Top = 70;

            btn->Text = "OK";
            btn->Top = 100;

            btn->Click += gcnew EventHandler(this, &AddForm::clickOK);

            Controls->Add(nameBox);
            Controls->Add(priceBox);
            Controls->Add(discountBox);
            Controls->Add(btn);
        }

    private:
        void clickOK(Object^ sender, EventArgs^ e) {
            try {
                roomName = nameBox->Text;
                price = Convert::ToDouble(priceBox->Text);
                discount = Convert::ToDouble(discountBox->Text);

                this->DialogResult = System::Windows::Forms::DialogResult::OK;
            }
            catch (...) {
                MessageBox::Show("Ошибка!");
            }
        }
    };

}