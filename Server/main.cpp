#include <iostream>
#include <string>
#include <WinSock2.h>

using namespace std;

void ShowErroMessage(string message)
{
	cout << "[오류 발생] :" << message << endl;
	system("pause");
	exit(1);
}

int main()
{
	cout << "[ TCP Echo Server Ver2.0]" << endl;
	WSADATA wsaData;
	SOCKET serverSocket, clientSocket;
	SOCKADDR_IN serverAdress, clientAdress;

	int serverPort = 9876;
	char received[256];

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) //Winsock 초기화.
		ShowErroMessage("WSAStartup()");

	serverSocket = socket(PF_INET, SOCK_STREAM, 0); //TCP소켓 생성

	if (serverSocket == INVALID_SOCKET)
		ShowErroMessage("socket()");

	memset(&serverAdress, 0, sizeof(serverAdress));
	serverAdress.sin_family = AF_INET;
	serverAdress.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAdress.sin_port = htons(serverPort);

	if (bind(serverSocket, (SOCKADDR*)&serverAdress, sizeof(serverAdress)) == SOCKET_ERROR)
		ShowErroMessage("bind()");
	cout << "[현재 상태] bind()" << endl;

	if (listen(serverSocket, 5) == SOCKET_ERROR)
		ShowErroMessage("listen()");
	cout << "[현재 상태] listen()" << endl;

	int sizeClientAddress = sizeof(clientAdress);
	clientSocket = accept(serverSocket, (SOCKADDR*)&clientAdress, &sizeClientAddress);
	cout << "[현재 상태] accept()" << endl;

	if (clientSocket == INVALID_SOCKET)
		ShowErroMessage("accept()");

	while (1)
	{
		int length = recv(clientSocket, received, sizeof(received), 0);
		received[length] = NULL; //엔터 소멸
		cout << "[클라이언트 메시지] : " << received << endl;
		cout << "[메시지 전송] : " << received << endl;
		if (strcmp(received, "[exit]") == 0)
		{
			send(clientSocket, received, sizeof(received) - 1, 0);
			cout << "[서버 종료]" << endl;
			break;
		}
		send(clientSocket, received, sizeof(received) - 1, 0);
	}

	closesocket(clientSocket);
	closesocket(serverSocket);
	WSACleanup();
	system("pause");

	return 0;
 }