//
//  main.cpp
//  CSC-332-Scheduling
//

//rewrite the round robin algorithm
//make sure the ready queue is implemented in all algorithms
//ask professor about ready queue and output format

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
    int endTime;
    
    switch (num) {
        case 0:
            cout << "First Come First Serve (non-preemptive):" << endl << endl;
            endTime = firstComeFirstServe(processArray, numJobs);
            break;
            
        case 1:
            cout << "Round Robin (preemptive): " << endl << endl;
            endTime = roundRobin(processArray, numJobs, quantum);
            break;
            
        default:
            return;
    }
    outputData(processArray, numJobs, endTime);
}

void outputData(Process processArray[], int numJobs, int endTime){
    
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
    
    efficiency = ((double)totalBurstTime / (totalBurstTime + processArray[numJobs - 1].getTotalSwitchTime())) * 100;
    totalTime = endTime - processArray[0].getStartTime();
    avgTAT = totalTAT / numJobs;
    avgWaitingTime = totalWaitingTime / numJobs; //not correct yet for roundrobin
    
    cout << "Total Time: " << totalTime << " time units" << endl;
    cout << "Average TAT: " << avgTAT << " time units" << endl;
    cout << "Average Waiting Time: " << avgWaitingTime << " time units" << endl;
    cout << "CPU Efficiency: " << fixed << setprecision(1) << efficiency << "%" << endl << endl;
    cout << left << setw(15) << "Process" << setw(20) << "Service Time" << setw(20) << "Turn Around Time" << endl;

    for(int i = 0; i < numJobs; i++){
        cout << left << setw(15) << ("P" + to_string(processArray[i].getProcessId()))
             << setw(20) << processArray[i].getBurstTime()
             << setw(20) << processArray[i].getTurnAroundTime() << endl;
        
//        cout << "Process " << processArray[i].getProcessId() << ": " << endl;
//        cout << "Service time = " << processArray[i].getBurstTime() << endl;
//        cout << "Turn Around Time = " << processArray[i].getTurnAroundTime() << endl << endl;
    }

    cout << endl;
}
