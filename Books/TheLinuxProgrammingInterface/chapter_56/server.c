#include <stdio.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>


#define PORT 9527
#define SERVER_IP "192.168.1.25"

int main(int argc, char ** argv)
{
	int ret;
	int sock_fd;
	int com_fd;

	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	socklen_t client_addr_len;
	
	char client_ip[256];
	
	char recv_buf[1024];
	char send_buf[1024];
	// 1.socket
	sock_fd = socket(AF_INET,SOCK_STREAM,0);
	
	// 2.bind
	memset(&server_addr,0,sizeof(struct sockaddr_in));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	//server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	inet_pton(AF_INET,SERVER_IP,&server_addr.sin_addr.s_addr);
	ret = bind(sock_fd,(struct sockaddr *)&server_addr,sizeof(server_addr));
	
	// 3.listen
	ret = listen(sock_fd,3);

	while(1){
		// 4.accept
		printf("waiting connect...\n");

		client_addr_len = sizeof(client_addr);
		int com_fd = accept(sock_fd,(struct sockaddr *)&client_addr,&client_addr_len);
		inet_ntop(AF_INET,&client_addr.sin_addr.s_addr,client_ip,sizeof(client_ip));
		printf("client addr:%s, port:%d\n",client_ip,ntohs(client_addr.sin_port));
		
		while(1){
			memset(recv_buf,0,sizeof(recv_buf));
			// 5.recv
			int size = recv(com_fd,recv_buf,sizeof(recv_buf),0);
			if(size == 0){
				printf("client closed\n");
				close(com_fd);
				break;
			}else if(size < 0){
				perror("recv error");	
				exit(1);
			}else{
				write(STDOUT_FILENO,recv_buf,size);
				memset(send_buf,0,sizeof(recv_buf));
				// 6.send
//				strncpy(send_buf,"recv\n",sizeof(send_buf));
//				send(com_fd,send_buf,strlen(send_buf),0);
			}
		}
	}
	
	close(sock_fd);

	return 0;
}








