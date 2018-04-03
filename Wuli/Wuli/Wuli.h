//#include "CJThreadLock.h"
#pragma once
#include <string>
using namespace std;
extern "C" {
#define WULI __declspec(dllexport)
typedef struct PARA
{
	int  nRet;
	char buff[10000];
}Para;

    char chTmp[10000];
//char *chDebug;


	//WULI omp_lock_t	m_ompLock;
	WULI bool SocketInit();
	WULI int nReceiveBuf( Para* &para);
	WULI bool bSaveBufToFile(Para &para, char(&time)[64]);
	WULI bool bReadBufFromFile(string& BufValue);

}