/*
 *  showmyip.c
 *  
 *
 *  Created by Latin on 9/9/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <time.h>
int main(int argc, char *argv[])
{
	/*
	 * Prepare socket address structures
	 */
    struct addrinfo hints, *res, *p;
	
	/*
	 * Status
	 */
    int status;
	
	/* 
	 * Will hold the IPv6 String
	 */
    char ipstr[INET6_ADDRSTRLEN];
    
	/*
	 * Check if argc is the application compile object plust hostname
	 * argv[0] = showmyip, argv[1] = www.google.com
	 */
	if (argc != 2) {
        fprintf(stderr,"usage: showip hostname\n");
        return 1;
	}
	
	/*
	 * Make sure the stack is empty
	 */
    memset(&hints, 0, sizeof hints);
	
	/*
	 * AF_INET or AF_INET6 to force version
	 * This doesn't care if its IPv4 or IPv6
	 */
    hints.ai_family = AF_UNSPEC;
	
	/*
	 * TCP Stream Sockets
	 */
    hints.ai_socktype = SOCK_STREAM;
	
	/*
	 * getaddrinfo(argv[1], NULL, &hints, &res)
	 * res is now pointing to one of more struct
	 */
    if ((status = getaddrinfo(argv[1], NULL, &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return 2;
	}
	
    /*
     * Time Related Sample
     */
    time_t start_t, end_t;
    double diff_t;
    
    printf("IP addresses for %s:\n\n", argv[1]);
    for(p = res;p != NULL; p = p->ai_next) {
        void *addr;
		char *ipver;
        // get the pointer to the address itself,
        // different fields in IPv4 and IPv6:
        if (p->ai_family == AF_INET) { // IPv4
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = "IPv4";
            time(&start_t);
        } else { // IPv6
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = "IPv6";
            time(&start_t);
		}
        sleep(5);
        // convert the IP to a string and print it:
        inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
        printf("  %s: %s\n", ipver, ipstr);
        time(&end_t);
        diff_t = difftime(end_t, start_t);
        printf("Execution time = %f\n", diff_t);
	}
    freeaddrinfo(res); // free the linked list
	return 0; 
}

