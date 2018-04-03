#include "Wuli.h"

#include "Winsock2.h"
#include <time.h>
#include<iostream>  
#include<fstream> 
#include<string>
#include<sstream>
#include<windows.h>
#pragma comment(lib,"WS2_32.lib")
SOCKET s;
using namespace std;

//��ʼ���׽���
bool SocketInit()
{
	WSADATA wsaData;
	WORD sockVersion = MAKEWORD(2, 0);
	WSAStartup(sockVersion, &wsaData);//�����׽���
	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (s == INVALID_SOCKET)
	{
		WSACleanup();
		return FALSE;
	}
	sockaddr_in servAddr;
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(8888);
	servAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	if (connect(s,(sockaddr*)&servAddr,sizeof(servAddr)) == -1)
	{
		WSACleanup();
		return FALSE;
	}
	return TRUE;
}


//������Ϣ
 int nReceiveBuf(Para* &para)
{	
	para->nRet = recv(s, para->buff, 10000, 0);
	if ( strcmp(para->buff, "-9999") != 0)
	{
		sprintf(chTmp, "%s", para->buff);
	}
	return 0;
}



 //����Ϊcsv�ļ�
bool bSaveBufToFile(Para &para,char(&time)[64])
{
	//��ȡ��ǰʱ��
	SYSTEMTIME st = { 0 };
	GetLocalTime(&st);
	sprintf(time, "%d��%02d��%02d��  %02d:%02d:%02d.%d",
		st.wYear,
		st.wMonth,
		st.wDay,
		st.wHour,
		st.wMinute,
		st.wSecond,
		st.wMilliseconds);

	string strTmp;
	string value = time;
	value = value + ",";
	if ( strlen(chTmp) == 0 )
	{
		strTmp = para.buff;
	}
	else
	{
		strTmp = chTmp;
	}
	value = value + strTmp;
	value = strTmp;
	ofstream outfile;
	outfile.open("..//DataOfLabview.csv", ios::out);
	outfile << value;
	outfile.close();
	return TRUE;
}
//��csv�ļ���ȡ����
bool bReadBufFromFile(string& BufValue)
{
	ifstream infile;
	infile.open("..//DataOfLabview.csv", ios::in);
	ostringstream sin;
	//���ļ����е��ַ����뵽�ַ�������  
	sin << infile.rdbuf();
	//��ȡ�ַ������е��ַ���  
	 BufValue = sin.str();
	 infile.close();
	 infile.clear();
	return TRUE;
}