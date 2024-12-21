#pragma once
#include "DatabaseHelper.h"

namespace TrainMS {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::Data::SqlClient;

    public ref class EditStations : public System::Windows::Forms::Form
    {
    public:
        EditStations(void)
        {
            InitializeComponent();
        }

    protected:
        ~EditStations()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::Windows::Forms::DataGridView^ dataGridViewStations;
        System::Windows::Forms::TextBox^ txtStationName;
        System::Windows::Forms::TextBox^ txtLocation;
        System::Windows::Forms::Button^ btnAdd;
        System::Windows::Forms::Button^ btnRemove;
        System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
        void InitializeComponent(void) {
            this->dataGridViewStations = (gcnew System::Windows::Forms::DataGridView());
            this->txtStationName = (gcnew System::Windows::Forms::TextBox());
            this->txtLocation = (gcnew System::Windows::Forms::TextBox());
            this->btnAdd = (gcnew System::Windows::Forms::Button());
            this->btnRemove = (gcnew System::Windows::Forms::Button());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridViewStations))->BeginInit();
            this->SuspendLayout();
            // 
            // dataGridViewStations
            // 
            this->dataGridViewStations->ColumnHeadersHeight = 29;
            this->dataGridViewStations->Location = System::Drawing::Point(12, 12);
            this->dataGridViewStations->MultiSelect = false;
            this->dataGridViewStations->Name = L"dataGridViewStations";
            this->dataGridViewStations->RowHeadersWidth = 51;
            this->dataGridViewStations->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
            this->dataGridViewStations->Size = System::Drawing::Size(446, 400);
            this->dataGridViewStations->TabIndex = 0;
            // 
            // txtStationName
            // 
            this->txtStationName->Location = System::Drawing::Point(495, 54);
            this->txtStationName->Name = L"txtStationName";
            this->txtStationName->Size = System::Drawing::Size(200, 22);
            this->txtStationName->TabIndex = 1;
            // 
            // txtLocation
            // 
            this->txtLocation->Location = System::Drawing::Point(495, 108);
            this->txtLocation->Name = L"txtLocation";
            this->txtLocation->Size = System::Drawing::Size(200, 22);
            this->txtLocation->TabIndex = 2;
            // 
            // btnAdd
            // 
            this->btnAdd->Location = System::Drawing::Point(539, 167);
            this->btnAdd->Name = L"btnAdd";
            this->btnAdd->Size = System::Drawing::Size(100, 30);
            this->btnAdd->TabIndex = 3;
            this->btnAdd->Text = L"Add";
            this->btnAdd->Click += gcnew System::EventHandler(this, &EditStations::AddStation);
            // 
            // btnRemove
            // 
            this->btnRemove->Location = System::Drawing::Point(539, 230);
            this->btnRemove->Name = L"btnRemove";
            this->btnRemove->Size = System::Drawing::Size(100, 30);
            this->btnRemove->TabIndex = 4;
            this->btnRemove->Text = L"Remove";
            this->btnRemove->Click += gcnew System::EventHandler(this, &EditStations::RemoveStation);
            // 
            // EditStations
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(900, 450);
            this->Controls->Add(this->dataGridViewStations);
            this->Controls->Add(this->txtStationName);
            this->Controls->Add(this->txtLocation);
            this->Controls->Add(this->btnAdd);
            this->Controls->Add(this->btnRemove);
            this->Name = L"EditStations";
            this->Text = L"Edit Stations";
            this->Load += gcnew System::EventHandler(this, &EditStations::EditStations_Load);
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridViewStations))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion

    private:
        void LoadStations() {
            SqlConnection^ conn = DatabaseHelper::GetConnection();
            try {
                conn->Open();
                SqlDataAdapter^ adapter = gcnew SqlDataAdapter("SELECT * FROM Stations ORDER BY StationName", conn);
                DataTable^ dt = gcnew DataTable();
                adapter->Fill(dt);
                dataGridViewStations->DataSource = dt;
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error loading stations: " + ex->Message);
            }
            finally {
                conn->Close();
            }
        }

        void AddStation(System::Object^ sender, System::EventArgs^ e) {
            String^ stationName = txtStationName->Text;
            String^ location = txtLocation->Text;

            if (String::IsNullOrWhiteSpace(stationName) || String::IsNullOrWhiteSpace(location)) {
                MessageBox::Show("Both Station Name and Location are required.");
                return;
            }

            SqlConnection^ conn = DatabaseHelper::GetConnection();
            try {
                conn->Open();

                // Check if the station already exists
                SqlCommand^ checkCmd = gcnew SqlCommand("SELECT COUNT(*) FROM Stations WHERE StationName = @StationName", conn);
                checkCmd->Parameters->AddWithValue("@StationName", stationName);
                int count = Convert::ToInt32(checkCmd->ExecuteScalar());

                if (count > 0) {
                    MessageBox::Show("Station with this name already exists.");
                    return;
                }

                // If not exists, insert the new station
                SqlCommand^ cmd = gcnew SqlCommand("INSERT INTO Stations (StationName, Location) VALUES (@StationName, @Location)", conn);
                cmd->Parameters->AddWithValue("@StationName", stationName);
                cmd->Parameters->AddWithValue("@Location", location);
                cmd->ExecuteNonQuery();

                LoadStations();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error adding station: " + ex->Message);
            }
            finally {
                conn->Close();
            }
        }


        void RemoveStation(System::Object^ sender, System::EventArgs^ e) {
            if (dataGridViewStations->SelectedRows->Count == 0) {
                MessageBox::Show("Please select a station to remove.");
                return;
            }

            int stationID = Convert::ToInt32(dataGridViewStations->SelectedRows[0]->Cells["StationID"]->Value);
            SqlConnection^ conn = DatabaseHelper::GetConnection();
            try {this->dataGridViewStations->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;

                conn->Open();
                SqlCommand^ cmd = gcnew SqlCommand("DELETE FROM Stations WHERE StationID = @StationID", conn);
                cmd->Parameters->AddWithValue("@StationID", stationID);
                cmd->ExecuteNonQuery();
                LoadStations();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Error removing station: " + ex->Message);
            }
            finally {
                conn->Close();
            }
        }

        void EditStations_Load(System::Object^ sender, System::EventArgs^ e) {
            LoadStations();
        }
    };
}
