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

#define MSG_STR_SIZE 1000000
/*
 * Used google and yahoo as it is the most popular and most visited site.
 * These two sites are also the one which i can GET a response successfully
 *  to which I can used received bytes relative to its speed.
 * (1) google.com
 * (2) search.yahoo.com
 */
int main(int argc, char *argv[]){
    /*
     * Constant Declation
     */
    static const char GOOGLE_HOST[] = "google.com";
    static const char GOOGLE_QUERYSTR[] = "GET /search?q=up+open+university HTTP/1.0\n\n";
    static const char YAHOO_HOST[] = "search.yahoo.com";
    static const char YAHOO_QUERYSTR[] = "GET //search?p=up+open+university HTTP/1.0\n\n";
    
    /* 
     * Process id
     */
    pid_t pid;
    
    /*
     * Time Related
     */
    time_t start_tdownload;
    time_t end_tdownload;
    int pid_holder;
    double diff_tdownload;
    double diff_tdownload2;
    
    /* 
     * Hosts and sockaddr info
     */
    struct hostent *hostPtr=NULL;
    struct sockaddr_in serverName = {0};
	
    /*
     * Integer Declarations
     */
    int clientSocket;
    int bytes;
    int sent;
    int received;
        int received_bytes;
        int received_bytes2;
    int total;
    int status=0;
    int remotePort = 80;
    
    /*
     * Char pointers and Strings
     */
    char message[MSG_STR_SIZE];
    char response[MSG_STR_SIZE];
    char *remoteHost=NULL;
    char *host;
    char *query_str;
    
    /*
     * Make two copies of addresses
     */
    pid = fork();
    printf("process id: %d\n", pid);
    switch (pid) {
        case -1:
            perror("fork() process error");
        case 0:
            /*
             * Set parent host and message fmt to google
             */
            host =        "google.com";
            query_str = "GET /search?q=up+open+university HTTP/1.0\n\n";
            break;
        default:
            host =        "search.yahoo.com";
            query_str = "GET //search?p=up+open+university HTTP/1.0\n\n";
            break;
    }
    /*
     * Set message query string for HTTP GET
     */
    sprintf(message,query_str,"","");
    /*
     * Uncomment to see host server and GET query
     * printf("URL: %s", host);
     * printf("\nRequest:\n%s\n",message);
     */
    
    /*
     * Allocare socket descriptor and assign to clientSocket
     */
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
    
    /*
     * Set socket struct addrinfo
     */
    serverName.sin_family=AF_INET;
    serverName.sin_port=htons(remotePort);
    (void)memcpy(&serverName.sin_addr, hostPtr->h_addr, hostPtr->h_length);
    status = connect(clientSocket, (struct sockaddr*)&serverName, sizeof(serverName));
    
    /*
     * Error checking
     */
    if(-1 == status){
        perror("connect");
        exit(1);
    }else{
        printf(".... Calculating internet response time: \n");
    }
    total = strlen(message);
    sent = 0;
    
    /*
     * Sending GET request to host
     */
    do {
        bytes = write(clientSocket,message+sent,total-sent);
        if (bytes < 0)
            perror("ERROR writing message to socket");
        if (bytes == 0)
            break;
        sent+=bytes;
    } while (sent < total);
    time(&start_tdownload);
    memset(response,0,sizeof(response));
    
    /*
     * Received response from host
     */
    time(&start_tdownload);
    total = sizeof(response)-1;
    received = 0;
    do {
        bytes = read(clientSocket,response-received,total-received);
        if (bytes < 0)
            perror("ERROR reading response from socket");
        if (bytes == 0)
            break;
        /*
         * Add total bytes received
         */
        received+=bytes;
    } while (bytes < 0);
    /*
     * Uncomment to see total bytes received and host response
     *
     * printf("\nResponse:\n%s\n",response);
     * printf("\nReceived: %d\n", received);
     */
    time(&end_tdownload);
    if (pid == 0) {
        received_bytes = received;
        diff_tdownload = difftime(end_tdownload, start_tdownload);
    }else{
        received_bytes2 = received;
        diff_tdownload2 = difftime(end_tdownload, start_tdownload);
        kill(pid, SIGKILL);
    }
    /*
     * Close client socket
     */
    close(clientSocket);
    if(pid!=0){
        printf("\nInternet speed connection is: Mbps%f\n", (((received_bytes+received_bytes2)/2)/((diff_tdownload+diff_tdownload2)/2))/1000);
    }
	return 0;
}
