#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>

int main(void)
{
	char *fw_buf = "I am your father\n";
	printf("fw_buf size : %ld\n", strlen(fw_buf));
	char *sw_buf = "I am your son\n";
	char fr_buf[32];
	char sr_buf[32];
	int fd[2];

	if(pipe(fd) == -1) {
		perror(strerror(errno));
		exit(EXIT_FAILURE);
	}

	pid_t pid = fork();
	
	if(pid  == -1) {
		perror(strerror(errno));
		exit(EXIT_FAILURE);
	}

	



	if(pid == 0) {
		close(fd[1]);
		int i=0;
		int len;
		while(1) {
			memset(sr_buf, '\0', sizeof(sr_buf));
			len = read(fd[0], sr_buf, sizeof(sr_buf));
		//	printf("read %d char\n", len);
			//write(STDOUT_FILENO, sr_buf, sizeof(sr_buf));	
			printf("SON PRINT : %s", sr_buf);
			sleep(1);
		}
	} else {
		close(fd[0]);
		int len;
//		printf("father pid:%d\n", getpid());
		while(1) {
			len = write(fd[1], fw_buf, strlen(fw_buf));	
		//	printf("write %d char\n", len);
			sleep(1);
		}
	}

	return 0;
}
