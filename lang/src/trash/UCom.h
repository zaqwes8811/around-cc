//---------------------------------------------------------------------------

#ifndef UComH
#define UComH
#include <windows.h>
#include <Classes.hpp>
//---------------------------------------------------------------------------
class TComPorts{
 private:
  HANDLE comh;          // ���������� �����
                        // ���������, ��� �������� ������� ������ ��������� �����
 public:
  int CreatePort(AnsiString); // �������� ����� (���������� ������)
  HANDLE GetHandCom();          // ����������� �����������
  void CloseManag();            // ����� �� �����
  int LoadSettings(DCB, COMMTIMEOUTS); // ��������� �������� ������ - �����
                                // �����������
};
/* ������� ������ � �������
0. ������� ��������� ������
1. ������� ����
2. �������� ����� �����(����������� �����)��������� �� ������
3. ���� ����� ������ ���������
4. ��������� ����

*/
#endif
/*
if(ports.CreatePort(ComboBox1->Text)!= 0)            //���� ������ �������� �����
  {
   ports.CloseManag();
  // ListBox1->Items->Add("�� ������� ������� ����") ;       //������� ��������� � ������ ���������
   return;

  }
  Form1->ComboBox1->Enabled = false;
  Form1->ComboBox2->Enabled = false;
 // ���������� ��������
 timeouts.ReadIntervalTimeout = 150;	 	//������� ����� ����� ���������
 timeouts.ReadTotalTimeoutMultiplier = 15;	//����� ������� �������� ������
 timeouts.ReadTotalTimeoutConstant = 100;      //��������� ��� ������ �������� �������� ������
 timeouts.WriteTotalTimeoutMultiplier = 15;      //����� ������� �������� ������
 timeouts.WriteTotalTimeoutConstant = 150;        //��������� ��� ������ �������� �������� ������
  //������������� ��������� DCB
 dcb.BaudRate = 9600;       //����� �������� �������� 115200 ���
 dcb.fBinary = TRUE;                                    //�������� �������� ����� ������
 dcb.fOutxCtsFlow = FALSE;                              //��������� ����� �������� �� �������� CTS
 dcb.fOutxDsrFlow = FALSE;                              //��������� ����� �������� �� �������� DSR
 dcb.fDtrControl = DTR_CONTROL_DISABLE;                 //��������� ������������� ����� DTR
 dcb.fDsrSensitivity = FALSE;                           //��������� ��������������� �������� � ��������� ����� DSR
 dcb.fNull = FALSE;                                     //��������� ���� ������� ������
 dcb.fRtsControl = RTS_CONTROL_DISABLE;                 //��������� ������������� ����� RTS
 dcb.fAbortOnError = FALSE;                             //��������� ��������� ���� �������� ������/������ ��� ������
 dcb.ByteSize = 8;                                      //����� 8 ��� � �����
 dcb.Parity = 0;                                        //��������� �������� ��������
 dcb.StopBits = 0;                                      //����� ���� ����-���
 //
 int key=ports.LoadSettings(dcb,timeouts);
 if(!key){ // ����� �� ������ ���������
    switch(key){   // �������� �����
      case 1:{
        ports.CloseManag();
       ListBox1->Items->Add("�� ������� ������� DCB");
        return;
      } 
      case 2:{
        ports.CloseManag();
        ListBox1->Items->Add("�� ������� ���������� DCB");
        return;
      }
      case 3:{
        ports.CloseManag();
        ListBox1->Items->Add("�� ������� ���������� ����-����");
        return;
      }
    }
 }
 // ��� ������
 Form1->Shape1->Brush->Color=clLime;//
 Form1->Label3->Caption="���� ������";
 //-----
 //������� ��� ������� ������������ ���� ��� ������ ����������� ������
 handle = open("test.txt", O_CREAT | O_APPEND | O_BINARY | O_WRONLY, S_IREAD | S_IWRITE);

 if(handle==-1)		//���� ��������� ������ �������� �����
  {
   //ListBox1->Items->Add("������ �������� �����");	//������� ��������� �� ���� � ��������� ������
   //Form1->CheckBox3->Checked = false;                                   //�������� � ��������� �������
  // Form1->CheckBox3->Enabled = false;
  }
 else { //ListBox1->Items->Add("���� ������ �������");
 } ////����� ������� � ������ ��������� ��������� �� �������� �������� �����
 // ��� ����� �� ����
 PurgeComm(ports.GetHandCom(), PURGE_RXCLEAR);	//�������� ����������� ����� �����
 // !! ������
 reader = new ReadThread(true);	                //������� � ��������� ����� ������ ������
 reader->Resume();
 reader->FreeOnTerminate = true;                //���������� ��� �������� ������, ����� �� ������������� ����������� ����� ����������

 writer = new WriteThread(true);                //������� ����� ������ ������ � ����
 writer->FreeOnTerminate = true;                //���������� ��� ��������, ����� ����� ������������� ����������� ����� ����������

 //------
 }else{  // ���� ���������
 SpeedButton2->Caption="������� ����";
 Form1->ComboBox1->Enabled = true;
  Form1->ComboBox2->Enabled = true;
  ports.CloseManag();
  //Mport=0; // �����
  Form1->Shape1->Brush->Color=clRed;
  Form1->Label3->Caption="���� ������";
   //���� ����� ������ ����������, ������ ��� ������� �� ���������� � ��������� ���, ����� �� �������� ����������;
 if(writer) //�������� if(writer) �����������, ����� ��������� ������;
  {
   writer->Terminate();
   writer->Resume();
  }

 if(reader)reader->Terminate();         //���� ����� ������ ��������, ��������� ���; �������� if(reader) �����������, ����� ��������� ������
 close(handle);				//������� ���� ��� ������ ����������� ������
 handle=0;				//�������� ���������� ��� ����������� �����

 }        
}
//---------------------------------------------------------------------------
//���������� �������� �����
void __fastcall TForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
 if(reader)reader->Terminate(); 	//��������� ����� ������ �� �����, �������� if(reader) �����������, ����� ��������� ������
 if(writer)writer->Terminate();         //��������� ����� ������ � ����, �������� if(writer) �����������, ����� ��������� ������
 if(ports.GetHandCom())ports.CloseManag();       //������� ����
 if(handle)close(handle);               //������� ����, � ������� ������ ������ ����������� ������

}
*/
