#include "socketClient.h"
#include "cocos2d.h"
USING_NS_CC;
bool socketClient::GetData(int clientFd, char* pDataBuffer, const int nDataSize )  
{  
    if (pDataBuffer == NULL)
    {
    	return false;
    }

    char *p = pDataBuffer;
    int len = nDataSize;
    int ret = 0;
    int returnlen = 0;

    while (len > 0)
    {
    	ret = recv(clientFd, p + (nDataSize - len), nDataSize - returnlen, 0);
    	if (ret == -1 || ret == 0)
    	{
    		return false;
    	}
    	len -= ret;
    	returnlen += ret;
    }
    return returnlen;
}  

bool socketClient::LoginSendData(string strName, string strPwd, int nCode)
{
	if (strName.empty()||strPwd.empty())
	{
		log("1");
		return false;
	}
	WSADATA  Ws;
    SOCKET CientSocket;
    struct sockaddr_in ServerAddr;
    int Ret = 0;
    int AddrLen = 0;
    HANDLE hThread = NULL;
    char SendBuffer[1024];
	char GetBuffer[1024];
	
    //Init Windows Socket
    if ( WSAStartup(MAKEWORD(2,2), &Ws) != 0 )
    {
         cout<<"Init Windows Socket Failed::"<<GetLastError()<<endl;
         return false;
    }

    CientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if ( CientSocket == INVALID_SOCKET )
    {
        cout<<"Create Socket Failed::"<<GetLastError()<<endl;
        return false;
    }
	log("2");
    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_addr.s_addr = inet_addr(IP_ADDRESS);
    ServerAddr.sin_port = htons(PORT);
    memset(ServerAddr.sin_zero, 0x00, 8);

    Ret = connect(CientSocket,(struct sockaddr*)&ServerAddr, sizeof(ServerAddr));
    if ( Ret == SOCKET_ERROR )
    {
        cout<<"Connect Error::"<<GetLastError()<<endl;
        return false;
    }
    else
    {
        cout<<"连接成功!"<<endl;
		log("连接成功");
    }
log("3");
	if(strName.empty() == false)
    {
          NetPacket_Test1 nettest;
          NetPacketHeader netheader;
          strcpy_s(nettest.username, strName.c_str());
          strcpy_s(nettest.userpwd, strPwd.c_str()); 
		  nettest.nCodeNum = nCode;
          netheader.wDataSize = sizeof(nettest);  ///< 数据包大小，包含封包头和封包数据大小  
          netheader.wOpcode = NET_TEST1; 
		  Ret = ::send(CientSocket, (char*)&netheader, sizeof(netheader), 0);
          Ret = ::send(CientSocket, (char*)&nettest, sizeof(nettest), 0);
    }
    //Ret = send(CientSocket, SendBuffer, (int)strlen(SendBuffer), 0);
    if ( Ret == SOCKET_ERROR )
    {
       cout<<"Send Info Error::"<<GetLastError()<<endl;
    }
	NetPacketHeader* pPackageHeader = NULL;
	memset(GetBuffer, 0, sizeof(GetBuffer));
	bool iRet = GetData(CientSocket, GetBuffer, sizeof(NetPacketHeader));
	pPackageHeader = (NetPacketHeader* )GetBuffer;;
	if (iRet == false)
	{
		printf("=== get fialed\n");
		return NULL;
	}
	cout<<pPackageHeader->wDataSize<< " "<<pPackageHeader->wOpcode<<endl;
	memset(SendBuffer, 0, sizeof(SendBuffer));
	//iRet = GetData(CientSocket, GetBuffer, sizeof(NetPacketResult));
	iRet = GetData(CientSocket, SendBuffer, pPackageHeader->wDataSize);
	printf("%d %d\n",pPackageHeader->wDataSize,sizeof(NetPacketResult));
	NetPacketResult *test = (NetPacketResult*)SendBuffer;
	//cout<<"---"<<GetBuffer<<endl;
	printf("%d\n",test->result);
	closesocket(CientSocket);
    WSACleanup();
	//while (1);
	return test->result;

}
