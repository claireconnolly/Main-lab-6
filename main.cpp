#include <iostream>
#include <iomanip>
using namespace std;

const int HOTPLATE_SIZE = 10;

void heatRow(int row, double (&hotPlate)[HOTPLATE_SIZE][HOTPLATE_SIZE]);

int main() {
    /* ========================= PART 1 ========================= */
    // Initialize matrix with 0
    double hotPlate[HOTPLATE_SIZE][HOTPLATE_SIZE] = {0};

    // Heat top and bottom rows
    heatRow(0, hotPlate);
    heatRow(9, hotPlate);

    // Print out hotplate
    for(int i = 0; i < HOTPLATE_SIZE; ++i) {
        for(int j = 0; j < HOTPLATE_SIZE; ++j) {
            cout << fixed << setprecision(3) << setw(9) << hotPlate[i][j];

            if (j < HOTPLATE_SIZE - 1){
                cout << ",";
            }
        }
        cout << endl;
    }

    /* ========================= PART 2 ========================= */
    double newHotPlate[HOTPLATE_SIZE][HOTPLATE_SIZE];

    heatRow(0, newHotPlate);
    heatRow(9, newHotPlate);

    for (int i = 1; i < HOTPLATE_SIZE - 1; ++i){
        for (int j = 1; j < HOTPLATE_SIZE - 1; ++j){
            newHotPlate[i][j] = (hotPlate[i-1][j] + hotPlate[i + 1][j] + hotPlate[i][j + 1] + hotPlate[i][j -1]) / 4.0;
        }
    }

    for(int i = 0; i < HOTPLATE_SIZE; ++i) {
        for(int j = 0; j < HOTPLATE_SIZE; ++j) {
            cout << fixed << setprecision(3) << setw(9) << newHotPlate[i][j];

            if (j < HOTPLATE_SIZE - 1){
                cout << ",";
            }
        }
        cout << endl;
    }
    return 0;
}

// Heat row, with corners = 0 and insides = 100
void heatRow(int row, double (&hotPlate)[HOTPLATE_SIZE][HOTPLATE_SIZE]) {
    for(int j = 1; j < HOTPLATE_SIZE - 1; ++j) {
        hotPlate[row][j] = 100;
    }
}