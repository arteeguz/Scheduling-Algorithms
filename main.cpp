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
void outputData(Process processArray[], int numJobs, int endTime, ofstream &outFile, const string &algorithmName);
void switchAlgorithm(int num, Process processArray[], int numJobs, int quantum, ofstream &outFile);

const int MAX_JOBS = 100;

int main() {
    const int NUM_ALGORITHMS = 2;
    const int QUANTUM = 50;
    Process processArray[MAX_JOBS];
    int processId, arrivalTime, burstTime, numJobs;

    ifstream file("./Data/SchedulingAlgorithmsInput.txt");
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

    ofstream outFile("./Data/output.txt");
    if (!outFile.is_open()) {
        cout << "Error opening output file" << endl;
        return -1;
    }

    for (int i = 0; i < NUM_ALGORITHMS; i++) {
        switchAlgorithm(i, processArray, numJobs, QUANTUM, outFile);
    }

    outFile.close();
    return 0;
}


void switchAlgorithm(int num, Process processArray[], int numJobs, int quantum, ofstream &outFile) {
    int endTime;
    string algorithmName;

    switch (num) {
        case 0:
            algorithmName = "First Come First Serve (non-preemptive)";
            cout << algorithmName << ":" << endl << endl;
            endTime = firstComeFirstServe(processArray, numJobs);
            break;

        case 1:
            algorithmName = "Round Robin (preemptive)";
            cout << algorithmName << ":" << endl << endl;
            endTime = roundRobin(processArray, numJobs, quantum);
            break;

        default:
            return;
    }
    outputData(processArray, numJobs, endTime, outFile, algorithmName);
}


void outputData(Process processArray[], int numJobs, int endTime, ofstream &outFile, const string &algorithmName) {
    double efficiency = 0.0;
    int avgTAT = 0;
    int avgWaitingTime = 0;
    int totalTAT = 0;
    int totalWaitingTime = 0;
    int totalTime = 0;
    int totalBurstTime = 0;

    for (int i = 0; i < numJobs; i++) {
        totalTAT += processArray[i].getTurnAroundTime();
        totalWaitingTime += processArray[i].getWaitingTime();
        totalBurstTime += processArray[i].getBurstTime();
    }

    efficiency = ((double)totalBurstTime / (totalBurstTime + processArray[numJobs - 1].getTotalSwitchTime())) * 100;
    totalTime = endTime - processArray[0].getStartTime();
    avgTAT = totalTAT / numJobs;
    avgWaitingTime = totalWaitingTime / numJobs;

    cout << "Algorithm: " << algorithmName << endl;
    cout << "Total Time: " << totalTime << " time units" << endl;
    cout << "Average TAT: " << avgTAT << " time units" << endl;
    cout << "Average Waiting Time: " << avgWaitingTime << " time units" << endl;
    cout << "CPU Efficiency: " << fixed << setprecision(1) << efficiency << "%" << endl << endl;

    outFile << "Algorithm: " << algorithmName << endl;
    outFile << "Total Time: " << totalTime << " time units" << endl;
    outFile << "Average TAT: " << avgTAT << " time units" << endl;
    outFile << "Average Waiting Time: " << avgWaitingTime << " time units" << endl;
    outFile << "CPU Efficiency: " << fixed << setprecision(1) << efficiency << "%" << endl << endl;

    for (int i = 0; i < numJobs; i++) {
        cout << left << setw(15) << ("P" + to_string(processArray[i].getProcessId()))
             << setw(20) << processArray[i].getBurstTime()
             << setw(20) << processArray[i].getTurnAroundTime() << endl;

        // outFile << "Process " << processArray[i].getProcessId() << ": " << endl;
        // outFile << "Service time = " << processArray[i].getBurstTime() << endl;
        // outFile << "Turn Around Time = " << processArray[i].getTurnAroundTime() << endl << endl;
    }

    cout << endl;
    outFile << endl;
}