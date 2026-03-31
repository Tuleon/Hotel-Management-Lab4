#pragma once
#include "Client.h"
#include "Room.h"

using namespace System;

ref class Booking {
public:
    property Client^ ClientData;
    property Room^ RoomData;
    property DateTime CheckInDate;
    property DateTime CheckOutDate;
    property int GuestsCount;
    property double TotalPrice;
    property String^ Notes;

    Booking(Client^ client, Room^ room, DateTime checkIn, DateTime checkOut, int guests) {
        ClientData = client;
        RoomData = room;
        CheckInDate = checkIn;
        CheckOutDate = checkOut;
        GuestsCount = guests;
        Notes = "";
        CalculateTotalPrice();
    }

    void CalculateTotalPrice() {
        int days = (CheckOutDate - CheckInDate).Days;
        TotalPrice = days * RoomData->PricePerDay;
    }

    // Для отображения в DataGridView
    property String^ ClientName {
        String^ get() {
            if (ClientData == nullptr) return "";
            return ClientData->Name;
        }
    }

    property String^ ClientPhone {
        String^ get() {
            if (ClientData == nullptr) return "";
            return ClientData->Phone;
        }
    }

    property int RoomNumber {
        int get() {
            if (RoomData == nullptr) return 0;
            return RoomData->RoomNumber;
        }
    }

    property String^ RoomTypeString {
        String^ get() {
            if (RoomData == nullptr) return "";
            return RoomData->TypeString;
        }
    }

    property String^ CheckInDateString {
        String^ get() {
            return CheckInDate.ToString("dd.MM.yyyy");
        }
    }

    property String^ CheckOutDateString {
        String^ get() {
            return CheckOutDate.ToString("dd.MM.yyyy");
        }
    }

    property int StayDuration {
        int get() {
            return (CheckOutDate - CheckInDate).Days;
        }
    }
};