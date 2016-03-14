#include "daemon.h"

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>

int createDaemon()
{
	pid_t pid;

	pid = fork();

	if(pid < 0)
	{
		return -1;
	}

	if(pid > 0)
	{
		exit(EXIT_SUCCESS);
	}

	if(setsid() < 0)
	{
		return -1;
	}

    signal(SIGCHLD, SIG_IGN);
	signal(SIGHUP, SIG_IGN);

	pid = fork();

	if(pid < 0)
	{
		return -1;
	}

	if(pid > 0)
	{
		exit(EXIT_SUCCESS);
	}

	umask(0);
	chdir("/");

	int x;
	for (x = sysconf(_SC_OPEN_MAX); x>0; x--)
	{
		close (x);
	}

	openlog("i3diashow", LOG_PID, LOG_DAEMON);

	return 0;
}
