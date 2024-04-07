// Maxwell Bohn
// AERSP 424 HW2 #1

#include <iostream>
#include <vector>
#include <memory>

// Abstract base class Sensor
class Sensor {
public:
    virtual ~Sensor() {}
    virtual void gatherData() = 0;
    virtual void processData() = 0;
};

// Derived classes for specific sensors
class TemperatureSensor : public Sensor {
public:
    void gatherData() override {
        std::cout << "Gathering data from Temperature Sensor." << std::endl;
    }
    void processData() override {
        std::cout << "Processing data from Temperature Sensor." << std::endl;
    }
};

class PressureSensor : public Sensor {
public:
    void gatherData() override {
        std::cout << "Gathering data from Pressure Sensor." << std::endl;
    }
    void processData() override {
        std::cout << "Processing data from Pressure Sensor." << std::endl;
    }
};

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
    static Sensor* createSensor(const std::string& type) {
        if (type == "Temperature") {
            return new TemperatureSensor();
        } else if (type == "Pressure") {
            return new PressureSensor();
        } else if (type == "Altitude") {
            return new AltitudeSensor();
        } else {
            return nullptr;
        }
    }
};

// AerospaceControlSystem class
class AerospaceControlSystem {
    std::vector<std::unique_ptr<Sensor>> sensors;
public:
    void addSensor(Sensor* sensor) {
        sensors.emplace_back(sensor);
    }
    void monitorAndAdjust() {
        for (auto& sensor : sensors) {
            sensor->gatherData();
            sensor->processData();
        }
        std::cout << "Adjusting controls based on sensor data." << std::endl;
    }
};

int main() {
    AerospaceControlSystem ctrlSys;

    // Adding sensors
    ctrlSys.addSensor(SensorFactory::createSensor("Temperature"));
    ctrlSys.addSensor(SensorFactory::createSensor("Pressure"));
    ctrlSys.addSensor(SensorFactory::createSensor("Altitude"));

    // Monitoring and adjusting
    ctrlSys.monitorAndAdjust();

    return 0;
}