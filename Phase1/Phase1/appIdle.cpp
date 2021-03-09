#include "appIdle.h"


int transferToServer() 
{
	WSADATA wsaData;
	sockaddr_in addr;
	int sock,port;
	string ip;
	cout << "IP Giriniz: ";    // 127.0.0.1 must be entered for localhost
	cin >> ip;
	cout << "Port Numarasi Giriniz: "; // 5999 must be entered to connect server
	cin >> port;
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.S_un.S_addr = inet_addr(ip.c_str());

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	sock = socket(AF_INET, SOCK_STREAM, 0); // creating socket
	if (sock == -1){cout << "Can't create socket!" << endl;return 0;}
	
		int connectRes = connect(sock, (sockaddr*)&addr, sizeof(addr)); // connecting to server
		if (connectRes == -1){return 0;}
	while (sock)
	{
			string helloMsg;
			cin >> helloMsg; // enter 'exit' to quit 
			helloMsg = helloMsg + '\n';
			char buf[4096];
			int sendRes = send(sock, helloMsg.c_str(), helloMsg.size() + 1, 0);  //sending input message 
			if (sendRes == -1) { cout << "Could not send to server! Whoops!\r\n"; return 0; }

			int bytesReceived = recv(sock, buf, 4096, 0); // coming message from server as response

			if (bytesReceived == -1 || bytesReceived == 0)
			{
				cout << "Server Disconnected." << endl;
				return 0;
			}
			cout << (string(buf, 0, bytesReceived)) << endl; // writing message that came from server to consoler
	}
	cout << "Server Disconnected.";
	return 0;
}

void appIdleLoop(const unsigned char* cashierName)
{
	int choiceIdleLoop;
	string temp;
	cout << "KASIYER: " << cashierName << endl<< endl;
	cout << "ISLEMLER" << endl << endl;

checkPoint:

	cout << "1 - SATIS" << endl;
	cout << "2 - TRANSFER" << endl;
	cout << "3 - CIKIS" << endl;
	cout << "Seciminizi Yapiniz: ";
	cin >> temp;

	if (CashierDb::check_number(temp))
		choiceIdleLoop = stoi(temp);
	else {
		cout << "Yanlis karakter girildi." << endl;
		goto checkPoint;
	}

	if (choiceIdleLoop == 1)
	{
		cout << "Henuz kayit yok." << endl;
		goto checkPoint;
	}
	else if (choiceIdleLoop == 2)
	{
		transferToServer();
		goto checkPoint;
	}
	else if (choiceIdleLoop == 3)
	{
		cout << "Cikis yapiliyor.";
	}
	else
	{
		cout << "Yanlis bir secim yapildi." << endl;
		goto checkPoint;
	}
}
