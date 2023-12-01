//
//  main.cpp
//  CSC-332-Scheduling
//

//make sure all the stats are calculated
//fix the round robin algorithm
//make sure the ready queue is implemented in all algorithms

#include <iostream>
#include <iomanip>
#include <fstream>
#include "process.h"
#include "algorithms.h"

using namespace std;

//func prototype
void outputData(Process processArray[], int numJobs, int totalSwitchTime);
void switchAlgorithm(int num, Process processArray[], int numJobs, int quantum);

const int MAX_JOBS = 100;

int main() {
    const int NUM_ALGORITHMS = 2;
    const int QUANTUM = 50;
    Process processArray[MAX_JOBS];
    int processId, arrivalTime, burstTime, numJobs;
    
    ifstream file("SchedulingAlgorithmsInput.txt");
    if (!file.is_open()) {
        cout << "Error opening file" << endl;
        return -1;
    }
    
    file >> numJobs;
    for (int i = 0; i < numJobs; i++) {
        file >> processId >> arrivalTime >> burstTime;
        processArray[i] = Process(processId, arrivalTime, burstTime);
    }
    
    file.close();
    
    for(int i = 0; i < NUM_ALGORITHMS; i++){
        switchAlgorithm(i, processArray, numJobs, QUANTUM);
    }
    
    return 0;
}

void switchAlgorithm(int num, Process processArray[], int numJobs, int quantum) {
    int totalSwitchTime;
    
    switch (num) {
        case 0:
            cout << "First Come First Serve (non-preemptive):" << endl << endl;
            totalSwitchTime = firstComeFirstServe(processArray, numJobs);
            break;
            
        case 1:
            cout << "Round Robin (preemptive): " << endl << endl;
            totalSwitchTime = roundRobin(processArray, numJobs, quantum);
            break;
            
        default:
            return;
    }
    outputData(processArray, numJobs, totalSwitchTime);
}

void outputData(Process processArray[], int numJobs, int totalSwitchTime){
    
    double efficiency = 0.0;
    int avgTAT = 0;
    int avgWaitingTime = 0;
    int totalTAT = 0;
    int totalWaitingTime = 0;
    int totalTime = 0;
    int totalBurstTime = 0;

    for(int i = 0; i < numJobs; i++){
        totalTAT += processArray[i].getTurnAroundTime();
        totalWaitingTime += processArray[i].getWaitingTime();
        totalBurstTime += processArray[i].getBurstTime();
    }
    
    efficiency = ((double)totalBurstTime / (totalBurstTime + totalSwitchTime)) * 100;
    totalTime = processArray[numJobs - 1].getFinishTime() - processArray[0].getStartTime();
    avgTAT = totalTAT / numJobs;
    avgWaitingTime = totalWaitingTime / numJobs; //not correct yet for roundrobin
    
    cout << "Total Time: " << totalTime << " time units" << endl;
    cout << "Average TAT: " << avgTAT << " time units" << endl;
    cout << "Average Waiting Time: " << avgWaitingTime << " time units" << endl;
    cout << "CPU Efficiency: " << fixed << setprecision(1) << efficiency << "%" << endl << endl;
    
    for(int i = 0; i < numJobs; i++){
        cout << "Process " << processArray[i].getProcessId() << ": " << endl;
        cout << "Service time = " << processArray[i].getBurstTime() << endl;
        cout << "Turn Around Time = " << processArray[i].getTurnAroundTime() << endl << endl;
    }
    
    cout << endl;
}