namespace TrainMS {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Data::SqlClient;

	/// <summary>
	/// Summary for ShowStations
	/// </summary>
	public ref class ShowStations : public System::Windows::Forms::Form
	{
	private: System::Windows::Forms::DataGridView^ dataGridViewStations;

	public:
		ShowStations(void)
		{
			InitializeComponent();
		}

	protected:
		~ShowStations()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->dataGridViewStations = gcnew System::Windows::Forms::DataGridView();
			this->SuspendLayout();
			// 
			// dataGridViewStations
			// 
			this->dataGridViewStations->Location = System::Drawing::Point(10, 10);
			this->dataGridViewStations->Size = System::Drawing::Size(1180, 450);
			this->dataGridViewStations->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			// 
			// ShowStations
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1213, 490);
			this->Controls->Add(this->dataGridViewStations);
			this->Name = L"ShowStations";
			this->Text = L"ShowStations";
			this->ResumeLayout(false);

			LoadStations();
		}

	private:
		SqlConnection^ GetConnection() {
			SqlConnectionStringBuilder^ builder = gcnew SqlConnectionStringBuilder();
			builder->DataSource = "DESKTOP-NEII4G1"; // Replace with your SQL Server name
			builder->InitialCatalog = "TrainManagementSystem"; // Replace with your database name
			builder->IntegratedSecurity = true;
			return gcnew SqlConnection(builder->ConnectionString);
		}

		void LoadStations() {
			SqlConnection^ conn = GetConnection();
			try {
				conn->Open();
				SqlDataAdapter^ adapter = gcnew SqlDataAdapter("SELECT * FROM Stations ORDER BY StationName", conn);
				DataTable^ dt = gcnew DataTable();
				adapter->Fill(dt);
				this->dataGridViewStations->DataSource = dt;
			}
			catch (Exception^ ex) {
				MessageBox::Show("Error: " + ex->Message);
			}
			finally {
				if (conn != nullptr) {
					conn->Close();
				}
			}
		}
	};
}
