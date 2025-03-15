#include "util.h"
#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>
#include <ctime>

using namespace std;

// Error function
void Error(string message) {
    cerr << "Error: " << message << endl;
    exit(1);
}

// readLine function
// readLine function
string readLine(const string prompt) {
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}

// readInt function (without range)
int readInt(const string prompt, const string reprompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the buffer
            break;
        }
        cin.clear(); // Clear error flags
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        cout << reprompt;
    }
    return value;
}

// readInt function (with range)
int readInt(const int low, const int high, const string prompt, const string reprompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value && value >= low && value <= high) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the buffer
            break;
        }
        cin.clear(); // Clear error flags
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        cout << reprompt;
    }
    return value;
}

// randInt function (without arguments)
int randInt() {
    static bool seeded = false;
    if (!seeded) {
        srand(static_cast<unsigned int>(time(nullptr))); // Seed the random number generator
        seeded = true;
    }
    return rand();
}

// randInt function (with range)
int randInt(int min, int max) {
    return min + (randInt() % (max - min + 1));
}

// setSeed function
void setSeed(int seed) {
    srand(seed);
}