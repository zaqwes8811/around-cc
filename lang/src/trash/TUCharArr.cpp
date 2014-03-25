//---------------------------------------------------------------------------


#pragma hdrstop

#include "TrRs.h"
#include "FileConst.h" //  ���������

//---------------------------------------------------------------------------

#pragma package(smart_init)
//---- ����������� --------------
TUCharArr::TUCharArr(){
   pos=0, posint=0,buf=0;
}
//-------------------------------------------------
int TUCharArr::StrToUnsCharAr(AnsiString bufe){
  pos=0, posint=0,buf=0; // �������� ������� - �� ����� ����������
  // ����������� �� ����������� ������ 256 ����
  strcpy(store, bufe.c_str());  // ���� ��� ��������
  // ����� ��� �� ��������� �� ������
  longL=strlen(store); // ����� ��������, �� ����������������� ��������
  if(longL==0){
     //"��� ������ ��� ��������";
     return(0);  // ����� �� �����������
  }
  if(longL%3 != 2){ // "AB_FD_AS"
        //ShowMessage("������� ������ � ����� ������");
  	return(1); // ����� �� �����������
  }
  // ������������� ����� ������ ��� ���������  ���������� ����������
  longL=(int)(longL/3)+1; // ����� ��� ������ � ���� ���� ���� ���� � �������
  unsigned char *sour=new unsigned char[longL+1];
  for(int i=0;i<longL+1;i++)sour[i]=0;// ��������, ���� ����� � �� �����
  //  sour - ���� ��� ���������� ������
  while(store[pos] != 0){ // ����� � for �.�. ���������������
  	if(store[pos] == ' ')pos++;
  	// calc begin
  	int i=0, j=0, k=1;
  	for(j=0;j<2;j++){ // ����� ������
  	  while(store[pos] != KEY[i]){
  	     i++;
  	     if(i==16){
  	       // ShowMessage("�������� ������ ������");
  	        delete [] sour;
  	        return(2);
  	     }
  	   }
  	   buf+=i*(unsigned int)(pow((float)(16),k));// ��������� � �����������
  	   i=0; // ��� ������ �� �����
  	   k--;
  	   pos++;
  	}
  	bait=static_cast<unsigned char>(buf);
  	sour[posint]=bait;
        buf=0;
  	posint++;
	// end of calk
	}
	sour[posint]='\0'; // ���������� ������
        // ����� ���� ������� ������� � ������ ����� ������
// ������ ��������� ������ ��� ��������
   if(posint > 255){  // �������� ������� ������� �������
      // ShowMessage("������ �� ������� �� ������� ������");
       return(3);
   }
   for(int i=0;i<longL+1;i++){ // ��������� � �������� �������
      store[i]=sour[i];
   }
// ������� ������������ �������, �� ��� ������������
  delete [] sour;
  return(longL);
}
//---------------------------------------------------------
void TUCharArr::GetConSum(unsigned char *bufer, int len){
  cSum[1]='\0';
  akk=0;
  for(int i=0;i<len;i++){
     akk+=static_cast<unsigned int>(bufer[i]);
  }
  cSum[0]=static_cast<unsigned char>(akk%256);
}
//----------------------------------------------------------
int TUCharArr::AddCoSum(){
  GetConSum(store, longL); // ��������� ����������� �����
  // longL - ��������� �� ������� ���� ������
  store[longL]=cSum[0]; // ��������
  return(longL+1);
}
