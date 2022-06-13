/*
Scott Hockaday
CS3360: Computer System Fundamentals
PA_1: Problem 1
*/
#include <time.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <iomanip>
#include <random>
#include <tuple>

int main() {

    // variable declaration and initialization
    const int PROCESSES = 1000; // # of total processes
    const double AVG_ARRIVAL_RATE = 2.0;  // arrival rate of 2 processes per second
    const double AVG_SERVICE_TIME = 1.0; // average service time of 1 second
    double random_numbers[PROCESSES]; // array for random numbers
    double time_Bet_Arrival[PROCESSES]; // array to hold the times between arrivals
    double service_Time[PROCESSES]; // array for service times
    double sum_Arrival_Time = 0.0; // tracks total arrival time
    double sum_Service_Time = 0.0; // tracks total service time
    double actual_Average_Rate = 0.0;
    double actual_Average_Service = 0.0;
    auto result = std::make_tuple(0, 0.0, 0.0);

    srand(time(NULL)); // generate a random seed each time this program runs

    // for-loop to display the tuple, get results of arrival and service time
    for (int i = 0; i < PROCESSES; i++) {

        // generate random numbers to calculate time between process arrivals
        random_numbers[i] = ((double)rand() / (RAND_MAX));
        time_Bet_Arrival[i] = -(1.0 / AVG_ARRIVAL_RATE) * log(random_numbers[i]);

        // total arrival time
        sum_Arrival_Time = sum_Arrival_Time + time_Bet_Arrival[i];

        // calculate random service time for each process
        service_Time[i] = -AVG_SERVICE_TIME * log(1 - (double)rand() / (RAND_MAX));

        // total service time
        sum_Service_Time = sum_Service_Time + service_Time[i];

        // create tuple to display results
        auto result = std::make_tuple(i + 1, sum_Arrival_Time, service_Time[i]);
        std::cout << "<" << std::get<0>(result) << ", "<<
            std::fixed << std::setprecision(3) << std::get<1>(result) << ", " <<
            std::get<2>(result) << ">\n";
    }
    // calculate actual average arrival and service time
    actual_Average_Rate = sum_Arrival_Time / PROCESSES;
    actual_Average_Service = sum_Service_Time / PROCESSES;

    // answer other questions on assignment
    printf("\n\nActual average arrival rate: %lf", actual_Average_Rate);
    printf("\nActual average service time: %lf\n\n", actual_Average_Service);

    return 0;
}
