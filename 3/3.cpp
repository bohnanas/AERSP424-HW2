// Maxwell Bohn
// AERSP 424 HW2 #3

#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>

// Queue representing the aircraft waiting to land
std::queue<int> trafficPattern;

// Mutex for synchronizing access to the queue
std::mutex mtx;

// Condition variables for signaling - though not used in the original code
std::condition_variable cv_atc, cv_aircraft;

// Maximum number of aircraft that can wait to land
const int maxAircraft = 3;

// Flag to control the simulation loop
bool simulationRunning = true;

// Timestamp to measure the simulation duration
std::chrono::steady_clock::time_point startTime;

// Function to simulate Air Traffic Control operations
void ATC() {
    // Lock acquisition deferred to avoid locking at declaration
    std::unique_lock<std::mutex> lock(mtx, std::defer_lock);
    while (simulationRunning || !trafficPattern.empty()) {
        lock.lock();
        if (!trafficPattern.empty()) {
            // ATC processes one aircraft at a time
            int aircraftId = trafficPattern.front();
            trafficPattern.pop();
            std::cout << "Aircraft #" << aircraftId << " is cleared to land." << std::endl;
            std::cout << "Runway is now free." << std::endl;
            lock.unlock();
            // Simulate time taken for landing
            std::this_thread::sleep_for(std::chrono::seconds(1));
        } else {
            lock.unlock();
        }
    }
}

// Function to simulate an aircraft requesting to land
void Aircraft(int id) {
    std::unique_lock<std::mutex> lock(mtx);
    std::cout << "Aircraft #" << id << " requesting landing." << std::endl;
    if (trafficPattern.size() < maxAircraft) {
        // If the queue is not full, add the aircraft
        trafficPattern.push(id);
        lock.unlock();
    } else {
        // If the queue is full, redirect the aircraft to another airport
        std::cout << "Approach pattern full. Aircraft #" << id << " redirected to another airport." << std::endl;
        std::cout << "Aircraft #" << id << " flying to another airport." << std::endl;
        lock.unlock();
    }
}

int main() {
    startTime = std::chrono::steady_clock::now();
    // Start the ATC thread
    std::thread atcThread(ATC);

    std::vector<std::thread> aircraftThreads;
    for (int i = 1; i <= 10; ++i) {
        // Create and start threads for each aircraft
        aircraftThreads.push_back(std::thread(Aircraft, i));
        // Simulate staggered arrival times of aircraft
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // Wait for all aircraft threads to finish
    for (auto &th : aircraftThreads) {
        th.join();
    }

    // Signal the ATC thread to exit
    simulationRunning = false;
    // Notify the ATC thread in case it's waiting (though not implemented)
    cv_atc.notify_one();
    atcThread.join();

    // Calculate and print the simulation duration
    auto endTime = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();
    std::cout << "Duration: " << duration << " seconds" << std::endl;

    return 0;
}