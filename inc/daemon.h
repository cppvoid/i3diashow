#ifndef DAEMON
#define DAEMON

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>

//return -1 if the daemon cannot be created
int createDaemon();

#endif //DAEMON_H
