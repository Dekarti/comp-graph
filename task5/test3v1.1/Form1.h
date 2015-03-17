#pragma once

#include <string>
#include "Clip.h"
#include <cmath>
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


	private: float left, right, top, bottom,
			       Wcx, Wcy, Wx, Wy,
				   Vcx, Vcy, Vx, Vy,
				   x  , xp , y , yp, ypp,
				   X  , Y;
	private: point Pmax, Pmin;
	private: int L, K;

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
				 this->ClientSize = System::Drawing::Size(556, 483);
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

			 }
#pragma endregion
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
				 left = right = top = bottom = 60;

				 Wcx = left;
				 Wcy = HEIGHT - bottom;
				 Wx = WIDTH - left - right;
				 Wy = HEIGHT - top - bottom;

				 Vcx = Vcy = 0;
				 Vx = Vy = 50;

				 xp = Wcx;
				 x = Vcx;

				 Pmax.x = WIDTH  - right;
				 Pmax.y = HEIGHT - bottom;		

				 Pmin.x = left;
				 Pmin.y = top;

				 L = 15;
				 K = 10;
			 }
	private: System::Void Form1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
				 Graphics^ g = e->Graphics;
				 g->Clear(Color::White);
				 Pen^ blackPen = gcnew Pen(Color::BlueViolet);
				 blackPen->Width = 2;

				 Pen^ linesPen = gcnew Pen(Color::Gray);
				 blackPen->Width = 1;

				 Pen^ rectPen = gcnew Pen(Color::Black);
				 rectPen->Width = 1;
				 
				 System::Drawing::Font^ font = gcnew System::Drawing::Font("Arial", 8);
				 SolidBrush^ brush = gcnew SolidBrush(Color::Black);

				 bool visible1 = false,
					  visible2 = false;

				 if (fexists(x)) {
					visible1 = true;
					y = f(x);
					yp = Wcy - (y - Vcy) * Wy / Vy;
				 }
				 else {
					 visible1 = false;
				 }

				 while (xp < Wcx + Wx) {
					x = (xp + 1 - Wcx) * Vx / Wx + Vcx;
					if (fexists(x)) {
						visible2 = true;
						y = f(x);
						ypp = Wcy - (y - Vcy) * Wy / Vy;
					}
					else {
						visible2 = false;
					}

					if (visible1 && visible2 && clip(xp, yp, xp + 1, ypp, Pmin, Pmax)) {
						g->DrawLine(blackPen, xp, yp, xp + 1, ypp);
					}
					xp++;
					yp = ypp;
					visible1 = visible2;
					
					float numb1 = Wx / K;
					for (float xs = Wcx + numb1; xs < Wx + left; xs += numb1) {
						X = ceil(((xs - Wcx) / Wx) * Vx + Vcx);
						g->DrawLine(linesPen, xs, top, xs, HEIGHT - bottom);
						g->DrawString(Convert::ToString(X), font, brush, xs, Wcy);
					}

					float numb2 = Wy / L;
					for (float ys = top + numb2; ys < Wcy; ys += numb2) {
						Y = ceil(Vcy - ((ys - Wcy) / Wy) * Vy);
						g->DrawLine(linesPen, left, ys, WIDTH - right, ys);
						g->DrawString(Convert::ToString(Y), font, brush, Wx + Wcx, ys);
					}
				}

				 g->DrawRectangle(rectPen, left, top, Wx, Wy);

			 }

	private: System::Void Form1_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
				 switch(e->KeyCode){
					case Keys::W :
						Vcy -= (Vy / Wy);
						break;
					case Keys::S :
						Vcy += (Vy / Wy);
						break;
					case Keys::D :
						Vcx -= (Vx / Wx);
						break;
					case Keys::A :
						Vcx += (Vx / Wx);
						break;
					case Keys::T :
						Vcy -= 15 * (Vy / Wy);
						break;
					case Keys::G :
						Vcy += 15 * (Vy / Wy);
						break;
					case Keys::F :
						Vcx += 15 * (Vx / Wx);
						break;
					case Keys::H :
						Vcx -= -15 * (Vx / Wx);
						break;
					/*case Keys::Q :
						K++;
						break;
					case Keys::E :
						if (K > 1) K--;
						break;
					case Keys::Z :
						L++;
						break;
					case Keys::C :
						if (L > 1) L--;
						break;
					case Keys::L :
						temp = Vx;
						Vx *= 1.1;
						Vcx += (temp - Vx) / 2;
						break;
					case Keys::K :
						temp = Vx;
						Vx *= 1 / 1.1;
						Vcx += (temp - Vx) / 2;
						break;
					case Keys::O :
						temp = Vy;
						Vy *= 1.1;
						Vcy += (temp - Vy) / 2;
						break;
					case Keys::I :
						temp = Vy;
						Vy *= 1 / 1.1;
						Vcy += (temp - Vy) / 2;
						break;
					case Keys::Escape :
						Vx = Vx_;
						Vy = Vy_;
						Vcx = Vcx_;
						Vcy = Vcy_;
						break;*/
				 }
				 this->Refresh();
			 }
	private: System::Void Form1_Resize(System::Object^  sender, System::EventArgs^  e) {
				 float oldWx = Wx,
					   oldWy = Wy;


				 Wcy = HEIGHT - bottom;
				 Wx = WIDTH - left - right;
				 Wy = HEIGHT - top - bottom;

				 Pmax.x = WIDTH  - right;
				 Pmax.y = HEIGHT - bottom;	

				 this->Refresh();
			 }
};
}

