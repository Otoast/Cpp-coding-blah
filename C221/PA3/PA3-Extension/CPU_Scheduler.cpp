#include <iostream>
#include <queue>
#include <string>
#include <thread>
#include <chrono>
#include "PriorityQueueHeap.h"

class Process {
public:
    Process() {};
    Process(int id, int processing_time) : id(id), processing_time(processing_time) {}

    int getId() const {
        return id;
    }

    int getProcessingTime() const {
        return processing_time;
    }

    bool operator >(const Process& other) const {
        // TODO Student
    }

private:
    int id;
    int processing_time;
};

class CPUScheduler {
public:
    void scheduleProcess(const Process& process) {
        // TODO Student
    }

    void runScheduler() {
        while (true) {
            if (!process_queue.is_pq_empty()) {
                // TODO STUDENT: Get the highest priority process and store in current_process (shortest processing time)
                Process current_process;

                // Log process being run
                std::cout << "Processing Process " << current_process.getId() << " with time "
                          << current_process.getProcessingTime() << " seconds" << std::endl;

                // Simulate processing time with sleep
                std::this_thread::sleep_for(std::chrono::seconds(current_process.getProcessingTime()));
            }
            else {
                // If the queue is empty, sleep for a short time before checking again
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        }
    }

private:
    PriorityQueueHeap<Process, std::greater<Process>> process_queue;
};

int main() {
    CPUScheduler scheduler;
    std::thread scheduler_thread(&CPUScheduler::runScheduler, &scheduler);

    // Example: Adding processes to the scheduler
    scheduler.scheduleProcess(Process(1, 20));
    scheduler.scheduleProcess(Process(2, 15));
    scheduler.scheduleProcess(Process(3, 25));

    // Example: Add more processes while the scheduler is running
    scheduler.scheduleProcess(Process(4, 10));
    scheduler.scheduleProcess(Process(5, 30));

    // delay in new processes being added
    std::this_thread::sleep_for(std::chrono::seconds(20));

    scheduler.scheduleProcess(Process(6, 8));
    scheduler.scheduleProcess(Process(7, 2));
    scheduler.scheduleProcess(Process(8, 20));


    // Join the scheduler thread (wait for it to finish)
    scheduler_thread.join();

    return 0;
}
