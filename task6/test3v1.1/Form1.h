#pragma once

#include <string>
#define HEIGHT this->ClientRectangle.Height
#define WIDTH this->ClientRectangle.Width

namespace test3v11 {

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
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog;
	private: System::Windows::Forms::Button^  btnOpen;

	private: float left, right, top, bottom,
			       Wcx, Wcy, Wx, Wy,
				   Vcx, Vcy, Vx, Vy;

#pragma region Windows Form Designer generated code
			 /// <summary>
			 /// Required method for Designer support - do not modify
			 /// the contents of this method with the code editor.
			 /// </summary>
			 void InitializeComponent(void)
			 {
				 this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
				 this->btnOpen = (gcnew System::Windows::Forms::Button());
				 this->SuspendLayout();
				 // 
				 // openFileDialog
				 // 
				 this->openFileDialog->DefaultExt = L"txt";
				 this->openFileDialog->FileName = L"openFileDialog1";
				 this->openFileDialog->Filter = L"Текстовые файлы (*.txt)|*.txt|Все файлы (*.*)|*.*";
				 this->openFileDialog->Title = L"Открыть файл";
				 this->openFileDialog->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &Form1::openFileDialog1_FileOk);
				 // 
				 // btnOpen
				 // 
				 this->btnOpen->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				 this->btnOpen->Location = System::Drawing::Point(780, 12);
				 this->btnOpen->Name = L"btnOpen";
				 this->btnOpen->Size = System::Drawing::Size(75, 23);
				 this->btnOpen->TabIndex = 0;
				 this->btnOpen->Text = L"Открыть";
				 this->btnOpen->UseVisualStyleBackColor = true;
				 this->btnOpen->Click += gcnew System::EventHandler(this, &Form1::btnOpen_Click);
				 // 
				 // Form1
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->ClientSize = System::Drawing::Size(904, 481);
				 this->Controls->Add(this->btnOpen);
				 this->DoubleBuffered = true;
				 this->KeyPreview = true;
				 this->MinimumSize = System::Drawing::Size(500, 350);
				 this->Name = L"Form1";
				 this->Text = L"Form1";
				 this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
				 this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::Form1_Paint);
				 this->DockChanged += gcnew System::EventHandler(this, &Form1::btnOpen_Click);
				 this->Resize += gcnew System::EventHandler(this, &Form1::Form1_Resize);
				 this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyDown);
				 this->ResumeLayout(false);

			 }
#pragma endregion
	private: void DrawFigure(Graphics^ g, Pen^ pen) {
				 g->DrawRectangle(pen, -20,-30,40,60);

               //  pen->Width = .1;

				 int a[100][4] = {
				 	{20 , 370, 20 , 350},
				 	{20 , 350, 40 , 310},
				 	{40 , 310, 70 , 290},
				 	{70 , 290, 90 , 230},
				 	{90 , 230, 50 , 210},
				 	{50 , 210, 40 , 200},
				 	{40 , 200, 20 , 160},
				 	{20 , 160, 20 , 140},
				 	{20 , 140, 40 , 100},
				 	{40 , 100, 60 , 80 },
				 	{60 , 80 , 90 , 70 },
				 	{90 , 70 , 130, 70 },
				 	{130, 70 , 150, 80 },
				 	{150, 80 , 160, 60 },
				 	{160, 60 , 170, 60 },
				 	{170, 60 , 190, 70 },
				 	{190, 70 , 190, 90 },
				 	{190, 90 , 180, 100},
				 	{180, 100, 190, 130},
				 	{190, 130, 190, 170},
				 	{190, 170, 180, 190},
				 	{180, 190, 140, 230},
				 	{140, 230, 160, 270},
				 	{160, 270, 160, 340},
				 	{160, 340, 120, 380},
				 	{120, 380, 90 , 360},
				 	{90 , 360, 90 , 340},
				 	{90 , 340, 40 , 370},
				 	{40 , 370, 20 , 370},
				 	{40 , 200, 60 , 200},
				 	{80 , 200, 100, 200},
				 	{60 , 200, 70 , 190},
				 	{100, 200, 110, 190},
				 	{70 , 190, 40 , 190},
				 	{110, 190, 80 , 190},
				 	{40 , 190, 40 , 200},
				 	{80 , 190, 80 , 200},
				 	{70 , 90 , 70 , 180},
				 	{70 , 180, 80 , 190},
				 	{80 , 190, 90 , 190},
				 	{90 , 190, 100, 180},
				 	{100, 180, 100, 130},
				 	{100, 130, 90 , 120},
				 	{90 , 120, 80 , 120},
				 	{80 , 120, 70 , 130},
				 	{70 , 130, 80 , 130},
				 	{80 , 130, 80 , 150},
				 	{80 , 150, 60 , 150},
				 	{60 , 150, 60 , 130},
				 	{60 , 130, 70 , 130},
				 	{70 , 130, 60 , 120},
				 	{60 , 120, 50 , 120},
				 	{50 , 120, 40 , 140},
				 	{40 , 140, 40 , 170},
				 	{40 , 170, 50 , 180},
				 	{50 , 180, 60 , 180},
				 	{60 , 180, 70 , 170},
				 	{90 , 70 , 80 , 60 },
				 	{80 , 60 , 60 , 50 },
				 	{60 , 50 , 60 , 30 },
				 	{60 , 30 , 70 , 20 },
				 	{70 , 20 , 100, 20 },
				 	{100, 20 , 100, 50 },
				 	{100, 50 , 110, 60 },
				 	{110, 60 , 100, 50 },
				 	{100, 50 , 100, 20 },
				 	{100, 20 , 150, 20 },
				 	{150, 20 , 160, 30 },
				 	{160, 30 , 160, 50 },
				 	{160, 50 , 140, 60 },
				 	{140, 60 , 130, 70 },
				 	{130, 70 , 90 , 70 },
				 	{90 , 340, 110, 320},
				 	{110, 320, 120, 270},
				 	{120, 270, 110, 240},
				 	{110, 240, 120, 240},
				 	{120, 240, 120, 270},
				 	{90 , 230, 140, 230},
				 	{40 , 120, 50 , 110},
				 	{50 , 110, 90 , 110},
				 	{90 , 110, 110, 130},
				 	{60 , 110, 60 , 90 },
				 	{60 , 90 , 80 , 90 },
				 	{80 , 90 , 80 , 110},
				 	{150, 110, 160, 110},
				 	{160, 110, 160, 100},
				 	{160, 100, 150, 80 },
				 	{150, 120, 170, 120},
				 	{170, 120, 170, 110},
				 	{170, 110, 180, 100},
				 	{190, 70 , 180, 80 },
				 	{170, 60 , 170, 70 },
				 	{40 , 100, 20 , 90 },
				 	{20 , 90 , 20 , 70 },
				 	{20 , 70 , 30 , 80 },
				 	{20 , 70 , 30 , 60 },
				 	{30 , 60 , 40 , 70 },
				 	{30 , 60 , 40 , 60 },
				 	{40 , 60 , 60 , 80 },
				 	{60 , 120, 80 , 120}
				 };

				 for (int i = 0; i < 100; i++) {
				 	g->DrawLine(pen,
							    (a[i][0] / 10 - 10.5) * 1.66666666666,
							    (a[i][1] / 10  - 20) * 1.66666666666,
								(a[i][2] / 10 - 10.5) * 1.66666666666,
								(float)((a[i][3] / 10 - 20) * 1.66666666666));
				 }
			 
			 }

	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
				 unit (T);
				 left = right = top = bottom = 60;

				 Wcx = left;
				 Wcy = HEIGHT - bottom;
				 Wx = WIDTH - left - right;
				 Wy = HEIGHT - top - bottom;
			 }
	private: System::Void Form1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
				 Graphics^ g = e->Graphics;
				 g->Clear(Color::White);
				 Pen^ blackPen = gcnew Pen(Color::Black);
				 blackPen->Width = 0.1;

				 Pen^ rectPen = gcnew Pen(Color::SteelBlue);
				 rectPen->Width = 2;
				 

				 Rectangle rect = System::Drawing::Rectangle(left, top, Wx, Wy);
				 g->DrawRectangle(rectPen, rect);
				 g->Clip = gcnew System::Drawing::Region(rect);

				 g->Transform = gcnew Drawing2D::Matrix(T[0][0], T[1][0],
														T[0][1], T[1][1],
														T[0][2], T[1][2]);
	
				 for (int i = 0; i < matrices.size(); i++) {
					mat С;
					times(T, matrices[i], С);
					g->Transform = gcnew System::Drawing::Drawing2D::Matrix(С[0][0], С[1][0],
																			С[0][1], С[1][1],
																			С[0][2], С[1][2]);
					DrawFigure(g, blackPen);
				 }
				 
			 }
	private: System::Void openFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {

			 }
	private: System::Void btnOpen_Click(System::Object^  sender, System::EventArgs^  e) {
				 if (this->openFileDialog->ShowDialog() ==
					 System::Windows::Forms::DialogResult::OK) {
						 wchar_t fileName[1024];
						 for (int i = 0; i < openFileDialog->FileName->Length; i++) {
							 fileName[i] = openFileDialog->FileName[i];
						 }
						 fileName[openFileDialog->FileName->Length] = '\0';
						 std::ifstream in;
						 in.open(fileName);

						 if (in.is_open()) {
							 matrices.clear();
							 std::stack<mat> matStack;
							 mat K;
							 unit(K);
							 unit(T);
							 std::string str;
							 getline(in, str);
							 while (in) {
								 if(str.find_first_not_of(" \t\r\n") != std::string::npos
									 && str[0] != '#') {
										 std::stringstream s(str);
										 std::string cmd;
										 s >> cmd;
										 if (cmd == "frame") {
											 float vcx, vcy, vx, vy;
											 s >> vcx >> vcy >> vx >> vy;
											 Vcx = Vcx;
											 Vcy = Vcy;
											 Vx = vx;
											 Vy = vy;
											 frame(Vx, Vy, Vcx, Vcy, Wx, Wy, Wcx, Wcy, T);
										 }
										 else if (cmd == "figure") {
											 matrices.push_back(K);
										 }
										 else if (cmd == "pushTransform") {
											 matStack.push(K);
										 }
										 else if (cmd == "popTransform") {
											 K = matStack.top();
											 matStack.pop();	
										 }
										 else if (cmd == "translate") {
											 float Tx, Ty;
											 s >> Tx >> Ty;
											 mat С, С1;
											 move(Tx, Ty, С);
											 times(K, С, С1);
											 K = С1;
										 }
										 else if (cmd == "scale") {
											 float S;
											 s >> S;
											 mat С, С1;
											 scale(S, С);
											 times(K, С, С1);
											 K = С1;
										 }
										 else if (cmd == "rotate") {
											 float Phi;
											 s >> Phi;
											 float pi = 3.1415926535;
											 float PhiR = Phi * (pi / 180);
											 mat C, C1;
											 rotate(PhiR, C);
											 times(K, C, C1);
											 K = C1;
										 }
								 }
								 getline(in, str);
							 }
						 }
						 this->Refresh();
				 }
			 }
	private: System::Void Form1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
				 mat R, T1;
				 switch(e->KeyCode){
					case Keys::W :
						move(0, -1, R);
						break;
					case Keys::S :
						move(0, 1, R);
						break;
					case Keys::A :
						move(-1, 0, R);
						break;
					case Keys::D :
						move(1, 0, R);
						break;
					case Keys::E :
						rotate(0.05, R);
						break;
					case Keys::Q :
						rotate(-0.05, R);
						break;
					case Keys::X :
						scale(1/1.1, R);
						break;
					case Keys::Z :
						scale(1.1, R);
						break;
					case Keys::T :
						move(0, -16, R);
						break;
					case Keys::G :
						move(0, 16, R);
						break;
					case Keys::F :
						move(-16, 0, R);
						break;
					case Keys::H :
						move(16, 0, R);
						break;
					case Keys::U : // 4
						mirror(false, R);
						times(R, T, T1);
						set(T1, T);

						move(WIDTH, 0, R);	
						break;
					case Keys::J : // 4
						mirror(true, R);
						times(R, T, T1);
						set(T1, T);

						move(0, HEIGHT, R);	
						break;
					case Keys::R : // 5
						move(-WIDTH / 2, -HEIGHT / 2, R);
						times(R, T, T1);
						set(T1, T);

						rotate(0.05, R);
						times(R, T, T1);
						set(T1, T);
						
						move(WIDTH / 2, HEIGHT / 2, R);
						break;
					case Keys::Y : // 5
						move(-WIDTH / 2, -HEIGHT / 2, R);
						times(R, T, T1);
						set(T1, T);

						rotate(-0.05, R);
						times(R, T, T1);
						set(T1, T);
						
						move(WIDTH / 2, HEIGHT / 2, R);
						break;
					case Keys::C : // 6
						move(-WIDTH / 2, -HEIGHT / 2, R);
						times(R, T, T1);
						set(T1, T);

						scale(1.1, R);
						times(R, T, T1);
						set(T1, T);
						
						move(WIDTH / 2, HEIGHT / 2, R);
						break;
					case Keys::V : // 6
						move(-WIDTH / 2, -HEIGHT / 2, R);
						times(R, T, T1);
						set(T1, T);

						scale(1 / 1.1, R);
						times(R, T, T1);
						set(T1, T);
						
						move(WIDTH / 2, HEIGHT / 2, R);
						break;
					case Keys::I : // 7
						move(-WIDTH / 2, 0, R);
						times(R, T, T1);
						set(T1, T);

						stretch(1.1, 1, R);
						times(R, T, T1);
						set(T1, T);

						move(WIDTH / 2, 0, R);
						break;
					case Keys::O : // 7
						move(-WIDTH / 2, 0, R);
						times(R, T, T1);
						set(T1, T);

						stretch(1/1.1, 1, R);
						times(R, T, T1);
						set(T1, T);

						move(WIDTH / 2, 0, R);
						break;
					case Keys::K : // 7
						move(0, -HEIGHT / 2, R);
						times(R, T, T1);
						set(T1, T);

						stretch(1, 1.1, R);
						times(R, T, T1);
						set(T1, T);

						move(0, HEIGHT / 2, R);
						break;
					case Keys::L : // 7
						move(0, -HEIGHT / 2, R);
						times(R, T, T1);
						set(T1, T);

						stretch(1, 1/1.1, R);
						times(R, T, T1);
						set(T1, T);

						move(0, HEIGHT / 2, R);
						break;
					case Keys::Escape : // 8
						unit(T);
						unit(R);
						frame(Vx, Vy, Vcx, Vcy, Wx, Wy, Wcx, Wcy, T);
						break;
					default :
						unit(R);
				 }
				 times(R, T, T1);
				 set(T1, T);
				 this->Refresh();
			 }
	private: System::Void Form1_Resize(System::Object^  sender, System::EventArgs^  e) {
				 float oldWx = Wx,
					   oldWy = Wy;


				 Wcy = HEIGHT - bottom;
				 Wx = WIDTH - left - right;
				 Wy = HEIGHT - top - bottom;

				 mat R, T1;

				 move(-Wcx, -top, R);
				 times(R, T, T1);
				 set(T1, T);

				 stretch(Wx / oldWx, Wy / oldWy, R);
				 times(R, T, T1);
				 set(T1, T);

				 move(Wcx, top, R);
				 times(R, T, T1);
				 set(T1, T);	

				 this->Refresh();
			 }
};
}

