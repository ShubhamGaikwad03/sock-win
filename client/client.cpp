#include <stdio.h> 
#include <string.h> 
#include <WinSock2.h>
#include <WS2tcpip.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

const int PORT = 8080;

void initWinSock()
{
	printf("\nInitialising Winsock Cilent\n");
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(1);
	}

	printf("Initialised\n");
}

int main() 
{ 
	int sock = 0;
	
	struct sockaddr_in serv_addr; 
	const char *hello = "Hello from client"; 
	char buffer[1024] = {0}; 
	char buffer1[1024] = { 0 };
	struct Certificate
	{
		char *name[38];
		unsigned int hash;
	};
	


	initWinSock();

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{ 
		printf("\n Socket creation error \n"); 
		return -1; 
	} 

	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(PORT); 

	// Convert IPv4 and IPv6 addresses from text to binary form 
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
	{ 
		printf("\n Invalid address/ Address not supported \n"); 
		return -1; 
	} 
	//Connect to server
	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
	{ 
		printf("\n Connection Failed \n"); 
		return -1; 
	} 

	

	//recieve certificate over here
	recv(sock, buffer, 1024, 0);
	printf("Received: %s\n", buffer);

	send(sock , hello , strlen(hello) , 0 ); 
	printf("Hello message sent from client to server\n"); 

	recv( sock, buffer1, 1024, 0); 
	printf("Received: %s\n",buffer1); 

	return 0; 
} 
