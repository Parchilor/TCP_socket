/*
 *Server
 */
#include <stdio.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define SERVERNAME "Parchilor"

int main(int argc, char *argv[])  
{  
	int server_sockfd;//Server's socket
	int client_sockfd;//Client's socket
	int len;  
	struct sockaddr_in *my_addr;//Struct of server's IP address
	struct sockaddr_in *remote_addr; //Struct of client IP address 
	socklen_t sin_size;
	char buf[BUFSIZ];//Buffer of sending data

	my_addr = malloc(sizeof(struct sockaddr_in));
	remote_addr = malloc(sizeof(struct sockaddr_in));
	memset(my_addr,0,sizeof(struct sockaddr_in));//Initialize datar
	memset(remote_addr,0,sizeof(struct sockaddr_in));//Initialize datar

	my_addr->sin_family = AF_INET;//Set to the IP communication
	my_addr->sin_addr.s_addr = INADDR_ANY;//The IP address of server--allow any local address
	my_addr->sin_port = htons(8000); //Port number of server

	//Create socket
	if((server_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)  
	{    
		perror("socket");  
		return 1;  
	}  

	//Binding socket on the server IP
	if (bind(server_sockfd, (struct sockaddr *)my_addr, sizeof(struct sockaddr)) < 0)  
	{  
		perror("bind");  
		return 1;  
	}  
  
	//Listen request
	listen(server_sockfd, 5);
  
	sin_size = sizeof(struct sockaddr_in);  
  
	//Wait for the client request
	if((client_sockfd = accept(server_sockfd, (struct sockaddr *)remote_addr, &sin_size)) < 0)  
	{  
		perror("accept");  
		return 1;  
	}  
	printf("accept client %s\n", inet_ntoa(remote_addr->sin_addr));
	char *tmp = "Welcome to "SERVERNAME" server\n";
//	len = send(client_sockfd,"Welcome to my server\n",21,0);//Send welcome information
	len = send(client_sockfd, tmp, strlen(tmp), 0);//Send welcome information
  
	//Receive client information
	while((len = recv(client_sockfd, buf, BUFSIZ, 0)) > 0)  
	{  
		//buf[len] = '\0';  
		printf("%s", buf);  
		if(send(client_sockfd, buf, len, 0) < 0)  
		{  
			perror("write");  
			return 1;  
		}  
	}
	close(client_sockfd);  
	close(server_sockfd);  
	return 0;  
}
