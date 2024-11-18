#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int resources = 3;
const int processes = 5;

void readMatrix(ifstream &input, int rows, int cols, int matrix[][resources]);
void readArray(ifstream &input, int size, int array[]);

int main() {
    ifstream inFile("input.txt");

    // Check if the file was opened successfully
    if (!inFile.is_open()) {
        cerr << "Error: Could not open input file." << endl;
        return 1;
    }

    int allocation[processes][resources];
    int max[processes][resources];
    int available[resources];

    readMatrix(inFile, processes, resources, allocation);
    readMatrix(inFile, processes, resources, max);
    readArray(inFile, resources, available);

    inFile.close();

    int store[processes] = {0};      
    int safeseq[processes] = {0};   
    int index = 0;
    int need[processes][resources];

    // calculate the need
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Find safe sequences
    for (int k = 0; k < processes; k++) {
        bool found = false;
        for (int i = 0; i < processes; i++) {
            // checking if already completed
            if (store[i] == 0) {
                bool canExecute = true;

                // Check if it can be executed successfully
                for (int j = 0; j < resources; j++) {
                    if (need[i][j] > available[j]) {
                        canExecute = false;
                        break;
                    }
                }

                // If the process can be safely executed
                if (canExecute) {
                    safeseq[index++] = i;

                    // Update available resources
                    for (int d = 0; d < resources; d++) {
                        available[d] += allocation[i][d];
                    }

                    store[i] = 1; // Mark process as completed
                    found = true;
                }
            }
        }

        // If no process was found in this pass, break early
        if (!found) {
            break;
        }
    }

    // Check if all processes are completed
    bool isSafe = true;
    for (int i = 0; i < processes; i++) {
        if (store[i] == 0) {
            isSafe = false;
            cout << "Sequence is not safe." << endl;
            break;
        }
    }

    if (isSafe) {
        cout << "Safe Sequence: ";
        for (int i = 0; i < processes - 1; i++) {
            cout << "P" << safeseq[i] << ", ";
        }
        cout << "P" << safeseq[processes - 1] << endl;
    }

    return 0;
}

void readMatrix(ifstream &input, int rows, int cols, int matrix[][resources]) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            input >> matrix[i][j];
        }
    }
}

void readArray(ifstream &input, int size, int array[]) {
    for (int i = 0; i < size; ++i) {
        input >> array[i];
    }
}
