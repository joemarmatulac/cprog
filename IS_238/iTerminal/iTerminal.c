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
#include <pthread.h>

#define BUFF_SIZE 1024
/*
 char *host =        "google.com";
 char *message_fmt = "GET /search?q=up+open+university HTTP/1.0\n\n";
 
 char *host =        "search.yahoo.com";
 char *message_fmt = "GET //search?p=up+open+university HTTP/1.0\n\n";
 
 char *host =        "www.bing.com";
 char *message_fmt = "GET /search?q=upou HTTP/1.0\n\n";
 
 char *host =        "en.wikipedia.org";
 char *message_fmt = "GET /wiki/University_of_the_Philippines_Open_University HTTP/1.0\n\n";
 
 char *host =        "youtube.com";
 char *message_fmt = "GET /?search_query=upou HTTP/1.0\n\n";
 
 char *host =        "facebook.com";
 char *message_fmt = "GET /search=UPOpenUniversity HTTP/1.0\n\n";
 
 char *host =        "twitter.com";
 char *message_fmt = "GET /search?q=UP HTTP/1.0\n\n";
 */

void *receivedMessagethreadListener(int *arg);

int main(int argc, char *argv[]){
    time_t start_t, end_t;
    double diff_t;
    
	struct hostent *hostPtr=NULL;
	struct sockaddr_in serverName = {0};
	char *remoteHost=NULL;
    int clientSocket, bytes, sent,total, status=0;
    char message[1024],response[4096];
    
    int remotePort =        80;
    char *host =        "api.twitter.com";
    char *message_fmt = "GET /1.1/search/tweets.json?q=freebandnames&since_id=24012619984051000&max_id=250126199840518145&result_type=mixed&count=4 HTTP/1.0\n\n";
    
    sprintf(message,message_fmt,"","");
    printf("Request:\n%s\n",message);

	clientSocket=socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(-1 == clientSocket){
		perror("socket");
		exit(1);
	}

	/*
	 * need to resolve the remote server name or IP address
	 */

	hostPtr = gethostbyname(host);
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
    }else{
        printf("Connected to server\n");
    }
    total = strlen(message);
    sent = 0;
    do {
        bytes = write(clientSocket,message+sent,total-sent);
        if (bytes < 0)
            perror("ERROR writing message to socket");
        if (bytes == 0)
            break;
        sent+=bytes;
    } while (sent < total);
    time(&start_t);

    memset(response,0,sizeof(response));
    int count = 0;
    while(0 < (status =  read(clientSocket, response, sizeof(response)-1))){
        printf("\n***** %d %s count[%d] \n", status, response, count);
        count++;
    }
    close(clientSocket);
    time(&end_t);
    diff_t = difftime(end_t, start_t);
    printf("\n Execution time = %f\n", diff_t);
	return 0;
}
