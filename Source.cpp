/*
Matthew Winter
CSC275 
Assignment Exceptions
October 27th 2024

Overview
	Create an application using exception-safe code.

Guidelines
	Write a program that demonstrates the try/catch exception handler blocks for a minimum of 2 different exceptions. Use more than one catch type.   Include sufficient output to indicate the exception and the condition that caused it.

Expectations
	Display a description of the program and how to use it for the user when it the application starts.
	Over comment your code!
	The program should do something in addition to demonstrate exceptions.
	This program should have a good UX.

Submission Deliverables
	Submit a zip of your project folder.
	Submit  a video of your program in action.  Show all functionality.

*/

#include <iostream>      // Include iostream for input and output operations
#include <stdexcept>     // Include stdexcept for standard exception handling
#include <limits>        // Include limits for resetting input stream

using namespace std;     // Use the standard namespace for convenience

// Function to display program instructions to the user
void displayInstructions() {
    cout << "=== Embedded Systems Motor Control Program ===\n"; // Display program title
    cout << "This program simulates reading a temperature sensor and controlling a motor.\n"; // Explain program functionality
    cout << "It will handle errors if sensor values are out of range or if the motor overheats.\n"; // Explain error handling
    cout << "Enter a temperature reading, or type 'exit' to end the program.\n\n"; // Explain user options
}

// Function to simulate reading from a temperature sensor
double readTemperatureSensor() {
    double temp;  // Declare variable to hold temperature reading
    cout << "Enter simulated temperature (C): "; // Prompt user for temperature input
    cin >> temp;  // Get temperature input from the user

    // Check if input is valid and within realistic sensor range
    if (cin.fail() || temp < -40 || temp > 125) { // Check if input is invalid or out of range
        throw out_of_range("Temperature sensor reading out of range (-40 to 125 C)."); // Throw exception for invalid range
    }
    return temp; // Return valid temperature reading
}

// Function to simulate controlling a motor based on temperature
void controlMotor(double temperature) {
    const double maxOperatingTemp = 70.0; // Define maximum safe temperature for motor

    // Check if temperature exceeds safe operating range
    if (temperature > maxOperatingTemp) { // If temperature is above safe limit
        throw runtime_error("Motor overheating detected! Temperature exceeds safe operating limit."); // Throw exception for overheating
    }
    cout << "Motor operating within safe temperature range.\n"; // Confirm motor is in safe range
}

int main() {
    displayInstructions(); // Display program instructions at the start

    double temperature; // Declare variable to store temperature input
    char continueProgram = 'y'; // Initialize continueProgram to 'y' for looping control

    // Start a loop to allow repeated attempts
    while (continueProgram == 'y' || continueProgram == 'Y') { // Continue loop if user enters 'y' or 'Y'
        try {
            temperature = readTemperatureSensor(); // Call function to read temperature input

            controlMotor(temperature); // Call function to control motor based on temperature

            cout << "Temperature read successfully. Motor controlled safely.\n"; // Display success message
        }
        // Catch and handle out-of-range sensor reading exception
        catch (const out_of_range& e) { // Catch specific out-of-range exceptions
            cerr << "Sensor Error: " << e.what() << "\n"; // Display error message for out-of-range reading
            cerr << "Please check the sensor and try again.\n"; // Suggest checking the sensor
        }
        // Catch and handle motor overheating exception
        catch (const runtime_error& e) { // Catch specific runtime errors related to overheating
            cerr << "Motor Control Error: " << e.what() << "\n"; // Display overheating error message
            cerr << "Cooling required. Please reduce load or pause operation.\n"; // Suggest cooling the motor
        }

        // Clear any errors in the input stream to prepare for the next input
        cin.clear(); // Reset error flags on cin
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard any remaining input in the buffer

        // Ask the user if they want to try again or exit
        cout << "\nDo you want to try another temperature reading? (y/n): "; // Prompt for continuation
        cin >> continueProgram; // Get user response to continue or exit
    }

    cout << "Thank you for using the Motor Control Program. Exiting...\n"; // Exit message
    return 0; // End program
}
