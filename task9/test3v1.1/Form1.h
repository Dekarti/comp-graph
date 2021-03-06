#pragma once

#define HEIGHT this->ClientRectangle.Height
#define WIDTH this->ClientRectangle.Width

namespace test3v11 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
		}

	protected:
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::ComponentModel::Container ^components;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog;
	private: System::Windows::Forms::Button^  btnOpen;

	private: Generic::List<polygon3D^> triangles;
			 Generic::List<System::Drawing::Color> clrs;
			 Color curColor;
	private: float left, right, top, bottom;
			 float Wcx, Wcy, Wx, Wy;
			 float Vcx, Vcy, Vx, Vy;
			 float far, alpha;
			 float aspect, aspectDefault;
			 float near  , nearDefault;
			 float fovy  , fovyDefault;
			 point3D centerDefault, center;
			 point3D eyeDefault   , eye;
			 point3D upDefault    , up;
			 bool prOrtho;



#pragma region Windows Form Designer generated code

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
				 this->openFileDialog->Title = L"Open file";
				 // 
				 // btnOpen
				 // 
				 this->btnOpen->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
				 this->btnOpen->Location = System::Drawing::Point(860, 12);
				 this->btnOpen->Name = L"btnOpen";
				 this->btnOpen->Size = System::Drawing::Size(75, 23);
				 this->btnOpen->TabIndex = 0;
				 this->btnOpen->Text = L"Open";
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
				 this->Resize += gcnew System::EventHandler(this, &Form1::Form1_Resize);
				 this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Form1::Form1_KeyDown);
				 this->ResumeLayout(false);
				 this->PerformLayout();

			 }
#pragma endregion

	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
				 
				 left = right = top = bottom = 60;

				 Wcx = left;
				 Wcy = HEIGHT - bottom;
				 Wx  = WIDTH - left - right;
				 Wy  = HEIGHT - top - bottom;

				 upDefault = point3D(0, 1, 0);
				 centerDefault = point3D(0, 0, 0);
				 eyeDefault = point3D(1, 1, 1);

				 LookAt(centerDefault, eyeDefault, upDefault, T);

				 aspect = Wx / Wy; 
			 }

	private: System::Void Form1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
				 Graphics^ g = e->Graphics;
				 g->Clear(Color::White);
				 Pen^ pen = gcnew Pen(Color::Black, 1);
				 Pen^ rectPen  = gcnew Pen(Color::Cyan, 8);
				 g->DrawRectangle(rectPen, left, top, Wx, Wy);

				 point Pmax = point(WIDTH - right, HEIGHT - bottom);
				 point Pmin = point(left, top);

				 mat3D V, U, R, T1;

				 LookAt(eye, center, up, V);

				 if (prOrtho == true) {
 					 float Vy = 2 * near * tan(fovy / 2);
					 float Vx = Vy * aspect;
					 Ortho(Vx, Vy, near, far, U);
				 }
				 else {
					 Perspective(fovy, aspect, near, far, U);
				 }

				 times(U, V, T1);
				 times(T1, T, R);

				 mat F;
				 frame(2, 2, -1, -1, Wx, Wy, Wcx, Wcy, F);

				 for (int i = 0; i < triangles.Count; i++) {
					 polygon3D^ p = triangles[i];
					 polygon^ p1 = gcnew polygon(0);

					 point a1, a2, c;
					 vec b1, b2;

					 point3D A;
					 vec3D B1, B2;

					 for (int j = 0; j < p->Count; j++) {
						 point2vec(p[j], B1);
						 timesMatVec(R, B1, B2);
						 vec2point(B2, A);
						 set(A, a1);

						 point2vec(a1, b1);
						 timesMatVec(F, b1, b2);
						 vec2point(b2, a1);
						 p1->Add(a1);
					 }

					 p1 = PСlip(p1, Pmin, Pmax);
					 if (p1->Count) {
						 pen->Color = clrs[i];
						 c = p1[p1->Count - 1];
						 for (int j = 0; j < p1->Count; j++) {
							 g ->DrawLine(pen, c.x, c.y, p1[j].x, p1[j].y);
							 c = p1[j];
						 }
					 }
				 }
			 }

	private: System::Void btnOpen_Click(System::Object^  sender, System::EventArgs^  e) {
				 triangles.Clear();
				 clrs.Clear();
				 curColor = Color::Black;
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
							 std::string str;
							 getline(in, str);
							 while (in) {
								 if(str.find_first_not_of(" \t\r\n") != std::string::npos
									 && str[0] != '#') {
										 std::stringstream s(str);
										 std::string cmd;
										 s >> cmd;
										 if (cmd == "triangle") {
											 point3D a, b, c;
											 s >> a.x >> a.y >> a.z;
											 s >> b.x >> b.y >> b.z;
											 s >> c.x >> c.y >> c.z;
											 polygon3D^ triangle = gcnew polygon3D(0);
											 triangle->Add(a);
											 triangle->Add(b);
											 triangle->Add(c);
											 triangles.Add(triangle);
											 clrs.Add(curColor);
										 }
										 else if (cmd == "lookat") {
											 float x1, y1, z1;
											 float x2, y2, z2;
											 float x3, y3, z3;

											 s >> x1 >> y1 >> z1;
											 s >> x2 >> y2 >> z2;
											 s >> x3 >> y3 >> z3;

											 eyeDefault    = point3D(x1, y1, z1);
											 centerDefault = point3D(x2, y2, z2);
											 upDefault     = point3D(x3, y3, z3);
										 }
										 else if (cmd == "color") {
											 float R, G, B;
											 s >> R >> G >> B;

											 curColor = Color::FromArgb((int)R, (int)G, (int)B);
										 }
										 else if (cmd == "screen") {
											 float fD, nD, f;
											 s >> fD >> nD >> f;

											 fovyDefault = fD;
											 nearDefault = nD;
											 far = f;
										 }


								 }
								 getline(in, str);
							 }
						 }
						 LookAt(centerDefault, eyeDefault, upDefault, T);
						 center = centerDefault;
						 near   = nearDefault;
						 fovy   = fovyDefault;
						 vec3D vec, vec1;
						 point3D p;
						 point2vec(eyeDefault, vec);
						 timesMatVec(T, vec, vec1);
						 vec2point(vec1, p);
						 eye = p;
						 up  = upDefault;
						 up  = point3D(0, 1, 0);
						 center = point3D(0, 0, 0);

						 alpha = 0.1f;
						 prOrtho = true;
						 this->Refresh();
				 }
			 }

	private: System::Void Form1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
				 mat3D R, T1;
				 unit(R);
				 switch(e->KeyCode) {
					 case Keys::W :
						 rotate(point3D(1, 0, 0),  alpha, R);
						 break;
					 case Keys::S :
						 rotate(point3D(1, 0, 0), -alpha, R);
						 break;
					 case Keys::A :
						 rotate(point3D(0, 1, 0),  alpha, R);
						 break;
					 case Keys::D :
						 rotate(point3D(0, 1, 0), -alpha, R);
						 break;
					 case Keys::Q :
						 rotate(point3D(0, 0, 1),  alpha, R);
						 break;
					 case Keys::E :
						 rotate(point3D(0, 0, 1), -alpha, R);
						 break;
					 case Keys::O :
						 alpha *= 1.1;
						 break;
					 case Keys::L :
						 alpha *= 1 / 1.1;
						 break;
					 case Keys::Z :
						 near /= 1.1;
						 break;
					 case Keys::X :
						  near *= 1.1;
						 break;
					 case Keys::C :
						 fovy += 0.1;
						 break;
					 case Keys::V :
						 fovy -= 0.1;
						 break;
					 case Keys::P :
						 prOrtho ^= 1;
						 break;
					 case Keys::Escape :
						 LookAt(centerDefault, eyeDefault, upDefault, T);
						 near   = nearDefault;
						 fovy   = fovyDefault;
						 vec3D vec, vec1;
						 point3D p;
						 point2vec(eyeDefault, vec);
						 timesMatVec(T, vec, vec1);
						 vec2point(vec1, p);
						 eye = p;

						 alpha = 0.1f;
						 prOrtho = true;
				 }

 				 times(R, T, T1);
				 set(T1, T);

				 this->Refresh();
			 }

	private: System::Void Form1_Resize(System::Object^  sender, System::EventArgs^  e) {
				 float oldWx = Wx;
				 float oldWy = Wy;

				 Wcx = left;
				 Wcy = HEIGHT - bottom;
				 Wx  = WIDTH - left - right;
				 Wy  = HEIGHT - top - bottom;

				 mat R, T1;
				 move(-Wcx, -top, R);
				 times(R, L, T1);

				 scale(Wx / oldWx, Wy / oldWy, R);
				 times(R, T1, L);

				 move(Wcx, top, R);
				 times(R, L, T1);
				 set(T1, L);

				 aspect = Wx / Wy;

				 this->Refresh();
			 }
	};
}
