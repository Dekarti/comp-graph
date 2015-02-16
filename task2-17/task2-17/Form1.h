#pragma once


namespace task217 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Name = L"Form1";
			this->Text = L"Form1";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::Form1_Paint);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Form1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
Graphics^ g = e->Graphics;
                                g->Clear(Color::White);
 
                                Rectangle rect = Form::ClientRectangle;
                                Pen^ pen = gcnew Pen(Color::Black);
 
                                pen->Width = 2;

								//	Ё“ќ ћќя »ƒ≈я!

                                int a[100][100] = {
								     {0, 20},
                                     {20, 40},
                                     {30, 20},
                                     {20, 60},
                                     {-40, 20},
                                     {-10, 10}, // уровень бровей
                                     {-20, 40},
                                     {0, 20},
                                     {20, 40},
                                     {20, 20},
                                     {30, 10},
                                     {40, 0},
                                     {20, -10},
                                     {10, 20},
                                     {10, 0},
                                     {20, -10},
                                     {0, -20},
                                     {-10, -10},
                                     {10, -30},
                                     {0, -40},
                                     {-10, -20},
                                     {-40, -40},
                                     {20, -40},
                                     {0, -70},
                                     {-40, -40},
                                     {-30, 20},
                                     {0, 20},
                                     {-50, -30},
                                     {-20, 0}
								};
																
 
                                int x0 = 20, y0 = 30;
                                for (int i = 0; i < 100; i++) {
                                        g->DrawLine( pen, x0, y0, x0 + a[i][0], y0 + a[i][1] );
                                        x0 += a[i][0];
                                        y0 += a[i][1];
                                }

								int b[100][100] = {
									{20, 0},
									{10, 10},
									{-30, 0},
									{0, -10}};

								int x11 = 40, x12 = 80;
								int y1 = 200;

								for (int i = 0; i < 100; i++) {
									g->DrawLine( pen, x11, y1, x11 + b[i][0], y1 + b[i][1] );
									g->DrawLine( pen, x12, y1, x12 + b[i][0], y1 + b[i][1] );
                                        x11 += b[i][0];
										x12 += b[i][0];
                                        y1 += b[i][1];
								}

								int x2 = 70, y2 = 310;
								int c[100][100] = {
									{0, -90},
									{10, -10},
									{10, 0},
									{10, 10},
									{0, 50},
									{-10, 10},
									{-10, 0},
									{-10, -10},
									{10, 0},
									{0, -20}, 
									{-20, 0}, 
									{0, 20}, 
									{10, 0},
									{-10, 10},
									{-10, 0}, 
									{-10, -20}, 
									{0, -30}, 
									{10, -10}, 
									{10, 0}, 
									{10, 10}
								};

								for (int i = 0; i < 50; i++) {
                                        g->DrawLine( pen, x2, y2, x2 + c[i][0], y2 + c[i][1] );
                                        x2 += c[i][0];
                                        y2 += c[i][1];
                                }

								int x3 = 90, y3 = 330;
								int d[100][100] = {
									{-10, 10},
									{-20, 10},
									{0, 20}, 
									{10, 10},
									{30, 0},
									{0, -30}, 
									{10, -10},
									{-10, 10},
									{0, 30},
									{50, 0},
									{10, -10}, 
									{0, -20},
									{-20, -10}, 
									{-10, -10}, 
									{-40, 0}
								};

								for (int i = 0; i < 50; i++) {
                                        g->DrawLine( pen, x3, y3, x3 + d[i][0], y3 + d[i][1] );
                                        x3 += d[i][0];
                                        y3 += d[i][1];
                                }

								g->DrawLine( pen, 90, 60, 110, 80 );
								g->DrawLine( pen, 110, 80, 120, 130 );
								g->DrawLine( pen, 120, 130, 110, 160 );
								g->DrawLine( pen, 110, 160, 120, 160 );
								g->DrawLine( pen, 120, 160, 120, 130 );
								g->DrawLine( pen, 90, 170, 140, 170 );
								g->DrawLine( pen, 40, 280, 50, 290);
								g->DrawLine( pen, 50, 290, 90, 290);
								g->DrawLine( pen, 90, 290, 110, 270 );
								g->DrawLine( pen, 60, 290, 60, 310 );
								g->DrawLine( pen, 60, 310, 80, 310 );
								g->DrawLine( pen, 80, 310, 80, 290 );
								g->DrawLine( pen, 150, 290, 160, 290 );
								g->DrawLine( pen, 160, 290, 160, 300 );
								g->DrawLine( pen, 160, 300, 150, 320 );
								g->DrawLine( pen, 150, 280, 170, 280 );
								g->DrawLine( pen, 170, 280, 170, 290 );
								g->DrawLine( pen, 170, 290, 180, 300 );
								g->DrawLine( pen, 190, 330, 180, 320 );
								g->DrawLine( pen, 170, 340, 170, 330 );
								g->DrawLine( pen, 40, 300, 20, 310 );
								g->DrawLine( pen, 20, 310, 20, 330 );
								g->DrawLine( pen, 20, 330, 30, 320 );
								g->DrawLine( pen, 20, 330, 30, 340 );
								g->DrawLine( pen, 30, 340, 40, 330 );
								g->DrawLine( pen, 30, 340, 40, 340 );
								g->DrawLine( pen, 40, 340, 60, 320 );
								g->DrawLine( pen, 60, 280, 80, 280 );


								


			 }
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
			 }
};
}

