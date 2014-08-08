//---------------------------------------------------------------------------


#pragma hdrstop

#include "Int22Str.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
TInt22Str::TInt22Str(int width)
{
  Clast.hexrep=new char[width/4+1]; 	// �����
  Clast. nibble_arr=new int[width/4];	// !
  Clast.width=width;
}
//-----------------------
TInt22Str::~TInt22Str()
{
 delete [] Clast.hexrep;
 delete [] Clast.nibble_arr;
}
//--------------------------
void TInt22Str::hex2int(char *buf)	// ��������� ������ � ������������ ������
{ 
	Clast.hexrep=buf;
	i=0, j=0;
	while(Clast.hexrep[j] != '\0'){ // ������ � �00 ����� ���������� �� � �48 ��� ����� ���������
		while(Clast.hexrep[j]!=HEX_DI_KEY[i]){
			i++;
			if(i > 15){ // ��� ������� ������
				throw NotHex(); // ����������: ������ ����� �� ������� ������
			} 
		}
	Clast.nibble_arr[j]=i; // ���������� ������
	j++;
	i=0; 
	}
	Clast.depth=j; // ���������� ����� ��������
}
//------------------------------
void TInt22Str::int2hex(long sourse)
{
    Clast.sourse = sourse; // ��������� ������
    sourse_buf = sourse;
    // ��� ������������� ��������� � �������������� ���
    Q15=pow(2,(Clast.width-1));
    if((sourse >= Q15)||(sourse < -Q15)){
       throw Overflow(); // ��������� ���������� return �������� �.�. ���� �����. void
    }
    if(sourse_buf < 0)
	{
        sourse_buf=2*Q15+sourse_buf; //  ��������� �������������� ���, �� ����� - uint
    }
    num_halbb=Clast.width/4;    // ����� �������� � ����������������� �������������
    Clast.depth=num_halbb;
    save=0,  j=0;
    // init
    Clast.hexrep[0]='\0' ;
    pStr[1]='\0';// �������� � �� �����, �� ���� ���������
    for(int i=0; i<num_halbb; i++)
	{
        save=sourse_buf%16; 			// ������ �������� ������
        change[num_halbb-i-1]=save;    // �� 0-15
        sourse_buf=sourse_buf/16;  	// ����� ��� �������� �� ��������� ��������
    }
    // ����������� � ������� ��������
    for(int i=0; i<num_halbb; i++)
	{
        while(change[i]!= j) // ����������� �� ������� ��� �������
		{  
			j++;
        }
        Clast.nibble_arr[i]=j;
        pStr[0] = HEX_DI_KEY[j];
        j=0; // ����������� ���������
        strcat(Clast.hexrep,pStr);
    }
 }
//----------------------------------
void TInt22Str::uchar2AnsiS(unsigned char buf){ 	// ����������� ������� � ���� ����� ������
	Out_set=""; 		// ����������
	tmpt=static_cast<int>(buf);
	// ��������� �����
	ibuf[1]=tmpt%16; 	// ������� ���� ������� ������ �������� �������
	tmpt/=16;
	ibuf[0]=tmpt%16; 	// ������� � ������
	if(ibuf[0]>9)
	{ 		// ��������� ������ ������� 
		switch(ibuf[0])
		{
			case 10: Out_set+="A"; break;
			case 11: Out_set+="B"; break;
			case 12: Out_set+="C"; break;
			case 13: Out_set+="D"; break;
			case 14: Out_set+="E"; break;
			case 15: Out_set+="F"; break;
		}
	} else {
		Out_set+=IntToStr(ibuf[0]);
	}
	if(ibuf[1]>9)
	{ // ������ �������
		switch(ibuf[1])
		{
			case 10: Out_set+="A"; break;
			case 11: Out_set+="B"; break;
			case 12: Out_set+="C"; break;
			case 13: Out_set+="D"; break;
			case 14: Out_set+="E"; break;
			case 15: Out_set+="F"; break;
		}
	}
	else
	{
		Out_set+=IntToStr(ibuf[1]); // ������ ��������
	}
 }
 //------------------------------
TClaster TInt22Str::GetClaster(void){		// ���������� �������
  return(Clast);
}
//------------------------
AnsiString TInt22Str::GetAnsiLine(void){ 	// ���������� ������ � ���� �������� "��"
  return(Out_set);
}

/*

void IntStrConv::IntIni(int width){
// ����������� ��� ������ �����
  Clast.width=width;
  Clast.hexrep=new char[width/4+1];
  Clast.nibble_arr=new int[width/4];
}
void IntStrConv::HexIni(int width){
 // ������������� ��� ����� ������ � hex������
  Clast.width=width;
  Clast.hexrep=new char[width/4+1];
  Clast.nibble_arr=new int[width/4];
} */
