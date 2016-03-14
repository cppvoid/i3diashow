#include "daemon.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

int createDaemon()
{
	pid_t pid;

	pid = fork();

	if(pid < 0)
	{
		exit(EXIT_FAILURE);
		return -1;
	}

	if(pid > 0)
	{
		exit(EXIT_SUCCESS);
	}

	if(setsid() < 0)
	{
		exit(EXIT_FAILURE);
		return -1;
	}

	pid = fork();

	if(pid < 0)
	{
		exit(EXIT_FAILURE);
		return -1;
	}

	if(pid > 0)
	{
		exit(EXIT_SUCCESS);
	}

	umask(0);

	if((chdir("/")) < 0)
	{
		exit(EXIT_FAILURE);
		return -1;
	}

	int x;
	for (x = sysconf(_SC_OPEN_MAX); x > 0; x--)
	{
		close (x);
	}

	return 0;
}
