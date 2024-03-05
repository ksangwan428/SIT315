#include <iostream>
#include <random>
#include <ctime>
#include <fstream>
#include <iomanip> // Added for setw function
#include <time.h>

using namespace std;

#define NUM_LIGHTS 12 // Number of traffic lights

int main()
{
    string output;
    
    time_t rawTime;
    time(&rawTime);

    srand(time(NULL));

    // Table header
    output += "Timestamp    | ID | Number of Cars\n";

    for (int i = 1; i <= NUM_LIGHTS; i++)
    {
        output += to_string(rawTime) + " | "; // Log entry timestamp
        output += to_string(i) + " | ";        // Light number
        int cars = rand() % ((10 - 1) + 1) + 1;
        output += to_string(cars) + "\n"; // Number of cars (random)
    }

    fstream log("log.txt", ios::app); // Append to log file
    if (!log.is_open())
    {
        cout << "Error: Log file not found" << endl;
    }
    else
    {
        log << output;
        cout << output;
        cout << "log.txt has been updated at " << ctime(&rawTime) << endl;
    }
    return 0;
}
