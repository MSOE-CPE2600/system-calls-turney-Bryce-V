/****************************************************
 * Name: Bryce Vosburg
 * Assignment: Lab 9 – System Calls
 * Section: CPE 2600
 *
 * finfo.c – File information using stat()
 ****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

static void print_type(mode_t mode){
    if(S_ISREG(mode))
        printf("Type: Regular file\n");
    else if(S_ISDIR(mode))
        printf("Type: Directory\n");
    else if(S_ISLNK(mode))
        printf("Type: Symbolic link\n");
    else if(S_ISCHR(mode))
        printf("Type: Character device\n");
    else if(S_ISBLK(mode))
        printf("Type: Block device\n");
    else if(S_ISFIFO(mode))
        printf("Type: FIFO/pipe\n");
    else if(S_ISSOCK(mode))
        printf("Type: Socket\n");
    else
        printf("Type: Unknown\n");
}

static void print_perms(mode_t mode){
    char perms[10];

    // User
    if(mode & S_IRUSR)
        perms[0] = 'r'; 
    else
        perms[0] = '-';

    if(mode & S_IWUSR)
        perms[1] = 'w';
    else
        perms[1] = '-';

    if(mode & S_IXUSR)
        perms[2] = 'x';
    else
        perms[2] = '-';

    // Group
    if(mode & S_IRGRP)
        perms[3] = 'r';
    else
        perms[3] = '-';

    if(mode & S_IWGRP) 
        perms[4] = 'w';
    else
        perms[4] = '-';

    if(mode & S_IXGRP)
        perms[5] = 'x';
    else
        perms[5] = '-';

    // Other
    if(mode & S_IROTH)
        perms[6] = 'r';
    else
        perms[6] = '-';

    if(mode & S_IWOTH)
        perms[7] = 'w';
    else
        perms[7] = '-';

    if(mode & S_IXOTH)
        perms[8] = 'x';
    else
        perms[8] = '-';

    perms[9] = '\0';

    printf("Permissions: %s\n", perms);
}


int main(int argc, char *argv[]){
    if(argc != 2){
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    struct stat st;

    if(stat(argv[1], &st) != 0){
        perror("stat");
        return 1;
    }

    print_type(st.st_mode);
    print_perms(st.st_mode);

    printf("Owner UID: %u\n", st.st_uid);
    printf("Size (bytes): %ld\n", st.st_size);

    char buf[64];
    struct tm *timeinfo = localtime(&st.st_mtime);
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", timeinfo);
    printf("Last Modified: %s\n", buf);

    return 0;
}
