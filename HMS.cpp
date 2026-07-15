#include<iostream>
#include<string>
#include<vector>
#include <iomanip>
#include <fstream>
using namespace std ;

// Student
struct Student {
    int rollNumber;
    string name;
    string address;
    int age;
};
/**
 * Add Student to Vector
*/
void addStudent(vector<Student> &students) {
    Student newStudent;
    cout << "Enter roll number: ";
    cin >> newStudent.rollNumber;
    cout << "Enter name: ";
    cin.ignore();
    getline(cin, newStudent.name);
    cout << "Enter address: ";
    getline(cin, newStudent.address);
    cout << "Enter age: ";
    cin >> newStudent.age;

    students.push_back(newStudent);
    cout << "Student added successfully!" << endl;
}


/**
 * Read all students from file system
*/
void readStudentsFromFile(vector<Student>& students, const string& filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cout << "Error opening file for reading." << endl;
        return;
    }

    Student student;
    while (inFile >> student.rollNumber) {
        inFile.ignore(); // Ignore the comma
        getline(inFile, student.name, ',');
        getline(inFile, student.address, ',');
        inFile >> student.age;
        students.push_back(student);
        inFile.ignore(); // Ignore the newline character
    }

    inFile.close();
}

/**
 * Append a student into file system
*/
void appendStudentToFile(const Student& student, const string& filename) {
    ofstream outFile(filename, ios_base::app); // Open in append mode
    if (!outFile.is_open()) {
        cout << "Error opening file for appending." << endl;
        return;
    }

    outFile << student.rollNumber << "," << student.name << ","
            << student.address << "," << student.age << endl;

    outFile.close();
    cout << "Student data appended to " << filename << endl;
}
/**
 * Overwrite a students list into file system
*/

void overwriteStudentsToFile(const vector<Student>& students, const string& filename) {
    ofstream outFile(filename, ios_base::trunc); // Open in append mode
    if (!outFile.is_open()) {
        cout << "Error opening file for appending." << endl;
        return;
    }

    for (const auto& student : students) {
        outFile << student.rollNumber << "," << student.name << ","
            << student.address << "," << student.age << endl;
    }
    outFile.close();
    cout << "Student data appended to " << filename << endl;
}

/**
 * Remove Student from Vector
*/
void removeStudent(vector<Student> &students, int rollNumber) {
    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->rollNumber == rollNumber) {
            students.erase(it);
            cout << "Student removed successfully!" << endl;
            overwriteStudentsToFile(students, "students.txt");
            return;
        }
    }
    cout << "Student with roll number " << rollNumber << " not found!" << endl;
}

/**
 * Displays a list of students on screen reading from Vector
*/
void displayStudents(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No students in the hostel." << endl;
        return;
    }

    cout << setw(15) << left << "Roll Number" << setw(30) << left << "Name" << setw(50) << left << "Address" << setw(1) << left << "Age" << endl;

    for (const auto& student : students) {
        cout << setw(15) << left << student.rollNumber << setw(30) << left << student.name << setw(50) << left << student.address << setw(1) << left << student.age << endl;

    }
}

/**
 * Search Students
*/
void searchStudent(const vector<Student> &students, int rollNumber) {
    for (const auto &student : students) {
        if (student.rollNumber == rollNumber) {
            cout << setw(15) << left << "Roll Number" << setw(30) << left << "Name" << setw(50) << left << "Address" << setw(1) << left << "Age" << endl;
            cout << setw(15) << left << student.rollNumber << setw(30) << left << student.name << setw(50) << left << student.address << setw(1) << left << student.age << endl;
            return;
        }
    }
    cout << "Student with roll number " << rollNumber << " not found!" << endl;
}

// Struct to represent an application
struct Application {
    string name, fathersName, department, nationality, address, email;
    int rollNumber, adm, merit ;
    long long int pnum ;
};


/**
 * Read all students from file system
*/
void readApplicationsFromFile(vector<Application>& applications, const string& filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cout << "Error opening file for reading." << endl;
        return;
    }

    Application application;
    while (getline(inFile, application.name, ',')) {
        inFile.ignore(); // Ignore the comma
        getline(inFile, application.fathersName, ',');
        getline(inFile, application.department, ',');
        getline(inFile, application.nationality, ',');
        getline(inFile, application.address, ',');
        getline(inFile, application.email, ',');
        inFile >> application.rollNumber;
        inFile >> application.adm;
        inFile >> application.merit;
        inFile >> application.pnum;
        applications.push_back(application);

        inFile.ignore(); // Ignore the newline character
    }

    inFile.close();
}

/**
 * Append a application into file system
*/
void appendApplicationToFile(const Application& application, const string& filename) {
    ofstream outFile(filename, ios_base::app); // Open in append mode
    if (!outFile.is_open()) {
        cout << "Error opening file for appending." << endl;
        return;
    }

    outFile << application.name << "," << application.fathersName << ","
            << application.department << "," << application.nationality  << ","
            << application.address << "," << application.email << ","
            << application.rollNumber << "," << application.adm << ","
            << application.merit << "," << application.pnum << endl;

    outFile.close();
    cout << "Application data appended to " << filename << endl;
}
class Hosteler {
public:
    // Method for hosteler to apply online
    Application applyOnline() {
        Application application;
        cout << "Name of student: ";
        cin.ignore(1,'\n') ;
        getline(cin,application.name);
        cout << "Father's name: ";
        getline(cin,application.fathersName) ;
        cout << "Roll Number: ";
        cin >> application.rollNumber;
        cout << "Admission letter number: ";
        cin >> application.adm;
        cout << "Merit number: ";
        cin >> application.merit;
        cout << "Department: ";
        cin.ignore(1,'\n') ;
        getline(cin,application.department) ;
        cout << "Nationality: ";
        getline(cin,application.nationality);
        cout << "Address: ";
        getline(cin,application.address) ;
        cout << "Email: ";
        cin >> application.email;
        cout << "Phone Number: ";
        cin >> application.pnum;
        return application;
    }
};
class HostelManager : public Hosteler{
private:
    vector<Application> applications;
    
public:
    // Method to display all online applications
    void displayApplications() {
        readApplicationsFromFile(applications, "applications.txt");

        cout << "\nOnline Applications:\n";
        if (applications.empty()) {
            cout << "No applications submitted yet.\n";
        } else {
            for (const auto& app : applications) {
                cout << "Name: " << app.name << endl;
                cout << "Father's name: " << app.fathersName << endl;
                cout << "Roll Number: " << app.rollNumber << endl;
                cout << "Admission letter number: " << app.adm << endl;
                cout << "Merit number: " << app.merit << endl;
                cout << "Department: " << app.department << endl;
                cout << "Nationality: " << app.nationality << endl;
                cout << "Address: " << app.address << endl;
                cout << "Email: " << app.email << endl;
                cout << "Phone number: " << app.pnum << endl << endl;

            }
        }
    }

    // Method to add an application
    void addApplication(const Application& application) {
        applications.push_back(application);
        appendApplicationToFile(applications.back(), "applications.txt");
        cout << "Application submitted successfully!\n";
    }
};

struct PaymentRecord {
    string studentName;
    double amountPaid;
};

class HostelPaymentManager {
private:
    vector<PaymentRecord> paymentRecords;

public:
    void addPaymentRecord(const string& studentName, double amountPaid) {
        PaymentRecord newRecord = {studentName, amountPaid};
        paymentRecords.push_back(newRecord);
        cout << "Payment record added successfully." << endl;
    }

    void deletePaymentRecord(int index) {
        if (index >= 0 && index < paymentRecords.size()) {
            paymentRecords.erase(paymentRecords.begin() + index);
            cout << "Payment record deleted successfully." << endl;
        } else {
            cout << "Invalid index. No payment record deleted." << endl;
        }
    }

    void displayPaymentRecords() {
        if (paymentRecords.empty()) {
            cout << "No payment records available." << endl;
        } else {
            cout << "Payment Records:" << endl;
            for (size_t i = 0; i < paymentRecords.size(); ++i) {
                cout << "Index: " << i << ", Student Name: " << paymentRecords[i].studentName
                     << ", Amount Paid: Rs." << paymentRecords[i].amountPaid << endl;
            }
        }
    }
};
struct Room {
    int roomNumber;
    string roomType;
    bool occupied;
    float price;
};

void displayRoom(const Room& room) {
    cout << "Room Number: " << room.roomNumber << endl;
    cout << "Room Type: " << room.roomType << endl;
    cout << "Occupied: " << (room.occupied ? "Yes" : "No") << endl;
    cout << "Room Rent per person: Rs." << room.price <<"/-"<< endl;
}
// Structure to represent a mess
struct Mess {
    string name;
    float costPerMeal;
    int capacity;
    int mealsServed;
};

// Function to display mess information
void displayMessInfo(const Mess& mess) {
    cout << "Mess Name: " << mess.name << endl;
    cout << "Cost per Meal: Rs." << mess.costPerMeal << endl;
    cout << "Capacity: " << mess.capacity << " students" << endl;
    cout << "Meals Served: " << mess.mealsServed << endl;
}
struct Room1 {
    int roomNumber;
    string roomType;
    bool occupied;
    float price;
};

void displayRoom(const Room1& room) {
    cout << "Room Number: " << room.roomNumber << endl;
    cout << "Room Type: " << room.roomType << endl;
    cout << "Occupied: " << (room.occupied ? "Yes" : "No") << endl;
    cout << "Room Rent per person: Rs." << room.price <<"/-"<< endl;
}
class hostellerfee {
public:
    // char name[30];
    // int roll;
    int messBill = 500;
    int electricityBill = 500;
    int laundryBill = 200;
    int hostelRent = 1500;

    void show_info();
};

void hostellerfee::show_info() {
    cout << "\n\n\t\t\t ***** FEE DETAILS *****\n\n\n";
    cout << "MESS BILL\tELEC. BILL\tLAUNDRY BILL\tHOSTEL RENT\tTOTAL BILL\n";
    cout << messBill << "\t\t" << electricityBill << "\t\t" << laundryBill << "\t\t" 
         << hostelRent << "\t\t" << (messBill + electricityBill + laundryBill + hostelRent);
}
int main(){
    HostelManager manager;
    Hosteler hosteler;

    int integer;
cout << "\t\t###      ###     ###      ###      ##########" << endl;
cout << "\t\t###      ###     ####    ####     ##########" << endl;
cout << "\t\t###      ###     #####  #####    ###" << endl;
cout << "\t\t############     ### ### ####    ##########" << endl;
cout << "\t\t############     ###  #   ###     ##########" << endl;
cout << "\t\t###      ###     ###      ###            #####" << endl;
cout << "\t\t###      ###     ###      ###     ############" << endl;
cout << "\t\t###      ###     ###      ###    ############" << endl;
cout << "\t\t************************************************" << endl;
cout << "\t\t************Hostel Management System************" << endl; 
cout << "\t\t************************************************" << endl;
    do {
        cout << "\nMenu:\n";
        cout << "1. Manager\n";
        cout << "2. Register for hostel\n";
        cout << "3. hosteler\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> integer;

        switch (integer) {
            case 1: {
                vector<Student> students;

                // Read students from the file system
                readStudentsFromFile(students, "students.txt");

            int choice;
            do {
                cout << "\nHostel Management System" << endl;
                cout << "1. Add Student" << endl;
                cout << "2. Remove Student" << endl;
                cout << "3. Display All Students" << endl;
                cout << "4. Search Student" << endl;
                cout << "5. Check application" << endl;
                cout << "6. Hostel payment record" << endl;
                cout << "7. Return to main menu" << endl;
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice) {
                    case 1:
                        addStudent(students);
                        appendStudentToFile(students.back(), "students.txt");
                        break;
                    case 2: {
                        int rollNumber;
                        cout << "Enter roll number of the student to remove: ";
                        cin >> rollNumber;
                        removeStudent(students, rollNumber);
                        break;
                    }
                    case 3:{
                        displayStudents(students);
                        break;
                    }
                    case 4: {
                        int rollNumber;
                        cout << "Enter roll number of the student to search: ";
                        cin >> rollNumber;
                        searchStudent(students, rollNumber);
                        break;
                    }
                    case 5: {
                    manager.displayApplications();
                        break;
                    }
                    case 6: {
                        HostelPaymentManager manager;
                int choice;
                do {
                    cout << "\nHostel Payment Management System" << endl;
                    cout << "1. Add Payment Record" << endl;
                    cout << "2. Delete Payment Record" << endl;
                    cout << "3. Display Payment Records" << endl;
                    cout << "4. Exit" << endl;
                    cout << "Enter your choice: ";
                    cin >> choice;

                    switch (choice) {
                        case 1: {
                            string name;
                            double amount;
                            cout << "Enter student name: ";
                            cin >> name;
                            cout << "Enter amount paid: ";
                            cin >> amount;
                            manager.addPaymentRecord(name, amount);
                            break;
                        }
                        case 2: {
                            int index;
                            cout << "Enter index of payment record to delete: ";
                            cin >> index;
                            manager.deletePaymentRecord(index);
                            break;
                        }
                        case 3:
                            manager.displayPaymentRecords();
                            break;
                        case 4:
                            cout << "Exiting.." << endl;
                            break;
                        default:
                            cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
                    }
                } while (choice != 4);
                break ;
                    }
                    case 7:
                        cout << "Returned to main menu..." << endl;
                        break;
                    default:
                        cout << "Invalid choice! Please try again." << endl;
                }
            } while (choice != 7);
                break ;
                    } 
            case 2: {
                Application newApplication = hosteler.applyOnline();
                manager.addApplication(newApplication);
                break;
            }
            case 3: {
                        // HostelPaymentManager manager;
                int choice;
                do {
                    cout << "\nInformation for the Hostelers" << endl;
                    cout << "1. Wifi services" << endl;
                    cout << "2. Water Management system" << endl;
                    cout << "3. Fee structure" << endl;
                    cout << "4. Room information" << endl;
                    cout << "5. Mess information" << endl;
                    cout << "6. Exit" << endl;
                    cout << "Enter your choice: ";
                    cin >> choice;

                switch (choice) {
                    case 1: {
                    cout<<"\n\nSTANDING RULES REGARDING WIFI LOGIN:\n\n";
                    cout<<"1. Wifi services are available for 24 hours."<<endl ; 
                    cout<<"2. Please do not pay for any wifi bill on any payment link." <<endl ;
                    cout<<"3. For the sake of privacy, different wifi passwords have been issued to the students."<<endl;
                    cout<<"4. Please DO NOT share your password with anybody else."<<endl;
                    cout<<"\n\nCONNECTION NAME: H8_5G \nPlease enter your 6-digit password\nPASSWORD:";
                    string pass;
                    cin >> pass;
                    string password1 = "CHD@h8";   // Defining valid passwords
                    string password2 = "ASR@h8";
                    string password3 = "PTL@h8";
                if (pass == password1 || pass == password2 || pass == password3) {  
                // Checking if the entered password matches any of the valid passwords    
                    cout << "WiFi password accepted!!" << endl;}
                    else {
                    cout << "Incorrect password!!" << endl; }

                    if (pass.length()!= 6){   
                     // Checking if the entered password is exactly 6 characters long
                        cout << "Please enter exactly 6 digits." << endl;
                        return 1;
                    }
                            break;
                        }
                case 2: {
                cout<<"\n\nWATER MANAGEMENT PAGE"<<endl;
                cout<<endl ;
                cout<<"KINDLY NOTE:-  WATER SERVICE CHARGES ARE INCLUDED IN THE HOSTEL FEE.";
                cout<<endl<<endl ;
                cout<<"STANDING RULES REGARDING WATER AMENITIES:\n\n";
                cout<<"1. Please do not pay for any water bill on any payment link." <<endl ; 
                cout<<"2. Fresh water is available in the mornings from 6AM to 9AM and from 6PM to 9PM in the evenings.\n";
                cout<<"3. Tank water is available 24/7. ";
                cout<<"4. Make sure to keep a check on any leakage from pipes or taps."<<endl ;
                cout<<"5. In case of any leakage, inform the authorities immediately or call on 1800652349."<<endl;
                cout<<"6. Please be responsible and DO NOT waste water.\n ";
                            break;
                        }
                        case 3: {
                            hostellerfee abc;
                            abc.show_info();
                            break ;
                        }
                        case 4: {
                            vector<Room1> hostelRooms = {
                        {101, "Single", true, 2500},
                        {102, "Double", false, 2000},
                        {103, "Single", true, 2500},
                        {104, "Double", false, 2000},
                        {105, "Single", false, 2500},
                        {106, "Double", true, 2000}
                        };

                        cout << "Hostel Room Information:" << endl;
                        for (const auto& room : hostelRooms) {
                            displayRoom(room);
                            cout << endl;
                        }
                            break;
                        }
                        case 5: {
                            // Creating mess objects
                        Mess mess1 = {"Mess A", 40, 100, 0};
                        Mess mess2 = {"Mess B", 45, 80, 0};

                        // Vector to store mess objects
                        vector<Mess> messList;
                        messList.push_back(mess1);
                        messList.push_back(mess2);

                        // Displaying mess information
                        cout << "Mess Information:" << endl;
                        for (const auto& mess : messList) {
                            displayMessInfo(mess);
                            cout << endl;
                        }
                            break;
                        }
                        case 6:
                            cout << "Exiting.." << endl;
                            break;
                        default:
                            cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
                    }
                } while (choice != 6);
                break ;
                    }
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (integer != 4);
    return 0 ;
}
