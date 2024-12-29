#pragma once

#include <cliext/list>

namespace TrainMS {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::Data::SqlClient;

    public ref class EditRoutes : public System::Windows::Forms::Form
    {
    public:
        EditRoutes(void)
        {
            InitializeComponent();
            LoadStations(); // Load stations for adding new route details
            LoadRouteDetails(); // Load all route details (station, time, stop order)
        }

    protected:
        ~EditRoutes()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::ComponentModel::Container^ components;
        System::Windows::Forms::TextBox^ routeNameTextBox;
        System::Windows::Forms::ComboBox^ stationComboBox;
        System::Windows::Forms::DateTimePicker^ arrivalDatePicker;
        System::Windows::Forms::DateTimePicker^ departureDatePicker;
        System::Windows::Forms::TextBox^ stopOrderTextBox;
        System::Windows::Forms::Button^ deleteButton;
        System::Windows::Forms::Button^ addButton;
        System::Windows::Forms::DataGridView^ routeDetailsDataGridView;
        SqlConnection^ conn;

        System::Collections::Generic::List<int>^ routeIDs = gcnew System::Collections::Generic::List<int>();


        void InitializeComponent(void)
        {
            this->routeNameTextBox = (gcnew System::Windows::Forms::TextBox());
            this->stationComboBox = (gcnew System::Windows::Forms::ComboBox());
            this->arrivalDatePicker = (gcnew System::Windows::Forms::DateTimePicker());
            this->departureDatePicker = (gcnew System::Windows::Forms::DateTimePicker());
            this->stopOrderTextBox = (gcnew System::Windows::Forms::TextBox());
            this->deleteButton = (gcnew System::Windows::Forms::Button());
            this->addButton = (gcnew System::Windows::Forms::Button());
            this->routeDetailsDataGridView = (gcnew System::Windows::Forms::DataGridView());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->routeDetailsDataGridView))->BeginInit();
            this->SuspendLayout();
            // 
            // routeNameTextBox
            // 
            this->routeNameTextBox->Location = System::Drawing::Point(30, 30);
            this->routeNameTextBox->Name = L"routeNameTextBox";
            this->routeNameTextBox->Size = System::Drawing::Size(200, 22);
            this->routeNameTextBox->TabIndex = 0;
            // 
            // stationComboBox
            // 
            this->stationComboBox->FormattingEnabled = true;
            this->stationComboBox->Location = System::Drawing::Point(30, 80);
            this->stationComboBox->Name = L"stationComboBox";
            this->stationComboBox->Size = System::Drawing::Size(200, 24);
            this->stationComboBox->TabIndex = 1;
            // 
            // arrivalDatePicker
            // 
            this->arrivalDatePicker->CustomFormat = L"yyyy-MM-dd HH:mm";
            this->arrivalDatePicker->Format = System::Windows::Forms::DateTimePickerFormat::Custom;
            this->arrivalDatePicker->Location = System::Drawing::Point(30, 130);
            this->arrivalDatePicker->Name = L"arrivalDatePicker";
            this->arrivalDatePicker->Size = System::Drawing::Size(250, 22);
            this->arrivalDatePicker->TabIndex = 2;
            // 
            // departureDatePicker
            // 
            this->departureDatePicker->CustomFormat = L"yyyy-MM-dd HH:mm";
            this->departureDatePicker->Format = System::Windows::Forms::DateTimePickerFormat::Custom;
            this->departureDatePicker->Location = System::Drawing::Point(30, 180);
            this->departureDatePicker->Name = L"departureDatePicker";
            this->departureDatePicker->Size = System::Drawing::Size(250, 22);
            this->departureDatePicker->TabIndex = 3;
            // 
            // stopOrderTextBox
            // 
            this->stopOrderTextBox->Location = System::Drawing::Point(30, 230);
            this->stopOrderTextBox->Name = L"stopOrderTextBox";
            this->stopOrderTextBox->Size = System::Drawing::Size(100, 22);
            this->stopOrderTextBox->TabIndex = 4;
            // 
            // deleteButton
            // 
            this->deleteButton->Location = System::Drawing::Point(30, 280);
            this->deleteButton->Name = L"deleteButton";
            this->deleteButton->Size = System::Drawing::Size(100, 30);
            this->deleteButton->TabIndex = 5;
            this->deleteButton->Text = L"Delete Route Detail";
            this->deleteButton->Click += gcnew System::EventHandler(this, &EditRoutes::DeleteRouteDetailButton_Click);
            // 
            // addButton
            // 
            this->addButton->Location = System::Drawing::Point(150, 280);
            this->addButton->Name = L"addButton";
            this->addButton->Size = System::Drawing::Size(100, 30);
            this->addButton->TabIndex = 6;
            this->addButton->Text = L"Add Route Detail";
            this->addButton->Click += gcnew System::EventHandler(this, &EditRoutes::AddRouteDetailButton_Click);
            // 
            // routeDetailsDataGridView
            // 
            this->routeDetailsDataGridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->routeDetailsDataGridView->Location = System::Drawing::Point(300, 30);
            this->routeDetailsDataGridView->Name = L"routeDetailsDataGridView";
            this->routeDetailsDataGridView->RowHeadersWidth = 51;
            this->routeDetailsDataGridView->Size = System::Drawing::Size(672, 280);
            this->routeDetailsDataGridView->TabIndex = 7;
            // 
            // EditRoutes
            // 
            this->ClientSize = System::Drawing::Size(1020, 350);
            this->Controls->Add(this->routeDetailsDataGridView);
            this->Controls->Add(this->routeNameTextBox);
            this->Controls->Add(this->stationComboBox);
            this->Controls->Add(this->arrivalDatePicker);
            this->Controls->Add(this->departureDatePicker);
            this->Controls->Add(this->stopOrderTextBox);
            this->Controls->Add(this->deleteButton);
            this->Controls->Add(this->addButton);
            this->Name = L"EditRoutes";
            this->Text = L"Edit Route Details";
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->routeDetailsDataGridView))->EndInit();
            this->ResumeLayout(false);
            this->PerformLayout();

        }

        void LoadStations()
        {
            conn = gcnew SqlConnection("Server=DESKTOP-NEII4G1;Database=TrainManagementSystem;Trusted_Connection=True;");
            SqlDataAdapter^ adapter = gcnew SqlDataAdapter("SELECT StationID, StationName FROM Stations", conn);
            DataTable^ stationsTable = gcnew DataTable();
            adapter->Fill(stationsTable);

            stationComboBox->DataSource = stationsTable;
            stationComboBox->DisplayMember = "StationName";
            stationComboBox->ValueMember = "StationID";
        }

        void LoadRouteDetails()
        {
            conn = gcnew SqlConnection("Server=DESKTOP-NEII4G1;Database=TrainManagementSystem;Trusted_Connection=True;");
            String^ query = "SELECT RD.RouteDetailID, R.RouteName, S.StationName, RD.ArrivalTime, RD.DepartureTime, RD.StopOrder "
                "FROM RouteDetails RD "
                "JOIN Routes R ON RD.RouteID = R.RouteID "
                "JOIN Stations S ON RD.StationID = S.StationID "
                "ORDER BY R.RouteName, RD.StopOrder";

            SqlDataAdapter^ adapter = gcnew SqlDataAdapter(query, conn);
            DataTable^ routeDetailsTable = gcnew DataTable();
            adapter->Fill(routeDetailsTable);

            routeDetailsDataGridView->DataSource = routeDetailsTable;

            // Customize the columns
            routeDetailsDataGridView->Columns["RouteDetailID"]->Visible = false; // Hide the RouteDetailID column
            routeDetailsDataGridView->Columns["RouteName"]->HeaderText = "Route Name";
            routeDetailsDataGridView->Columns["StationName"]->HeaderText = "Station";
            routeDetailsDataGridView->Columns["ArrivalTime"]->HeaderText = "Arrival Time";
            routeDetailsDataGridView->Columns["DepartureTime"]->HeaderText = "Departure Time";
            routeDetailsDataGridView->Columns["StopOrder"]->HeaderText = "Stop Order";

            // Set specific column widths
            routeDetailsDataGridView->Columns["RouteName"]->Width = 120;  // Route Name
            routeDetailsDataGridView->Columns["StationName"]->Width = 150;  // Station Name
            routeDetailsDataGridView->Columns["ArrivalTime"]->Width = 130;  // Arrival Time
            routeDetailsDataGridView->Columns["DepartureTime"]->Width = 130;  // Departure Time
            routeDetailsDataGridView->Columns["StopOrder"]->Width = 90;  // Stop Order
        }

        void AddRouteDetailButton_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (String::IsNullOrEmpty(routeNameTextBox->Text) || String::IsNullOrEmpty(stopOrderTextBox->Text) || stationComboBox->SelectedIndex == -1)
            {
                MessageBox::Show("Please provide all details.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            try
            {
                int stopOrder = Convert::ToInt32(stopOrderTextBox->Text);
                int stationID = Convert::ToInt32(stationComboBox->SelectedValue);
                String^ routeName = routeNameTextBox->Text;
                DateTime arrivalTime = arrivalDatePicker->Value;
                DateTime departureTime = departureDatePicker->Value;

                conn->Open();
                String^ query = "INSERT INTO RouteDetails (RouteID, StationID, ArrivalTime, DepartureTime, StopOrder) "
                               "VALUES ((SELECT RouteID FROM Routes WHERE RouteName = @RouteName), @StationID, @ArrivalTime, @DepartureTime, @StopOrder)";
                SqlCommand^ cmd = gcnew SqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@RouteName", routeName);
                cmd->Parameters->AddWithValue("@StationID", stationID);
                cmd->Parameters->AddWithValue("@ArrivalTime", arrivalTime);
                cmd->Parameters->AddWithValue("@DepartureTime", departureTime);
                cmd->Parameters->AddWithValue("@StopOrder", stopOrder);
                cmd->ExecuteNonQuery();

                MessageBox::Show("Route detail added successfully.", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
                LoadRouteDetails();
            }
            catch (Exception^ ex)
            {
                MessageBox::Show("Error: " + ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
            finally
            {
                conn->Close();
            }
        }

        void DeleteRouteDetailButton_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (routeDetailsDataGridView->SelectedRows->Count == 0)
            {
                MessageBox::Show("Please select a route detail to delete.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            try
            {
                int routeDetailID = Convert::ToInt32(routeDetailsDataGridView->SelectedRows[0]->Cells["RouteDetailID"]->Value);
                conn->Open();
                String^ query = "DELETE FROM RouteDetails WHERE RouteDetailID = @RouteDetailID";
                SqlCommand^ cmd = gcnew SqlCommand(query, conn);
                cmd->Parameters->AddWithValue("@RouteDetailID", routeDetailID);
                cmd->ExecuteNonQuery();

                MessageBox::Show("Route detail deleted successfully.", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
                LoadRouteDetails();
            }
            catch (Exception^ ex)
            {
                MessageBox::Show("Error: " + ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
            finally
            {
                conn->Close();
            }
        }
    };
}