#pragma once

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
        System::Windows::Forms::DataGridView^ routeDetailsDataGridView; // DataGridView for displaying route details
        SqlConnection^ conn;

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

            // Adjust columns to fit content
            routeDetailsDataGridView->AutoResizeColumns();
        }

        void AddRouteDetailButton_Click(System::Object^ sender, System::EventArgs^ e)
        {
            String^ routeName = routeNameTextBox->Text;
            String^ stationID = stationComboBox->SelectedValue->ToString();
            String^ arrivalTime = arrivalDatePicker->Value.ToString("yyyy-MM-dd HH:mm");
            String^ departureTime = departureDatePicker->Value.ToString("yyyy-MM-dd HH:mm");
            String^ stopOrder = stopOrderTextBox->Text;

            // Check if any field is empty
            if (routeName->Trim()->Length == 0 || stationID->Trim()->Length == 0 || stopOrder->Trim()->Length == 0)
            {
                MessageBox::Show("All fields must be filled. Please provide values for Route Name, Station, and Stop Order.", "Violation: Empty Fields", MessageBoxButtons::OK, MessageBoxIcon::Error);
                return;
            }

            conn = gcnew SqlConnection("Server=DESKTOP-NEII4G1;Database=TrainManagementSystem;Trusted_Connection=True;");

            // Query to check if the RouteName exists
            String^ checkRouteQuery = "SELECT RouteID FROM Routes WHERE RouteName = @RouteName";
            SqlCommand^ checkRouteCommand = gcnew SqlCommand(checkRouteQuery, conn);
            checkRouteCommand->Parameters->AddWithValue("@RouteName", routeName);

            conn->Open();
            SqlDataReader^ reader = checkRouteCommand->ExecuteReader();

            int routeID = -1;

            if (reader->HasRows) // If the RouteName exists
            {
                reader->Read();
                routeID = reader->GetInt32(0); // Get the existing RouteID
            }
            else
            {
                // If RouteName doesn't exist, insert a new route
                reader->Close(); // Close reader to execute another query

                String^ insertRouteQuery = "INSERT INTO Routes (RouteName) VALUES (@RouteName); SELECT SCOPE_IDENTITY();";
                SqlCommand^ insertRouteCommand = gcnew SqlCommand(insertRouteQuery, conn);
                insertRouteCommand->Parameters->AddWithValue("@RouteName", routeName);

                routeID = Convert::ToInt32(insertRouteCommand->ExecuteScalar()); // Get the newly inserted RouteID
            }

            // Close reader after finishing
            reader->Close();

            // Validation 1: Same named routes cannot have the same named station
            String^ checkStationQuery = "SELECT COUNT(*) FROM RouteDetails WHERE RouteID = @RouteID AND StationID = @StationID";
            SqlCommand^ checkStationCommand = gcnew SqlCommand(checkStationQuery, conn);
            checkStationCommand->Parameters->AddWithValue("@RouteID", routeID);
            checkStationCommand->Parameters->AddWithValue("@StationID", stationID);
            int stationExists = Convert::ToInt32(checkStationCommand->ExecuteScalar());

            if (stationExists > 0)
            {
                MessageBox::Show("This station already exists for the same route. Please select a different station.", "Violation: Same Station", MessageBoxButtons::OK, MessageBoxIcon::Error);
                conn->Close();
                return; // Exit method if station is duplicated
            }

            // Validation 2: Arrival time cannot be ahead of departure time
            DateTime arrival = arrivalDatePicker->Value;
            DateTime departure = departureDatePicker->Value;

            if (arrival >= departure)
            {
                MessageBox::Show("Arrival time cannot be ahead of or the same as the departure time.", "Violation: Arrival Time", MessageBoxButtons::OK, MessageBoxIcon::Error);
                conn->Close();
                return; // Exit method if arrival time is invalid
            }

            // Validation 3: Arrival and Departure time cannot be the same for the same entry
            if (arrival == departure)
            {
                MessageBox::Show("Arrival and Departure times cannot be the same. Please enter different times.", "Violation: Same Time", MessageBoxButtons::OK, MessageBoxIcon::Error);
                conn->Close();
                return; // Exit method if arrival and departure times are the same
            }

            // Validation 4: Check for time overlap for the same RouteName
            String^ checkTimeOverlapQuery = "SELECT COUNT(*) FROM RouteDetails RD "
                "INNER JOIN Routes R ON RD.RouteID = R.RouteID "
                "WHERE R.RouteName = @RouteName AND "
                "( (RD.ArrivalTime <= @ArrivalTime AND RD.DepartureTime >= @ArrivalTime) OR "
                "(RD.ArrivalTime <= @DepartureTime AND RD.DepartureTime >= @DepartureTime) )";
            SqlCommand^ checkTimeOverlapCommand = gcnew SqlCommand(checkTimeOverlapQuery, conn);
            checkTimeOverlapCommand->Parameters->AddWithValue("@RouteName", routeName);
            checkTimeOverlapCommand->Parameters->AddWithValue("@ArrivalTime", arrivalTime);
            checkTimeOverlapCommand->Parameters->AddWithValue("@DepartureTime", departureTime);

            int timeOverlapExists = Convert::ToInt32(checkTimeOverlapCommand->ExecuteScalar());

            if (timeOverlapExists > 0)
            {
                MessageBox::Show("The timings you entered overlap with an existing train schedule for the same route. Please adjust the timings.", "Violation: Time Overlap", MessageBoxButtons::OK, MessageBoxIcon::Error);
                conn->Close();
                return; // Exit method if there is a time overlap
            }

            // Proceed with adding the route detail
            String^ insertDetailQuery = "INSERT INTO RouteDetails (RouteID, StationID, ArrivalTime, DepartureTime, StopOrder) "
                "VALUES (@RouteID, @StationID, @ArrivalTime, @DepartureTime, @StopOrder)";

            SqlCommand^ insertDetailCommand = gcnew SqlCommand(insertDetailQuery, conn);
            insertDetailCommand->Parameters->AddWithValue("@RouteID", routeID);
            insertDetailCommand->Parameters->AddWithValue("@StationID", stationID);
            insertDetailCommand->Parameters->AddWithValue("@ArrivalTime", arrivalTime);
            insertDetailCommand->Parameters->AddWithValue("@DepartureTime", departureTime);
            insertDetailCommand->Parameters->AddWithValue("@StopOrder", stopOrder);

            try
            {
                insertDetailCommand->ExecuteNonQuery();
                MessageBox::Show("Route detail added successfully.", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
            catch (SqlException^ ex)
            {
                if (ex->Number == 2627) // 2627 is the error code for UNIQUE constraint violation in SQL Server
                {
                    MessageBox::Show("This route-station combination already exists. Please check the route and station details.");
                }
                else
                {
                    // Handle other SQL exceptions if needed
                    MessageBox::Show("An error occurred: " + ex->Message);
                }
            }

            conn->Close();
            LoadRouteDetails(); // Reload route details after adding a new entry
        }






        void DeleteRouteDetailButton_Click(System::Object^ sender, System::EventArgs^ e)
        {
            if (routeDetailsDataGridView->SelectedRows->Count > 0)
            {
                int selectedRowIndex = routeDetailsDataGridView->SelectedRows[0]->Index;
                int routeDetailID = Convert::ToInt32(routeDetailsDataGridView->Rows[selectedRowIndex]->Cells["RouteDetailID"]->Value);

                conn = gcnew SqlConnection("Server=DESKTOP-NEII4G1;Database=TrainManagementSystem;Trusted_Connection=True;");
                conn->Open();

                // Get the RouteID for the selected RouteDetail
                String^ getRouteQuery = "SELECT RouteID FROM RouteDetails WHERE RouteDetailID = @RouteDetailID";
                SqlCommand^ getRouteCommand = gcnew SqlCommand(getRouteQuery, conn);
                getRouteCommand->Parameters->AddWithValue("@RouteDetailID", routeDetailID);
                SqlDataReader^ reader = getRouteCommand->ExecuteReader();

                int routeID = -1;

                if (reader->HasRows)
                {
                    reader->Read();
                    routeID = reader->GetInt32(0); // Get the RouteID
                }

                reader->Close();

                // Delete the selected RouteDetail
                String^ deleteRouteDetailQuery = "DELETE FROM RouteDetails WHERE RouteDetailID = @RouteDetailID";
                SqlCommand^ deleteRouteDetailCommand = gcnew SqlCommand(deleteRouteDetailQuery, conn);
                deleteRouteDetailCommand->Parameters->AddWithValue("@RouteDetailID", routeDetailID);
                deleteRouteDetailCommand->ExecuteNonQuery();

                // Check if there are any remaining RouteDetails for this route
                String^ checkRouteDetailsQuery = "SELECT COUNT(*) FROM RouteDetails WHERE RouteID = @RouteID";
                SqlCommand^ checkRouteDetailsCommand = gcnew SqlCommand(checkRouteDetailsQuery, conn);
                checkRouteDetailsCommand->Parameters->AddWithValue("@RouteID", routeID);
                int remainingDetails = Convert::ToInt32(checkRouteDetailsCommand->ExecuteScalar());

                // If there are no remaining RouteDetails, delete the route from the Routes table
                if (remainingDetails == 0)
                {
                    String^ deleteRouteQuery = "DELETE FROM Routes WHERE RouteID = @RouteID";
                    SqlCommand^ deleteRouteCommand = gcnew SqlCommand(deleteRouteQuery, conn);
                    deleteRouteCommand->Parameters->AddWithValue("@RouteID", routeID);
                    deleteRouteCommand->ExecuteNonQuery();
                }

                conn->Close();

                LoadRouteDetails(); // Reload route details after deletion
                MessageBox::Show("Route detail deleted successfully.", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);
            }
            else
            {
                MessageBox::Show("Please select a route detail to delete.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

    };
}
