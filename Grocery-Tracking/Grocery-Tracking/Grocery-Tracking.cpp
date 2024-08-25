// Developed by: Jeremy Brown
//Date: 8/18/2024

#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

class GroceryItemTracker {  //Class to handle tracking item frequencies
private:
    map<string, int> frequency; //Map to store item frequency
    
    //Function to load items from the input file and update their frequencies
    bool loadItems(const string& fileName) {    
        ifstream file(fileName);    //Open the file
        string item;

        if (!file.is_open()) {  //Ensure the file was successfully opened
            cout << "Unable to open file!" << endl;
            return false;
        }
        
        //Read each line from the file and update the frequency map
        while (getline(file, item)) {
            if (!item.empty()) {    //ignore empty lines
                frequency[item]++;
            }
        }

        file.close();   //close the file
        return true;
    }
    
    //function ro save frequency data to back up file
    bool saveBackup(const string& backupFile) const {   
        ofstream file(backupFile);  //open the output file

        if (!file.is_open()) {  //Ensure file opened successfully
            cout << "Unable to open file!" << endl;
            return false;
        }

        //Write ach item and its  frequency to the backup file
        for (map<string, int>::const_iterator it = frequency.begin(); it != frequency.end(); ++it) {
            file << it->first << " " << it->second << endl;
        }

        file.close();   //close the file
        return true;
    }
public:
    //Constructor  to load items from the file and create the back up    
    GroceryItemTracker(const string& fileName, const string& backupFile) {
        if (loadItems(fileName)) {  //if we were able to load the file, create the backup file
            saveBackup(backupFile);
        }
    }

    //function to search for a specific items frequency
    int searchItem(const string& item) const {
        //if the item exists in the map, return the frequency, else return 0
        if (frequency.count(item)) {
            return frequency.at(item);
        }
        else {
            return 0;
        }
    }

    //function to display the frequency of all items in the map
    void displayFrequencies() const {
        //iterate through the map and print items and their associated frequency
        for (map<string, int>::const_iterator it = frequency.begin(); it != frequency.end(); ++it) {
            cout << it->first << " " << it->second << endl;
        }
    }

    //function to display the histogram of item frequencies
    void displayHistogram() const {
        // Iterate through the map and print each item and its frequency as asterisks
        for (map<string, int>::const_iterator it = frequency.begin(); it != frequency.end(); ++it) {
            cout << it->first << " " << string(it->second, '*') << endl;
        }
    }
};

//Function to display the menu and handle user input
void menu() {
    string fileName = "CS210_Project_Three_Input_File.txt";
    string backupFile = "frequency.dat";
    GroceryItemTracker tracker(fileName, backupFile);   // Create a GroceryItemTracker object
    bool menuActive = true;
    int userInput;
    string userInputStr;
    
    //loop to display the menu and begin accepting input until the user choses to exit
    while (menuActive) {
        cout << "+--------------CORNER GROCER-------------+\n"  <<
                "| Please select a menu option from below |\n" <<
                "| 1 - Count specific item                |\n" <<
                "| 2 - Count all items                    |\n" <<
                "| 3 - Create Histogram                   |\n" <<
                "| 4 - Exit the Program                   |\n" <<
                "+----------------------------------------+" << endl;
        
        //loop to handle input validation to ensurew a valid integer is input
        while (true) {
            cin >> userInputStr;    //read the input as a string

            try {
                userInput = stoi(userInputStr); //Convert string to integer
                break; // Exit loop if conversion is successful
            }
            catch (const invalid_argument&) {   //catch exception if the input is invalid
                cout << "Invalid input! Please enter a number." << endl;
            }
        }
        
        string item;

        //switch statement to handle different menu options
        switch (userInput) {
        case 1:
            cout << "Enter item to search: ";   //Prompt the user to input an item
            cin >> item;
            cout << item << ": " << tracker.searchItem(item) << endl;   //Display frequency of the specific item
            break;
        case 2:
            tracker.displayFrequencies();   //Function call to display frequency of all items
            break;
        case 3:
            tracker.displayHistogram();     //Function call to display histogram of item frequency
            break;
        case 4:
            cout << "Quitting now..." << endl;
            menuActive = false;     //set the menuActive to false to end the loop
            break;
        default:    //default case if an integer that is not an option is input
            cout << "Invalid selection! Please input a menu option below" << endl;
        }
    }
}

//Main function
int main()
{
    menu();     //function call to start the menu
    return 0;
}
