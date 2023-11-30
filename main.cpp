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
#include <vector>
#include <queue>

using namespace std;

const int MAX_JOBS = 100;
const int SWITCH_TIME = 2;

class Process {
public:
    Process() {
        this->processId = 0;
        this->turnAroundTime = 0;
        this->startTime = 0;
        this->finishTime = 0;
        this->burstTime = 0;
        this->arrivalTime = 0;
        this->waitingTime = 0;
    }
    
    Process(int processId, int arrivalTime, int burstTime) {
        this->processId = processId;
        this->arrivalTime = arrivalTime;
        this->burstTime = burstTime;
    }
    
    int getProcessId() {
        return processId;
    }

    void setProcessId(int processId) {
        this->processId = processId;
    }

    int getTurnAroundTime() {
        return turnAroundTime;
    }

    void setTurnAroundTime(int turnAroundTime) {
        this->turnAroundTime = turnAroundTime;
    }

    int getStartTime() {
        return startTime;
    }

     void setStartTime(int startTime) {
        this->startTime = startTime;
    }

    int getFinishTime() {
        return finishTime;
    }

    void setFinishTime(int finishTime) {
        this->finishTime = finishTime;
    }
        
    int getBurstTime() {
        return burstTime;
    }

    void setBurstTime(int burstTime) {
        this->burstTime = burstTime;
    }
    
    int getArrivalTime() {
        return arrivalTime;
    }

    void setArrivalTime(int arrivalTime) {
        this->arrivalTime = arrivalTime;
    }
    
    int getWaitingTime() {
        return waitingTime;
    }

    void setWaitingTime(int waitingTime) {
        this->waitingTime = waitingTime;
    }

private:
    int processId; //id of the process
    int turnAroundTime; //Total time process spent in the system
    int arrivalTime; //Time the process enters the system
    int finishTime; //Time the process finishes executing
    int burstTime; //Time required to execute
    int startTime; //Time the process beigns executing
    int waitingTime; //Time the process spent before beginning its execution
};

int firstComeFirstServe(Process processArray[], int numJobs) {
    int currentTime = 0;
    int totalSwitchTime = 0;

    for (int i = 0; i < numJobs; i++) {
        if (currentTime < processArray[i].getArrivalTime()) {
            currentTime = processArray[i].getArrivalTime();
        }
        if (i > 0) {
            currentTime += SWITCH_TIME;
            totalSwitchTime += SWITCH_TIME;
        }
        processArray[i].setWaitingTime(currentTime - processArray[i].getArrivalTime());
        processArray[i].setStartTime(currentTime);
        currentTime += processArray[i].getBurstTime();
        processArray[i].setFinishTime(currentTime);
        processArray[i].setTurnAroundTime(currentTime - processArray[i].getArrivalTime());
    }
    return totalSwitchTime;
}

//fix algorithm
int roundRobin(Process processArray[], int numJobs, int quantum) {
    queue<int> processQueue;
    vector<int> exeOrder;
    vector<bool> addedToQueue(numJobs, false);
    int currentTime = 0;
    int totalSwitchTime = 0;
    
    for(int i = 0; i < numJobs; i++){
        processArray[i].setStartTime(0);
    }

    while (exeOrder.size() < numJobs) {
        for (int i = 0; i < numJobs; ++i) {
            if (processArray[i].getArrivalTime() <= currentTime && !addedToQueue[i]) {
                processQueue.push(i);
                addedToQueue[i] = true;
            }
        }

        if (!processQueue.empty()) {
            int idx = processQueue.front();
            processQueue.pop();

            int timeSlice = min(quantum , processArray[idx].getBurstTime());

            if (processArray[idx].getStartTime() == 0) {
                processArray[idx].setWaitingTime(currentTime - processArray[idx].getArrivalTime());
                processArray[idx].setStartTime(currentTime);
            }

            currentTime += timeSlice;
            processArray[idx].setBurstTime(processArray[idx].getBurstTime() - timeSlice);

            if (processArray[idx].getBurstTime() == 0) {
                processArray[idx].setFinishTime(currentTime);
                processArray[idx].setTurnAroundTime(currentTime - processArray[idx].getArrivalTime());
                exeOrder.push_back(processArray[idx].getProcessId());
            } else {
                processQueue.push(idx);
            }
        } else {
            int nextArrivalTime = INT_MAX;
            for (int i = 0; i < numJobs; i++) {
                if (!addedToQueue[i] && processArray[i].getArrivalTime() < nextArrivalTime) {
                    nextArrivalTime = processArray[i].getArrivalTime();
                }
            }
            currentTime = nextArrivalTime;
        }
    }
    return totalSwitchTime;
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

int main() {
    const int NUM_ALGORITHMS = 2;
    const int QUANTUM = 50;
    Process processArray[MAX_JOBS];
    int processId, arrivalTime, burstTime, numJobs;
    
    ifstream file("/Users/jawadrada/Desktop/CSC-332-Scheduling/SchedulingAlgorithmsInput.txt");
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
