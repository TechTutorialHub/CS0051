#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

void generateDataFile(const string &filename, int size) {
    ofstream outFile(filename);
    srand(time(0));

    if (!outFile) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    for (int i = 0; i < size; i++) {
        outFile << (rand() % 100) << endl;
    }

    outFile.close();
}

void readDataFile(const string &filename, int arr[], int size) {
    ifstream inFile(filename);

    if (!inFile) {
        cerr << "Error opening file for reading!" << endl;
        return;
    }

    for (int i = 0; i < size; i++) {
        inFile >> arr[i];
    }

    inFile.close();
}

void writeDataFile(const string &filename, int arr[], int size) {
    ofstream outFile(filename);

    if (!outFile) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    for (int i = 0; i < size; i++) {
        outFile << arr[i] << endl;
    }

    outFile.close();
}

int main() {
    int N;
    cout << "Enter the number of data points: ";
    cin >> N;

    const string inputFile = "data.txt";
    const string outputFile = "output.txt";
    int *arr = new int[N];

    generateDataFile(inputFile, N);
    readDataFile(inputFile, arr, N);

    // Processing without OpenACC
    for (int i = 0; i < N; i++) {
        arr[i] *= arr[i]; // Squaring each element
    }

    writeDataFile(outputFile, arr, N);

    cout << "Processed Data (Squared Values): ";
    for (int i = 0; i < N; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    delete[] arr;
    return 0;
}
