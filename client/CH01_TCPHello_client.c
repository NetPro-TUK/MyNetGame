
#include <stdio.h>
#include <WinSock2.h>
#define MAX_BUF_SIZE 100
void ErrorHandling(char* message);

int main(void)
{
	WSADATA		winsockData;
	int			errorNum, errorCode;
	 
	printf("> start TCP client.\n");

	errorNum = WSAStartup( MAKEWORD(2,2), &winsockData );

	SOCKET clientSocket;
	clientSocket = socket( PF_INET, SOCK_STREAM, IPPROTO_TCP );

	SOCKADDR_IN  serverAddr;
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family			= AF_INET;
	serverAddr.sin_port				= htons(9000);  
	serverAddr.sin_addr.s_addr		= inet_addr("127.0.0.1");

	errorNum = connect(clientSocket, (SOCKADDR *)&serverAddr, sizeof(serverAddr) );

	char Buffer[MAX_BUF_SIZE] = "Hello";
	int  returnValue;

	returnValue = send(clientSocket, Buffer, MAX_BUF_SIZE, 0);
	if( returnValue == SOCKET_ERROR ){
		ErrorHandling("send() error");
	}else {
		printf("> client sent data: %s\n", Buffer);
	}

	closesocket(clientSocket);
	WSACleanup();
}

void ErrorHandling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}