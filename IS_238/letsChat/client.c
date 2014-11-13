#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#define BUFF_SIZE 1024

int main(int argc, char *argv[]){
	int clientSocket, remotePort, status=0;
	struct hostent *hostPtr=NULL;
	struct sockaddr_in serverName = {0};
    char messageFromServer[BUFF_SIZE]="";
    char messageTobeSent[BUFF_SIZE]="";
	char *remoteHost=NULL;

	if(3 != argc){
		fprintf(stderr, "Usage: %s <serverHost> <serverPosr>\n", argv[0]);
		exit(1);
	}

	remoteHost=argv[1];
	remotePort=atoi(argv[2]);
	clientSocket=socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(-1 == clientSocket){
		perror("socket");
		exit(1);
	}

	/*
	 * need to resolve the remote server name or IP address
	 */

	hostPtr = gethostbyname(remoteHost);
	if(NULL == hostPtr){
		hostPtr = gethostbyaddr(remoteHost,strlen(remoteHost),AF_INET);
		if(NULL == hostPtr){
			perror("Error resolving server address ");
			exit(1);
		}		
	}

	serverName.sin_family=AF_INET;
	serverName.sin_port=htons(remotePort);
	(void)memcpy(&serverName.sin_addr, hostPtr->h_addr, hostPtr->h_length);
	status = connect(clientSocket, (struct sockaddr*)&serverName, sizeof(serverName));
	
	if(-1 == status){
		perror("connect");
		exit(1);
	}

	/*
   	 * Client application specific code goes here
	 *
	 * e.g. receive message from server, respond etc.
	 */
    for (;;) {
        printf("Client: Enter Data for Server:\n");
        fgets(messageTobeSent,BUFF_SIZE-1,stdin);
        if ((send(clientSocket,messageTobeSent, strlen(messageTobeSent),0))== -1) {
            fprintf(stderr, "Failure Sending Message\n");
            close(clientSocket);
            exit(1);
        }
        else {
            printf("Client:Message being sent: %s\n",messageFromServer);
            status = recv(clientSocket, messageFromServer, sizeof(messageFromServer),0);
            if ( status <= 0 )
            {
                printf("Either Connection Closed or Error\n");
                //Break from the While
                break;
            }
            
            messageFromServer[status] = '\0';
            printf("Client:Message Received From Server -  %s\n",messageFromServer);
        }
    }


	/*
     *int byte_count = recv(clientSocket, buffer, sizeof(buffer)-1, 0);
	 *printf("recv()'d %d bytes of data in buf\n", byte_count);
	 *printf("recv()'d %s bytes of data in buf\n", buffer);
	 *if(-1 == status){
	 *	perror("read()");
	 *}
     */
	
	/*
	 * close(clientSocket);
	 */
	
	return 0;
} 
