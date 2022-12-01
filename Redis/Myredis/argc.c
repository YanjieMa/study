#include <stdio.h>

int main(int argc,const char **argv)
{
	printf("argc is %d\n",argc);
	for(int i=0; i< argc+100; i++){
		printf("argv[%d]:%s\n",i,argv[i]);
	}


	return 0;
}
