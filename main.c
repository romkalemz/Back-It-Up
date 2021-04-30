#include "inc.h"

struct stat st = {0};   // used to check the status of directories

int main(int argc, char **argv) {

    int r_flag_set = 0;
    // CHECK FOR [-r] FLAG IN COMMAND LINE
    if((r_flag_set = checkArgInput(argc, argv)) == -1)
        exit(1);    // if error detected, exit program

    // CREATE .backup/ DIR IF NEEDED
    if(checkBackupDir(r_flag_set) == -1)
        exit(1);    // if error detected, exit program
    
    // TRAVERSE .backup DIR AND RESTORE ALL FILES
    // *** CAREFUL SINCE OVERRIDING IS OCCURING ***
    if(r_flag_set == 1) {
        // restore_backups();
    }

    // CREATE A THREAD TO WAIT FOR TRAVERSING + BACKING UP THREADS TO FINISH
    printf("[NOTE]     backup starting...\n");
    pthread_t mainThread;
    int ret;
    char *initPath = NULL;
    if((ret = pthread_create(&mainThread, NULL, traverse, &initPath)) != 0) {
        fprintf(stderr, "ERROR - %d (%s) -\n", ret, strerror(ret));
        return EXIT_FAILURE;
    }

    // WAIT FOR THE THREADS TO FINISH
    if ((ret = pthread_join(mainThread, NULL)) == -1) {
        fprintf(stderr, "ERROR - %d (%s) -\n", ret, strerror(ret));
        return EXIT_FAILURE;
    }

    printf("[NOTE]     backup finished!\n\n");

    return 0;
}

int checkArgInput(int argc, char **argv) {
    if(argc > 2 || (argc == 2 && strcmp(argv[1], "-r") != 0)) {
        printf("\nERROR - INCORRECT COMMAND LINE INPUT! -\n");
        printf("    Please use this format: \"./backup [-r]\"\n\n");
        return -1;
    } else if(argc == 2 && strcmp(argv[1], "-r") == 0) {
        return 1;
    }
    return 0;
}

int checkBackupDir(int r_flag_set) {
    int ret = stat(".backup", &st);
    if(ret == -1 && errno == ENOENT) {
        if(r_flag_set == 1) {
            printf("\nERROR - NO BACKUP DIRECTORY FOUND! -\n\n");
            return -1;
        }
        printf("\n[NOTE]     Creating .backup/ directory...\n");
        mkdir(".backup", 0700);
        return 0;
    } else if(ret == 0) {
        // directory exists
        return 1;
    } else {
        // some other error occured
        fprintf(stderr, "\nERROR - %s -\n\n", strerror(errno));
        return -1;
    }
}