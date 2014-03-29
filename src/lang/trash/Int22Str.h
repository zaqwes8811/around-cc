//---------------------------------------------------------------------------

#ifndef Int22StrH
#define Int22StrH
//#include <vcl.h>
#include <Classes.hpp> 	// ��� ������ � AnsiString
#include <math.h> 		// ���������� �������
#include <string.h> 	// ��������� �� ��������
#include "FileConst.h" 	// �������� ���������
#include "Claster.h"    // � �������� ������
//����� ��
//#include <stdio.h>
//#include <stdlib.h>
//#include <fstream.h>
//---------------------------------------------------------------------------

//----------
class TInt22Str // ������� �������� ����� � �������� ������ ��������
{
private:
 // ��������� ����������
	int sourse_buf;
	long Q15; // ����� ��� �������� � �������������� ���
	char pStr[2];   // ��������� ���������
	int  change[10] ; // ��� ������������ �������
	int save;  
	int j; 	// ������� � ���������� ������
	int i;	// ������� � ������-�����
 	int num_halbb; // ������
	//
	int ibuf[2];
	int tmpt;
 // ���������
	TClaster Clast; 	        // ��������� � �������
	AnsiString Out_set;     // ����� ����� ��������� �������������
public :
	// ����������� ���������� � �������� ������-������ ��������
	TInt22Str(int);   // !����������� �������� ������ ��� �������
	~TInt22Str();
	//
	class NotHex{  }; // �������������� �������� - �� �� ������� ��������� ��� ������ ����-���
        class Overflow{  }; // �������������� �������� - ������������
	// ������
	void int2hex(long);  		// ��������� ��������� ��������� �� ����� �������� �����!!!
	void hex2int(char *);   	// -"-
	void uchar2AnsiS(unsigned char); // ����������� �������������
	// ����������� ���������
	TClaster GetClaster(void); 		// ���������� �������
	AnsiString GetAnsiLine(void); 	// ���������� ������ � ���� �������� "��"
};
//-------------------------------
//1. ������� �� ����� � �������� ���
//2. ����������������
 //void IntIni(int);   // ������������� ��� ���������� int->hex
 //void HexIni(int);    //hex->int
#endif

/*  testbench
// ���������
char invtest[6]={'F', '1', '2', ':', 'A','\0'};
char *test=new char[6];
*test='\0';
int source=StrToInt(Edit1->Text);  // ��� ���������������

// ������� �������
TInt22Str Conv(StrToInt(Edit2->Text)),DeConv(StrToInt(Edit2->Text)); // �������� ��������� ������������
//
try{ // ����������� �� ����
  Conv.int2hex(source);
}
catch(TInt22Str::Overflow){
  ShowMessage("Exception(TInt22Str::Overflow):������������");
  return;
}
try{  // �������������� �� �������
   DeConv.hex2int(invtest);
}
catch(TInt22Str::NotHex){
    ShowMessage("Exception(TInt22Str::NotHex):������������ ������");
    return;
}
// �������� ����
Conv.uchar2AnsiS(static_cast<unsigned char>(179)); // �������� ���������
Edit3->Text=Conv.GetAnsiLine();     // ������� ���������
// ����������
char* bufer=Conv.GetClaster().hexrep;
int* ib=DeConv.GetClaster().nibble_arr;
for(int i=0;i<5;i++){
  int t=ib[i];
}
// ������������
 delete [] test;

*/

