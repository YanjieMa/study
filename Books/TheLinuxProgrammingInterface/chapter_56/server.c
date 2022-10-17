#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <ctype.h>
#include <arpa/inet.h>

#define SERVER_PORT 9527

int main(int argc, char ** argv)
{
	int ret = 0;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	socklen_t client_addr_len;
	char addr_p[128];
	char recv_buf[1024];
	

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(SERVER_PORT);

	
	int tcp_listen_fd;
	tcp_listen_fd = socket(AF_INET,SOCK_STREAM,0);
	if(tcp_listen_fd < 0){
		perror("socket error");
		exit(-1);
	}

	ret = bind(tcp_listen_fd,(struct sockaddr *)&server_addr,sizeof(server_addr));
	if(ret < 0){
		perror("bind error");
		exit(-1);
	}

	ret = listen(tcp_listen_fd,3);
	if(ret < 0){
		perror("listen error");
		exit(-1);
	}

	printf("waiting...\n");
	while(1){
		int tcp_com_fd = accept(tcp_listen_fd,(struct sockaddr *)&client_addr,&client_addr_len);
		if(ret < 0){
			perror("accept error");
			exit(-1);
		}
		bzero(addr_p,sizeof(addr_p));
		inet_ntop(AF_INET,&client_addr,addr_p,sizeof(addr_p));
		printf("client addr:%s, port:%d\n",addr_p,ntohs(client_addr.sin_port));

		int n = recv(tcp_com_fd,recv_buf,sizeof(recv_buf),0);
		if(n<0){
			perror("recv error");
		}else if(n == 0){
			printf("client closed\n");
			close(tcp_com_fd);
			continue;
		}
		printf("recv:%s\n",recv_buf);
	}

	return 0;
}


