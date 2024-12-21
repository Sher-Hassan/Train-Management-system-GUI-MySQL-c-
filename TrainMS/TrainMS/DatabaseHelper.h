#pragma once
#pragma once

using namespace System;
using namespace System::Data;
using namespace System::Data::SqlClient;

ref class DatabaseHelper {
public:
    static SqlConnection^ GetConnection() {
        String^ connectionString = "Server=DESKTOP-NEII4G1;Database=TrainManagementSystem;Trusted_Connection=True;";
        return gcnew SqlConnection(connectionString);
    }
};
