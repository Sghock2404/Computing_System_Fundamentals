/*
Scott Hockaday
CS 3360 Programming Assignment 2
Due: 4/11/22
*/

#include <iostream>
#include <list>
#include <random>
#include <iterator>
#include <time.h>
#include <cmath>

#define ARR 0
#define DEP 1

const int SIMULATIONS = 10000;

struct event {
    int type; //type of event
    float time = 0; // time of event
};

std::list<event> eventQueue{};

bool serverIdle; // if server is idle
int readyQueueCount; // events in reay queue
double arrivalRate;
double serviceTime;
float t; // time for each event

void scheduleEvent(int type, float t) {
    event e;
    e.time = t;
    e.type = type;
    eventQueue.push_back(e);
}

void Init(float& systemClock, float rnd) {
    systemClock = 0;
    serverIdle = true;
    readyQueueCount = 0;
    float a = -(1.0 / arrivalRate) * log(rnd);
    t = systemClock + a;
    scheduleEvent(ARR, t);
}

void arr_handler(event e, float systemClock, float rnd) {
    if (serverIdle == true) {
        serverIdle = false;
        float s = serviceTime * exp(-serviceTime * rnd);
        scheduleEvent(DEP, systemClock + s);
    }
    else {
        readyQueueCount++;
    }
    double a = -(1.0 / arrivalRate) * log(rnd);
    scheduleEvent(ARR, systemClock + a);
}

void dep_handler(event e, float systemClock, float rnd) {
    if (readyQueueCount == 0) {
        serverIdle = true;
    }
    else {
        readyQueueCount--;
        double s = serviceTime * exp(-serviceTime * rnd);
        s += systemClock;
        scheduleEvent(DEP, systemClock + s);
    }
}

int main(int argc, char* argv[]) {
    srand(time(0));
    float rnd = rand();
    float systemClock = 0.0;
 
    std::cout << "Lambda: ";
    std::cin >> arrivalRate;
    std::cout << "Service time: ";
    std::cin >> serviceTime;
    std::cout << std::endl;

    // initialize runs
    Init(systemClock, rand());

    // run the simulation
    int counter = 0;
    while (counter < SIMULATIONS) {
        double old_clock = systemClock;
        event e = eventQueue.front();
        systemClock = e.time;
        double time_elapsed = systemClock - old_clock;
        if (e.type == ARR) {
            arr_handler(e, systemClock, rand());
        }
        else {
            dep_handler(e, systemClock, rand());
            counter++;
        }
        eventQueue.pop_front();
    }
 
    // compute metrics
    double avg_CPU_Utilization = arrivalRate * serviceTime;
    double avgInside = avg_CPU_Utilization / (1 - avg_CPU_Utilization);
    double avg_Waiting = avgInside - avg_CPU_Utilization;
    double avg_WT = (avg_Waiting / arrivalRate) / SIMULATIONS;
    double average_TAT = serviceTime + avg_WT;
    double throughput = 0.0;

    if (avg_CPU_Utilization <= 1) {
        throughput = arrivalRate;
    }
    else {
        throughput = 1 / serviceTime;
    }

    // display results
    printf("Average turnaround time: %.3lf\n", average_TAT);
    printf("Total throughput: %.3lf\n", throughput);
    printf("Average CPU Utilization: %.3lf\n", avg_CPU_Utilization);
    printf("Average number of processes in ready queue: %lf\n", avg_WT);

    return 0;
}