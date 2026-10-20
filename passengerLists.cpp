// Read Titanic Passenger data from a cleaned .csv
#include <iostream>  
#include <iomanip>  // formatting strings
#include <fstream>  // loading from files
#include <sstream>  // processing comma separated fields
#include <string>   // stoi, stod to convert strings to int, double
using namespace std;

// Passenger is a custom datatype matching titanic.csv columns
struct Passenger {
    int PassengerId;
    int Survived;
    int Class;
    string LastName;
    string Gender;
    int Age;
    double Fare;
};

// we use this to nicely format a passenger info
// make use of the iomanip library with setw to set width
void PrintPassenger(Passenger p) {
    cout << left
         << setw(12) << p.PassengerId
         << setw(10) << p.Survived
         << setw(8) << p.Class
         << setw(25) << p.LastName.substr(0, 24)
         << setw(8) << p.Gender.substr(0, 6)
         << right
         << setw(5) << p.Age
         << setw(12) << fixed << setprecision(2) << p.Fare
         << endl;
}

// header with passenger data columns labels
void PrintPassengerHeader() {
    cout << left
        << setw(12) << "PassengerId"
        << setw(10) << "Survived"
        << setw(8) << "Class"
        << setw(25) << "LastName"
        << setw(8) << "Gender"
        << right
        << setw(5) << "Age"
        << setw(12) << "Fare"
        << endl;
    // divider line of dashes
    cout << string(80, '-') << endl;
}

int main() {
    // we will use these to read from titanic.csv
    // and populate an array of passengers
    int count = 0; 
    const int MAX_PASSENGERS = 1000;
    Passenger passengers[MAX_PASSENGERS];
    string line, field;

    // open titanic.csv as an input file string called "infile"
    ifstream infile("titanic.csv");
    if (!infile) {
        cout << "Error opening file." << endl;
        return 1;
    }

    // Skip the header row
    getline(infile, line);

    // Read each passenger
    while (getline(infile, line) &&
        count < MAX_PASSENGERS) {
        // "line" is a line of comma separated data
        stringstream ss(line);

        // "field" is all characters from "ss" until the first ,
        // use "stoi" from string library to convert field to an integer
        // use "stod" to convert field to an double
        getline(ss, field, ',');
        passengers[count].PassengerId = stoi(field);
        getline(ss, field, ',');
        passengers[count].Survived = stoi(field);
        getline(ss, field, ',');
        passengers[count].Class = stoi(field);
        getline(ss, passengers[count].LastName, ',');
        getline(ss, passengers[count].Gender, ',');
        getline(ss, field, ',');
        passengers[count].Age = stoi(field);
        getline(ss, field, ',');
        passengers[count].Fare = stod(field);
        count++;
    }

    // close the file
    infile.close();
    cout << "Read " << count << " passengers." << endl;

    // Display the surviors
    PrintPassengerHeader();
    for (int i = 0; i < count; i++)
        if (passengers[i].Survived)
            PrintPassenger(passengers[i]);
    // success!!
    return 0;
}
