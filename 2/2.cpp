// Maxwell Bohn
// AERSP 424 HW2 #2 (working, but needs to be 18 seconds and not 20)

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

const int NUM_ROBOTS = 5;
const int TASK_DURATION = 5; // Duration for performing the task, in seconds
const int DATA_COLLECTION_TIME = 1; // Time to simulate data collection, in seconds

std::mutex tools[NUM_ROBOTS];
std::mutex cout_mutex; // Mutex for synchronized output

// Function to simulate each robot's task
void robotTask(int robotID) {
    // Wait before starting to collect data to stagger the start times appropriately
    if (robotID % 2 == 0) {
        std::this_thread::sleep_for(std::chrono::seconds(DATA_COLLECTION_TIME)); // Offset for even robots
    }

    {
        std::lock_guard<std::mutex> cout_lock(cout_mutex);
        std::cout << "Robot " << robotID << " is collecting data." << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::seconds(DATA_COLLECTION_TIME));

    int leftTool = robotID;
    int rightTool = (robotID + 1) % NUM_ROBOTS;

    // Special case for the last robot to avoid deadlock
    if (robotID == NUM_ROBOTS - 1) {
        std::swap(leftTool, rightTool);
    }

    std::unique_lock<std::mutex> lock1(tools[leftTool], std::defer_lock);
    std::unique_lock<std::mutex> lock2(tools[rightTool], std::defer_lock);
    std::lock(lock1, lock2); // Acquiring the tools

    {
        std::lock_guard<std::mutex> cout_lock(cout_mutex);
        std::cout << "Robot " << robotID << " acquired tools and starts performing a task." << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::seconds(TASK_DURATION));

    {
        std::lock_guard<std::mutex> cout_lock(cout_mutex);
        std::cout << "Robot " << robotID << " finished task and returning the tools." << std::endl;
    }
}

int main() {
    auto start = std::chrono::steady_clock::now();

    std::vector<std::thread> robots;

    // Start threads for robots 0 and 2 first, then 1 and 3, and 4 last
    robots.emplace_back(robotTask, 0);
    robots.emplace_back(robotTask, 2);
    robots[0].join();
    robots[1].join();

    robots.emplace_back(robotTask, 1);
    robots.emplace_back(robotTask, 3);
    robots[2].join();
    robots[3].join();

    robots.emplace_back(robotTask, 4);
    robots[4].join();

    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

    std::cout << "Duration: " << duration << " seconds" << std::endl;

    return 0;
}