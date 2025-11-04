/****************************************************
 * Name: Bryce Vosburg
 * Assignment: Lab 9 – System Calls
 * Section: CPE 2600
 *
 * pmod.c – Modify priority and sleep
 ****************************************************/

#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main(void){

    int result = nice(10);
    if(result == -1){
        perror("nice");
    }

    struct timespec ts;
    ts.tv_sec = 1;
    ts.tv_nsec = 837272638;

    nanosleep(&ts, NULL);

    printf("Goodbye from pmod\n");

    return 0;
}
