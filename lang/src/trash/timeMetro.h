/**
  File: timeMetro.h

  Abstract:
    ������ ��������������� ��� ���������(���������� �������
    ��� ��� ����-����)

  Nib:
    - ��������� �������� ���������� ����
*/
#ifndef timeMetroH
#define timeMetroH
// libs ///
#include <windows.h>

class intervalsMetro {
  LARGE_INTEGER timerFrequency;
  LARGE_INTEGER timerStart;
  LARGE_INTEGER timerStop;
public:
  intervalsMetro();
};
/**
  Abst.: ����� ��� ��������� ��������� ����������
*/


#endif
 