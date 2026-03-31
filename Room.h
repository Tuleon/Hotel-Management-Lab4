#pragma once
using namespace System;

public enum class RoomType {
    Standard,
    Comfort,
    Luxury,
    Suite
};

public enum class RoomStatus {
    Available,
    Occupied,
    Reserved,
    Maintenance
};

ref class Room {
public:
    property int RoomNumber;
    property RoomType Type;
    property RoomStatus Status;
    property double PricePerDay;
    property int Capacity;      // Вместимость (количество гостей)
    property String^ Description;

    Room(int number, RoomType type, double price, int capacity) {
        RoomNumber = number;
        Type = type;
        PricePerDay = price;
        Capacity = capacity;
        Status = RoomStatus::Available;
        Description = "";
    }

    // Для отображения в DataGridView
    property String^ TypeString {
        String^ get() {
            switch (Type) {
            case RoomType::Standard: return "Стандарт";
            case RoomType::Comfort: return "Комфорт";
            case RoomType::Luxury: return "Люкс";
            case RoomType::Suite: return "Апартаменты";
            default: return "Неизвестно";
            }
        }
    }

    property String^ StatusString {
        String^ get() {
            switch (Status) {
            case RoomStatus::Available: return "Свободен";
            case RoomStatus::Occupied: return "Занят";
            case RoomStatus::Reserved: return "Забронирован";
            case RoomStatus::Maintenance: return "На ремонте";
            default: return "Неизвестно";
            }
        }
    }
};