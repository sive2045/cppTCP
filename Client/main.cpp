#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <string>
#include <WinSock2.h>

using namespace std;

void ShowErroMessage(string message)
{
	cout << "[���� �߻�] : " << message << endl;
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

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) //winsock�� �ʱ�ȭ�մϴ�.
		ShowErroMessage("SWAStartyp()");

	clientSocket = socket(PF_INET, SOCK_STREAM, 0); //TCP ������ ����

	if (clientSocket == INVALID_SOCKET)
		ShowErroMessage("socket()");

	memset(&serverAdress, 0, sizeof(serverAdress));
	serverAdress.sin_family = AF_INET;
	serverAdress.sin_addr.s_addr = inet_addr("127.0.0.1"); //���ڿ� IP�� ��Ʈ��ũ ����Ʈ ��������
	serverAdress.sin_port = htons(serverPort); //2����Ʈ ���� ��Ʈ��ũ ����Ʈ ��������
	if (connect(clientSocket, (SOCKADDR*)&serverAdress, sizeof(serverAdress)) == SOCKET_ERROR)
		ShowErroMessage("connect()");
	cout << "[���� ����] : connect()" << endl;

	while (1)
	{
		cout << "[�޽��� ����] : ";
		getline(cin, sent);
		if (sent == "") continue;
		send(clientSocket, sent.c_str(), sent.length(), 0);
		int length = recv(clientSocket, received, sizeof(received), 0);
		received[length] = '\0';
		if (strcmp(received, "[exit]") == 0)
		{
			cout << "[���� ����]" << endl;
			break;
		}
		cout << "[���� �޽���] : " << received << endl;
	}


	closesocket(clientSocket);
	WSACleanup();
	system("pause");
	return 0;
}