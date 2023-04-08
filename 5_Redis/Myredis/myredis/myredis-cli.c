#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

static struct config {
    char *hostip;
    int hostport;
    long repeat;
    int dbnum;
    int interactive;
    char *auth;
} config;

struct redisCommand {
    char *name;
    int arity;
    int flags;
};

static void usage() {
    fprintf(stderr, "usage: redis-cli [-h host] [-p port] [-a authpw] [-r repeat_times] [-n db_num] [-i] cmd arg1 arg2 arg3 ... argN\n");
    fprintf(stderr, "usage: echo \"argN\" | redis-cli [-h host] [-a authpw] [-p port] [-r repeat_times] [-n db_num] cmd arg1 arg2 ... arg(N-1)\n");
    fprintf(stderr, "\nIf a pipe from standard input is detected this data is used as last argument.\n\n");
    fprintf(stderr, "example: cat /etc/passwd | redis-cli set my_passwd\n");
    fprintf(stderr, "example: redis-cli get my_passwd\n");
    fprintf(stderr, "example: redis-cli -r 100 lpush mylist x\n");
    fprintf(stderr, "\nRun in interactive mode: redis-cli -i or just don't pass any command\n");
    exit(1);
}


static int parseOptions(int argc, char **argv) {
    int i;
    printf("argc is:%d\n",argc);
    for(int index=0; index<argc; index++){
        printf("argv[%d]:%s\n",index,argv[index]);
    }
    for (i = 1; i < argc; i++) {
        int lastarg = i==argc-1; //lastarg表示是否是最后一个参数

        if (!strcmp(argv[i],"-h") && !lastarg) {
            // char *ip = zmalloc(32);
            // if (anetResolve(NULL,argv[i+1],ip) == ANET_ERR) {
            //     printf("Can't resolve %s\n", argv[i]);
            //     exit(1);
            // }
            // config.hostip = ip;
            i++;
        } else if (!strcmp(argv[i],"-h") && lastarg) {
            usage();
        } else if (!strcmp(argv[i],"-p") && !lastarg) {
            printf("-p is:%d\n",atoi(argv[i+1]));
            config.hostport = atoi(argv[i+1]);
            i++;
        } else if (!strcmp(argv[i],"-r") && !lastarg) {
            printf("-r is:%d\n",strtoll(argv[i+1],NULL,10));
            config.repeat = strtoll(argv[i+1],NULL,10);
            i++;
        } else if (!strcmp(argv[i],"-n") && !lastarg) {
            printf("-n is:%d\n",atoi(argv[i+1]));
            config.dbnum = atoi(argv[i+1]);
            i++;
        } else if (!strcmp(argv[i],"-a") && !lastarg) {
            printf("-n is:%d\n",argv[i+1]);
            config.auth = argv[i+1];
            i++;
        } else if (!strcmp(argv[i],"-i")) {
            config.interactive = 1;
        } else {
            break;
        }
    }
    printf("parseOptions return value is:%d\n",i);
    return i;
}


int main(int argc, char **argv) {
    int firstarg;
    char **argvcopy;
    struct redisCommand *rc;

    config.hostip = "127.0.0.1";
    config.hostport = 6379;
    config.repeat = 1;
    config.dbnum = 0;
    config.interactive = 0;
    config.auth = NULL;

    firstarg = parseOptions(argc,argv);
    argc -= firstarg;
    argv += firstarg;


}