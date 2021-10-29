#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>

using namespace std;

const int HOTPLATE_SIZE = 10;

void HeatRow(int row, double (&hotPlate)[HOTPLATE_SIZE][HOTPLATE_SIZE]);
bool UpdateElements(double (&hotPlate)[HOTPLATE_SIZE][HOTPLATE_SIZE]);
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
        steadyStateAchieved = UpdateElements(hotPlate);

        // Print hot plate when required
        if(!steadyStateAchieved) {
            if(iteration == 0) {
                // first iteration
                cout << "Printing plate after one iteration..." << endl;
                // Print out hotplate
                PrintHotPlate(hotPlate);
            }
        } else {
            // Final hot plate
            cout << "Printing final plate..." << endl;
            // Print out hotplate
            PrintHotPlate(hotPlate);
        }

        iteration++;
    } while (steadyStateAchieved == false);


    // output into file

    cout << "Writing final plate to \"Hotplate.csv.\"..." << endl << endl;
    ofstream out;
    out.open("Hotplate.csv");

    if (out.is_open()){
        for(int i = 0; i < HOTPLATE_SIZE; ++i) {
            for(int j = 0; j < HOTPLATE_SIZE; ++j) {
                out << fixed << setprecision(3) << setw(9) << hotPlate[i][j];

                if (j < HOTPLATE_SIZE - 1){
                    out << ",";
                }
            }
            out << endl;
        }
        out << endl;

    }

    out.close();

    //input test from file

    ifstream in;
    in.open("Inputplate.txt");

    // Initialize matrix with 0
    double inputPlate[HOTPLATE_SIZE][HOTPLATE_SIZE] = {0};

    // Load input plate
    for (int i = 0; i < HOTPLATE_SIZE; ++i){
        for (int j = 0; j < HOTPLATE_SIZE; ++j){
            in >> inputPlate[i][j];
        }
    }

    for (int i = 0; i < 3; i++) {
        UpdateElements(inputPlate);
    }

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