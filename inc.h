#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <semaphore.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <dirent.h>

// MAIN THREAD FUNCTIONS
int checkArgInput(int, char**);
int checkBackupDir(int);

// TRAVERSE FILES FUNCTIONS
void *traverse(void *path);
int isFile(char* pathname);
int isDirectory(char* pathname);
int checkPermissions(char* pathname);