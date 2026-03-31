#pragma once

using namespace System;

public ref class Room {
public:
    String^ name;
    double price;
    double discount;

    Room(String^ n, double p, double d) {
        name = n;
        price = p;
        discount = d;
    }

    double getPrice() {
        return price * (1 - discount / 100);
    }
};