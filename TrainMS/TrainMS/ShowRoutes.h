#pragma once

namespace TrainMS {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::Data::SqlClient;

    public ref class ShowRoutes : public System::Windows::Forms::Form
    {
    public:
        ShowRoutes(void)
        {
            InitializeComponent();
            LoadRoutes();  // Load all route names and details when the form is initialized
        }

    protected:
        ~ShowRoutes()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::ComponentModel::Container^ components;
        System::Windows::Forms::DataGridView^ routesDataGridView;
        System::Windows::Forms::ComboBox^ routeComboBox;  // ComboBox for route selection
        SqlConnection^ conn;

        void InitializeComponent(void)
        {
            this->routesDataGridView = (gcnew System::Windows::Forms::DataGridView());
            this->routeComboBox = (gcnew System::Windows::Forms::ComboBox());
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->routesDataGridView))->BeginInit();
            this->SuspendLayout();
            // 
            // routesDataGridView
            // 
            this->routesDataGridView->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
            this->routesDataGridView->Location = System::Drawing::Point(76, 78);
            this->routesDataGridView->Name = L"routesDataGridView";
            this->routesDataGridView->RowHeadersWidth = 51;
            this->routesDataGridView->Size = System::Drawing::Size(774, 400);
            this->routesDataGridView->TabIndex = 0;
            // 
            // routeComboBox
            // 
            this->routeComboBox->FormattingEnabled = true;
            this->routeComboBox->Location = System::Drawing::Point(76, 30);
            this->routeComboBox->Name = L"routeComboBox";
            this->routeComboBox->Size = System::Drawing::Size(200, 24);
            this->routeComboBox->TabIndex = 1;
            this->routeComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &ShowRoutes::routeComboBox_SelectedIndexChanged);
            // 
            // ShowRoutes
            // 
            this->ClientSize = System::Drawing::Size(914, 500);
            this->Controls->Add(this->routeComboBox);
            this->Controls->Add(this->routesDataGridView);
            this->Name = L"ShowRoutes";
            this->Text = L"Show Routes";
            (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->routesDataGridView))->EndInit();
            this->ResumeLayout(false);

        }

        void LoadRoutes()
        {
            conn = gcnew SqlConnection("Server=DESKTOP-NEII4G1;Database=TrainManagementSystem;Trusted_Connection=True;");
            String^ query = "SELECT DISTINCT RouteName FROM Routes";

            SqlDataAdapter^ adapter = gcnew SqlDataAdapter(query, conn);
            DataTable^ routesTable = gcnew DataTable();
            adapter->Fill(routesTable);

            // Populate ComboBox with unique route names
            routeComboBox->DataSource = routesTable;
            routeComboBox->DisplayMember = "RouteName";
            routeComboBox->ValueMember = "RouteName";

            // Load initial data (all routes)
            LoadRouteDetails("");  // Load all routes initially
        }

        void LoadRouteDetails(String^ selectedRoute)
        {
            String^ query;
            if (String::IsNullOrEmpty(selectedRoute))
            {
                // Load all routes, sorted by RouteName and then StopOrder
                query = "SELECT R.RouteName, S.StationName, RD.ArrivalTime, RD.DepartureTime, RD.StopOrder "
                    "FROM Routes R "
                    "JOIN RouteDetails RD ON R.RouteID = RD.RouteID "
                    "JOIN Stations S ON RD.StationID = S.StationID "
                    "ORDER BY R.RouteName, RD.StopOrder";
            }
            else
            {
                // Load details for a selected route, sorted by StopOrder
                query = "SELECT R.RouteName, S.StationName, RD.ArrivalTime, RD.DepartureTime, RD.StopOrder "
                    "FROM Routes R "
                    "JOIN RouteDetails RD ON R.RouteID = RD.RouteID "
                    "JOIN Stations S ON RD.StationID = S.StationID "
                    "WHERE R.RouteName = @RouteName "
                    "ORDER BY RD.StopOrder";  // Sorting by StopOrder for the selected route
            }

            SqlDataAdapter^ adapter = gcnew SqlDataAdapter(query, conn);

            // Add parameter for selected route name if necessary
            if (!String::IsNullOrEmpty(selectedRoute))
            {
                adapter->SelectCommand->Parameters->AddWithValue("@RouteName", selectedRoute);
            }

            DataTable^ routeDetailsTable = gcnew DataTable();
            adapter->Fill(routeDetailsTable);

            // Bind the loaded data to the DataGridView
            routesDataGridView->DataSource = routeDetailsTable;

            // Customize the DataGridView columns
            routesDataGridView->Columns["RouteName"]->HeaderText = "Route Name";
            routesDataGridView->Columns["StationName"]->HeaderText = "Station";
            routesDataGridView->Columns["ArrivalTime"]->HeaderText = "Arrival Time";
            routesDataGridView->Columns["DepartureTime"]->HeaderText = "Departure Time";
            routesDataGridView->Columns["StopOrder"]->HeaderText = "Stop Order";

            // Set specific column widths
            routesDataGridView->Columns["RouteName"]->Width = 150;  // Route Name
            routesDataGridView->Columns["StationName"]->Width = 180;  // Station Name
            routesDataGridView->Columns["ArrivalTime"]->Width = 150;  // Arrival Time
            routesDataGridView->Columns["DepartureTime"]->Width = 150;  // Departure Time
            routesDataGridView->Columns["StopOrder"]->Width = 120;  // Stop Order

            // Adjust columns to fit content
            routesDataGridView->AutoResizeColumns();
        }


        // Event handler to filter data based on selected route
        void routeComboBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
        {
            String^ selectedRoute = routeComboBox->SelectedValue->ToString();
            LoadRouteDetails(selectedRoute);  // Filter the route details based on the selected route
        }

    };
}
