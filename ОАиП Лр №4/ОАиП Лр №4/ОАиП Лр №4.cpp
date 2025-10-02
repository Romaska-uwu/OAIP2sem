#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct Citizen {
    string fullName;
    string dateOfBirth;
    string address;
    char gender; // 'M' for male, 'F' for female
};

void inputCitizen(std::vector<Citizen>& citizens) {
    Citizen c;
    cout << "Enter full name: ";
    cin.ignore();
    getline(cin, c.fullName);
    cout << "Enter date of birth (DD/MM/YYYY): ";
    cin >> c.dateOfBirth;
    cout << "Enter address: ";
    cin.ignore();
    getline(cin, c.address);
    cout << "Enter gender (M/F): ";
    cin >> c.gender;
    citizens.push_back(c);
}

void outputCitizens(const vector<Citizen>& citizens) {
    for (const auto& citizen : citizens) {
        cout << "Full Name: " << citizen.fullName << ", Date of Birth: " << citizen.dateOfBirth
            << ", Address: " << citizen.address << ", Gender: " << citizen.gender << endl;
    }
}

void deleteCitizen(vector<Citizen>& citizens, const string& fullName) {
    auto it = find_if(citizens.begin(), citizens.end(), [&fullName](const Citizen& c) { return c.fullName == fullName; });
    if (it != citizens.end()) {
        citizens.erase(it);
        cout << "Citizen deleted successfully." << std::endl;
    }
    else {
        cout << "Citizen not found." << endl;
    }
}

void searchCitizen(const vector<Citizen>& citizens, const string& fullName) {
    auto it = find_if(citizens.begin(), citizens.end(), [&fullName](const Citizen& c) { return c.fullName == fullName; });
    if (it != citizens.end()) {
        cout << "Full Name: " << it->fullName << ", Date of Birth: " << it->dateOfBirth
            << ", Address: " << it->address << ", Gender: " << it->gender << endl;
    }
    else {
        cout << "Citizen not found." << endl;
    }
}

void writeToFile(const vector<Citizen>& citizens, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& citizen : citizens) {
            file << citizen.fullName << " " << citizen.dateOfBirth << " " << citizen.address << " " << citizen.gender << "\\n";
        }
        file.close();
        cout << "Data written to file successfully." << endl;
    }
    else {
        cout << "Unable to open file." << endl;
    }
}

void readFromFile(vector<Citizen>& citizens, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        Citizen c;
        while (file >> c.fullName >> c.dateOfBirth >> c.address >> c.gender) {
            citizens.push_back(c);
        }
        file.close();
        cout << "Data read from file successfully." << endl;
    }
    else {
        cout << "Unable to open file." << endl;
    }
}

void filterByYearOfBirth(const vector<Citizen>& citizens, int year) {
    for (const auto& citizen : citizens) {
        if (citizen.dateOfBirth.substr(6, 4) == to_string(year)) {
            cout << "Full Name: " << citizen.fullName << ", Date of Birth: " << citizen.dateOfBirth << ", Address: " << citizen.address << ", Gender: " < &lt; citizen.gender << endl;
        }
    }
}

int main() {
    vector<Citizen> citizens;
    int choice;

    do {
        cout << "\\nMenu:\\n1. Add Citizen\\n2. Display All Citizens\\n3. Delete Citizen\\n4. Search Citizen\\n5. Write to File\\n6. Read from File\\n7. Filter by Year of Birth\\n0. Exit\\n";
        cin >> choice;

        switch (choice) {
        case 1:
            inputCitizen(citizens);
            break;
        case 2:
            outputCitizens(citizens);
            break;
        case 3:
        {
            string nameToDelete;
            cout << "Enter full name of citizen to delete: ";
            cin.ignore();
            getline(cin, nameToDelete);
            deleteCitizen(citizens, nameToDelete);
        }
        break;
        case 4:
        {
            string nameToSearch;
            cout << "Enter full name of citizen to search: ";
            cin.ignore();
            getline(cin, nameToSearch);
            searchCitizen(citizens, nameToSearch);
        }
        break;
        case 5:
            writeToFile(citizens, "citizens.txt");
            break;
        case 6:
            readFromFile(citizens, "citizens.txt");
            break;
        case 7:
        {
            int year;
            cout << "Enter the year of birth to filter by: ";
            cin >> year;
            filterByYearOfBirth(citizens, year);
        }
        break;
        case 0:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    } while (choice != 0);

    return 0;
}
