//---------------------------------------------------------------------------
#ifndef AnsiProcH
#define AnsiProcH
//---------------------------------------------------------------------------
#include <Classes.hpp> 	// ��� ������ � AnsiString
#include <math.h>
#include "FileConst.h" //  ���������
#include "IntStrConv.h"
//---------------------------------------------------------------------------
// ������ �������� ����������� �������� � ���������� �����
class TAnsiProc // 
{
private:
        // �������������� ������ ������� uchar -> HL
        int tmp;		// ��������������� ������ ���
        int ibuf[2]; 	        // ��� ���������� ��������
	AnsiString AOut;        // ����� ����� ��������� �������������
	void uchar2AnsiS(void); // ����������� �������������
        // �������������� ��� ����� ������
	int akk; 			// �����������
        long lakk;
	unsigned char Sum; 	        // ��� ����������� �����
        unsigned char SumIn; 	// ��� ����������� �����
        // ?? ������������� ��� ���� ��� ���� ��� ��������
	unsigned char store[255]; 	// ������ ���������� ��������������
        // ��� �� �������� ����������� ���������(���� ������ �������� ������ ��������� �������)
	unsigned char *sour;            // ��������� �� ���� ������������ ������
	AnsiString Abuf;		// �������� ������
        int longL;    	// ������ ��������������� ������(����� ��������)
        // ������
        int len;
        int jj;
        int pos;      	// ������� � �������� ������
        int posint;   	// ������� � ��������������� ������
	// ������
	void StrToUnsCharAr(void); 	// ����������� �������. �� ���������� ������ ���
	void AddCoSum(void); 		// ��������� ����������� �����
        AnsiString Abuff;
public :
        AnsiString FloatToInt(AnsiString); // ������� �� ������ "����" ������� ��� ����� 
	TAnsiProc();
        AnsiString GetAnsiLine(unsigned char); 	// ���������� ������ � ���� �������� "��"
	unsigned char GetConSum(unsigned char*, int);  // ��������� ������������ ����� ��������� ������������ �������
                                // ������ �������� �� ������� ������ SumIn
	unsigned char GetConSum(void);  // ��������� ������������ ����� ��������� ������������ �������
                                // ������ ������ �� ����������� �������
        bool Compary_cs(void);  // ���������� ������� � ���������� ����������� �����
        // !����� strcat ��������� ������ � �� ������
	unsigned char *Astr2UCstr(AnsiString);     // ����������� ���� ������ � ������ ����������� ���(XX_XX->uchar[])
        unsigned char *Astr2UCstr_cs(AnsiString);  // �� ��, �� � ���������� ����������� �����
	int GetLenSend(void); // �.�. ������� ����� ��������� ������� �����, �� ������ ������ �����
        unsigned char *GetStat(void);
	// ����������
        // ���� �� ��� � ������� � ������������ ������ ������
	class NotHex{  }; // �������������� �������� - �� �� ������� ��������� ��� ������ ����-���
};
/* ���� �������
  Astr2UCstr -> (GetConSum,GetLenSend)
  Astr2UCstr_cs -> GetLenSend
  GetConSum(������� ������) - ���������
*/
/* testbench � �������������
TAnsiProc AnsiProc;
AnsiString Ainput=Edit3->Text;
unsigned char rd[]={static_cast<unsigned char>(171), static_cast<unsigned char>(69)};
///*
unsigned char *ucbuf;
try{  // ������� ����������
  ucbuf=AnsiProc.Astr2UCstr_cs(Ainput);
}
catch(TAnsiProc::NotHex){
// ��������� ��������� ������ �� ����������� �������
}
//
int tmp;
//unsigned char cs = AnsiProc.GetConSum();
unsigned char csIn = AnsiProc.GetConSum(rd,2);
bool test =AnsiProc.Compary_cs();
//tmp=static_cast<int>(cs);
int len = AnsiProc.GetLenSend();
for(int i=0;i<len;i++){
   tmp=static_cast<int>(ucbuf[i]);
} //
Edit2->Text=IntToStr(static_cast<int>(ucbuf[len-1]));
//

unsigned char cbuf=static_cast<unsigned char>(StrToInt(Edit2->Text));
AnsiString AinpuXX=AnsiProc.GetAnsiLine(cbuf);
Edit1->Text=AinpuXX;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
  AnsiString Settings="";
  TAnsiProc AnsiProc;
  TIntStrConv IntStrConv(4);
  Edit5->Text=AnsiProc.FloatToInt(Edit4->Text);
  int ifreq;
  try{
     ifreq=StrToInt(Edit5->Text);
  }catch(const EConvertError &){
  ShowMessage("������������ ������");
  return;
  }


  // ���������  �� ��������� �����
   int buf_array[8];
    for(int i=0;i<8;i++){ // ������ ����� ������
       buf_array[7-i]=ifreq%10;
       ifreq/=10;
    }
  // �����������
     for(int i=0;i<8;i++){ // ������������ ��������
       IntStrConv.int2hex(buf_array[i]);
       Settings+=AnsiString(IntStrConv.Clast.hexrep);
       if(i%2 !=0)Settings+=" ";
    }
    Edit1->Text=Settings;
*/
#endif
