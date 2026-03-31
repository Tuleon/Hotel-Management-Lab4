#pragma once
#include "Client.h"
#include "Room.h"
#include "Booking.h"
using namespace System::Collections::Generic;
using namespace System::ComponentModel;

ref class Hotel {
private:
    BindingList<Client^>^ clients;
    BindingList<Room^>^ rooms;
    BindingList<Booking^>^ bookings;

public:
    Hotel() {
        clients = gcnew BindingList<Client^>();
        rooms = gcnew BindingList<Room^>();
        bookings = gcnew BindingList<Booking^>();

        // Добавляем тестовые номера
        InitializeTestRooms();
        InitializeTestClients(); // Добавляем тестовых клиентов
    }

    void InitializeTestRooms() {
        rooms->Add(gcnew Room(101, RoomType::Standard, 2500, 2));
        rooms->Add(gcnew Room(102, RoomType::Standard, 2500, 2));
        rooms->Add(gcnew Room(103, RoomType::Standard, 2500, 2));
        rooms->Add(gcnew Room(201, RoomType::Comfort, 3500, 2));
        rooms->Add(gcnew Room(202, RoomType::Comfort, 3500, 3));
        rooms->Add(gcnew Room(301, RoomType::Luxury, 5000, 3));
        rooms->Add(gcnew Room(302, RoomType::Luxury, 5000, 4));
        rooms->Add(gcnew Room(401, RoomType::Suite, 8000, 4));
        rooms->Add(gcnew Room(402, RoomType::Suite, 8000, 5));
    }

    void InitializeTestClients() {
        clients->Add(gcnew Client("Иван Петров", "+79991234567", "1234 567890", "ivan@mail.ru"));
        clients->Add(gcnew Client("Мария Сидорова", "+79992345678", "2345 678901", "maria@mail.ru"));
        clients->Add(gcnew Client("Алексей Смирнов", "+79993456789", "3456 789012", "alex@mail.ru"));
    }

    // Добавление клиента с проверкой на дубликат
    bool AddClient(Client^ client) {
        // Проверяем, существует ли клиент с таким же номером телефона или паспортом
        for each (Client ^ c in clients) {
            // Проверка по телефону (основной идентификатор)
            if (c->Phone == client->Phone) {
                return false; // Клиент с таким телефоном уже существует
            }
            // Проверка по паспорту (если паспорт указан)
            if (!String::IsNullOrWhiteSpace(client->PassportNumber) &&
                !String::IsNullOrWhiteSpace(c->PassportNumber) &&
                c->PassportNumber == client->PassportNumber) {
                return false; // Клиент с таким паспортом уже существует
            }
        }

        clients->Add(client);
        return true;
    }

    void AddRoom(Room^ room) {
        // Проверка номера комнаты
        if (room->RoomNumber < 101 || room->RoomNumber > 599) {
            throw gcnew Exception("Номер комнаты должен быть в диапазоне от 101 до 599!");
        }
        // Проверка цены
        if (room->PricePerDay > 100000) {
            throw gcnew Exception("Цена номера не может превышать 100 000 рублей!");
        }
        if (room->PricePerDay < 500) {
            throw gcnew Exception("Цена номера должна быть больше 500!");
        }
        rooms->Add(room);
    }

    bool AddBooking(Booking^ booking) {
        // Проверяем доступность номера на указанные даты
        if (IsRoomAvailable(booking->RoomData->RoomNumber, booking->CheckInDate, booking->CheckOutDate)) {
            bookings->Add(booking);
            booking->RoomData->Status = RoomStatus::Reserved;
            return true;
        }
        return false;
    }

    bool IsRoomAvailable(int roomNumber, DateTime checkIn, DateTime checkOut) {
        for each (Booking ^ b in bookings) {
            if (b->RoomData->RoomNumber == roomNumber) {
                // Проверяем пересечение дат
                if (!(checkOut <= b->CheckInDate || checkIn >= b->CheckOutDate)) {
                    return false; // Даты пересекаются
                }
            }
        }
        return true;
    }

    array<Room^>^ GetAvailableRooms(DateTime checkIn, DateTime checkOut, int guests) {
        List<Room^>^ available = gcnew List<Room^>();

        for each (Room ^ room in rooms) {
            if (room->Capacity >= guests &&
                room->Status != RoomStatus::Maintenance &&
                IsRoomAvailable(room->RoomNumber, checkIn, checkOut)) {
                available->Add(room);
            }
        }

        return available->ToArray();
    }

    void CheckIn(int bookingId) {
        if (bookingId >= 0 && bookingId < bookings->Count) {
            Booking^ booking = bookings[bookingId];
            booking->RoomData->Status = RoomStatus::Occupied;
        }
    }

    void CheckOut(int bookingId) {
        if (bookingId >= 0 && bookingId < bookings->Count) {
            Booking^ booking = bookings[bookingId];
            booking->RoomData->Status = RoomStatus::Available;
            bookings->RemoveAt(bookingId);
        }
    }

    void RemoveClient(Client^ client) {
        // Удаляем все бронирования клиента
        for (int i = bookings->Count - 1; i >= 0; i--) {
            if (bookings[i]->ClientData == client) {
                bookings[i]->RoomData->Status = RoomStatus::Available;
                bookings->RemoveAt(i);
            }
        }
        clients->Remove(client);
    }

    void RemoveRoom(Room^ room) {
        rooms->Remove(room);
    }

    void RemoveBooking(Booking^ booking) {
        booking->RoomData->Status = RoomStatus::Available;
        bookings->Remove(booking);
    }

    BindingList<Client^>^ GetClients() { return clients; }
    BindingList<Room^>^ GetRooms() { return rooms; }
    BindingList<Booking^>^ GetBookings() { return bookings; }

    // Получить список доступных номеров для выбора
    BindingList<Room^>^ GetAvailableRoomsList() {
        BindingList<Room^>^ available = gcnew BindingList<Room^>();
        for each (Room ^ room in rooms) {
            if (room->Status == RoomStatus::Available) {
                available->Add(room);
            }
        }
        return available;
    }

    // Проверка существования клиента по телефону
    bool IsClientExists(String^ phone) {
        for each (Client ^ c in clients) {
            if (c->Phone == phone) {
                return true;
            }
        }
        return false;
    }

    // Поиск клиента по телефону
    Client^ FindClientByPhone(String^ phone) {
        for each (Client ^ c in clients) {
            if (c->Phone == phone) {
                return c;
            }
        }
        return nullptr;
    }
};