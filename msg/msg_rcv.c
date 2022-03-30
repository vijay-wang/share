#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>

void err_ocur(void)
{
	perror(strerror(errno));
	exit(EXIT_FAILURE);
	
}

typedef struct {
	long type;
	char ch;
} Msg;



int main(int argc , char *argv[])
{
	int id;
	int ret;
	int i = 0;
	Msg msg_rcv_buf;

	id = msgget(ftok("/etc", 1), IPC_CREAT | 0664);	

	if(id == -1)
		err_ocur();

	while(i < 6) {
		i++;
		msgrcv(id, &msg_rcv_buf, sizeof(msg_rcv_buf), atol(argv[1]) ,0);
		i %= 5;
		printf("{type : %ld    ch : %c}\n", msg_rcv_buf.type, msg_rcv_buf.ch);
		sleep(1);
	}


	return 0;
}
