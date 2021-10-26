#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

const int HOTPLATE_SIZE = 10;

void HeatRow(int row, double (&hotPlate)[HOTPLATE_SIZE][HOTPLATE_SIZE]);
bool UpdateElements(double (&hotPlate)[HOTPLATE_SIZE][HOTPLATE_SIZE], int iteration = 0);
void CopyHotPlate(double (&newHotPlate)[HOTPLATE_SIZE][HOTPLATE_SIZE], double (&oldHotPlate)[HOTPLATE_SIZE][HOTPLATE_SIZE]);
void PrintHotPlate(double hotPlate[HOTPLATE_SIZE][HOTPLATE_SIZE]);
bool CheckSteadyState(double oldHotPlate[HOTPLATE_SIZE][HOTPLATE_SIZE], double newHotPlate[HOTPLATE_SIZE][HOTPLATE_SIZE]);

int main() {
    // Initialize matrix with 0
    double hotPlate[HOTPLATE_SIZE][HOTPLATE_SIZE] = {0};

    // Heat top and bottom rows
    HeatRow(0, hotPlate);
    HeatRow(9, hotPlate);

    cout << "Hotplate simulator" << endl << endl;
    cout << "Printing the initial plate values..." << endl;
    // Print out hotplate
    PrintHotPlate(hotPlate);

    cout << endl;

    bool steadyStateAchieved = false;
    int iteration = 0;

    do {
        steadyStateAchieved = UpdateElements(hotPlate, iteration);
        iteration++;
    } while (steadyStateAchieved == false);

    return 0;
}

// Heat row, with corners = 0 and insides = 100
void HeatRow(int row, double (&hotPlate)[HOTPLATE_SIZE][HOTPLATE_SIZE]) {
    for(int j = 1; j < HOTPLATE_SIZE - 1; ++j) {
        hotPlate[row][j] = 100;
    }
}

bool UpdateElements(double (&hotPlate)[HOTPLATE_SIZE][HOTPLATE_SIZE], int iteration) {
    double newHotPlate[HOTPLATE_SIZE][HOTPLATE_SIZE] = {0};

    CopyHotPlate(hotPlate, newHotPlate);

    for (int i = 1; i < HOTPLATE_SIZE - 1; ++i){
        for (int j = 1; j < HOTPLATE_SIZE - 1; ++j){
            newHotPlate[i][j] = (hotPlate[i-1][j] + hotPlate[i + 1][j] + hotPlate[i][j + 1] + hotPlate[i][j -1]) / 4.0;
        }
    }

    bool steadyStateAchieved = CheckSteadyState(hotPlate, newHotPlate);

    if(!steadyStateAchieved) {
        if(iteration == 0) {
            // first iteration
            cout << "Printing plate after one iteration..." << endl;
            // Print out hotplate
            PrintHotPlate(newHotPlate);
        }

        // Copy new hotplate into old hotplate
        CopyHotPlate(newHotPlate, hotPlate);

        return false;
    } else {
        // Final hot plate
        cout << "Printing final plate..." << endl;

        // Print out hotplate
        PrintHotPlate(newHotPlate);

        return true;
    }
}

void CopyHotPlate(double (&newHotPlate)[HOTPLATE_SIZE][HOTPLATE_SIZE], double (&oldHotPlate)[HOTPLATE_SIZE][HOTPLATE_SIZE]) {
    for (int i = 0; i < HOTPLATE_SIZE; ++i) {
        for (int j = 0; j < HOTPLATE_SIZE; ++j) {
            oldHotPlate[i][j] = newHotPlate[i][j];
        }
    }
}

void PrintHotPlate(double hotPlate[HOTPLATE_SIZE][HOTPLATE_SIZE]){
    for(int i = 0; i < HOTPLATE_SIZE; ++i) {
        for(int j = 0; j < HOTPLATE_SIZE; ++j) {
            cout << fixed << setprecision(3) << setw(9) << hotPlate[i][j];

            if (j < HOTPLATE_SIZE - 1){
                cout << ",";
            }
        }
        cout << endl;
    }
    cout << endl;
}

bool CheckSteadyState(double oldHotPlate[HOTPLATE_SIZE][HOTPLATE_SIZE], double newHotPlate[HOTPLATE_SIZE][HOTPLATE_SIZE]) {
    bool steadyStateAchieved = true;
    for (int i = 0; i < HOTPLATE_SIZE; ++i) {
        for (int j = 0; j < HOTPLATE_SIZE; j++) {
            if (fabs(oldHotPlate[i][j] - newHotPlate[i][j]) > 0.1) {
                steadyStateAchieved = false;
            }
        }
    }
    return steadyStateAchieved;
}