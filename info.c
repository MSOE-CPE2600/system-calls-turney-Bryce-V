/****************************************************
 * Name: Bryce Vosburg
 * Assignment: Lab 9 – System Calls
 * Section: CPE 2600
 *
 * info.c – Print system information using POSIX calls
 ****************************************************/

#define _GNU_SOURCE
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <sys/types.h>

int main(int argc, char* argv[]){

    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    printf("Current Time (ns): %ld\n", ts.tv_nsec);

    char hostname[256];
    if(gethostname(hostname, sizeof(hostname)) == 0){
        printf("Hostname: %s\n", hostname);
    }

    struct utsname u;
    if(uname(&u) == 0){
        if(u.sysname[0] != '\0'){
            printf("OS Name: %s\n", u.sysname);
        }
        if(u.release[0] != '\0'){
            printf("OS Release: %s\n", u.release);
        }
        if(u.version[0] != '\0'){
            printf("OS Version: %s\n", u.version);
        }
        if(u.machine[0] != '\0'){
            printf("Hardware Type: %s\n", u.machine);
        }
    }

    printf("CPU Count: %d\n", get_nprocs());

    long page_size = sysconf(_SC_PAGESIZE);
    long pages_total = sysconf(_SC_PHYS_PAGES);
    long pages_free = sysconf(_SC_AVPHYS_PAGES);

    long long total_mem = (long long)page_size * pages_total;
    long long free_mem  = (long long)page_size * pages_free;

    printf("Total Memory (bytes): %lld\n", total_mem);
    printf("Free Memory (bytes): %lld\n", free_mem);

    return 0;
}
