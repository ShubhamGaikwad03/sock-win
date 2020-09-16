#include <stdio.h> 
#include<stdlib.h> 
#include<string.h> 
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

const int PORT = 8080;

void initWinSock()
{
	printf("\nInitialising Winsock Server");
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
	int server_fd = 0;  // Socket descriptor
	int new_socket = 0;
	int valread = 0;
	struct sockaddr_in address; 
	int addrlen = sizeof(address); 
	char buffer[1024] = {0}; 
	const char *hello = "Hello from server"; 
	
	struct Certificate
{
    char name[38];
    unsigned int hash;
};

	Certificate obj1;
	
	strcpy_s(obj1.name, "Congrats for course completion");
	

	initWinSock();

	// Create socket descriptor 
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) //AF_INET-internetwork: UDP, TCP, etc.  SOCK_STREAM - TCP Protocol used
	{ 
		perror("socket failed"); 
		exit(EXIT_FAILURE); 
	} 
	
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons( PORT ); 
	
	// Attach socket to the port 8080 
	if (bind(server_fd, (struct sockaddr *)&address, 
								sizeof(address))<0) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	// Setup listen queue
	if (listen(server_fd, 3) < 0) 
	{ 
		perror("listen"); 
		exit(EXIT_FAILURE); 
	} 
	printf("Waiting for connection...\n");
	if ((new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen)) < 0)
	{
		perror("accept");
		exit(EXIT_FAILURE);
	}


	//send certificate
	send(new_socket, obj1.name, strlen(obj1.name), 0);
	
	
	
	printf("Waiting for data...\n");

	recv( new_socket , buffer, 1024, 0); 
	
	printf("Received: %s\n", buffer ); 
	
	send(new_socket , hello , strlen(hello) , 0 ); 
	printf("Hello message sent\n"); 

	return 0; 
} 
