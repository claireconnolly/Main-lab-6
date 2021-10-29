#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

const int HOTPLATE_SIZE = 10;
const int PRECISION = 3;
const int WIDTH = 9;
const double MIN_VARIATION = 0.1; // 0.1 degrees difference

void HeatRow(int row, double (&hotPlate)[HOTPLATE_SIZE][HOTPLATE_SIZE]);
bool UpdateElements(double (&hotPlate)[HOTPLATE_SIZE][HOTPLATE_SIZE]);
bool CheckSteadyState(double oldHotPlate[HOTPLATE_SIZE][HOTPLATE_SIZE], double newHotPlate[HOTPLATE_SIZE][HOTPLATE_SIZE]);
void CopyHotPlate(double (&newHotPlate)[HOTPLATE_SIZE][HOTPLATE_SIZE], double (&oldHotPlate)[HOTPLATE_SIZE][HOTPLATE_SIZE]);
void PrintHotPlate(double hotPlate[HOTPLATE_SIZE][HOTPLATE_SIZE]);
void OutputHotPlateToFile(double hotPlate[HOTPLATE_SIZE][HOTPLATE_SIZE], ostream& out);

int main() {
    cout << "Hotplate simulator" << endl << endl;

    // Initialize array with 0
    double hotPlate[HOTPLATE_SIZE][HOTPLATE_SIZE] = {0};

    // Heat top and bottom rows
    HeatRow(0, hotPlate);
    HeatRow(9, hotPlate);

    // Print initial hot plate
    cout << "Printing the initial plate values..." << endl;
    PrintHotPlate(hotPlate);
    cout << endl;

    // Iterate until a steady state is achieved
    bool steadyStateAchieved = false;
    int iteration = 0;
    do {
        // Update elements
        steadyStateAchieved = UpdateElements(hotPlate);

        // Print plate after one iteration
        if(iteration == 0) {
            cout << "Printing plate after one iteration..." << endl;
            PrintHotPlate(hotPlate);
        }

        // Print final plate
        if(steadyStateAchieved) {
            cout << "Printing final plate..." << endl;
            PrintHotPlate(hotPlate);
        }

        iteration++;
    } while (steadyStateAchieved == false);


    // Output to Hotplate.csv
    cout << "Writing final plate to \"Hotplate.csv.\"..." << endl << endl;

    // Create/open file
    ofstream out;
    out.open("Hotplate.csv");

    if (out.is_open()){
        OutputHotPlateToFile(hotPlate, out);
    }

    out.close();

    // Input plate from Inputplate.txt
    ifstream in;
    in.open("Inputplate.txt");

    // Initialize array with 0
    double inputPlate[HOTPLATE_SIZE][HOTPLATE_SIZE] = {0};

    // Load input plate
    for (int i = 0; i < HOTPLATE_SIZE; ++i){
        for (int j = 0; j < HOTPLATE_SIZE; ++j){
            in >> inputPlate[i][j];
        }
    }

    // Iterate 3 times
    for (int i = 0; i < 3; i++) {
        UpdateElements(inputPlate);
    }

    // Print plate after 3 iterations
    cout << "Printing input plate after 3 updates..." << endl;
    PrintHotPlate(inputPlate);

    in.close();

    return 0;

}

// Heat row, with corners = 0 and insides = 100
void HeatRow(int row, double (&hotPlate)[HOTPLATE_SIZE][HOTPLATE_SIZE]) {
    for(int j = 1; j < HOTPLATE_SIZE - 1; ++j) {
        hotPlate[row][j] = 100;
    }
}

// Update the elements in the hotplate and return true if steady state is achieved
bool UpdateElements(double (&hotPlate)[HOTPLATE_SIZE][HOTPLATE_SIZE]) {
    double newHotPlate[HOTPLATE_SIZE][HOTPLATE_SIZE] = {0};
    CopyHotPlate(hotPlate, newHotPlate);

    for (int i = 1; i < HOTPLATE_SIZE - 1; ++i){
        for (int j = 1; j < HOTPLATE_SIZE - 1; ++j){
            newHotPlate[i][j] = (hotPlate[i-1][j] + hotPlate[i + 1][j] + hotPlate[i][j + 1] + hotPlate[i][j -1]) / 4.0;
        }
    }

    bool steadyStateAchieved = CheckSteadyState(hotPlate, newHotPlate);

    // Copy new hotplate into old hotplate
    CopyHotPlate(newHotPlate, hotPlate);

    return steadyStateAchieved;
}

// Return true if values in new hot plate vary less than MIN_VARIATION
bool CheckSteadyState(double oldHotPlate[HOTPLATE_SIZE][HOTPLATE_SIZE], double newHotPlate[HOTPLATE_SIZE][HOTPLATE_SIZE]) {
    bool steadyStateAchieved = true;
    for (int i = 0; i < HOTPLATE_SIZE; ++i) {
        for (int j = 0; j < HOTPLATE_SIZE; j++) {
            if (fabs(oldHotPlate[i][j] - newHotPlate[i][j]) > MIN_VARIATION) {
                steadyStateAchieved = false;
            }
        }
    }
    return steadyStateAchieved;
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
            cout << fixed << setprecision(PRECISION) << setw(WIDTH) << hotPlate[i][j];

            if (j < HOTPLATE_SIZE - 1){
                cout << ",";
            }
        }
        cout << endl;
    }
    cout << endl;
}

void OutputHotPlateToFile(double hotPlate[HOTPLATE_SIZE][HOTPLATE_SIZE], ostream& out) {
    for(int i = 0; i < HOTPLATE_SIZE; ++i) {
        for(int j = 0; j < HOTPLATE_SIZE; ++j) {
            out << fixed << setprecision(PRECISION) << setw(WIDTH) << hotPlate[i][j];

            if (j < HOTPLATE_SIZE - 1){
                out << ",";
            }
        }
        out << endl;
    }
    out << endl;
}