//---------------------------------------------------------------------------

#ifndef GenHarmH
#define GenHarmH
#include <vcl.h>
#include <math.h>

#include "FileConst.h"
//---------------------------------------------------------------------------
class THarmGen{
public:
   THarmGen(int, int);//
  ~THarmGen();
  struct Claster{
    int NumPoint; // ������         // ����� ����� ��� ���� �������� ����
    int Width;            // ����������� ������ - �������� 16
  } Clast;
  // ���������� ������� � �����������
  void GenSinQ();
  void GenCosIQSin();
  void GenCosIQNSin(); // ����������������� ��������(I-QIQ) ������������������ ��������� ���� � ���� �������  � ������
   int *SinCos;
private:
  int Q15;
  int j;
};
// ������������������ ����� ������� ��� ��������� ������ � ������������
//void GenIni(int size_air, int width_air);
#endif
