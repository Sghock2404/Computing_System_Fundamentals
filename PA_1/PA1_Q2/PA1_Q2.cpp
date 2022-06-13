/*
* Scott Hockaday
* CS3360: Computer System Fundamentals
* PA_1: Problem 2
* Due: 3/10/22
*/

#include <time.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <iomanip>
#include <random>

int main() {
    
    //variable declaration and initialization
    const int HOURS_IN_20_YEARS = 175200; // calculation of hours in 20 yrs: 20 yrs * 365 days * 24 hrs
    const int RESTORATION = 10; // given restoration time is exactly 10 hrs
    const int MTBF = 500; // mean time before failure is 500 hrs
    int server_A[400]; // time between failures in server A
    int server_B[400]; // time between failures in server B
    int hour = 0; // tracks time of failures and restorations

    srand(time(NULL)); // generates a new seed each time this program compiles

    // Server A fail and restoration times
    printf("/* Server A */  \n\n");
    int i = 0;

    do {
        server_A[i] = -MTBF * log(1 - (double)rand() / (RAND_MAX));
        hour += server_A[i];

        printf("Server A failed at hour: %d. ", hour);

        hour = hour + RESTORATION;
        printf("Server A restored at hour: %d.\n", hour);
        i++;
    } while (hour < HOURS_IN_20_YEARS);

    printf("\nActual MTBF for Server A: %d hours.\n\n", HOURS_IN_20_YEARS / i);

    // Server B fail and restoration times
    printf("/* Server B */ \n");

    hour = 0; // reset the hour to 0
    int j = 0;

    do {
        server_B[j] = -MTBF * log(1 - (double)rand() / (RAND_MAX));
        hour += server_B[j];

        printf("Server B failed at hour: %d. ", hour);

        hour = hour + RESTORATION;
        printf("Server B restored at hour: %d.\n", hour);
        j++;
    } while (hour < HOURS_IN_20_YEARS);

    printf("\nActual MTBF for Server B: %d hours\n", HOURS_IN_20_YEARS / j);

    // Problem 2b
    int first_Server_Fail = 0;
    int n = 0;

    do {
        if ((server_A[n] - server_B[n]) <= 10 && (server_A[n] - server_B[n]) >= -10) {
            first_Server_Fail = n;
        }
        n++;
    } while (first_Server_Fail == 0);

    int both_Servers_Fail = 0;

    for (int t = 0; t < first_Server_Fail; t++) {
        both_Servers_Fail += server_A[t];
    }
    std::cout << "\n";
    both_Servers_Fail = both_Servers_Fail + (RESTORATION * first_Server_Fail);

    printf("Both servers fail at hour: %d\n\n", both_Servers_Fail);
    return 0;
}
