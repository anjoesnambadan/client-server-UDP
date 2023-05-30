#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void errors(int eno, int sockfd)
{
	switch(eno)
	{
		case 1 : printf("\nSocket error!\n");
				 break;
		case 2 : printf("\nBinding error!\n");
				 break;
	}
	printf("Exiting...\n");
	close(sockfd);
	exit(1);
}

void main()
{
	char message[100];
	char response[100];

	int server_sockfd;
	int err;
	
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8080);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	
	server_sockfd = socket(AF_INET, SOCK_DGRAM, 0);//socket
	if(server_sockfd == -1)
	{
		errors(1, server_sockfd);
	}
	else
	{
		err = bind(server_sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));//bind
		if(err == -1)
		{
			errors(2, server_sockfd);
		}
		else
		{
			printf("Server is listening on port 8080...\n");
			struct sockaddr_in client_addr;
			socklen_t client_len = sizeof(client_addr);
			int n = recvfrom(server_sockfd, message, sizeof(message), 0, (struct sockaddr*)&client_addr, &client_len);//receive message
			printf("\nMessage recieved from the client: %s\n", message);
			printf("\nEnter the response: ");
			fgets(response, sizeof(response), stdin);//use fgets instead of scanf to read full sentence
			sendto(server_sockfd, response, sizeof(response), 0,(struct sockaddr*)&client_addr, client_len);//send response
			printf("\nResponse successfully trasmitted.\n");
			close(server_sockfd);	
			
		}
	}
}

