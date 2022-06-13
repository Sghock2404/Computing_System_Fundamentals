// PA2_COPY.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <random>

#define ARR 0;
#define DEP 1;

using namespace std;

int const SIMULATIONS = 10000; // number of simulations to run
// enum EventType { ARR, DEP }; // defining event types arrival and departure

struct event {
    int type; // type of event
    float time; // time of event
    event* nextEvent; // points to next event
};

float systemClock;
bool serverIdle; // indicates if server is idle or not
double arrivalRate;
double serviceTime;
int readyQueueCount;
float t; // time for each event
event* eq_head;

void schedule_event(int type, double time, event head) {
    event* e = new event;
    e->type = type;
    e->time = time;
    e->nextEvent = NULL;
}

void Init(float& systemClock, float rnd) {
    systemClock = 0;
    serverIdle = true;
    readyQueueCount = 0;
    eq_head = NULL;
    float a = -(1.0 / arrivalRate) * log(rnd);
    t = systemClock + a;
}

void arr_handler(int type, float systemClock, float rnd) {
    if (serverIdle == true) {
        serverIdle = false;
        float s = serviceTime * exp(-serviceTime * rnd);
    }
    else {
        double a = -(1.0 / arrivalRate) * log(rnd);
        readyQueueCount++;
    }
}

void dep_handler(int type, float systemClock, float rnd) {
    if (readyQueueCount == 0) {
        serverIdle = true;
    }
    else {
        readyQueueCount--;
        double s = serviceTime * exp(-serviceTime * rnd);
        s += systemClock;
    }
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    float systemClock;

    std::cout << "Lambda: ";
    std::cin >> arrivalRate;
    std::cout << "Service Time: ";
    std::cin >> serviceTime;
    std::cout << "\n";
    // sscanf(argv[1], "%lf", &arrivalRate);
    // sscanf(argv[2], "%lf", &serviceTime);

    // initialize conditions
    Init(systemClock, rand());

    // create events list
    int arrivalEvent = 0; // used to keep track of arrival events
    int departureEvent = 1; // used to keep track of departure events

    while (!(arrivalEvent > SIMULATIONS) || !(departureEvent > SIMULATIONS)) {

        event* eventPtr; // to traverse list

        if (arrivalEvent <= SIMULATIONS) {
            event* e = new event;
            e->type = 0;
            e->time = arrivalEvent * t;
            e->nextEvent = NULL;

            if (eq_head == NULL) {
                eq_head = e;
            }
            else {
                eventPtr = eq_head;

                while (eventPtr->nextEvent) {
                    eventPtr = eventPtr->nextEvent;
                }
                eventPtr->nextEvent = e;
            }
            arrivalEvent++;
        }

        if (departureEvent * t + serviceTime <= (arrivalEvent * t)
            || arrivalEvent >= SIMULATIONS) {
            event* e = new event;
            e->type = 1;
            e->time = departureEvent * t + serviceTime;
            e->nextEvent = NULL;
            eventPtr = eq_head;

            while (eventPtr->nextEvent) {
                eventPtr = eventPtr->nextEvent;
            }

            eventPtr->nextEvent = e;
            departureEvent++;
        }
    }

    // run simulation
    event* eventPtr = eq_head;
    double duration;
    double old_clock;
    int counter = 0;
    while (counter < SIMULATIONS) {

        event* e = eq_head;
        float temp_busy = 0;
        old_clock = systemClock; // used to calculate CPU utilization
        systemClock = e->time; // current time
        duration = systemClock - old_clock;

        if (!serverIdle) {
            temp_busy += duration;
        }

        switch (e->type) {
        case 0:
            arr_handler(arrivalEvent, systemClock, rand());
            break;

        case 1:
            dep_handler(departureEvent, systemClock, rand());
            break;
        }

        // delete e from event queue
        eventPtr = eq_head->nextEvent;
        delete eq_head;
        eq_head = eventPtr;
        counter++;
    }
    float total_time = systemClock;

    // report metrics
    double avg_CPU_Utilization = arrivalRate * serviceTime;
    double avg_Interarrival = avg_CPU_Utilization / (1 - avg_CPU_Utilization);
    double avg_Waiting = avg_Interarrival - avg_CPU_Utilization;
    double avg_WT = avg_Waiting / arrivalRate;
    double avg_TAT = serviceTime + avg_WT;

    double throughput = 0.0;

    if (avg_CPU_Utilization <= 1) {
        throughput = arrivalRate;
    }
    else {
        throughput = 1 / serviceTime;
    }

    printf("Average turnaround time: %.3lf\n", avg_TAT);
    printf("Total throughput: %.3lf\n", throughput);
    printf("Average CPU utilization: %.3lf\n", avg_CPU_Utilization);
    printf("Average number of processes in the ready queue: %.3lf\n", arrivalRate * avg_TAT);

    return 0;
}