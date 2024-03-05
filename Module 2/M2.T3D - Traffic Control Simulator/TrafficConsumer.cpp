#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

#define NUM_LIGHTS 12
#define MEASUREMENTS 13 // 12 per hour plus held average value

// Function to print details of traffic measurements
void printDetails(int array[NUM_LIGHTS][MEASUREMENTS])
{
    for (int i = 0; i < NUM_LIGHTS; i++)
    {
        cout << to_string(i + 1) + ":\t";
        for (int j = 0; j < MEASUREMENTS; j++)
        {
            cout << to_string(array[i][j]) + ";";
        }
        cout << endl;
    }
}

// Function to calculate average traffic volume for each traffic light
void calculateTrafficVolume(int array[NUM_LIGHTS][MEASUREMENTS])
{
    cout << "Calculating...\t";
    for (int i = 0; i < NUM_LIGHTS; i++)
    {
        array[i][0] = 0;
        for (int j = 1; j < MEASUREMENTS; j++)
        {
            array[i][0] += array[i][j];
        }
        array[i][0] = array[i][0] / (MEASUREMENTS - 1); // Integer division for simplicity
    }
    cout << "Done" << endl;
}

int main()
{
    int Array[NUM_LIGHTS][MEASUREMENTS];

    // Open log file for reading
    fstream log("log.txt", ios::in);
    if (!log.is_open())
    {
        cout << "Error: Log file not found" << endl;
    }
    else
    {
        cout << "Retrieving initial data from log.txt...\t";

        // Initialize the array with zeros
        for (int i = 0; i < NUM_LIGHTS; i++)
        {
            for (int j = 0; j < MEASUREMENTS; j++)
            {
                Array[i][j] = 0;
            }
        }

        // Read data from the log file
        long rawTime;
        int lightNum;
        int trafficVolume;

        for (int k = 0; k < MEASUREMENTS; k++)
        {
            for (int i = 0; i < NUM_LIGHTS; i++)
            {
                log >> rawTime >> lightNum >> trafficVolume;

                // Shift the values in the array
                for (int j = MEASUREMENTS - 1; j > 0; j--)
                {
                    Array[lightNum - 1][j] = Array[lightNum - 1][j - 1];
                }
                // Store the new traffic volume
                Array[lightNum - 1][0] = trafficVolume;
            }
        }

        log.close();
        cout << "Complete" << endl;
    }

    calculateTrafficVolume(Array);
    printDetails(Array);

    return 0;
}
