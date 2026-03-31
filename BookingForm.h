#pragma once
#include "Hotel.h"

namespace HotelManagement {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class BookingForm : public Form
    {
    public:
        BookingForm(Hotel^ hotel) {
            this->hotel = hotel;
            InitializeComponent();
            InitializeData();
        }

        property Client^ SelectedClient {
            Client^ get() {
                if (cmbClients->SelectedItem == nullptr) return nullptr;
                return safe_cast<Client^>(cmbClients->SelectedItem);
            }
        }

        property Room^ SelectedRoom {
            Room^ get() {
                if (cmbRooms->SelectedItem == nullptr) return nullptr;
                return safe_cast<Room^>(cmbRooms->SelectedItem);
            }
        }

        property DateTime CheckInDate {
            DateTime get() { return dtpCheckIn->Value; }
        }

        property DateTime CheckOutDate {
            DateTime get() { return dtpCheckOut->Value; }
        }

        property int GuestsCount {
            int get() { return Convert::ToInt32(numGuests->Value); }
        }

    protected:
        ~BookingForm() {
            if (components) delete components;
        }

    private:
        Hotel^ hotel;
        System::ComponentModel::Container^ components;

        ComboBox^ cmbClients;
        ComboBox^ cmbRooms;
        DateTimePicker^ dtpCheckIn;
        DateTimePicker^ dtpCheckOut;
        NumericUpDown^ numGuests;
        Button^ btnCheckAvailability;
        Button^ btnBook;
        Label^ lblClient;
        Label^ lblRoom;
        Label^ lblCheckIn;
        Label^ lblCheckOut;
        Label^ lblGuests;
        Label^ lblTotalPrice;
        Label^ lblClientBookings;  // Новая метка для отображения бронирований клиента

        void InitializeComponent(void) {
            this->components = gcnew System::ComponentModel::Container();
            this->cmbClients = gcnew ComboBox();
            this->cmbRooms = gcnew ComboBox();
            this->dtpCheckIn = gcnew DateTimePicker();
            this->dtpCheckOut = gcnew DateTimePicker();
            this->numGuests = gcnew NumericUpDown();
            this->btnCheckAvailability = gcnew Button();
            this->btnBook = gcnew Button();
            this->lblClient = gcnew Label();
            this->lblRoom = gcnew Label();
            this->lblCheckIn = gcnew Label();
            this->lblCheckOut = gcnew Label();
            this->lblGuests = gcnew Label();
            this->lblTotalPrice = gcnew Label();
            this->lblClientBookings = gcnew Label();

            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numGuests))->BeginInit();
            this->SuspendLayout();

            // lblClient
            this->lblClient->Text = L"Клиент:";
            this->lblClient->Location = Drawing::Point(12, 15);
            this->lblClient->Size = Drawing::Size(80, 23);

            // cmbClients
            this->cmbClients->Location = Drawing::Point(100, 12);
            this->cmbClients->Size = Drawing::Size(200, 21);
            this->cmbClients->DisplayMember = "Name";
            this->cmbClients->DropDownStyle = ComboBoxStyle::DropDownList;
            this->cmbClients->SelectedIndexChanged += gcnew EventHandler(this, &BookingForm::cmbClients_SelectedIndexChanged);

            // lblClientBookings
            this->lblClientBookings->Location = Drawing::Point(100, 38);
            this->lblClientBookings->Size = Drawing::Size(280, 30);
            this->lblClientBookings->Text = L"";
            this->lblClientBookings->ForeColor = Drawing::Color::Blue;
            this->lblClientBookings->Font = gcnew Drawing::Font("Arial", 8);

            // lblRoom
            this->lblRoom->Text = L"Номер:";
            this->lblRoom->Location = Drawing::Point(12, 75);
            this->lblRoom->Size = Drawing::Size(80, 23);

            // cmbRooms
            this->cmbRooms->Location = Drawing::Point(100, 72);
            this->cmbRooms->Size = Drawing::Size(200, 21);
            this->cmbRooms->DisplayMember = "RoomNumber";
            this->cmbRooms->DropDownStyle = ComboBoxStyle::DropDownList;

            // lblCheckIn
            this->lblCheckIn->Text = L"Дата заезда:";
            this->lblCheckIn->Location = Drawing::Point(12, 105);
            this->lblCheckIn->Size = Drawing::Size(80, 23);

            // dtpCheckIn
            this->dtpCheckIn->Location = Drawing::Point(100, 102);
            this->dtpCheckIn->Size = Drawing::Size(150, 20);
            this->dtpCheckIn->Value = DateTime::Now;
            this->dtpCheckIn->ValueChanged += gcnew EventHandler(this, &BookingForm::dtpCheckIn_ValueChanged);

            // lblCheckOut
            this->lblCheckOut->Text = L"Дата выезда:";
            this->lblCheckOut->Location = Drawing::Point(12, 135);
            this->lblCheckOut->Size = Drawing::Size(80, 23);

            // dtpCheckOut
            this->dtpCheckOut->Location = Drawing::Point(100, 132);
            this->dtpCheckOut->Size = Drawing::Size(150, 20);
            this->dtpCheckOut->Value = DateTime::Now.AddDays(1);
            this->dtpCheckOut->ValueChanged += gcnew EventHandler(this, &BookingForm::dtpCheckOut_ValueChanged);

            // lblGuests
            this->lblGuests->Text = L"Кол-во гостей:";
            this->lblGuests->Location = Drawing::Point(12, 165);
            this->lblGuests->Size = Drawing::Size(80, 23);

            // numGuests
            this->numGuests->Location = Drawing::Point(100, 162);
            this->numGuests->Size = Drawing::Size(60, 20);
            this->numGuests->Minimum = 1;
            this->numGuests->Maximum = 10;
            this->numGuests->Value = 1;
            this->numGuests->ValueChanged += gcnew EventHandler(this, &BookingForm::numGuests_ValueChanged);

            // lblTotalPrice
            this->lblTotalPrice->Location = Drawing::Point(12, 195);
            this->lblTotalPrice->Size = Drawing::Size(300, 23);
            this->lblTotalPrice->Text = L"Итоговая стоимость: 0 руб.";
            this->lblTotalPrice->Font = gcnew Drawing::Font("Arial", 10, FontStyle::Bold);

            // btnCheckAvailability
            this->btnCheckAvailability->Text = L"Проверить доступность";
            this->btnCheckAvailability->Location = Drawing::Point(260, 102);
            this->btnCheckAvailability->Size = Drawing::Size(120, 30);
            this->btnCheckAvailability->Click += gcnew EventHandler(this, &BookingForm::btnCheckAvailability_Click);

            // btnBook
            this->btnBook->Text = L"Забронировать";
            this->btnBook->Location = Drawing::Point(150, 230);
            this->btnBook->Size = Drawing::Size(100, 30);
            this->btnBook->Click += gcnew EventHandler(this, &BookingForm::btnBook_Click);

            // Form
            this->ClientSize = Drawing::Size(400, 280);
            this->Controls->Add(this->lblClient);
            this->Controls->Add(this->cmbClients);
            this->Controls->Add(this->lblClientBookings);
            this->Controls->Add(this->lblRoom);
            this->Controls->Add(this->cmbRooms);
            this->Controls->Add(this->lblCheckIn);
            this->Controls->Add(this->dtpCheckIn);
            this->Controls->Add(this->lblCheckOut);
            this->Controls->Add(this->dtpCheckOut);
            this->Controls->Add(this->lblGuests);
            this->Controls->Add(this->numGuests);
            this->Controls->Add(this->lblTotalPrice);
            this->Controls->Add(this->btnCheckAvailability);
            this->Controls->Add(this->btnBook);
            this->StartPosition = FormStartPosition::CenterParent;

            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numGuests))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();
        }

        void InitializeData() {
            cmbClients->DataSource = hotel->GetClients();
            UpdateAvailableRooms();
        }

        void cmbClients_SelectedIndexChanged(Object^ sender, EventArgs^ e) {
            if (cmbClients->SelectedItem != nullptr) {
                Client^ client = safe_cast<Client^>(cmbClients->SelectedItem);

                // Подсчитываем текущие бронирования клиента
                int bookingsCount = 0;
                int totalGuests = 0;
                for each (Booking ^ booking in hotel->GetBookings()) {
                    if (booking->ClientData == client) {
                        bookingsCount++;
                        totalGuests += booking->GuestsCount;
                    }
                }

                if (bookingsCount > 0) {
                    lblClientBookings->Text = String::Format(
                        "У клиента уже есть {0} бронирований на {1} гостей",
                        bookingsCount, totalGuests);
                    lblClientBookings->Visible = true;
                }
                else {
                    lblClientBookings->Text = "У клиента нет активных бронирований";
                    lblClientBookings->Visible = true;
                }
            }
            else {
                lblClientBookings->Visible = false;
            }
        }

        void UpdateAvailableRooms() {
            if (dtpCheckOut->Value <= dtpCheckIn->Value) {
                cmbRooms->DataSource = nullptr;
                return;
            }

            int guests = Convert::ToInt32(numGuests->Value);
            array<Room^>^ availableRooms = hotel->GetAvailableRooms(
                dtpCheckIn->Value, dtpCheckOut->Value, guests);

            BindingList<Room^>^ roomsList = gcnew BindingList<Room^>();
            for each (Room ^ room in availableRooms) {
                roomsList->Add(room);
            }
            cmbRooms->DataSource = roomsList;
            cmbRooms->DisplayMember = "RoomNumber";

            UpdateTotalPrice();
        }

        void UpdateTotalPrice() {
            if (cmbRooms->SelectedItem != nullptr && dtpCheckOut->Value > dtpCheckIn->Value) {
                Room^ room = safe_cast<Room^>(cmbRooms->SelectedItem);
                int days = (dtpCheckOut->Value - dtpCheckIn->Value).Days;
                if (days > 0) {
                    double total = days * room->PricePerDay;
                    lblTotalPrice->Text = String::Format("Итоговая стоимость: {0:F2} руб.", total);
                }
                else {
                    lblTotalPrice->Text = "Итоговая стоимость: 0 руб.";
                }
            }
            else {
                lblTotalPrice->Text = "Итоговая стоимость: 0 руб.";
            }
        }

        void dtpCheckIn_ValueChanged(Object^ sender, EventArgs^ e) {
            if (dtpCheckOut->Value <= dtpCheckIn->Value) {
                dtpCheckOut->Value = dtpCheckIn->Value.AddDays(1);
            }
            UpdateAvailableRooms();
        }

        void dtpCheckOut_ValueChanged(Object^ sender, EventArgs^ e) {
            if (dtpCheckOut->Value <= dtpCheckIn->Value) {
                dtpCheckOut->Value = dtpCheckIn->Value.AddDays(1);
            }
            UpdateAvailableRooms();
        }

        void numGuests_ValueChanged(Object^ sender, EventArgs^ e) {
            UpdateAvailableRooms();
        }

        void btnCheckAvailability_Click(Object^ sender, EventArgs^ e) {
            if (dtpCheckOut->Value <= dtpCheckIn->Value) {
                MessageBox::Show("Дата выезда должна быть позже даты заезда",
                    "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            UpdateAvailableRooms();

            if (cmbRooms->Items->Count == 0) {
                MessageBox::Show("Нет доступных номеров на выбранные даты",
                    "Информация", MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
            else {
                MessageBox::Show(String::Format("Найдено {0} доступных номеров",
                    cmbRooms->Items->Count), "Информация",
                    MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
        }

        void btnBook_Click(Object^ sender, EventArgs^ e) {
            if (cmbClients->SelectedItem == nullptr) {
                MessageBox::Show("Выберите клиента", "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            if (cmbRooms->SelectedItem == nullptr) {
                MessageBox::Show("Выберите номер", "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            if (dtpCheckOut->Value <= dtpCheckIn->Value) {
                MessageBox::Show("Дата выезда должна быть позже даты заезда",
                    "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            // Дополнительная проверка - убеждаемся, что номер все еще доступен
            Room^ selectedRoom = safe_cast<Room^>(cmbRooms->SelectedItem);
            if (!hotel->IsRoomAvailable(selectedRoom->RoomNumber, dtpCheckIn->Value, dtpCheckOut->Value)) {
                MessageBox::Show("Выбранный номер больше не доступен на указанные даты.\nПожалуйста, проверьте доступность снова.",
                    "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                UpdateAvailableRooms();
                return;
            }

            this->DialogResult = System::Windows::Forms::DialogResult::OK;
            this->Close();
        }
    };
}