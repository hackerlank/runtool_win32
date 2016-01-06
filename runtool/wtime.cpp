#include "wtime.h"

#include <WinSock.h>
#include <time.h>
#pragma comment (lib,"Ws2_32")

struct   NTP_Packet
{
	int      Control_Word;
	int      root_delay;
	int      root_dispersion;
	int      reference_identifier;
	__int64	reference_timestamp;
	__int64 originate_timestamp;
	__int64 receive_timestamp;
	int      transmit_timestamp_seconds;
	int      transmit_timestamp_fractions;
};

/************************************************************************/
/* 函数说明:自动与时间服务器同步更新
/* 参数说明:无
/* 返 回 值:成功返回TRUE，失败返回FALSE
/************************************************************************/

bool UpdateSysTime()
{
	WORD	wVersionRequested;
	WSADATA wsaData;

	// 初始化版本
	wVersionRequested = MAKEWORD( 1, 1 );
	if (0!=WSAStartup(wVersionRequested, &wsaData))
	{
		WSACleanup();
		return FALSE;
	}
	if (LOBYTE(wsaData.wVersion)!=1 || HIBYTE(wsaData.wVersion)!=1)
	{
		WSACleanup( );
		return FALSE;
	}

	// 这个IP是中国大陆时间同步服务器地址，可自行修改
	SOCKET soc=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	struct sockaddr_in addrSrv;
	addrSrv.sin_addr.S_un.S_addr=inet_addr("202.120.2.101"); //210.72.145.44 //time-a.nist.gov
	addrSrv.sin_family=AF_INET;
	addrSrv.sin_port=htons(123);

	NTP_Packet NTP_Send,NTP_Recv;
	NTP_Send.Control_Word   =   htonl(0x0B000000);
	NTP_Send.root_delay		=   0;
	NTP_Send.root_dispersion   =   0;
	NTP_Send.reference_identifier	=   0;
	NTP_Send.reference_timestamp	=   0;
	NTP_Send.originate_timestamp	=   0;
	NTP_Send.receive_timestamp		=   0;
	NTP_Send.transmit_timestamp_seconds		=   0;
	NTP_Send.transmit_timestamp_fractions   =   0;

	if(SOCKET_ERROR==sendto(soc,(const char*)&NTP_Send,sizeof(NTP_Send),
		0,(struct sockaddr*)&addrSrv,sizeof(addrSrv)))
	{
		closesocket(soc);
		return FALSE;
	}
	int sockaddr_Size =sizeof(addrSrv);
	if(SOCKET_ERROR==recvfrom(soc,(char*)&NTP_Recv,sizeof(NTP_Recv),
		0,(struct sockaddr*)&addrSrv,&sockaddr_Size))
	{
		closesocket(soc);
		return FALSE;
	}
	closesocket(soc);
	WSACleanup();

	SYSTEMTIME	newtime;
	float		Splitseconds;
	struct		tm	*lpLocalTime;
	time_t		ntp_time;

	// 获取时间服务器的时间
	ntp_time	= ntohl(NTP_Recv.transmit_timestamp_seconds)-2208988800;
	lpLocalTime = localtime(&ntp_time);
	if(lpLocalTime == NULL)
	{
		return FALSE;
	}

	// 获取新的时间
	newtime.wYear      =lpLocalTime->tm_year+1900;
	newtime.wMonth     =lpLocalTime->tm_mon+1;
	newtime.wDayOfWeek =lpLocalTime->tm_wday;
	newtime.wDay       =lpLocalTime->tm_mday;
	newtime.wHour      =lpLocalTime->tm_hour;
	newtime.wMinute    =lpLocalTime->tm_min;
	newtime.wSecond    =lpLocalTime->tm_sec;

	// 设置时间精度
	Splitseconds=(float)ntohl(NTP_Recv.transmit_timestamp_fractions);
	Splitseconds=(float)0.000000000200 * Splitseconds;
	Splitseconds=(float)1000.0 * Splitseconds;
	newtime.wMilliseconds   =   (unsigned   short)Splitseconds;

	// 修改本机系统时间
	SetLocalTime(&newtime);
	return TRUE;
}


