//---------------------------------------------------------------------------

#ifndef ConSumH
#define ConSumH
#include "FileConst.h"
#include <string.h>
//---------------------------------------------------------------------------
class ConSum{ // ���� ����������� �������������
                // ���� ���� ���������� � ����������������� ��������
                // �� ������������� �������� ����
public:
  ConSum(); 	// �����������
  void LoadHByte(int);     	// ����� �� int
  void LoadChar(char );   	// �� ������� ����
  char *GetConSum(); 	// ���������� �������������������� ������ �� ���.
						// ����� ������������
// ����������
  class NotHex{  };						
private:
  int ind;      // ��������� ���� ���������� ���������; �����. �������
  int carry;    // ������� �� ��������
  int SAH;  // ���������� ��� �������� �������
  int SAL;  // ���������� ��������
  char pStrH[2];
  char pStrL[2];
  int j;
  int cout; // ������� ���������� �� ������ ��������
  int chbuf; // ������ ��� ����� ��� ��������� ���������� ��������
};
#endif

/* testbench
char *p;
CoderSum ConSum; // ����������
int array[7]={1,1,15,15,15,15,15};
for(int i=0;i<7;i++){
ConSum.LoadHByte(array[i]);
}
p=ConSum.GetConSum();
*/
