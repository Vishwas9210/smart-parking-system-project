#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class ParkingSystem {
private:
    string licensePlates[50];  // Stores the license plates of parked vehicles
    string vehicleTypes[50];   // Stores the types of vehicles parked
    double parkingCharges[50]; // Stores the parking charges for each slot

public:
    // Constructor to initialize all parking slots to empty
    ParkingSystem() {
        for (int i = 0; i < 50; i++) {
            licensePlates[i] = "";  // Empty string indicates the slot is available
            vehicleTypes[i] = "";   // Empty string indicates no vehicle type is set
            parkingCharges[i] = 0.0; // Zero charge means no vehicle is parked
        }
    }

    // Function to display all parking slots and their status (available or occupied)
    void showSlots() {
        cout << "Parking Slots Status:\n";
        for (int i = 0; i < 50; i++) {
            if (licensePlates[i] == "") {  // Check if the slot is available
                cout << "Slot " << (i + 1) << ": Available\n";
            } else {
                cout << "Slot " << (i + 1) << ": Occupied by " << licensePlates[i] << "\n";
            }
        }
    }

    // Function to park a vehicle in a slot
    void parkVehicle() {
        int slotNumber;
        string plate, type;
        double hours;

        cout << "Enter slot number to park the vehicle: ";
        cin >> slotNumber;

        // Check if the slot number is valid and available
        if (slotNumber < 1 || slotNumber > 50 || licensePlates[slotNumber - 1] != "") {
            cout << "Invalid slot number or slot already occupied!\n";
            return;
        }

        // Get vehicle details from the user
        cout << "Enter vehicle license plate: ";
        cin >> plate;
        cout << "Enter vehicle type: ";
        cin >> type;
        cout << "Enter number of hours to park: ";
        cin >> hours;

        // Store vehicle details and calculate parking charge
        licensePlates[slotNumber - 1] = plate;
        vehicleTypes[slotNumber - 1] = type;
        parkingCharges[slotNumber - 1] = calculateCharge(hours);

        cout << "Vehicle parked in slot " << slotNumber << ".\n";
        cout << "Charge: Rs" << parkingCharges[slotNumber - 1] << "\n";

        saveData();  // Save the updated parking data to the file
    }

    // Function to remove a vehicle from a slot
    void removeVehicle() {
        int slotNumber;
        double payment;

        cout << "Enter slot number to remove the vehicle from: ";
        cin >> slotNumber;

        // Check if the slot number is valid and occupied
        if (slotNumber < 1 || slotNumber > 50 || licensePlates[slotNumber - 1] == "") {
            cout << "Invalid slot number or slot is empty!\n";
            return;
        }

        cout << "Parking charge for slot " << slotNumber << ": Rs" << parkingCharges[slotNumber - 1] << "\n";

        // Get payment from the user and check if it's sufficient
        cout << "Enter payment amount: ";
        cin >> payment;

        if (payment >= parkingCharges[slotNumber - 1]) {
            cout << "Payment successful! Vehicle removed from slot " << slotNumber << ".\n";
            // Clear the slot data
            licensePlates[slotNumber - 1] = "";
            vehicleTypes[slotNumber - 1] = "";
            parkingCharges[slotNumber - 1] = 0.0;
        } else {
            cout << "Insufficient payment. Vehicle not removed.\n";
        }

        saveData();  // Save the updated parking data to the file
    }

    // Function to calculate parking charges based on hours
    double calculateCharge(double hours) {
        double ratePerHour = 10.0; // Simple fixed rate per hour
        return hours * ratePerHour;
    }

    // Function to save parking data to a file
    void saveData() {
        ofstream file("parking_data.txt");
        for (int i = 0; i < 50; i++) {
            file << licensePlates[i] << endl;
            file << vehicleTypes[i] << endl;
            file << parkingCharges[i] << endl;
        }
        file.close();
    }

    // Function to load parking data from a file
    void loadData() {
        ifstream file("parking_data.txt");
        for (int i = 0; i < 50; i++) {
            getline(file, licensePlates[i]);
            getline(file, vehicleTypes[i]);
            file >> parkingCharges[i];
            file.ignore(); // Ignore the newline character after the charge
        }
        file.close();
    }
};

int main() {
    ParkingSystem parking;
    parking.loadData();  // Load existing parking data from the file

    int choice;
    do {
        cout << "\nSmart Parking System Menu:\n";
        cout << "1. Show Parking Slots\n";
        cout << "2. Park a Vehicle\n";
        cout << "3. Remove a Vehicle\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                parking.showSlots();
                break;
            case 2:
                parking.parkVehicle();
                break;
            case 3:
                parking.removeVehicle();
                break;
            case 4:
                cout << "Exiting the system. Goodbye!\n";
                parking.saveData();  // Save data before exiting
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
                break;
        }
    } while (choice != 4);

    return 0;
}

