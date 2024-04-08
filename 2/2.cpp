// Maxwell Bohn
// AERSP 424 HW2 #2

#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>

const int NUM_ROBOTS = 5; // Number of robots in the simulation
const int TASK_DURATION = 5; // Duration for performing the task, in seconds
const int DATA_COLLECTION_TIME = 1; // Time to simulate data collection, in seconds

std::mutex tools[NUM_ROBOTS]; // Array of mutexes, one per tool
std::mutex cout_mutex; // Mutex for synchronized output to prevent garbled text

// Function to simulate each robot's task
void robotTask(int robotID) {
    // Stagger start times for even and odd robots to simulate non-uniform start
    if (robotID % 2 == 0) {
        std::this_thread::sleep_for(std::chrono::seconds(DATA_COLLECTION_TIME)); // Delay for even ID robots
    }

    // Announce data collection start
    {
        std::lock_guard<std::mutex> cout_lock(cout_mutex); // Lock for safe console output
        std::cout << "Robot " << robotID << " is collecting data." << std::endl;
    }
    // Simulate the time taken for data collection
    std::this_thread::sleep_for(std::chrono::seconds(DATA_COLLECTION_TIME));

    // Determine the tools this robot needs
    int leftTool = robotID;
    int rightTool = (robotID + 1) % NUM_ROBOTS;

    // Avoid deadlock by swapping tool order for the last robot
    if (robotID == NUM_ROBOTS - 1) {
        std::swap(leftTool, rightTool);
    }

    // Locks for the tools, without immediately locking them
    std::unique_lock<std::mutex> lock1(tools[leftTool], std::defer_lock);
    std::unique_lock<std::mutex> lock2(tools[rightTool], std::defer_lock);
    std::lock(lock1, lock2); // Acquire both locks without deadlock

    // Announce task start
    {
        std::lock_guard<std::mutex> cout_lock(cout_mutex); // Lock for safe console output
        std::cout << "Robot " << robotID << " acquired tools and starts performing a task." << std::endl;
    }
    // Simulate task duration
    std::this_thread::sleep_for(std::chrono::seconds(TASK_DURATION));

    // Announce task completion
    {
        std::lock_guard<std::mutex> cout_lock(cout_mutex); // Lock for safe console output
        std::cout << "Robot " << robotID << " finished task and returning the tools." << std::endl;
    }
}

int main() {
    auto start = std::chrono::steady_clock::now(); // Start time for duration measurement

    std::vector<std::thread> robots; // Vector to hold the robot threads

    // Start threads for robots 0 and 2 first, then 1 and 3, and 4 last
    // This sequential start and join does not fully utilize concurrency
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

    auto end = std::chrono::steady_clock::now(); // End time for duration measurement
    auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

    // Print the total duration of the simulation
    std::cout << "Duration: " << duration << " seconds" << std::endl;

    return 0;
}