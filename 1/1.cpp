// Maxwell Bohn
// AERSP 424 HW2 #1

#include <iostream>
#include <vector>
#include <memory>

// Abstract base class Sensor
class Sensor {
public:
    virtual ~Sensor() {} // Virtual destructor to ensure proper cleanup of derived class objects.
    virtual void gatherData() = 0; // Pure virtual function for data gathering, to be implemented by derived classes.
    virtual void processData() = 0; // Pure virtual function for data processing, to be implemented by derived classes.
};

// Derived class for a Temperature sensor
class TemperatureSensor : public Sensor {
public:
    void gatherData() override {
        std::cout << "Gathering data from Temperature Sensor." << std::endl;
    }
    void processData() override {
        std::cout << "Processing data from Temperature Sensor." << std::endl;
    }
};

// Derived class for a Pressure sensor
class PressureSensor : public Sensor {
public:
    void gatherData() override {
        std::cout << "Gathering data from Pressure Sensor." << std::endl;
    }
    void processData() override {
        std::cout << "Processing data from Pressure Sensor." << std::endl;
    }
};

// Derived class for an Altitude sensor
class AltitudeSensor : public Sensor {
public:
    void gatherData() override {
        std::cout << "Gathering data from Altitude Sensor." << std::endl;
    }
    void processData() override {
        std::cout << "Processing data from Altitude Sensor." << std::endl;
    }
};

// SensorFactory class
class SensorFactory {
public:
    // Creates a Sensor object based on the specified type
    static Sensor* createSensor(const std::string& type) {
        if (type == "Temperature") {
            return new TemperatureSensor();
        } else if (type == "Pressure") {
            return new PressureSensor();
        } else if (type == "Altitude") {
            return new AltitudeSensor();
        } else {
            return nullptr; // Returns nullptr if no matching sensor type is found
        }
    }
};

// AerospaceControlSystem class
class AerospaceControlSystem {
    std::vector<std::unique_ptr<Sensor>> sensors; // Vector of unique pointers to Sensor objects
public:
    // Adds a sensor to the control system
    void addSensor(Sensor* sensor) {
        sensors.emplace_back(sensor); // Takes ownership of the sensor pointer
    }
    // Monitors and adjusts based on sensor data
    void monitorAndAdjust() {
        for (auto& sensor : sensors) {
            sensor->gatherData(); // Calls gatherData on each sensor
            sensor->processData(); // Calls processData on each sensor
        }
        std::cout << "Adjusting controls based on sensor data." << std::endl; // Adjusts controls after processing data
    }
};

int main() {
    AerospaceControlSystem ctrlSys; // Creates an AerospaceControlSystem object

    // Adding sensors to the control system
    ctrlSys.addSensor(SensorFactory::createSensor("Temperature"));
    ctrlSys.addSensor(SensorFactory::createSensor("Pressure"));
    ctrlSys.addSensor(SensorFactory::createSensor("Altitude"));

    // Monitoring and adjusting based on sensor data
    ctrlSys.monitorAndAdjust();

    return 0;
}