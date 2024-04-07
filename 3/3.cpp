// Maxwell Bohn
// AERSP 424 HW2 #3 (working i think)

#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>

std::queue<int> trafficPattern;
std::mutex mtx;
std::condition_variable cv_atc, cv_aircraft;
const int maxAircraft = 3;
bool simulationRunning = true;
std::chrono::steady_clock::time_point startTime;

void ATC() {
    std::unique_lock<std::mutex> lock(mtx, std::defer_lock);
    while (simulationRunning || !trafficPattern.empty()) {
        lock.lock();
        if (!trafficPattern.empty()) {
            int aircraftId = trafficPattern.front();
            trafficPattern.pop();
            std::cout << "Aircraft #" << aircraftId << " is cleared to land." << std::endl;
            std::cout << "Runway is now free." << std::endl;
            lock.unlock();
            std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate landing
        } else {
            lock.unlock();
        }
    }
}

void Aircraft(int id) {
    std::unique_lock<std::mutex> lock(mtx);
    std::cout << "Aircraft #" << id << " requesting landing." << std::endl;
    if (trafficPattern.size() < maxAircraft) {
        trafficPattern.push(id);
        lock.unlock();
    } else {
        std::cout << "Approach pattern full. Aircraft #" << id << " redirected to another airport." << std::endl;
        std::cout << "Aircraft #" << id << " flying to another airport." << std::endl;
        lock.unlock();
    }
}

int main() {
    startTime = std::chrono::steady_clock::now();
    std::thread atcThread(ATC);

    std::vector<std::thread> aircraftThreads;
    for (int i = 1; i <= 10; ++i) { // Start IDs from 1
        aircraftThreads.push_back(std::thread(Aircraft, i));
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate different arrival times
    }

    for (auto &th : aircraftThreads) {
        th.join();
    }

    simulationRunning = false;
    cv_atc.notify_one(); // Ensure ATC thread can exit if waiting
    atcThread.join();

    auto endTime = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime).count();
    std::cout << "Duration: " << duration << " seconds" << std::endl;

    return 0;
}