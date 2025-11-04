/****************************************************
 * Name: Bryce Vosburg
 * Assignment: Lab 9 – System Calls
 * Section: CPE 2600
 *
 * pinfo.c – Print process scheduling info
 ****************************************************/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sched.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>

static const char *policy_to_string(int p){
    switch(p){
        case SCHED_OTHER:
            return "SCHED_OTHER";
        case SCHED_FIFO:
            return "SCHED_FIFO";
        case SCHED_RR:
            return "SCHED_RR";
        case SCHED_BATCH:
            return "SCHED_BATCH";
        case SCHED_IDLE:
            return "SCHED_IDLE";
        case SCHED_DEADLINE:
            return "SCHED_DEADLINE";
        default:
            return "UNKNOWN";
    }
}

int main(int argc, char *argv[]){
    pid_t pid;

    if(argc == 1){
        pid = getpid();
    }else{
        pid = atoi(argv[1]);
        if(pid <= 0){
            fprintf(stderr, "Invalid PID.\n");
            return 1;
        }
    }

    errno = 0;
    int prio = getpriority(PRIO_PROCESS, pid);
    if(errno != 0){
        perror("getpriority");
        return 1;
    }

    int pol = sched_getscheduler(pid);
    if(pol < 0){
        perror("sched_getscheduler");
        return 1;
    }

    printf("Process ID: %d\n", pid);
    printf("Priority: %d\n", prio);
    printf("Scheduling Method: %s\n", policy_to_string(pol));

    return 0;
}
