#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	pid_t crianca = fork();
	if (crianca > 0)
		sleep(10);
	if (crianca == 0)
		exit(0);
	return 0;
}
