#include <stdio.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>


int main(int argc, char ** argv)
{
	const char *sock_path = "/home/ma/tmp/my_unix_socket";

	int sock_fd = socket(AF_UNIX,SOCK_STREAM,0);
	if(sock_fd < 0){
		perror("socket error");
		exit(-1);
		/*
		fprintf(stderr,"Error: %s(errno:%d)\n",strerr(errno),errno);
		*/
	}
	
	if(remove(sock_path) == -1 && errno != ENOENT){
		perror("remove error");
		exit(-1);
	}

	struct sockaddr_un addr;
	memset(&addr,0,sizeof(struct sockaddr_un));
	addr.sun_family = AF_UNIX;
	strncpy(addr.sun_path,sock_path,sizeof(addr.sun_path)-1);

	int ret = bind(sock_fd,(struct sockaddr *)&addr,sizeof(struct sockaddr_un));
	if(ret < 0){
		perror("bind error");
		exit(-1);
	}

	ret = listen(sock_fd,3);
	if(ret < 0){
		perror("listen error");
		exit(-1);
	}
	printf("waiting...\n");

	int com_fd;
	char recv_buf[1024];
	struct sockaddr_un client_addr;
	socklen_t client_addr_len;
	client_addr_len = sizeof(struct sockaddr_un);

	while(1){
		com_fd = accept(sock_fd,(struct sockaddr *)&client_addr,&client_addr_len);
		if(com_fd < 0){
			perror("accept error");
			exit(-1);
		}
		printf("client addr:%s\n",client_addr.sun_path);


		int n;
		while((n = read(com_fd,recv_buf,1024)) > 0){
			if(write(STDOUT_FILENO,recv_buf,n) != n){
				printf("write error\n");
			}
		}
		if(n < 0){
			perror("read error");
			exit(-1);
		}
		else if(n == 0){
			printf("client closed\n");
			close(com_fd);
		}
	}


	return 0;
}








