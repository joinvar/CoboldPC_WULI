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
//HANDLE hEvent;

//初始化套接字
bool SocketInit()
{
	//hEvent = CreateEvent(NULL, FALSE, TRUE, L"event");
	//omp_init_lock(&m_ompLock);
	//CCJThreadLock tdLock(&m_ompLock);
	//string value = "********时间********,**数据**,\n";
	//ofstream outfile;//..//DataOfLabview.csv
	//outfile.open("..//DataOfLabview.csv", ios::out);
	//outfile << value;
	//outfile.close();

	WSADATA wsaData;
	WORD sockVersion = MAKEWORD(2, 0);
	WSAStartup(sockVersion, &wsaData);//创建套接字
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


//接收信息
 int nReceiveBuf(Para* &para)
{	
	// WaitForSingleObject(hEvent, INFINITE);
	 //CCJThreadLock tdLock(&m_ompLock);
	 OutputDebugString(L"[JUNHUA]  recv     BEGIN  ");
	para->nRet = recv(s, para->buff, 10000, 0);
	string strTmp1 = "[JUNHUA]  --------->>>>>>  ";
	string strTmp2 = para->buff;
	strTmp1 = strTmp1 + strTmp2;




	int  len = 0;
	len = strTmp1.length();
	int  unicodeLen = ::MultiByteToWideChar(CP_UTF8,0,strTmp1.c_str(),-1,NULL,0);
	wchar_t *  pUnicode;
	pUnicode = new  wchar_t[unicodeLen + 1];
	memset(pUnicode, 0, (unicodeLen + 1)*sizeof(wchar_t));
	::MultiByteToWideChar(CP_UTF8,0,strTmp1.c_str(),-1,	(LPWSTR)pUnicode,unicodeLen);
	OutputDebugString(L"[JUNHUA]  pUnicode   BEFORE ");
	OutputDebugString(pUnicode);
	OutputDebugString(L"[JUNHUA]  pUnicode  AFTER");
	delete  []pUnicode;
	OutputDebugString(L"[JUNHUA]  recv     END  ");
	//para->buff[strlen(para->buff)] = '\0';
	if ( strcmp(para->buff, "-9999") != 0)
	{
		OutputDebugString(L"[JUNHUA]  para->buff   is  NOT   -9999    -------> ");
		sprintf(chTmp, "%s", para->buff);
	}
	

	return 0;
}



 //保存为csv文件
bool bSaveBufToFile(Para &para,char(&time)[64])
{
	//WaitForSingleObject(hEvent, INFINITE);
	//CCJThreadLock tdLock(&m_ompLock);
	//获取当前时间
	SYSTEMTIME st = { 0 };
	GetLocalTime(&st);
	sprintf(time, "%d年%02d月%02d日  %02d:%02d:%02d.%d",
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
		OutputDebugString(L"[JUNHUA]  chTmp  is  NULL     -------> ");
		strTmp = para.buff;
	}
	else
	{
		OutputDebugString(L"[JUNHUA]  chTmp  is    NOT   NULL     -------> ");
		strTmp = chTmp;
	}
	
	//strTmp = strTmp + ",\n";
	value = value + strTmp;
	value = strTmp;
	ofstream outfile;
	outfile.open("..//DataOfLabview.csv", ios::out);
	outfile << value;
	outfile.close();
	return TRUE;
}

bool bReadBufFromFile(string& BufValue)
{
	ifstream infile;
	infile.open("..//DataOfLabview.csv", ios::in);

	ostringstream sin;
	//把文件流中的字符输入到字符串流中  
	sin << infile.rdbuf();
	//获取字符串流中的字符串  
	 BufValue = sin.str();
	 infile.close();
	 infile.clear();
	return TRUE;
}