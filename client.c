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
 case 2 : printf("\nConnection error!\n");
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

 int client_sockfd;
 int err;
 
 struct sockaddr_in server_addr;
 server_addr.sin_family = AF_INET;
 server_addr.sin_port = htons(8080);
 server_addr.sin_addr.s_addr = INADDR_ANY;//use loopback address for testing
 
 client_sockfd = socket(AF_INET, SOCK_DGRAM, 0);//socket
 if(client_sockfd == -1)
 {
 errors(1, client_sockfd);
 }
 else
 {
 printf("Enter the message: ");
 fgets(message, sizeof(message), stdin);//use fgets instead of scanf to read full sentence
 sendto(client_sockfd, message, sizeof(message), 0,(struct sockaddr*)&server_addr, sizeof(server_addr));//send message
 printf("\nMessage successfully trasmitted.\n");
 int n = recvfrom(client_sockfd, response, sizeof(response), 0, NULL, NULL);//receive response
 printf("\nResponse recieved from the server: %s\n", response);
 close(client_sockfd); 
 }
}
