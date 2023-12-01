#ifndef Process_H
#define Process_H
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

    int getRemainingBurstTime() {
        return remainingBurstTime;
    }

    void setRemainingBurstTime(int remaining) {
        remainingBurstTime = remaining;
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
    int burstTime; //Time required to execute ----
    int remainingBurstTime = burstTime; //Don't change burstTime once its set, we need to reuse it for RR func
    int startTime; //Time the process beigns executing
    int waitingTime; //Time the process spent before beginning its execution
};
#endif