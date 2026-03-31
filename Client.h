#pragma once
using namespace System;

ref class Client {
public:
    property String^ Name;
    property String^ Phone;
    property String^ PassportNumber;
    property String^ Email;

    Client(String^ name, String^ phone, String^ passport, String^ email) {
        Name = name;
        Phone = phone;
        PassportNumber = passport;
        Email = email;
    }

    Client(String^ name, String^ phone) {
        Name = name;
        Phone = phone;
        PassportNumber = "";
        Email = "";
    }

    property String^ FullInfo {
        String^ get() {
            return Name + " (" + Phone + ")";
        }
    }
};