#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#define QTD_MESSAGES 2

int main() {
    int pipeFileDescriptors[2];
    int returnStatus;
    char writeMessages[20] = "Maria";
    char readMessages[20];
    memset(readMessages, '\0', sizeof(char) * 20);

    returnStatus = pipe(pipeFileDescriptors);

    if (returnStatus == -1) {
        printf("Error when create pipe\n");
        return 1;
    }
    pid_t Id = fork();
    if(Id > 0){
	    write(pipeFileDescriptors[1], writeMessages, sizeof(char) * 20);
	    printf("Writing Message is %s\n", writeMessages);
    }else{
		read(pipeFileDescriptors[0], readMessages, sizeof(char) * 20);
		printf("Reading Message is %s\n", readMessages);
	    }
    return 0;
}

