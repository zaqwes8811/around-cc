 //������ ������������������
 /*if(tmplen != 0){
 
// ����������� ����
   counter=0;// ��������� �������
   Timer1->Enabled=false;
   // ������� �������
   PurgeComm(COMport, PURGE_TXCLEAR);             //�������� ���������� ����� �����
   char otvet[100];  // ��� ������
   int sakk=0;    // ��� ����������� �����
   int j=0;
   lensend=0;
   for(j=0;j<20;j++){
     sakk++;
     otvet[j]=static_cast<char>(1);
     lensend++;  // ���� ��������
   }
   sakk=sakk%16;
   otvet[j]=static_cast<char>(sakk);
   lensend++; // �� ����������� ������
   // �������� ����� ������
   memset(bufwr,0,BUFSIZE);// ������� �����
   int i=0;
   for(i=0;i<lensend+1;i++){      // ����������
     bufwr[i]=otvet[i];
   }
   bufwr[i]='\0';  // �� ������� ������
   i=0;
   // start stream
  writer->Resume();	//������������ ����� ������ � ����

  ////////////////////\\
  if((static_cast<int>(bufrd[0])==0)&& (slaver==0)){ // ������� ������ ���������
    // ������� ��������� � ������ �������
    slaver=1;// ��������� � ����� slave
    AnsiString bufe="12 1A";
    lensend=StrToGlobBufw(bufe,bufwr);
 }
 //////////////////////
 
 ///!!
 /*if(Form1->CheckBox4->Checked == true){ // ������� �������� �����
 //========  ����� ���������� ��������� ==========
  if((bufrd[0]=='\0') && (cycle == 1)){ // � �������� ������
   GetStateSl();   // ����� �� ������� ������-���������
   if(stageState == 0)stageState=1; //
   }
 // ������� ����������� �����
   if((stageState == 1) && (cycle == 2)){
     McSum[1]='\0';
     getCSumChArr(bufrd, tmplen-1,McSum); // ����� ������ �������������� �������
     if(McSum[0]==bufrd[tmplen-1]){
      // ShowMessage("��");
     }
     stageState=0; //stageState=0;
   }
 //=============
 if(static_cast<unsigned int>(bufrd[0])== 1 && (cycle == 1)){ // � �������� ������
   GetSetSl();     // ������ ��������� ���������
   if(stageSet == 0)stageSet=1; //
 }
   // ������� ����������� �����
   if((stageSet == 1) && (cycle == 2)){
     McSum[1]='\0';
     getCSumChArr(bufrd, tmplen-1,McSum);
     if(McSum[0]==bufrd[tmplen-1]){
       int i=0;
     }
     stageSet=0; //stageState=0;
   }

 //=====================
 if((static_cast<unsigned int>(bufrd[0])== 2)&&(cycle == 1)){
 // � �������� ������ (���-����� ����������)
   Echo2();
 }
 
 // ========== �������� ���������� ==========
  if((static_cast<unsigned int>(bufrd[0])== 3)&&(cycle == 1)){
 // � �������� ������ (���-����� ����������)
   Echo3();
 }
 if((static_cast<unsigned int>(bufrd[0])== 3)&&(cycle == 2)){ // ��������� ������� ���
 // � �������� ������ (���-����� ����������)
   LoadSet();  // �������� ���������� ���������
 }
 // ��� ����� �� �������� �����
  if(cycle == 3){ // ��������� ������ ������ ����������� �����
 // � �������� ������ (���-����� ����������)
   Check(bufrd, tmplen);  // �������� ���������� ���������
}
 if(cycle == 4){ // ��������
 // � �������� ������ (���-����� ����������)
    if(bufrd[0]==McSum[0]){
      //ShowMessage("�������� ������ �������");
    }
 }
 }else{// ����� �������
   // ��������� ����� ����� ��������
   if(cycle == 1){  // �� ����� ��������� ����
     // ��������� ����������� �����
     McSum[1]='\0';
     getCSumChArr(bufrd, tmplen-1,McSum);
     if(McSum[0]!=bufrd[tmplen-1]){
       ShowMessage("������ ����� � �����������");
     }
     // ���������� ���������
     AnalyseState();
   //}
   }
   //  ��������� ���������
   if(cycle == 2){  // �� ����� ��������� ����
      //void AnaluseSet(void){
   }
   //  ��� ��� �������� ����������
   if(cycle == 3){  // �� ����� ��������� ����
     if((static_cast<unsigned int>(bufrd[0])== 2)){ // �������� ���

     }
   }
   //  ��� ��� ����� ����������
   if(cycle == 4){  // �� ����� ��������� ����
     if((static_cast<unsigned int>(bufrd[0])== 3)){ // �������� ���
        LoadSet();
     }
   }
   if(cycle == 5){  // �� ����� ��������� ����

   }
 }
*/

\\\\\\\\\\\\\\\\\\\\\\\\

//=================================
// ------------ slave---------------
/*
void GetStateSl(){  // �������� ��������� ����������
  // ������� �������
  PurgeComm(COMport, PURGE_TXCLEAR);             //�������� ���������� ����� �����
  memset(bufwr,0,BUFSIZE);// !! ������� �����
  // �������
  AnsiString SendMax="12 00 C1 01 02 01 02 09";
  lensend=StrToGlobBufw(SendMax,bufwr,255) ;    // ����������� � ������ �������
  // ������� ����������� �����
  unsigned char cSum[2]; // ����� ��� ����������� �����
  getCSumChArr(bufwr, lensend, cSum);
  bufwr[lensend]=cSum[0];   // �.�. ����� ���� ���� ����� ������ ���, � �� ��������
  lensend++;
  //
  writer->Resume();	//������������ ����� ������ � ����
}
//---------------------
void GetSetSl(void){ // ������� ��������� ���������(slave)
  PurgeComm(COMport, PURGE_TXCLEAR);             //�������� ���������� ����� �����
  memset(bufwr,0,BUFSIZE);// !! ������� �����
  // �������
  AnsiString SendMax="12 01 00 C1 02 01 02 09 11 11 A1";
  lensend=StrToGlobBufw(SendMax,bufwr, 255) ;    // ����������� � ������ �������
  // ������� ����������� �����
  unsigned char cSum[2];
  getCSumChArr(bufwr, lensend, cSum);
  bufwr[lensend]=cSum[0];   //
  lensend++;
  //
  writer->Resume();	//������������ ����� ������ � ����
}
//--------------
void Echo2(void){ // ������ �������
  PurgeComm(COMport, PURGE_TXCLEAR);             //�������� ���������� ����� �����
  memset(bufwr,0,BUFSIZE);// !! ������� �����
  // ���-�������
  AnsiString SendMax=LOAD_MOD;
  lensend=StrToGlobBufw(SendMax,bufwr,255) ;    // ����������� � ������ �������
  writer->Resume();	//������������ ����� ������ � ����
}
//--------------
void Echo3(void){ // ������ �������
  PurgeComm(COMport, PURGE_TXCLEAR);             //�������� ���������� ����� �����
  memset(bufwr,0,BUFSIZE);// !! ������� �����
  //
  AnsiString SendMax=INPUT_SET_PARAM;
  lensend=StrToGlobBufw(SendMax,bufwr,255) ;    // ����������� � ������ �������
  writer->Resume();	//������������ ����� ������ � ����
}
void Check(unsigned char *buf, int len){ // ��������� ����������� ����� �������
  PurgeComm(COMport, PURGE_TXCLEAR);
  memset(bufwr,0,BUFSIZE);//
  //
  unsigned char cSum[2];
  getCSumChArr(buf, len,cSum);
  bufwr[0]=cSum[0];
  lensend=1;  // ������ ����� ����
  writer->Resume();	//������������ ����� ������ � ����
}
//=================================
// ------------ master ---------------

void LoadSet(void){  // ��������� ��������� � ���������
  PurgeComm(COMport, PURGE_TXCLEAR);             //�������� ���������� ����� �����
  memset(bufwr,0,BUFSIZE);// !! ������� �����

  AnsiString SendMax="12 01 01 00 02 01 02 A9 02 A9";
  // ������������
  lensend=StrToGlobBufw(SendMax,bufwr,255) ;    // ����������� � ������ �������
  // ������� ����������� �����
  McSum[1]='\0';  // ���������� ������
  getCSumChArr(bufwr, lensend,McSum);
  writer->Resume();	//������������ ����� ������ � ����

}

//-------------------------
*/
 