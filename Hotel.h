#pragma once
#include "Room.h"

using namespace System;
using namespace System::Collections::Generic;

public ref class Hotel {
public:
    static int CompareRoomsByPrice(Room^ a, Room^ b) {
        return a->getPrice().CompareTo(b->getPrice());
    }
    List<Room^>^ rooms;

    Hotel() {
        rooms = gcnew List<Room^>();
    }

    void addRoom(Room^ r) {
        rooms->Add(r);
    }

    void removeRoom(int i) {
        if (i >= 0 && i < rooms->Count)
            rooms->RemoveAt(i);
    }

    double average() {
        if (rooms->Count == 0) return 0;

        double sum = 0;
        for each (Room ^ r in rooms)
            sum += r->getPrice();

        return sum / rooms->Count;
    }

    void sortByPrice() {
        rooms->Sort(gcnew Comparison<Room^>(&Hotel::CompareRoomsByPrice));
    }
};