#include <stdio.h>
#include <tchar.h>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#include <stdlib.h>
#include <Windows.h>
#include <iostream>
#include <string.h>
using namespace std;
#define  PORT 8888
#define  IP_ADDRESS "192.168.13.181"
#define NET_PACKET_DATA_SIZE 1024   
#define NET_PACKET_SIZE (sizeof(NetPacketHeader) + NET_PACKET_DATA_SIZE) * 10  

/// 网络数据包包头  
struct NetPacketHeader  
{  
    unsigned short      wDataSize;  ///< 数据包大小，包含封包头和封包数据大小  
    unsigned short      wOpcode;    ///< 操作码  
};  
//////////////////////////////////////////////////////////////////////////  
  
  
/// 网络操作码  
enum eNetOpcode  
{  
    NET_TEST1           = 1,  
};  
  
/// 测试1的网络数据包定义  
struct NetPacket_Test1  
{  
    char username[20];  
    char userpwd[20];  
	int nCodeNum;
};  

struct NetPacketResult  
{  
    int result;
};   
class socketClient
{
public:
	bool LoginSendData(string strName, string strPwd, int nCode);
	bool GetData(int clientFd, char* pDataBuffer, const int nDataSize ); 
};