#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

// tracker class definition
class tracker {
private:
    // A map to store items and their frequencies
    map<string, int> items;

public:
    // Adds an item to the tracking data
    void addItem(const string& item) {
        items[item]++;
    }

    // Returns the frequency of the specified item
    int getItemFrequency(const string& item) {
        return items[item];
    }

    // Returns a map containing the frequency of all items
    map<string, int> getItemFrequency() {
        return items;
    }

    // Loads item data from the specified file and populates the tracking data
    void loadData(const string& filename) {
        ifstream infile(filename);
        string item;

        if (infile.is_open()) {
            while (getline(infile, item)) {
                addItem(item);
            }
            infile.close();
        } else {
            throw runtime_error("Unable to open file");
        }
    }

    // Saves the tracking data to the specified file
    void saveData(const string& filename) {
        ofstream outfile(filename);

        if (outfile.is_open()) {
            for (const auto &item : items) {
                outfile << item.first << " " << item.second << endl;
            }
            outfile.close();
        } else {
            throw runtime_error("Unable to open file");
        }
    }
};

// Function to print the menu options
void printMenu() {
    cout << "\nMenu Options:\n";
    cout << "1. Check item frequency\n";
    cout << "2. Print frequency of all items\n";
    cout << "3. Print histogram of all items\n";
    cout << "4. Exit\n";
    cout << "Enter your choice: ";
}

// Main function
int main() {
    // Create a tracker object
    tracker tracker;

    // Load data from the input file and save it to the backup file
    try {
        tracker.loadData(R"(C:\Users\walte\CLionProjects\Project3\CS210_Project_Three_Input_File.txt)");
        tracker.saveData("frequency.dat");
    } catch (const runtime_error &e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    int userInput;

    // Main loop to handle user input and menu options
    while (true) {
        printMenu();
        cin >> userInput;

        switch (userInput) {
            case 1: {
                // Check and display the frequency of a specified item
                string item;
                cout << "Enter the item you want to check: ";
                cin >> item;
                int frequency = tracker.getItemFrequency(item);
                cout << "The frequency of " << item << " is: " << frequency << endl;
                break;
            }
            case 2: {
                // Print the frequency of all items
                map<string, int> frequencies = tracker.getItemFrequency();
                for (const auto &item : frequencies) {
                    cout << item.first << " " << item.second << endl;
                }
                break;
            }
            case 3: {
                // Print a histogram of the frequency of all items
                map<string, int> frequencies = tracker.getItemFrequency();
                for (const auto &item : frequencies) {
                    cout << item.first << " ";
                    for (int i = 0; i < item.second; i++) {
                        cout << "*";
                    }
                    cout << endl;
                }
                break;
            }
            case 4:
                // Exit the program
                return 0;
            default:
                // Handle invalid user input
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
}