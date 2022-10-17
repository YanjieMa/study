#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <ctype.h>
#include <arpa/inet.h>

#define SERVER_PORT 9527
#define SERVER_IP "127.0.0.1"

int main(int argc, char ** argv)
{
	struct sockaddr_in server_addr;
	char *server_ip = SERVER_IP;
	memset(&server_addr,0,sizeof(struct sockaddr_in));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	inet_pton(AF_INET,server_ip,&server_addr.sin_addr);
	
	int tcp_com_fd;
	tcp_com_fd = socket(AF_INET,SOCK_STREAM,0);
	if(tcp_com_fd < 0){
		perror("socket error");
		exit(-1);
	}

	int ret = 0;
	ret = connect(tcp_com_fd,(struct sockaddr *)&server_addr,sizeof(struct sockaddr));
	if(ret < 0){
		perror("connect error");
		exit(-1);
	}
	
	char * send_buf = "hello";
	int n = 0;
	n = send(tcp_com_fd,send_buf,strlen(send_buf),0);
	if(n < 0){
		perror("send error");
	}

	close(tcp_com_fd);
	tcp_com_fd = -1;

	return 0;
}


