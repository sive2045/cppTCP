#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <string>
#include <WinSock2.h>

using namespace std;

void ShowErroMessage(string message)
{
	cout << "[오류 발생] : " << message << endl;
	system("pause");
	exit(1);
}

int main()
{
	WSADATA wsaData;
	SOCKET clientSocket;
	SOCKADDR_IN serverAdress;

	int serverPort = 9876;
	char received[256];
	string sent;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) //winsock을 초기화합니다.
		ShowErroMessage("SWAStartyp()");

	clientSocket = socket(PF_INET, SOCK_STREAM, 0); //TCP 소켓을 생성

	if (clientSocket == INVALID_SOCKET)
		ShowErroMessage("socket()");

	memset(&serverAdress, 0, sizeof(serverAdress));
	serverAdress.sin_family = AF_INET;
	serverAdress.sin_addr.s_addr = inet_addr("127.0.0.1"); //문자열 IP를 네트워크 바이트 형식으로
	serverAdress.sin_port = htons(serverPort); //2바이트 정수 네트워크 바이트 형식으로
	if (connect(clientSocket, (SOCKADDR*)&serverAdress, sizeof(serverAdress)) == SOCKET_ERROR)
		ShowErroMessage("connect()");
	cout << "[현재 상태] : connect()" << endl;

	while (1)
	{
		cout << "[메시지 전송] : ";
		getline(cin, sent);
		if (sent == "") continue;
		send(clientSocket, sent.c_str(), sent.length(), 0);
		int length = recv(clientSocket, received, sizeof(received), 0);
		received[length] = '\0';
		if (strcmp(received, "[exit]") == 0)
		{
			cout << "[서버 종료]" << endl;
			break;
		}
		cout << "[서버 메시지] : " << received << endl;
	}


	closesocket(clientSocket);
	WSACleanup();
	system("pause");
	return 0;
}