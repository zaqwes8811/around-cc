//---------------------------------------------------------------------------


#pragma hdrstop

#include "IntStrConv.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
IntStrConv::IntStrConv(int width){
  Clast.hexrep=new char[width/4+1];
  Clast.nibble_arr=new int[width/4];
  Clast.width=width;
}
//-----------------------
IntStrConv::~IntStrConv(){
 delete [] Clast.hexrep;
 delete [] Clast.nibble_arr;
}
//--------------------------
void IntStrConv::hex2int(char *buf){
Clast.hexrep=buf;
  int i=0, j=0;
  while(Clast.hexrep[j] != '\0'){
    while(Clast.hexrep[j]!=HEX_DI_KEY[i]){
      i++;
      if(i > 16){
      i=16;
      break;} // ��� ������� ������
    }
  Clast.nibble_arr[j]=i;
  j++ ;
  i=0;
  }
  Clast.depth=j;
}
//------------------------------
void IntStrConv::int2hex(long sourse){
    Clast.sourse = sourse; // ��������� ������
    int sourse_buf = sourse;
     // 2. �������������� ����������� ������� ������
     // ��� ������������� ��������� � �������������� ���
     long Q15=pow(2,(Clast.width-1));
     if(sourse_buf < 0){
          sourse_buf=2*Q15+sourse_buf; //  ��������� �������������� ���, �� ����� - uint
     }
      char pStr[2];   // ��������� ���������
      int  change[10] ; // ��� ������������ �������
      int num_halbb=Clast.width/4;    // ����� �������� � ����������������� �������������
      Clast.depth=num_halbb;
      int save=0,  j=0;
      // init
      Clast.hexrep[0]='\0' ;
      pStr[1]='\0';// �������� � �� �����, �� ���� ���������
      for(int i=0; i<num_halbb; i++){//while(test != 0){ // ���� �� ������ ����
         save=sourse_buf%16; // ������ �������� ������
         change[num_halbb-i-1]=save;    // �� 0-15
         sourse_buf=sourse_buf/16;  // ����� ��� �������� �� ��������� ��������
         }
      // ����������� � ������� ��������
      
      for(int i=0; i<num_halbb; i++){
           while(change[i]!= j){   // ����������� �� ������� ��� �������
           j++;
           }
           Clast.nibble_arr[i]=j;
           pStr[0] = HEX_DI_KEY[j];
           j=0; // ����������� ���������
            strcat(Clast.hexrep,pStr);
      }

 }
 //----------------------------------
   // ��� ���������������� ���
/*void IntStrConv::IntIni(int width){
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
