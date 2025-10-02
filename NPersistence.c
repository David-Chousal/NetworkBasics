/*
* Name: David Chousal
* Date: 09/30/2025 (the day you have lab)
* Title: Lab2 – NPersistence.c
* Description: This program computes the non-persistent senario
*/

//COEN 146L : Lab2, step 4
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
        // No arguments needed for this step
        if (argc != 1) {
                fprintf(stderr, "usage: %s\n", argv[0]);
                return 1;
        }
        //Declare and values to n (n connections), np (np parralel connections), RTT0, RTT1, RTT2, RTTHTTP, RTTDNS,  
        int np;
        int n = 10;
        int RTT0, RTT1, RTT2, RTTHTTP, RTTDNS, RTTTotal;
        RTT0 = 3;
        RTT1 = 20;
        RTT2 = 26;
        RTTHTTP = 47;
        RTTDNS = RTT0 + RTT1 + RTT2;

        //find how many np (parralel connections)s
        np = n / 2;

        //find the total time for one object: DNS + 2*RTTHTTP (handshake + req/resp)
        RTTTotal = RTTDNS + 2 * RTTHTTP;        // 4a
        printf("One object: %d msec\n", RTTTotal);
        printf("Non-Persistent 6 objects: %d msec\n", 6 * RTTTotal); // 4b

        //find how many np (parralel connections)
        printf("%d parallel connection - Persistent: %d msec\n", np, RTTTotal); // 4c
        printf("%d parallel connection - Non-Persistent: %d msec\n", np, 6 * RTTTotal); // 4d

return 0;
}