

/*

	1911
	Client code for the TCP client-server model

*/

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h> //for exit
#include <string.h>
#include <arpa/inet.h>

void main(){	

	struct sockaddr_in client_addr;

	int sock_id;	

	bzero(&client_addr, sizeof(client_addr) );

	// create socket for the client	
	sock_id = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// initialize the client address and port number

	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(9011);
	client_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	// if there is error in creating the socket
	if (sock_id == -1){
		write(1, "socket error", 12);
		exit(-1);
	}

	int len = sizeof(client_addr);

	/*	connect call, to connect to ther server
		if error display error message
	*/

	if ( connect(sock_id, (struct sockaddr*)&client_addr, len) == -1 ){
		write(1, "connect error.", 14);
		exit(-1);
	}
	
	/*
		read a ten character input from the client,
		and send it to the server.
		Write to the terminal, the response from the server.
	*/

	char buff[10];

	char msg[60] = "Client Online: Enter message of ten characters only: ";
	write(1, msg, sizeof(msg) );	

	read(0, buff, 10);

	write(sock_id, buff, sizeof(buff) );

	bzero(msg, sizeof(msg) );

	read(sock_id, msg, sizeof(msg));	

	write(1, msg, sizeof(msg) );

	write(1, "\n", 1 );

	close(sock_id);

	exit(0);

}

