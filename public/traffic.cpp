#include <iostream>
#include <string>
#include "firebase/app.h"
#include "firebase/database.h"
#include "firebase/auth.h"

using namespace std;
using namespace firebase;

// Firebase Realtime Database
Database* database = nullptr;

// Class to handle traffic data and update Firebase
class TrafficSystem {
public:
    TrafficSystem() {
        InitFirebase();
    }

    void InitFirebase() {
        // Initialize Firebase App
        App* app = App::Create(AppOptions());
        
        // Connect to Firebase Realtime Database
        database = Database::GetInstance(app);
    }

    // Function to simulate real-time traffic sensor input
    void updateTrafficData(string road, int trafficDensity) {
        DatabaseReference ref = database->GetReference("traffic_data/" + road);
        ref.SetValue(trafficDensity);
        cout << "Traffic data updated on Firebase for " << road << ": " << trafficDensity << " cars." << endl;
    }

    // Simulate emergency vehicle detection and push to Firebase
    void detectEmergencyVehicle(string road, bool isDetected) {
        DatabaseReference ref = database->GetReference("emergency_vehicle/" + road);
        ref.SetValue(isDetected);
        if (isDetected)
            cout << "Emergency vehicle detected on " << road << ". Prioritizing!" << endl;
    }
    
    // Simulate weather update and push to Firebase
    void updateWeatherCondition(string road, string condition) {
        DatabaseReference ref = database->GetReference("weather_condition/" + road);
        ref.SetValue(condition);
        cout << "Weather condition updated on Firebase for " << road << ": " << condition << endl;
    }

    // Monitor real-time updates from Firebase
    void monitorRealTimeData(string road) {
        DatabaseReference ref = database->GetReference("traffic_data/" + road);
        ref.AddValueListener(new ValueListener());
        // Assuming a listener to react to real-time data updates
    }

    // Function to simulate entire system
    void runSimulation(string road) {
        // Example: Simulating data and pushing to Firebase
        updateTrafficData(road, 120);
        detectEmergencyVehicle(road, true);
        updateWeatherCondition(road, "Rainy");
    }
};

// Listener class for Firebase real-time updates
class ValueListener : public DatabaseReference::ValueListener {
public:
    void OnValueChanged(const DataSnapshot& snapshot) override {
        if (snapshot.exists()) {
            cout << "Real-time traffic update: " << snapshot.value().AsString().c_str() << endl;
        }
    }

    void OnCancelled(const Error& error) override {
        cout << "Listener cancelled: " << error.message() << endl;
    }
};

int main() {
    // Initialize the system
    TrafficSystem trafficSystem;

    // Simulate the system
    trafficSystem.runSimulation("Main_Street");

    return 0;
}
