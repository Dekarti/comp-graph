#pragma once

#include <string>
#include "PClip.h"
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

	private: System::Collections::Generic::List<polygon^> polygons;
			 System::Collections::Generic::List<Color> clrs;
	private: Color curColor;
	private: float left, right, top, bottom,
			       Wcx, Wcy, Wx, Wy,
				   Vcx, Vcy, Vx, Vy;
			 Pen^ polygonPen;


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
				 this->btnOpen->Location = System::Drawing::Point(860, 12);
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
				 this->ClientSize = System::Drawing::Size(984, 661);
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
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
				 this->Refresh();
				 polygonPen = gcnew Pen(Color::Black);
				 left = right = top = bottom = 60;

				 Wcx = left;
				 Wcy = HEIGHT - bottom;
				 Wx = WIDTH - left - right;
				 Wy = HEIGHT - top - bottom;

				 polygons.Clear();
				 clrs.Clear();
				 unit (T);
				 
			 }
	private: System::Void Form1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
				 Bitmap^ image1 = gcnew Bitmap(WIDTH, HEIGHT);
				 Graphics^ g = Graphics::FromImage(image1);

				 Pen^ rectPen = gcnew Pen(Color::DarkGray);
				 rectPen->Width = 8;

				 point Pmax, Pmin;
				 Pmax.x = WIDTH  - right;
				 Pmin.x = left;

				 Pmax.y = HEIGHT - bottom;
				 Pmin.y = top;
				 g->DrawRectangle(rectPen, left, top, Wx, Wy);

				 for (int i = 0; i < polygons.Count; i++) {
					 polygon^ p = polygons[i];
					 polygon^ p1 = gcnew polygon(0);
					 point b, c;
					 vec B, B1;
 
					 for (int j = 0; j < p->Count; j++) {
						 point2vec(p[j], B);
						 timesMatVec(T, B, B1);
						 vec2point(B1, b);
						 p1->Add(b);
					 }
 
					 p1 = Pclip(p1, Pmin, Pmax);
					 if (p1->Count) {
						 c = p1[p1->Count - 1];
						 for (int j = 0; j < p1->Count; j++) {
							 polygonPen->Color = clrs[i];
							 g ->DrawLine(polygonPen, c.x, c.y, p1[j].x, p1[j].y);
							 c = p1[j];
						 }
						 PFill(p1, image1, clrs[i]);
					 }
				 }
				 g = e->Graphics;
				 g->DrawImage(image1,0,0);
				 delete image1;
			 }
	private: System::Void openFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e) {

			 }
	private: System::Void btnOpen_Click(System::Object^  sender, System::EventArgs^  e) {
				 polygons.Clear();
				 clrs.Clear();
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
										 else if (cmd == "polygon") {
											 int numpoint;
											 s >> numpoint;

											 polygon^ P = gcnew polygon(0);
											 for (int i = 0; i < numpoint; i++) {
												point p;
												s >> p.x >> p.y;
												P->Add(p);
											 }
											 polygons.Add(P);
											 clrs.Add(curColor);
										 }
										 else if(cmd == "color") {
											float R, G, B;
											s >> R >> G >> B;
											curColor = Color::FromArgb(R, G, B);
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

						rotate(0.13, R);
						times(R, T, T1);
						set(T1, T);
						
						move(WIDTH / 2, HEIGHT / 2, R);
						break;
					case Keys::Y : // 5
						move(-WIDTH / 2, -HEIGHT / 2, R);
						times(R, T, T1);
						set(T1, T);

						rotate(-0.13, R);
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
					case Keys::P :
						unit(R);
						//drawNames ^= 1;
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
