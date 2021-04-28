#include "inc.h"
/*  MAIN THREAD
 *  - create .backup/ dir if necessary
 *  - create threads to deal with files
*/ 
struct stat st = {0};   // used to check the status of directories

int main(int argc, char **argv) {

    // CHECK FOR [-r] FLAG IN COMMAND LINE
    if(checkArgInput(argc, argv))
        exit(1);    // if error detected, exit program

    // CREATE .backup/ DIR IF NEEDED
    if(checkBackupDir())
        exit(1);    // if error detected, exit program
    // 

    return 0;
}

int checkArgInput(int argc, char **argv) {
    if(argc > 2 || (argc == 2 && strcmp(argv[1], "-r") != 0)) {
        printf("\nERROR - INCORRECT COMMAND LINE INPUT! -\n");
        printf("    Please use this format: \"./backup [-r]\"\n\n");
        return 1;
    }
    return 0;
}

int checkBackupDir() {
    int ret = stat(".backup", &st);
    if(ret == -1 && errno == ENOENT) {
        printf("\n[NOTE]     Creating .backup/ directory...\n");
        mkdir(".backup", 0700);
    } else if(ret == 0) {
        // directory exists
        return 0;
    } else {
        // some other error occured
        fprintf(stderr, "\nERROR - %s -\n\n", strerror(errno));
        return 1;
    }
    return 0;
}