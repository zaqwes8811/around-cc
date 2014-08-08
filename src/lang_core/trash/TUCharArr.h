//---------------------------------------------------------------------------

#ifndef TrRsH
#define TrRsH
#include <Classes.hpp>
#include <math.h>
//---------------------------------------------------------------------------
class TUCharArr{
public:
   unsigned char cSum[2]; // ��� ����������� �����
   char store[255]; // ���������
   // metods
   TUCharArr();
   void GetConSum(unsigned char*, int);  // ��������� ������������ �����
     // �������� �����������������
     // !������ ������������������ ����� ��������� ������� �������
   int StrToUnsCharAr(AnsiString); // ����������� ���� ������ � ������ ���(����������)
     // !����� strcat ��������� ������ � �� ������
   int AddCoSum();
   // ����� �������� ������� ��������� ��������������
private:
  int pos;      // ������� � �������� ������
  int posint;   // ������� � ��������������� ������
  int longL;    // ������ �������� ������
  unsigned char bait;   // ��� ������ ���������������� �������
  int buf;              // ��������� �������� int-������������� ���������������� �����
  int akk; // �����������
};
#endif
/* testbench
int key=name.StrToUnsCharAr("sdf");
switch(i)
{
case 0:{}break;
}

*/
