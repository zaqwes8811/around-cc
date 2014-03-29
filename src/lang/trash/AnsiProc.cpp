//---------------------------------------------------------------------------


#pragma hdrstop

#include "AnsiProc.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
//---- ����������� --------------
TAnsiProc::TAnsiProc(){
   pos=0, posint=0,akk=0;
}
// ================ char ������� � ���� �������������
 void TAnsiProc::uchar2AnsiS(void){ 	// ����������� ������� � ���� ����� ������
	AOut=""; 		// ����������
	// ��������� �����
	ibuf[1]=tmp%16; 	// ������� ���� ������� ������ �������� �������
	tmp/=16;
	ibuf[0]=tmp%16;
	// ����������	
	if(ibuf[0]>9) // ��������� ������ ������� 
	{ 		
		switch(ibuf[0])
		{
			case 10: AOut+="A"; break;
			case 11: AOut+="B"; break;
			case 12: AOut+="C"; break;
			case 13: AOut+="D"; break;
			case 14: AOut+="E"; break;
			case 15: AOut+="F"; break;
		}
	} else {
		AOut+=IntToStr(ibuf[0]);
	}
	if(ibuf[1]>9)
	{ // ������ �������
		switch(ibuf[1])
		{
			case 10: AOut+="A"; break;
			case 11: AOut+="B"; break;
			case 12: AOut+="C"; break;
			case 13: AOut+="D"; break;
			case 14: AOut+="E"; break;
			case 15: AOut+="F"; break;
		}
	}
	else
	{
		AOut+=IntToStr(ibuf[1]); // ������ ��������
	}
 }
//------------------------
AnsiString TAnsiProc::GetAnsiLine(unsigned char buf){ 	// ���������� ������ � ���� �������� "��"
  tmp=static_cast<int>(buf);
  uchar2AnsiS(); // �������� ���������
  return(AOut);
}
//-------------------------------------------------
void TAnsiProc::StrToUnsCharAr(void){
  pos=0, posint=0,akk=0; // �������� ������� - �� ����� ����������
  // ����������� �� ����������� ������ 256 ����
   if(Abuf.Length() > 255){     // �������� ������� ������� �������
       throw NotHex();		// ������� ������� ������
   }
  strcpy(store, Abuf.c_str());  // ���� ��� ��������
  // ����� ��� �� ��������� �� ������
  longL=strlen(store); // ����� ��������, �� ����������������� ��������
  if(longL==0){
        throw NotHex();  //"��� ������ ��� ��������";
  }
  if(longL%3 != 2){      // "AB_FD_AS"
        throw NotHex();  // ������������ ������
  }
  // ��������������� �������� �������� � ������
  // ������������� ����� ������ ��� ���������  ���������� ����������
  longL=(int)(longL/3)+1; // ����� ��� ������ � ���� ���� ���� ���� � �������
  sour=new unsigned char[longL+1];
    for(int i=0;i<longL+1;i++)sour[i]=0;// ��������, ���� ����� � �� �����

  //  store - ���� ��� ���������� ������
  while(store[pos] != 0){ // ����� � for �.�. ���������������
  	if(store[pos] == ' ')pos++; // ����� ������ � ����������
  	int i=0, j=0, k=1;
  	for(j=0;j<2;j++){ // ����� ������
  	  while(store[pos] != KEY[i]){  // �������� �� ����� ���������� � ����� switch
  	     i++;
  	     if(i==16){ // ������ �� ������
  	        delete [] sour;
		throw NotHex();  // ������� ��� �� �� ��
  	     }
  	   }
           //
  	   akk+=i*(unsigned int)(pow((float)(16),k));// ��������� � �����������
  	   i=0; // ��� ������ �� �����
  	   k--;
  	   pos++;
  	} // ���� �������������
  	sour[posint]=static_cast<unsigned char>(akk); // ��������� � ��������
        akk=0; // ���������� ����������
  	posint++;
	}
  sour[posint]='\0'; // ���������� ������

  // ������ ��������� ������ ��� ��������
  for(int i=0;i<longL+1;i++){ 	// ��������� � �������� �������
      store[i]=sour[i]; 	// �������� ������ ��������
   }
  // ������� ������������ �������, �� ��� ������������
  delete [] sour; // !! ������� ����� ���������
  sour=NULL;
}
//--------- ��������� ����������� ����� ��� ������������� ������� ������� -------------------------
unsigned char TAnsiProc::GetConSum(unsigned char *bufer, int len){
  akk=0;
  for(int i=0;i<len;i++){
     akk+=static_cast<unsigned int>(bufer[i]);
  }
  SumIn=static_cast<unsigned char>(akk%256);
  return(SumIn);
}
//---- ���������� �������� ����������� ����� -------
unsigned char TAnsiProc::GetConSum(void){
   GetConSum(store, longL); // ��������� ����������� ����� ���������� �����
   // ��� ������ ��������� �� ������� ������
   // �� ����� �������� �� ��������� � ������
   Sum=SumIn;
   return(Sum);
}
//----------------------------------------------------------
void TAnsiProc::AddCoSum(){
  GetConSum(store, longL);      // ��������� ����������� ����� ���������� �����
  Sum=SumIn;                    // �������� �� ����������
  store[longL]=Sum;             // ��������
  longL++;  // ! �����
}
//=============== ��������� ������������ ������� ===================
unsigned char *TAnsiProc::Astr2UCstr(AnsiString Ainput){
/*
1. ��������� ������ �� ���������� ������� ������
2. �����������
*/
 Abuf=Ainput;
 StrToUnsCharAr();
 return(store);
}
//
unsigned char *TAnsiProc::Astr2UCstr_cs(AnsiString Ainput){
/*
1. ��������� ������ �� ���������� ������� ������
2. �����������
3. ��������� ����������� �����
4. ���������� � ����� 
*/
 Abuf=Ainput;
 StrToUnsCharAr();
 AddCoSum();   // ��������� ������
 return(store);
}
//--- ���������� ������ --
int TAnsiProc::GetLenSend(void){
  return(longL);
}
//  ��������� ��������� � ������� ����������� �����
bool TAnsiProc::Compary_cs(void){
  if(Sum == SumIn){
  return(true);
  }else{
  return(false);
  }
}
//--------------------
AnsiString TAnsiProc::FloatToInt(AnsiString Temp)
{

Abuff="";
len=Temp.Length();
for(jj=1;jj<len+1;jj++){
   if((Temp[jj] == ',')||(Temp[jj] == '.')){
    Temp.Delete(jj,1); // ������ � ������� ����������
    jj--;
    len--;
   }
  }
 Abuff+=Temp;
 return(Abuff);
}
/////


