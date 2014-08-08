//---------------------------------------------------------------------------


#pragma hdrstop

#include "UCom.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
int TComPorts::CreatePort(AnsiString namecom){  // �������� ����
  comh = CreateFile(namecom.c_str(),  // ��������� ����
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_FLAG_OVERLAPPED,
        NULL);
  // �������� �� ������
  if(comh == INVALID_HANDLE_VALUE)            //���� ������ �������� �����
  {
     return(1); // ������ ��������
  }
  return(0); // ������ ��������
}
//---------------------
void TComPorts::CloseManag(){  // ���������
     CloseHandle(comh);
     comh=0;
}
//---------------
HANDLE TComPorts::GetHandCom(){ // ������ ����������� ����������
  return(comh);
}
//---------------------------------------
int TComPorts::LoadSettings(DCB dcb, COMMTIMEOUTS timeouts){  //
  dcb.DCBlength = sizeof(DCB);  //� ������ ���� ��������� DCB ���������� ������� � �����, ��� ����� �������������� ��������� ��������� ����� ��� �������� ������������ ���������  GetCommState(comh, &dcb);
  //������� ��������� DCB �� �����
 if(!GetCommState(comh, &dcb))
  {
   CloseManag(); //���� �� ������� - ������� ���� � ������� ��������� �� ������ � ������ ���������
   return(1);  //
  }
  // ���������
  if(!SetCommState(comh, &dcb))	//���� �� ������� - ������� ���� � ������� ��������� �� ������ � ������ ���������
  {
   CloseManag();
   return(2);
  }
  //�������� ��������� ��������� � ����
 if(!SetCommTimeouts(comh, &timeouts))	//���� �� ������� - ������� ���� � ������� ��������� �� ������ � ������ ���������
  {
    return(3);
  }
 //���������� ������� �������� ����� � ��������
 SetupComm(comh,2000,2000);
 // ��� ������ �������
 return(0);
}
