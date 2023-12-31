#include "process.h"
#include <iostream>
#include <climits>
#include <vector>
#include <queue>

using namespace std;

const int SWITCH_TIME = 2;

int firstComeFirstServe(Process processArray[], int numJobs) {
    int currentTime = 0;
    int totalSwitch = 0;

    for (int i = 0; i < numJobs; i++) {
        if (currentTime < processArray[i].getArrivalTime()) {
            currentTime = processArray[i].getArrivalTime();
        }
        if (i > 0) {
            currentTime += SWITCH_TIME;
            totalSwitch += SWITCH_TIME;
        }
        processArray[i].setWaitingTime(currentTime - processArray[i].getArrivalTime());
        processArray[i].setStartTime(currentTime);
        currentTime += processArray[i].getBurstTime();
        processArray[i].setFinishTime(currentTime);
        processArray[i].setTurnAroundTime(currentTime - processArray[i].getArrivalTime());
    }
    processArray[numJobs - 1].setTotalSwitchTime(totalSwitch);
    return currentTime;
}

//fix algorithm
int roundRobin(Process processArray[], int numJobs, int quantum) {
    queue<int> processQueue;
    vector<int> exeOrder;
    vector<bool> addedToQueue(numJobs, false);
    int currentTime = 0;
    int totalSwitch = 0;
    
    for(int i = 0; i < numJobs; i++){
        processArray[i].setStartTime(0);
    }

    while (exeOrder.size() < numJobs) {
        for (int i = 0; i < numJobs; i++) {
            if (processArray[i].getArrivalTime() <= currentTime && !addedToQueue[i]) {
                processQueue.push(i);
                addedToQueue[i] = true;
            }
        }

        if (!processQueue.empty()) {
            int idx = processQueue.front();
            processQueue.pop();

            int timeSlice = min(quantum , processArray[idx].getRemainingBurstTime());

            if (processArray[idx].getStartTime() == 0) {
                processArray[idx].setWaitingTime(currentTime - processArray[idx].getArrivalTime());
                processArray[idx].setStartTime(currentTime);
                currentTime += SWITCH_TIME;
                totalSwitch += SWITCH_TIME;
            }

            currentTime += timeSlice;
            processArray[idx].setRemainingBurstTime(processArray[idx].getRemainingBurstTime() - timeSlice);
            currentTime += SWITCH_TIME;
            totalSwitch += SWITCH_TIME;

            if (processArray[idx].getRemainingBurstTime() == 0) {
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
    
    processArray[numJobs - 1].setTotalSwitchTime(totalSwitch);
    return currentTime;
}
