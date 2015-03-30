#include "socketClient.h"
//#include "cocos2d.h"
//USING_NS_CC;



socketClient::socketClient(void)
{
}


socketClient::~socketClient(void)
{
}

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

bool socketClient::ServerConnection()
{
	WSADATA  Ws;
    struct sockaddr_in ServerAddr;
    int Ret = 0;
    int AddrLen = 0;
	
    //Init Windows Socket
    if ( WSAStartup(MAKEWORD(2,2), &Ws) != 0 )
    {
         cout<<"Init Windows Socket Failed::"<<GetLastError()<<endl;
         return false;
    }

    m_clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if ( m_clientSocket == INVALID_SOCKET )
    {
        cout<<"Create Socket Failed::"<<GetLastError()<<endl;
        return false;
    }
	//log("2");
    ServerAddr.sin_family = AF_INET;
    ServerAddr.sin_addr.s_addr = inet_addr(IP_ADDRESS);
    ServerAddr.sin_port = htons(PORT);
    memset(ServerAddr.sin_zero, 0x00, 8);

    Ret = connect(m_clientSocket,(struct sockaddr*)&ServerAddr, sizeof(ServerAddr));
    if ( Ret == SOCKET_ERROR )
    {
        cout<<"Connect Error::"<<GetLastError()<<endl;
        return false;
    }
    else
    {
        cout<<"连接成功!"<<endl;
		//log("连接成功");
    }
}

bool socketClient::GetScoreRankList(std::vector<NetPacket_Score*>& scoreVec)
{
	int Ret;
    char SendBuffer[1024];
	char GetBuffer[1024];	
	if (!ServerConnection())
	{
		return false;
	}
	NetPacketHeader netheader;
	netheader.wDataSize = 0;
	netheader.wOpcode = GET_SCORE_CODE;
	Ret = ::send(m_clientSocket, (char*)&netheader, sizeof(netheader), 0);

	NetPacket_Score* test = NULL;
	NetPacketHeader* pPackageHeader = NULL;
	NetPacketResult* testResult;

	memset(GetBuffer, 0, sizeof(GetBuffer));
	bool iRet = GetData(m_clientSocket, GetBuffer, sizeof(NetPacketHeader));
	pPackageHeader = (NetPacketHeader* )GetBuffer;;
	if (iRet == false)
	{
		printf("second === get fialed\n");
		return false;
	}
		
	memset(SendBuffer, 0, sizeof(SendBuffer));
	iRet = GetData(m_clientSocket, SendBuffer, pPackageHeader->wDataSize);
	testResult = (NetPacketResult*)SendBuffer;
	cout<<pPackageHeader->wDataSize<< " "<<pPackageHeader->wOpcode<<" "<<testResult->result<<endl;
	int nCnt = testResult->result;
	while (nCnt--)
	{
		memset(GetBuffer, 0, sizeof(GetBuffer));
		bool iRet = GetData(m_clientSocket, GetBuffer, sizeof(NetPacketHeader));
		pPackageHeader = (NetPacketHeader* )GetBuffer;;
		if (iRet == false)
		{
			printf("second === get fialed\n");
			break;
		}
		cout<<pPackageHeader->wDataSize<< " "<<pPackageHeader->wOpcode<<endl;
		
		memset(SendBuffer, 0, sizeof(SendBuffer));
		iRet = GetData(m_clientSocket, SendBuffer, pPackageHeader->wDataSize);
		test = (NetPacket_Score*)SendBuffer;
		//printf("%s %d\n", test->strUserName, test->nScore);
		
		scoreVec.push_back(new NetPacket_Score(test->strUserName, test->nScore));
	}
	closesocket(m_clientSocket);
}

bool socketClient::LoginSendData(string strName, string strPwd, int nCode , int nScore)
{
	if (strName.empty()||strPwd.empty())
	{
		return false;
	}

	int Ret = 0;
    char SendBuffer[1024];
	char GetBuffer[1024];	
	if (!ServerConnection())
	{
		return false;
	}
	if(strName.empty() == false)
    {
          NetPacketHeader netheader;
		  switch (nCode)
		  {
		  case  REGISTER_CODE:
		  case LOGIN_CODE:
		  {
			  NetPacket_Register nettest;
			  strcpy(nettest.strUserName, strName.c_str());
			  strcpy(nettest.strUserPwd, strPwd.c_str());
			  netheader.wDataSize = sizeof(nettest);
			  netheader.wOpcode = nCode;
			  Ret = ::send(m_clientSocket, (char*)&netheader, sizeof(netheader), 0);
			  Ret = ::send(m_clientSocket, (char*)&nettest, sizeof(nettest), 0);
			  break;
		  }
		  case SCORE_CODE:
			  {
				NetPacket_Score nettest;
				strcpy(nettest.strUserName, strName.c_str());
				nettest.nScore = nScore;
				netheader.wDataSize = sizeof(nettest);
				netheader.wOpcode = nCode;
				Ret = ::send(m_clientSocket, (char*)&netheader, sizeof(netheader), 0);
				Ret = ::send(m_clientSocket, (char*)&nettest, sizeof(nettest), 0);
			  }
			  break;
		  default:
			  break;
		  }
    }
	else
	{
		return false;
	}
    if ( Ret == SOCKET_ERROR )
    {
       cout<<"Send Info Error::"<<GetLastError()<<endl;
    }

	NetPacketHeader* pPackageHeader = NULL;
	memset(GetBuffer, 0, sizeof(GetBuffer));
	bool iRet = GetData(m_clientSocket, GetBuffer, sizeof(NetPacketHeader));
	pPackageHeader = (NetPacketHeader* )GetBuffer;;
	if (iRet == false)
	{
		printf("=== get fialed\n");
		return NULL;
	}
	cout<<pPackageHeader->wDataSize<< " "<<pPackageHeader->wOpcode<<endl;
	memset(SendBuffer, 0, sizeof(SendBuffer));
	//iRet = GetData(CientSocket, GetBuffer, sizeof(NetPacketResult));
	iRet = GetData(m_clientSocket, SendBuffer, pPackageHeader->wDataSize);
	NetPacketResult *test ;
	switch (pPackageHeader->wOpcode)
	{
	case RESULT_CODE:
		{
			test = (NetPacketResult*)SendBuffer;
			//cout<<"---"<<GetBuffer<<endl;
			//printf("%d\n",test->result);
		}
		break;
	default:
		break;
	}
	closesocket(m_clientSocket);
    WSACleanup();
	return test->result;

}

