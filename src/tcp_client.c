/*
 *Client
 */
#include <stdio.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define CLIENTNAME "Renne"

int main(int argc, char *argv[])  
{  
	int client_sockfd;  
	int len;  
	struct sockaddr_in *remote_addr;//Struct of server's IP address
	char buf[BUFSIZ];//Buffer of sending data

	remote_addr = malloc(sizeof(struct sockaddr_in));
	memset(remote_addr, 0, sizeof(struct sockaddr_in));//Initialize datar
	remote_addr->sin_family = AF_INET;//Set to the IP communication
	remote_addr->sin_addr.s_addr = inet_addr("127.0.0.1");//The IP of server
	remote_addr->sin_port = htons(8000); //Port of server

	//Create socket
	if((client_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket");
		return 1;
	}

	getchar();
	//Binding on server IP
	if(connect(client_sockfd, (struct sockaddr *)remote_addr, sizeof(struct sockaddr)) < 0)
	{
		perror("connect");  
		return 1;  
	}  
	printf("connected to server\n");  
	len=recv(client_sockfd, buf, BUFSIZ, 0);//Receive server information
	buf[len] = '\0';  
	printf("%s", buf);//Print server port information
      	
	while(1)
	{
		printf("Enter string to send:");
		//scanf("%s", buf);
		fgets(buf, BUFSIZ, stdin);
		if(!strcmp(buf, "quit"))
			break;
		len=send(client_sockfd, buf, strlen(buf), 0);
		len=recv(client_sockfd, buf, BUFSIZ, 0);
		//buf[len] = '\0';
		printf("received:%s", buf);  
	}  
	close(client_sockfd);//Close socket
	return 0;  
}
