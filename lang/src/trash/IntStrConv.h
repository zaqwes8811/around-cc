//---------------------------------------------------------------------------

#ifndef IntStrConvH
#define IntStrConvH
#include <vcl.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <fstream.h>
#include <stdlib.h>
#include "FileConst.h"
//---------------------------------------------------------------------------
class IntStrConv{ 

public :
// ����������� ���������� � �������� ������-������ ��������
 IntStrConv(int);   // �������� ������ ��� �������
 ~IntStrConv();

 void int2hex(long);  //
 void hex2int(char *);   // [xxxxx\0]
 struct Claster{
   // �����
   long sourse; // ���������� � �������� �����
   int  width; // ����������� ��������� �����
   // ������
   char *hexrep; // ������������ ������������� ����� 2 � 16
   int *nibble_arr; // ������������� �������
   int depth; // ����� �������� � ����-�������������
   } Clast;
};
//1. ������� �� ����� � �������� ���

//2. ����������������
 //void
 //void IntIni(int);   // ������������� ��� ���������� int->hex
 //void HexIni(int);    //hex->int
#endif

