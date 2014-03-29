//---------------------------------------------------------------------------

#include <vcl.h>

//
#pragma hdrstop
#include "Calc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;  
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
    Edit1->Text=32;
    if(FullByte->Checked == true){WIDTH=8;} // 8 ���
    if(Sinus->Checked == true){TYPECALK=0;} // ��� �������
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
Application->Terminate(); // �������
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender){
  AnsiString A;
  int k;
  int j;
  int way=2, addon=1;  // ��� ���������� ����������
  FILE *f;
  int REQUEST=StrToInt(Edit1->Text);// ������ ����� ��������
  char *buffer = new char[2*REQUEST*(6+1)+1];   // ������� ��� ���� ������ ������� ������
  // ������������� �����������
  THarmGen GenI(REQUEST, WIDTH);
  // ���������������
  IntStrConv ArrConv(WIDTH), AddrConv(16);   // ��������������� � ����
  CoderSum ICSum;
  AnsiString TYPE;

  /////////////////////
  f = fopen("Harmonics.mif", "w+t");
  *buffer=0;
  //
  TYPE=Edit1->Text;
  Messager->Items->Add("# ���������: ����� ����� - "+TYPE+", ����������� - "+IntToStr(WIDTH));
  Messager->Perform(LB_SETHORIZONTALEXTENT,512,0);

  // ����� ����� ��������� ����������
  switch(TYPECALK){
    case 0: {
      GenI.GenSinQ();
      way = 2;  addon = 1;
    }break;
    case 1: {
      GenI.GenCosIQSin();
      way = 1;  addon = 2;
    }break;
    case 2: {
      GenI.GenCosIQNSin();
      way = 1;  addon = 2;
    }break;
  }
  Messager->Items->Add("����������� ����� ��� 'AB C' -> XY=AB+C0, � ������ ��������");
  //
  for(j = 0; j < (int)(REQUEST/(8*way)); j++){
    // ��������� �����
    AddrConv.int2hex(j*(8*way));   // ��������� � ���� �����
    strcat(buffer,AddrConv.Clast.hexrep );
    strcat(buffer," : " );
    // ��������� ������ ��� ������
    for(int i=j*(8*way)*addon; i<(j+1)*(8*way)*addon; i++){
      ArrConv.int2hex(GenI.SinCos[i]);
      // ��������� � ����
      if((i%2 == 0)&&(TYPECALK != 0))
        strcat(buffer," " );
      if(TYPECALK == 0)
        strcat(buffer," " );
      strcat(buffer,ArrConv.Clast.hexrep );
      // ��������� ����������� �����
      for(k = 0; k < WIDTH/4; k++)
        ICSum.GetHByte(ArrConv.Clast.nibble_arr[k]);
    }  // i
    // ��������� ����������� �����
    strcat(buffer,"; -- " );
    strcat(buffer,ICSum.GetConSum());
    // ��������� ������ � ����
    fprintf(f, "%s\n", buffer);
    *buffer=0;
  }  // j

  // ���� ����� ��������� �� ������ 8*way
  // ��� ��� ��� ������� ��� ���������� ����������� ���� ������������ � �������� �����
  if(REQUEST%(8*way) != 0){
    // ��������� �����
    AddrConv.int2hex(j*(8*way));   // ��������� � ���� �����
    strcat(buffer,AddrConv.Clast.hexrep );
    strcat(buffer," : " );
    for(int i=addon*j*(8*way); i<addon*(j*(8*way)+REQUEST%(8*way)); i++){  // ��������� ������
      ArrConv.int2hex(GenI.SinCos[i]);
      // ��������� � ����
      if((i%2 == 0)&&(TYPECALK != 0))
        strcat(buffer," " );
      if(TYPECALK == 0)
        strcat(buffer," " );
      strcat(buffer,ArrConv.Clast.hexrep );
      // ��������� ����������� �����
      for(k=0;k<WIDTH/4; k++)
       ICSum.GetHByte(ArrConv.Clast.nibble_arr[k]);
    }  // i
    strcat(buffer,"; -- " );
    strcat(buffer,ICSum.GetConSum());
    fprintf(f, "%s\n", buffer);
    *buffer=0;
  }  // j
  // ������������
  Messager->Items->Add("���������� ��������� � ����� Harmonics.mif");

  // ��������� ���������� � ���� ///////
  fprintf(f, "%s", "-- ����� �����: ");
  fprintf(f, "%s", TYPE.c_str());
  fprintf(f, "%s", " ; �����������:");
  fprintf(f, "%s", IntToStr(WIDTH).c_str());
  switch(TYPECALK){
    case 0:{
      fprintf(f, "%s", " ; ��� ���������� - sin");
      fprintf(f, "%s", "\n\n");
    }break;
    case 1:{
      fprintf(f, "%s", " ; ��� ���������� - cos+sin");
      fprintf(f, "%s", "\n\n");

    }break;
    case 2:{
      fprintf(f, "%s", " ; ��� ���������� - cos-sin");
      fprintf(f, "%s", "\n\n");
    }break;
  }
  // ��������� ����
  fclose(f);
  // ������� ������
  delete [] buffer;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FullByteClick(TObject *Sender)
{   // �������� �������������
     WIDTH=8; // ������ �������  �� ���� ����� ����������
     // �� ���������� �� ��� ����������
}
//-----------  --------------------------------------------------------------

void __fastcall TForm1::ByteAndHalbClick(TObject *Sender)
{     // 12 ��������
       WIDTH=12;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::TwoByteClick(TObject *Sender)
{        // ��� ����� - �����
   WIDTH=16;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SinusClick(TObject *Sender)
{
   TYPECALK=0; // ������� �����
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CosinClick(TObject *Sender)
{
   TYPECALK=1; // ������� �������+����� 
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SCosinClick(TObject *Sender)
{
   TYPECALK=2; // ������� �������-�����
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
    Messager->Clear();
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button4Click(TObject *Sender)
{
  HANDLE Handl;
  //ShellExecute(Handl, "C:\\WINDOWS\\notepad.exe", "Harmonics.mif", 0, 0, SW_SHOWNORMAL);
  ShellExecute(Handl, "open", "Harmonics.mif", 0, 0, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------

