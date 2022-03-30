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

int main(void)
{
	int id;
	int ret;
	int i = 0;
	Msg msg_buf[5] = {
		{ 1, 'a' },
		{ 2, 'b' },
		{ 3, 'c' },
		{ 4, 'd' },
		{ 5, 'e' },
	};	

	id = msgget(ftok("/etc", 1),IPC_CREAT | 0664);	

	if(id == -1)
		err_ocur();

	while((i%5) < 5) {
		msgsnd(id, &msg_buf[i%5], sizeof(msg_buf[i%5]), 0);
		i++;
		sleep(1);
	}



	return 0;
}
