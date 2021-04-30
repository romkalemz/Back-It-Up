#include "inc.h"

/**********************************************************************
Take as input some path. Recursively traverse the files that are readable.
Create a thread for each readable file and begin backup process.
**********************************************************************/

void *traverse(void *path) {

	char *inputPath = path;
	//if no input given at first entry
	//take current working directory
	if(strcmp(inputPath, "") == 0) {
		getcwd(inputPath, 200);
    }
    // ignore .backup/ and .git/ for now
    else if((strcmp(inputPath, ".backup") == 0) || (strcmp(inputPath, ".git") == 0)) {
        return NULL;
    }

	//first check if the file/dir is readable
	//0 if readable
	if(checkPermissions(inputPath) == 0) {

	    //check if its a directory
	    if(isDirectory(inputPath)) {

			//change into the directory inputted
			chdir(inputPath);

			//print out names of files in dir
			struct dirent* dp;
			DIR* myDir = opendir(".");

			//find permissions of files/dir inside of dir
			while((dp = readdir(myDir)) != NULL) {
				//ignore (. and ..)
				if(strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
					//check permissions for each entry
					if(checkPermissions(dp->d_name) == 0) {
						//check if entry is a file
						if(isFile(dp->d_name)) {
                            // CREATE THREAD HERE
                           printf("[THREAD 0] %s\n", dp->d_name);
                        }
						//if not, check if its a directory
						else if(isDirectory(dp->d_name)) {
                            traverse((void *)dp->d_name);
						}
					}
					else {
						fprintf(stderr, "%s: %s\n", strerror(errno), inputPath);
					}
				}
			}
			chdir("..");
		}
	}

	//permissions were denied
	else 
		fprintf(stderr, "%s: %s\n", strerror(errno), inputPath);

	return NULL;
}

int checkPermissions(char* pathname) {
	return access(pathname, R_OK);
}

int isFile(char* pathname) {
	struct stat area, *s = &area;
	return (lstat(pathname, s) == 0) &&
					S_ISREG(s->st_mode);
}

int isDirectory(char* pathname) {
	struct stat area, *s = &area;
	return (lstat(pathname, s) == 0) &&
		S_ISDIR(s->st_mode);
}
