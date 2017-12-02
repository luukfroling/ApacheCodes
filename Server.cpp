#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <fstream>
#include <iostream>
void error(const char *msg){
	perror(msg);
	exit(1);
}

void writeToFile(char buffer[]){
	std::ofstream websites;
	websites.open("websites.txt", std::ios::app);
	if(websites.is_open()){
	printf("file open");
	}
	printf(buffer);
	websites << buffer << std::endl;
	websites.close();
	if(websites.is_open()){
	printf("file still open you fucked up");
	}
}

int main(int argc, char *argv[]){
int sockfd, newsockfd, portno;
socklen_t clilen;
char buffer[256];
struct sockaddr_in serv_addr, cli_addr;
int n;

if (argc < 2){
fprintf(stderr, "error, no port \n");
exit(1);
}

sockfd = socket(AF_INET, SOCK_STREAM, 0);
if(sockfd < 0){
 printf("connection closed, lets try again");
 goto Try;
}
bzero((char*)&serv_addr, sizeof(serv_addr));
portno = atoi(argv[1]);
serv_addr.sin_family = AF_INET;
serv_addr.sin_addr.s_addr = INADDR_ANY;
serv_addr.sin_port = htons(portno);
Try:
if(bind(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0)
	error("ERROR on binding");
listen(sockfd,5);
clilen = sizeof(cli_addr);
newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
if(newsockfd < 0) error("ERROR on accept");
bzero(buffer, 256);
while(1){
n = read(newsockfd, buffer, 256);
if (n < 0) error("ERROR reading from socket");
printf("Here is the message: %s\n", buffer);
writeToFile(buffer);
bzero(buffer, 256);
}
close(newsockfd);
close(sockfd);
return 0;
}
