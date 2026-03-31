#pragma once
#include "Hotel.h"
#include "RoomEditForm.h"
#include "BookingForm.h"

namespace HotelManagement {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::IO;
    using namespace System::Text;

    public ref class MainForm : public Form
    {
    public:
        MainForm() {
            InitializeComponent();
            hotel = gcnew Hotel();
            InitializeBindings();
            LoadData();
        }

    protected:
        ~MainForm() {
            if (components) delete components;
        }

    private:
        Hotel^ hotel;
        System::ComponentModel::Container^ components;

        DataGridView^ roomsGrid;
        DataGridView^ clientsGrid;
        DataGridView^ bookingsGrid;
        BindingSource^ roomsBindingSource;
        BindingSource^ clientsBindingSource;
        BindingSource^ bookingsBindingSource;

        Button^ btnAddRoom;
        Button^ btnAddClient;
        Button^ btnEditRoom;
        Button^ btnEditClient;
        Button^ btnDeleteRoom;
        Button^ btnDeleteClient;
        Button^ btnAddBooking;
        Button^ btnCheckIn;
        Button^ btnCheckOut;
        Button^ btnExportBookings;
        Button^ btnImportBookings;

        TabControl^ tabControl;
        TabPage^ tabRooms;
        TabPage^ tabClients;
        TabPage^ tabBookings;

        // Сохраняем ссылки на элементы управления для форм
        Form^ clientForm;
        TextBox^ clientTxtName;
        TextBox^ clientTxtPhone;
        TextBox^ clientTxtPassport;
        TextBox^ clientTxtEmail;
        Label^ clientLblStatus;
        Button^ clientBtnSave;

        Form^ editClientForm;
        TextBox^ editClientTxtName;
        TextBox^ editClientTxtPhone;
        TextBox^ editClientTxtPassport;
        TextBox^ editClientTxtEmail;
        Label^ editClientLblStatus;
        Button^ editClientBtnSave;
        Client^ editClientSelected;
        String^ editClientOriginalPhone;

        void InitializeComponent(void) {
            this->components = gcnew System::ComponentModel::Container();

            this->roomsGrid = gcnew DataGridView();
            this->clientsGrid = gcnew DataGridView();
            this->bookingsGrid = gcnew DataGridView();
            this->roomsBindingSource = gcnew BindingSource(this->components);
            this->clientsBindingSource = gcnew BindingSource(this->components);
            this->bookingsBindingSource = gcnew BindingSource(this->components);

            this->btnAddRoom = gcnew Button();
            this->btnAddClient = gcnew Button();
            this->btnEditRoom = gcnew Button();
            this->btnEditClient = gcnew Button();
            this->btnDeleteRoom = gcnew Button();
            this->btnDeleteClient = gcnew Button();
            this->btnAddBooking = gcnew Button();
            this->btnCheckIn = gcnew Button();
            this->btnCheckOut = gcnew Button();
            this->btnExportBookings = gcnew Button();
            this->btnImportBookings = gcnew Button();

            this->tabControl = gcnew TabControl();
            this->tabRooms = gcnew TabPage();
            this->tabClients = gcnew TabPage();
            this->tabBookings = gcnew TabPage();

            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->roomsGrid))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->clientsGrid))->BeginInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->bookingsGrid))->BeginInit();
            this->SuspendLayout();

            // tabControl
            this->tabControl->Location = Point(10, 10);
            this->tabControl->Size = Drawing::Size(900, 500);

            // tabRooms
            this->tabRooms->Text = L"Номера";
            this->tabRooms->Controls->Add(this->roomsGrid);
            this->tabRooms->Controls->Add(this->btnAddRoom);
            this->tabRooms->Controls->Add(this->btnEditRoom);
            this->tabRooms->Controls->Add(this->btnDeleteRoom);

            // roomsGrid
            this->roomsGrid->Location = Point(10, 10);
            this->roomsGrid->Size = Drawing::Size(860, 400);
            this->roomsGrid->ReadOnly = true;
            this->roomsGrid->AllowUserToAddRows = false;
            this->roomsGrid->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;

            // btnAddRoom
            this->btnAddRoom->Text = L"Добавить номер";
            this->btnAddRoom->Location = Point(10, 420);
            this->btnAddRoom->Size = Drawing::Size(100, 30);
            this->btnAddRoom->Click += gcnew EventHandler(this, &MainForm::btnAddRoom_Click);

            // btnEditRoom
            this->btnEditRoom->Text = L"Редактировать";
            this->btnEditRoom->Location = Point(120, 420);
            this->btnEditRoom->Size = Drawing::Size(100, 30);
            this->btnEditRoom->Click += gcnew EventHandler(this, &MainForm::btnEditRoom_Click);

            // btnDeleteRoom
            this->btnDeleteRoom->Text = L"Удалить номер";
            this->btnDeleteRoom->Location = Point(230, 420);
            this->btnDeleteRoom->Size = Drawing::Size(100, 30);
            this->btnDeleteRoom->Click += gcnew EventHandler(this, &MainForm::btnDeleteRoom_Click);

            // tabClients
            this->tabClients->Text = L"Клиенты";
            this->tabClients->Controls->Add(this->clientsGrid);
            this->tabClients->Controls->Add(this->btnAddClient);
            this->tabClients->Controls->Add(this->btnEditClient);
            this->tabClients->Controls->Add(this->btnDeleteClient);

            // clientsGrid
            this->clientsGrid->Location = Point(10, 10);
            this->clientsGrid->Size = Drawing::Size(860, 400);
            this->clientsGrid->ReadOnly = true;
            this->clientsGrid->AllowUserToAddRows = false;
            this->clientsGrid->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;

            // btnAddClient
            this->btnAddClient->Text = L"Добавить клиента";
            this->btnAddClient->Location = Point(10, 420);
            this->btnAddClient->Size = Drawing::Size(100, 30);
            this->btnAddClient->Click += gcnew EventHandler(this, &MainForm::btnAddClient_Click);

            // btnEditClient
            this->btnEditClient->Text = L"Редактировать";
            this->btnEditClient->Location = Point(120, 420);
            this->btnEditClient->Size = Drawing::Size(100, 30);
            this->btnEditClient->Click += gcnew EventHandler(this, &MainForm::btnEditClient_Click);

            // btnDeleteClient
            this->btnDeleteClient->Text = L"Удалить клиента";
            this->btnDeleteClient->Location = Point(230, 420);
            this->btnDeleteClient->Size = Drawing::Size(100, 30);
            this->btnDeleteClient->Click += gcnew EventHandler(this, &MainForm::btnDeleteClient_Click);

            // tabBookings
            this->tabBookings->Text = L"Бронирования";
            this->tabBookings->Controls->Add(this->bookingsGrid);
            this->tabBookings->Controls->Add(this->btnAddBooking);
            this->tabBookings->Controls->Add(this->btnCheckIn);
            this->tabBookings->Controls->Add(this->btnCheckOut);
            this->tabBookings->Controls->Add(this->btnExportBookings);
            this->tabBookings->Controls->Add(this->btnImportBookings);

            // bookingsGrid
            this->bookingsGrid->Location = Point(10, 10);
            this->bookingsGrid->Size = Drawing::Size(860, 380);
            this->bookingsGrid->ReadOnly = true;
            this->bookingsGrid->AllowUserToAddRows = false;
            this->bookingsGrid->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;

            // btnAddBooking
            this->btnAddBooking->Text = L"Новое бронирование";
            this->btnAddBooking->Location = Point(10, 400);
            this->btnAddBooking->Size = Drawing::Size(120, 30);
            this->btnAddBooking->Click += gcnew EventHandler(this, &MainForm::btnAddBooking_Click);

            // btnCheckIn
            this->btnCheckIn->Text = L"Заселить";
            this->btnCheckIn->Location = Point(140, 400);
            this->btnCheckIn->Size = Drawing::Size(80, 30);
            this->btnCheckIn->Click += gcnew EventHandler(this, &MainForm::btnCheckIn_Click);

            // btnCheckOut
            this->btnCheckOut->Text = L"Выселить";
            this->btnCheckOut->Location = Point(230, 400);
            this->btnCheckOut->Size = Drawing::Size(80, 30);
            this->btnCheckOut->Click += gcnew EventHandler(this, &MainForm::btnCheckOut_Click);

            // btnExportBookings
            this->btnExportBookings->Text = L"Экспорт";
            this->btnExportBookings->Location = Point(750, 400);
            this->btnExportBookings->Size = Drawing::Size(60, 30);
            this->btnExportBookings->Click += gcnew EventHandler(this, &MainForm::btnExportBookings_Click);

            // btnImportBookings
            this->btnImportBookings->Text = L"Импорт";
            this->btnImportBookings->Location = Point(820, 400);
            this->btnImportBookings->Size = Drawing::Size(60, 30);
            this->btnImportBookings->Click += gcnew EventHandler(this, &MainForm::btnImportBookings_Click);

            this->tabControl->TabPages->Add(this->tabRooms);
            this->tabControl->TabPages->Add(this->tabClients);
            this->tabControl->TabPages->Add(this->tabBookings);

            // MainForm
            this->ClientSize = Drawing::Size(920, 520);
            this->Controls->Add(this->tabControl);
            this->Text = L"Управление гостиницей";
            this->StartPosition = FormStartPosition::CenterScreen;

            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->roomsGrid))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->clientsGrid))->EndInit();
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->bookingsGrid))->EndInit();
            this->ResumeLayout(false);
        }

        void InitializeBindings() {
            // Настройка колонок для номеров
            roomsGrid->Columns->Clear();

            DataGridViewTextBoxColumn^ colNumber = gcnew DataGridViewTextBoxColumn();
            colNumber->Name = "RoomNumber";
            colNumber->HeaderText = "Номер";
            colNumber->DataPropertyName = "RoomNumber";
            roomsGrid->Columns->Add(colNumber);

            DataGridViewTextBoxColumn^ colType = gcnew DataGridViewTextBoxColumn();
            colType->Name = "TypeString";
            colType->HeaderText = "Тип";
            colType->DataPropertyName = "TypeString";
            roomsGrid->Columns->Add(colType);

            DataGridViewTextBoxColumn^ colPrice = gcnew DataGridViewTextBoxColumn();
            colPrice->Name = "PricePerDay";
            colPrice->HeaderText = "Цена/сутки";
            colPrice->DataPropertyName = "PricePerDay";
            roomsGrid->Columns->Add(colPrice);

            DataGridViewTextBoxColumn^ colCapacity = gcnew DataGridViewTextBoxColumn();
            colCapacity->Name = "Capacity";
            colCapacity->HeaderText = "Мест";
            colCapacity->DataPropertyName = "Capacity";
            roomsGrid->Columns->Add(colCapacity);

            DataGridViewTextBoxColumn^ colStatus = gcnew DataGridViewTextBoxColumn();
            colStatus->Name = "StatusString";
            colStatus->HeaderText = "Статус";
            colStatus->DataPropertyName = "StatusString";
            roomsGrid->Columns->Add(colStatus);

            // Настройка колонок для клиентов
            clientsGrid->Columns->Clear();

            DataGridViewTextBoxColumn^ colName = gcnew DataGridViewTextBoxColumn();
            colName->Name = "Name";
            colName->HeaderText = "Имя";
            colName->DataPropertyName = "Name";
            clientsGrid->Columns->Add(colName);

            DataGridViewTextBoxColumn^ colPhone = gcnew DataGridViewTextBoxColumn();
            colPhone->Name = "Phone";
            colPhone->HeaderText = "Телефон";
            colPhone->DataPropertyName = "Phone";
            clientsGrid->Columns->Add(colPhone);

            DataGridViewTextBoxColumn^ colPassport = gcnew DataGridViewTextBoxColumn();
            colPassport->Name = "PassportNumber";
            colPassport->HeaderText = "Паспорт";
            colPassport->DataPropertyName = "PassportNumber";
            clientsGrid->Columns->Add(colPassport);

            DataGridViewTextBoxColumn^ colEmail = gcnew DataGridViewTextBoxColumn();
            colEmail->Name = "Email";
            colEmail->HeaderText = "Email";
            colEmail->DataPropertyName = "Email";
            clientsGrid->Columns->Add(colEmail);

            // Настройка колонок для бронирований
            bookingsGrid->Columns->Clear();

            DataGridViewTextBoxColumn^ colBookClient = gcnew DataGridViewTextBoxColumn();
            colBookClient->Name = "ClientName";
            colBookClient->HeaderText = "Клиент";
            colBookClient->DataPropertyName = "ClientName";
            bookingsGrid->Columns->Add(colBookClient);

            DataGridViewTextBoxColumn^ colBookRoom = gcnew DataGridViewTextBoxColumn();
            colBookRoom->Name = "RoomNumber";
            colBookRoom->HeaderText = "Номер";
            colBookRoom->DataPropertyName = "RoomNumber";
            bookingsGrid->Columns->Add(colBookRoom);

            DataGridViewTextBoxColumn^ colBookType = gcnew DataGridViewTextBoxColumn();
            colBookType->Name = "RoomTypeString";
            colBookType->HeaderText = "Тип номера";
            colBookType->DataPropertyName = "RoomTypeString";
            bookingsGrid->Columns->Add(colBookType);

            DataGridViewTextBoxColumn^ colCheckIn = gcnew DataGridViewTextBoxColumn();
            colCheckIn->Name = "CheckInDateString";
            colCheckIn->HeaderText = "Заезд";
            colCheckIn->DataPropertyName = "CheckInDateString";
            bookingsGrid->Columns->Add(colCheckIn);

            DataGridViewTextBoxColumn^ colCheckOut = gcnew DataGridViewTextBoxColumn();
            colCheckOut->Name = "CheckOutDateString";
            colCheckOut->HeaderText = "Выезд";
            colCheckOut->DataPropertyName = "CheckOutDateString";
            bookingsGrid->Columns->Add(colCheckOut);

            DataGridViewTextBoxColumn^ colDays = gcnew DataGridViewTextBoxColumn();
            colDays->Name = "StayDuration";
            colDays->HeaderText = "Дней";
            colDays->DataPropertyName = "StayDuration";
            bookingsGrid->Columns->Add(colDays);

            DataGridViewTextBoxColumn^ colTotal = gcnew DataGridViewTextBoxColumn();
            colTotal->Name = "TotalPrice";
            colTotal->HeaderText = "Сумма";
            colTotal->DataPropertyName = "TotalPrice";
            bookingsGrid->Columns->Add(colTotal);

            // Привязка данных
            roomsBindingSource->DataSource = hotel->GetRooms();
            clientsBindingSource->DataSource = hotel->GetClients();
            bookingsBindingSource->DataSource = hotel->GetBookings();

            roomsGrid->DataSource = roomsBindingSource;
            clientsGrid->DataSource = clientsBindingSource;
            bookingsGrid->DataSource = bookingsBindingSource;
        }

        void LoadData() {
            roomsBindingSource->ResetBindings(false);
            clientsBindingSource->ResetBindings(false);
            bookingsBindingSource->ResetBindings(false);
        }

        void btnAddRoom_Click(Object^ sender, EventArgs^ e) {
            RoomEditForm^ form = gcnew RoomEditForm();
            form->SetModeForAdd("Room");

            if (form->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                try {
                    // Проверка номера комнаты
                    if (form->RoomNumber < 1 || form->RoomNumber > 599) {
                        MessageBox::Show("Номер комнаты должен быть в диапазоне от 101 до 599!",
                            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                        return;
                    }

                    // Проверка цены
                    if (form->PricePerDay > 100000) {
                        MessageBox::Show("Цена номера не может превышать 100 000 рублей за сутки!",
                            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                        return;
                    }

                    if (form->PricePerDay <= 0) {
                        MessageBox::Show("Цена номера должна быть положительной!",
                            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                        return;
                    }

                    Room^ room = gcnew Room(
                        form->RoomNumber,
                        form->Type,
                        form->PricePerDay,
                        form->Capacity
                    );
                    room->Description = form->Description;
                    hotel->AddRoom(room);
                    roomsBindingSource->ResetBindings(false);
                    MessageBox::Show("Номер успешно добавлен!", "Успех",
                        MessageBoxButtons::OK, MessageBoxIcon::Information);
                }
                catch (Exception^ ex) {
                    MessageBox::Show("Ошибка при добавлении номера: " + ex->Message,
                        "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                }
            }
        }

        void btnEditRoom_Click(Object^ sender, EventArgs^ e) {
            if (roomsGrid->CurrentRow == nullptr) return;

            Room^ selected = safe_cast<Room^>(roomsGrid->CurrentRow->DataBoundItem);
            RoomEditForm^ form = gcnew RoomEditForm();
            form->SetMode("Room", selected);

            if (form->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                try {
                    // Проверка цены (номер не меняется при редактировании)
                    if (form->PricePerDay > 100000) {
                        MessageBox::Show("Цена номера не может превышать 100 000 рублей за сутки!",
                            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                        return;
                    }

                    if (form->PricePerDay <= 0) {
                        MessageBox::Show("Цена номера должна быть положительной!",
                            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                        return;
                    }

                    selected->Type = form->Type;
                    selected->PricePerDay = form->PricePerDay;
                    selected->Capacity = form->Capacity;
                    selected->Description = form->Description;
                    roomsBindingSource->ResetBindings(false);
                    MessageBox::Show("Данные номера обновлены!", "Успех",
                        MessageBoxButtons::OK, MessageBoxIcon::Information);
                }
                catch (Exception^ ex) {
                    MessageBox::Show("Ошибка при обновлении номера: " + ex->Message,
                        "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                }
            }
        }

        void btnDeleteRoom_Click(Object^ sender, EventArgs^ e) {
            if (roomsGrid->CurrentRow == nullptr) return;

            Room^ selected = safe_cast<Room^>(roomsGrid->CurrentRow->DataBoundItem);

            if (MessageBox::Show("Удалить выбранный номер?", "Подтверждение",
                MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes) {
                hotel->RemoveRoom(selected);
                roomsBindingSource->ResetBindings(false);
                MessageBox::Show("Номер удалён!", "Успех",
                    MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
        }

        void btnAddClient_Click(Object^ sender, EventArgs^ e) {
            // Создаем форму для добавления клиента
            clientForm = gcnew Form();
            clientForm->Text = "Добавить клиента";
            clientForm->Size = Drawing::Size(400, 350);
            clientForm->StartPosition = FormStartPosition::CenterParent;
            clientForm->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            clientForm->MaximizeBox = false;
            clientForm->MinimizeBox = false;

            clientTxtName = gcnew TextBox();
            clientTxtName->Location = Drawing::Point(120, 20);
            clientTxtName->Size = Drawing::Size(250, 20);

            clientTxtPhone = gcnew TextBox();
            clientTxtPhone->Location = Drawing::Point(120, 55);
            clientTxtPhone->Size = Drawing::Size(250, 20);
            clientTxtPhone->TextChanged += gcnew EventHandler(this, &MainForm::ClientPhone_TextChanged);
            clientTxtPhone->KeyPress += gcnew KeyPressEventHandler(this, &MainForm::PhoneNumber_KeyPress); // Добавляем проверку

            clientTxtPassport = gcnew TextBox();
            clientTxtPassport->Location = Drawing::Point(120, 90);
            clientTxtPassport->Size = Drawing::Size(250, 20);

            clientTxtEmail = gcnew TextBox();
            clientTxtEmail->Location = Drawing::Point(120, 125);
            clientTxtEmail->Size = Drawing::Size(250, 20);

            clientLblStatus = gcnew Label();
            clientLblStatus->Location = Drawing::Point(20, 160);
            clientLblStatus->Size = Drawing::Size(350, 30);
            clientLblStatus->Text = L"";
            clientLblStatus->ForeColor = Drawing::Color::Red;

            // Добавляем подсказку о формате телефона
            Label^ lblPhoneHint = gcnew Label();
            lblPhoneHint->Text = L"(только цифры, 10-15 цифр)";
            lblPhoneHint->Location = Drawing::Point(120, 78);
            lblPhoneHint->Size = Drawing::Size(200, 15);
            lblPhoneHint->Font = gcnew Drawing::Font("Arial", 7);
            lblPhoneHint->ForeColor = Drawing::Color::Gray;

            clientBtnSave = gcnew Button();
            clientBtnSave->Text = "Сохранить";
            clientBtnSave->Location = Drawing::Point(150, 210);
            clientBtnSave->Size = Drawing::Size(100, 30);
            clientBtnSave->Click += gcnew EventHandler(this, &MainForm::SaveClient_Click);

            Label^ lblName = gcnew Label();
            lblName->Text = "Имя:*";
            lblName->Location = Drawing::Point(20, 23);
            lblName->Size = Drawing::Size(70, 20);

            Label^ lblPhone = gcnew Label();
            lblPhone->Text = "Телефон:*";
            lblPhone->Location = Drawing::Point(20, 58);
            lblPhone->Size = Drawing::Size(70, 20);

            Label^ lblPassport = gcnew Label();
            lblPassport->Text = "Паспорт:";
            lblPassport->Location = Drawing::Point(20, 93);
            lblPassport->Size = Drawing::Size(70, 20);

            Label^ lblEmail = gcnew Label();
            lblEmail->Text = "Email:";
            lblEmail->Location = Drawing::Point(20, 128);
            lblEmail->Size = Drawing::Size(70, 20);

            clientForm->Controls->Add(lblName);
            clientForm->Controls->Add(lblPhone);
            clientForm->Controls->Add(lblPassport);
            clientForm->Controls->Add(lblEmail);
            clientForm->Controls->Add(clientTxtName);
            clientForm->Controls->Add(clientTxtPhone);
            clientForm->Controls->Add(clientTxtPassport);
            clientForm->Controls->Add(clientTxtEmail);
            clientForm->Controls->Add(lblPhoneHint);
            clientForm->Controls->Add(clientLblStatus);
            clientForm->Controls->Add(clientBtnSave);

            clientForm->ShowDialog();
        }

        // Обработчик для проверки ввода только цифр
        void PhoneNumber_KeyPress(Object^ sender, KeyPressEventArgs^ e) {
            // Разрешаем цифры, Backspace, Delete, Enter, Tab
            if (!Char::IsDigit(e->KeyChar) &&
                e->KeyChar != '\b' &&      // Backspace
                e->KeyChar != 127 &&       // Delete
                e->KeyChar != '\r' &&      // Enter
                e->KeyChar != '\t') {      // Tab
                e->Handled = true; // Блокируем ввод
            }
        }

        // Обработчик для проверки телефона (валидация и проверка на дубликат)
        void ClientPhone_TextChanged(Object^ sender, EventArgs^ e) {
            String^ phone = clientTxtPhone->Text;

            // Проверяем, что телефон содержит только цифры и имеет правильную длину
            if (!String::IsNullOrWhiteSpace(phone)) {
                // Проверяем, что все символы - цифры
                bool isValid = true;
                for each(Char c in phone) {
                    if (!Char::IsDigit(c)) {
                        isValid = false;
                        break;
                    }
                }

                if (!isValid) {
                    clientLblStatus->Text = "Телефон должен содержать только цифры!";
                    clientLblStatus->ForeColor = Drawing::Color::Red;
                    clientBtnSave->Enabled = false;
                    return;
                }

                if (phone->Length < 10) {
                    clientLblStatus->Text = "Телефон должен содержать минимум 10 цифр!";
                    clientLblStatus->ForeColor = Drawing::Color::Orange;
                    clientBtnSave->Enabled = false;
                    return;
                }

                if (phone->Length > 15) {
                    clientLblStatus->Text = "Телефон должен содержать максимум 15 цифр!";
                    clientLblStatus->ForeColor = Drawing::Color::Orange;
                    clientBtnSave->Enabled = false;
                    return;
                }

                // Проверка на дубликат
                if (hotel->IsClientExists(phone)) {
                    clientLblStatus->Text = "Клиент с таким телефоном уже существует!";
                    clientLblStatus->ForeColor = Drawing::Color::Red;
                    clientBtnSave->Enabled = false;
                }
                else {
                    clientLblStatus->Text = "Телефон корректный и свободен";
                    clientLblStatus->ForeColor = Drawing::Color::Green;
                    clientBtnSave->Enabled = true;
                }
            }
            else {
                clientLblStatus->Text = "";
                clientBtnSave->Enabled = true;
            }
        }

        void SaveClient_Click(Object^ sender, EventArgs^ e) {
            if (String::IsNullOrWhiteSpace(clientTxtName->Text)) {
                MessageBox::Show("Введите имя клиента!", "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            if (String::IsNullOrWhiteSpace(clientTxtPhone->Text)) {
                MessageBox::Show("Введите телефон клиента!", "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            String^ phone = clientTxtPhone->Text;

            // Проверка, что телефон содержит только цифры
            for each(Char c in phone) {
                if (!Char::IsDigit(c)) {
                    MessageBox::Show("Телефон должен содержать только цифры!", "Ошибка",
                        MessageBoxButtons::OK, MessageBoxIcon::Error);
                    return;
                }
            }

            // Проверка длины телефона
            if (phone->Length < 10 || phone->Length > 15) {
                MessageBox::Show("Телефон должен содержать от 10 до 15 цифр!", "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            // Проверка на дубликат
            if (hotel->IsClientExists(phone)) {
                MessageBox::Show("Клиент с таким номером телефона уже существует!\nПожалуйста, введите другой номер.",
                    "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            // Создаем клиента
            Client^ client = gcnew Client(clientTxtName->Text, clientTxtPhone->Text,
                clientTxtPassport->Text, clientTxtEmail->Text);

            // Добавляем с проверкой
            if (hotel->AddClient(client)) {
                clientsBindingSource->ResetBindings(false);
                clientForm->Close();
                MessageBox::Show("Клиент успешно добавлен!", "Успех",
                    MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
            else {
                MessageBox::Show("Клиент с таким телефоном уже существует!",
                    "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        

        

        void btnEditClient_Click(Object^ sender, EventArgs^ e) {
            if (clientsGrid->CurrentRow == nullptr) return;

            editClientSelected = safe_cast<Client^>(clientsGrid->CurrentRow->DataBoundItem);
            editClientOriginalPhone = editClientSelected->Phone;

            editClientForm = gcnew Form();
            editClientForm->Text = "Редактировать клиента";
            editClientForm->Size = Drawing::Size(400, 320);
            editClientForm->StartPosition = FormStartPosition::CenterParent;
            editClientForm->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
            editClientForm->MaximizeBox = false;
            editClientForm->MinimizeBox = false;

            editClientTxtName = gcnew TextBox();
            editClientTxtName->Location = Drawing::Point(120, 20);
            editClientTxtName->Size = Drawing::Size(250, 20);
            editClientTxtName->Text = editClientSelected->Name;

            editClientTxtPhone = gcnew TextBox();
            editClientTxtPhone->Location = Drawing::Point(120, 55);
            editClientTxtPhone->Size = Drawing::Size(250, 20);
            editClientTxtPhone->Text = editClientSelected->Phone;
            editClientTxtPhone->TextChanged += gcnew EventHandler(this, &MainForm::EditClientPhone_TextChanged);

            editClientTxtPassport = gcnew TextBox();
            editClientTxtPassport->Location = Drawing::Point(120, 90);
            editClientTxtPassport->Size = Drawing::Size(250, 20);
            editClientTxtPassport->Text = editClientSelected->PassportNumber;

            editClientTxtEmail = gcnew TextBox();
            editClientTxtEmail->Location = Drawing::Point(120, 125);
            editClientTxtEmail->Size = Drawing::Size(250, 20);
            editClientTxtEmail->Text = editClientSelected->Email;

            editClientLblStatus = gcnew Label();
            editClientLblStatus->Location = Drawing::Point(20, 160);
            editClientLblStatus->Size = Drawing::Size(350, 30);
            editClientLblStatus->Text = L"";
            editClientLblStatus->ForeColor = Drawing::Color::Red;

            editClientBtnSave = gcnew Button();
            editClientBtnSave->Text = "Сохранить";
            editClientBtnSave->Location = Drawing::Point(150, 200);
            editClientBtnSave->Size = Drawing::Size(100, 30);
            editClientBtnSave->Click += gcnew EventHandler(this, &MainForm::UpdateClient_Click);

            Label^ lblName = gcnew Label();
            lblName->Text = "Имя:*";
            lblName->Location = Drawing::Point(20, 23);
            lblName->Size = Drawing::Size(70, 20);

            Label^ lblPhone = gcnew Label();
            lblPhone->Text = "Телефон:*";
            lblPhone->Location = Drawing::Point(20, 58);
            lblPhone->Size = Drawing::Size(70, 20);

            Label^ lblPassport = gcnew Label();
            lblPassport->Text = "Паспорт:";
            lblPassport->Location = Drawing::Point(20, 93);
            lblPassport->Size = Drawing::Size(70, 20);

            Label^ lblEmail = gcnew Label();
            lblEmail->Text = "Email:";
            lblEmail->Location = Drawing::Point(20, 128);
            lblEmail->Size = Drawing::Size(70, 20);

            editClientForm->Controls->Add(lblName);
            editClientForm->Controls->Add(lblPhone);
            editClientForm->Controls->Add(lblPassport);
            editClientForm->Controls->Add(lblEmail);
            editClientForm->Controls->Add(editClientTxtName);
            editClientForm->Controls->Add(editClientTxtPhone);
            editClientForm->Controls->Add(editClientTxtPassport);
            editClientForm->Controls->Add(editClientTxtEmail);
            editClientForm->Controls->Add(editClientLblStatus);
            editClientForm->Controls->Add(editClientBtnSave);

            editClientForm->ShowDialog();
        }

        void EditClientPhone_TextChanged(Object^ sender, EventArgs^ e) {
            if (!String::IsNullOrWhiteSpace(editClientTxtPhone->Text)) {
                if (editClientTxtPhone->Text != editClientOriginalPhone && hotel->IsClientExists(editClientTxtPhone->Text)) {
                    editClientLblStatus->Text = "Клиент с таким телефоном уже существует!";
                    editClientLblStatus->ForeColor = Drawing::Color::Red;
                    editClientBtnSave->Enabled = false;
                }
                else {
                    editClientLblStatus->Text = "Телефон доступен";
                    editClientLblStatus->ForeColor = Drawing::Color::Green;
                    editClientBtnSave->Enabled = true;
                }
            }
            else {
                editClientLblStatus->Text = "";
                editClientBtnSave->Enabled = true;
            }
        }

        void UpdateClient_Click(Object^ sender, EventArgs^ e) {
            if (String::IsNullOrWhiteSpace(editClientTxtName->Text)) {
                MessageBox::Show("Введите имя клиента!", "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            if (String::IsNullOrWhiteSpace(editClientTxtPhone->Text)) {
                MessageBox::Show("Введите телефон клиента!", "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            // Проверяем, изменился ли телефон
            if (editClientTxtPhone->Text != editClientOriginalPhone && hotel->IsClientExists(editClientTxtPhone->Text)) {
                MessageBox::Show("Клиент с таким номером телефона уже существует!",
                    "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            // Обновляем данные
            editClientSelected->Name = editClientTxtName->Text;
            editClientSelected->Phone = editClientTxtPhone->Text;
            editClientSelected->PassportNumber = editClientTxtPassport->Text;
            editClientSelected->Email = editClientTxtEmail->Text;

            clientsBindingSource->ResetBindings(false);
            editClientForm->Close();
            MessageBox::Show("Данные клиента обновлены!", "Успех",
                MessageBoxButtons::OK, MessageBoxIcon::Information);
        }

        void btnDeleteClient_Click(Object^ sender, EventArgs^ e) {
            if (clientsGrid->CurrentRow == nullptr) return;

            Client^ selected = safe_cast<Client^>(clientsGrid->CurrentRow->DataBoundItem);

            if (MessageBox::Show("Удалить выбранного клиента и все его бронирования?",
                "Подтверждение", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes) {
                hotel->RemoveClient(selected);
                clientsBindingSource->ResetBindings(false);
                bookingsBindingSource->ResetBindings(false);
                MessageBox::Show("Клиент удалён!", "Успех",
                    MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
        }

        void btnAddBooking_Click(Object^ sender, EventArgs^ e) {
            if (hotel->GetClients()->Count == 0) {
                MessageBox::Show("Сначала добавьте клиента!", "Информация",
                    MessageBoxButtons::OK, MessageBoxIcon::Information);
                return;
            }

            BookingForm^ form = gcnew BookingForm(hotel);
            form->StartPosition = FormStartPosition::CenterParent;

            if (form->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
                try {
                    Booking^ booking = gcnew Booking(
                        form->SelectedClient,
                        form->SelectedRoom,
                        form->CheckInDate,
                        form->CheckOutDate,
                        form->GuestsCount
                    );
                    if (hotel->AddBooking(booking)) {
                        bookingsBindingSource->ResetBindings(false);
                        roomsBindingSource->ResetBindings(false);
                        MessageBox::Show("Бронирование успешно создано!", "Успех",
                            MessageBoxButtons::OK, MessageBoxIcon::Information);
                    }
                    else {
                        MessageBox::Show("Номер уже забронирован на выбранные даты!",
                            "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                    }
                }
                catch (Exception^ ex) {
                    MessageBox::Show("Ошибка при создании бронирования: " + ex->Message,
                        "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
                }
            }
        }

        void btnCheckIn_Click(Object^ sender, EventArgs^ e) {
            if (bookingsGrid->CurrentRow == nullptr) return;

            Booking^ selected = safe_cast<Booking^>(bookingsGrid->CurrentRow->DataBoundItem);

            if (selected->RoomData->Status == RoomStatus::Occupied) {
                MessageBox::Show("Номер уже занят!", "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            selected->RoomData->Status = RoomStatus::Occupied;
            bookingsBindingSource->ResetBindings(false);
            roomsBindingSource->ResetBindings(false);
            MessageBox::Show("Гость заселён!", "Успех",
                MessageBoxButtons::OK, MessageBoxIcon::Information);
        }

        void btnCheckOut_Click(Object^ sender, EventArgs^ e) {
            if (bookingsGrid->CurrentRow == nullptr) return;

            Booking^ selected = safe_cast<Booking^>(bookingsGrid->CurrentRow->DataBoundItem);

            if (MessageBox::Show("Выселить гостя и закрыть бронирование?",
                "Подтверждение", MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes) {
                selected->RoomData->Status = RoomStatus::Available;
                hotel->RemoveBooking(selected);
                bookingsBindingSource->ResetBindings(false);
                roomsBindingSource->ResetBindings(false);
                MessageBox::Show("Гость выселен!", "Успех",
                    MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
        }

        void btnExportBookings_Click(Object^ sender, EventArgs^ e) {
            SaveFileDialog^ saveDialog = gcnew SaveFileDialog();
            saveDialog->Filter = "CSV файлы (*.csv)|*.csv";
            saveDialog->FileName = "Bookings.csv";

            if (saveDialog->ShowDialog() != System::Windows::Forms::DialogResult::OK) return;

            try {
                StringBuilder^ sb = gcnew StringBuilder();
                // Расширенный заголовок с паспортом и email
                sb->AppendLine("Клиент;Телефон;Паспорт;Email;Номер;Тип;Заезд;Выезд;Дней;Сумма");

                for each(Booking ^ booking in hotel->GetBookings()) {
                    sb->AppendLine(String::Format("{0};{1};{2};{3};{4};{5};{6};{7};{8};{9:F2}",
                        booking->ClientName,
                        booking->ClientPhone,
                        booking->ClientData->PassportNumber,  // Паспорт
                        booking->ClientData->Email,           // Email
                        booking->RoomNumber,
                        booking->RoomTypeString,
                        booking->CheckInDateString,
                        booking->CheckOutDateString,
                        booking->StayDuration,
                        booking->TotalPrice));
                }

                File::WriteAllText(saveDialog->FileName, sb->ToString(), Encoding::UTF8);
                MessageBox::Show("Бронирования успешно экспортированы!", "Успех",
                    MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
            catch (Exception^ ex) {
                MessageBox::Show("Ошибка экспорта: " + ex->Message, "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        void btnImportBookings_Click(Object^ sender, EventArgs^ e) {
            OpenFileDialog^ openDialog = gcnew OpenFileDialog();
            openDialog->Filter = "CSV файлы (*.csv)|*.csv";

            if (openDialog->ShowDialog() != System::Windows::Forms::DialogResult::OK) return;

            try {
                array<String^>^ lines = File::ReadAllLines(openDialog->FileName, Encoding::UTF8);

                if (lines->Length < 2) {
                    MessageBox::Show("Файл пуст", "Ошибка",
                        MessageBoxButtons::OK, MessageBoxIcon::Error);
                    return;
                }

                int imported = 0;
                int errors = 0;

                // Определяем формат файла по заголовку
                bool isExtendedFormat = false;
                String^ header = lines[0];
                if (header->Contains("Паспорт") && header->Contains("Email")) {
                    isExtendedFormat = true;
                }

                // Пропускаем заголовок
                for (int i = 1; i < lines->Length; i++) {
                    if (String::IsNullOrWhiteSpace(lines[i])) continue;

                    try {
                        array<String^>^ parts = lines[i]->Split(';');

                        if (isExtendedFormat && parts->Length >= 10) {
                            // Расширенный формат: Клиент;Телефон;Паспорт;Email;Номер;Тип;Заезд;Выезд;Дней;Сумма
                            String^ clientName = parts[0]->Trim('"');
                            String^ clientPhone = parts[1]->Trim('"');
                            String^ clientPassport = parts[2]->Trim('"');
                            String^ clientEmail = parts[3]->Trim('"');
                            int roomNumber = Convert::ToInt32(parts[4]);
                            String^ roomType = parts[5]->Trim('"');
                            DateTime checkIn = DateTime::Parse(parts[6]);
                            DateTime checkOut = DateTime::Parse(parts[7]);
                            int guests = Convert::ToInt32(parts[8]);

                            // Находим или создаем клиента с паспортом и email
                            Client^ client = FindOrCreateClientExtended(clientName, clientPhone, clientPassport, clientEmail);
                            if (client == nullptr) {
                                errors++;
                                continue;
                            }

                            // Находим номер
                            Room^ room = FindRoomByNumber(roomNumber);
                            if (room == nullptr) {
                                errors++;
                                continue;
                            }

                            // Проверяем доступность номера
                            if (hotel->IsRoomAvailable(roomNumber, checkIn, checkOut)) {
                                // Создаем бронирование
                                Booking^ booking = gcnew Booking(client, room, checkIn, checkOut, guests);

                                // Добавляем в отель
                                if (hotel->AddBooking(booking)) {
                                    imported++;
                                }
                                else {
                                    errors++;
                                }
                            }
                            else {
                                errors++;
                            }
                        }
                        else if (parts->Length >= 8) {
                            // Старый формат: Клиент;Телефон;Номер;Тип;Заезд;Выезд;Дней;Сумма
                            String^ clientName = parts[0]->Trim('"');
                            String^ clientPhone = parts[1]->Trim('"');
                            int roomNumber = Convert::ToInt32(parts[2]);
                            String^ roomType = parts[3]->Trim('"');
                            DateTime checkIn = DateTime::Parse(parts[4]);
                            DateTime checkOut = DateTime::Parse(parts[5]);
                            int guests = Convert::ToInt32(parts[6]);

                            // Находим или создаем клиента (с пустыми паспортом и email)
                            Client^ client = FindOrCreateClient(clientName, clientPhone);
                            if (client == nullptr) {
                                errors++;
                                continue;
                            }

                            // Находим номер
                            Room^ room = FindRoomByNumber(roomNumber);
                            if (room == nullptr) {
                                errors++;
                                continue;
                            }

                            // Проверяем доступность номера
                            if (hotel->IsRoomAvailable(roomNumber, checkIn, checkOut)) {
                                // Создаем бронирование
                                Booking^ booking = gcnew Booking(client, room, checkIn, checkOut, guests);

                                // Добавляем в отель
                                if (hotel->AddBooking(booking)) {
                                    imported++;
                                }
                                else {
                                    errors++;
                                }
                            }
                            else {
                                errors++;
                            }
                        }
                        else {
                            errors++;
                        }
                    }
                    catch (Exception^ ex) {
                        errors++;
                        System::Diagnostics::Debug::WriteLine("Ошибка импорта строки " + i + ": " + ex->Message);
                    }
                }

                // Обновляем все привязки данных
                bookingsBindingSource->ResetBindings(false);
                roomsBindingSource->ResetBindings(false);
                clientsBindingSource->ResetBindings(false);

                // Обновляем DataGridView
                bookingsGrid->Refresh();
                roomsGrid->Refresh();
                clientsGrid->Refresh();

                String^ message = String::Format("Импорт завершен!\nФормат: {0}\nУспешно импортировано: {1}\nОшибок: {2}",
                    isExtendedFormat ? "расширенный" : "стандартный",
                    imported, errors);
                MessageBox::Show(message, "Результат импорта",
                    MessageBoxButtons::OK, MessageBoxIcon::Information);

            }
            catch (Exception^ ex) {
                MessageBox::Show("Ошибка импорта: " + ex->Message, "Ошибка",
                    MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        // Метод для поиска или создания клиента с паспортом и email
        Client^ FindOrCreateClientExtended(String^ name, String^ phone, String^ passport, String^ email) {
            // Ищем существующего клиента по телефону
            for each(Client ^ c in hotel->GetClients()) {
                if (c->Phone == phone) {
                    // Обновляем данные, если они пустые
                    if (String::IsNullOrWhiteSpace(c->PassportNumber) && !String::IsNullOrWhiteSpace(passport)) {
                        c->PassportNumber = passport;
                    }
                    if (String::IsNullOrWhiteSpace(c->Email) && !String::IsNullOrWhiteSpace(email)) {
                        c->Email = email;
                    }
                    return c;
                }
            }

            // Ищем по паспорту
            if (!String::IsNullOrWhiteSpace(passport)) {
                for each(Client ^ c in hotel->GetClients()) {
                    if (c->PassportNumber == passport) {
                        // Обновляем телефон и email если нужно
                        if (String::IsNullOrWhiteSpace(c->Phone) && !String::IsNullOrWhiteSpace(phone)) {
                            c->Phone = phone;
                        }
                        if (String::IsNullOrWhiteSpace(c->Email) && !String::IsNullOrWhiteSpace(email)) {
                            c->Email = email;
                        }
                        return c;
                    }
                }
            }

            // Если клиент не найден, создаем нового
            Client^ newClient = gcnew Client(name, phone, passport, email);
            if (hotel->AddClient(newClient)) {
                return newClient;
            }
            return nullptr;
        }

        // Метод для поиска или создания клиента (без паспорта и email)
        Client^ FindOrCreateClient(String^ name, String^ phone) {
            // Ищем существующего клиента
            for each(Client ^ c in hotel->GetClients()) {
                if (c->Phone == phone) {
                    return c;
                }
            }

            // Если клиент не найден, создаем нового с пустыми паспортом и email
            Client^ newClient = gcnew Client(name, phone, "", "");
            if (hotel->AddClient(newClient)) {
                return newClient;
            }
            return nullptr;
        }

        Room^ FindRoomByNumber(int roomNumber) {
            for each(Room ^ r in hotel->GetRooms()) {
                if (r->RoomNumber == roomNumber) {
                    return r;
                }
            }
            return nullptr;
        }
    };
}