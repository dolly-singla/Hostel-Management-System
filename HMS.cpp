#include<iostream>
#include<string>
#include<vector>
#include<iomanip>
#include<fstream>
#include<sstream>
using namespace std;

/* ======================================================================
   BASE CLASS: HostelMember
   ----------------------------------------------------------------------
   Abstract base class demonstrating INHERITANCE + POLYMORPHISM.
   Any "person" tracked by the hostel (a registered Student, or someone
   who has submitted an online Application) shares a name and address,
   and every derived type must define its own displayInfo().
   ====================================================================== */
class HostelMember {
protected:
    string name;
    string address;

public:
    HostelMember(string n = "", string a = "") : name(n), address(a) {}

    // Encapsulation: controlled access to protected data
    string getName() const { return name; }
    string getAddress() const { return address; }
    void setName(const string& n) { name = n; }
    void setAddress(const string& a) { address = a; }

    // Pure virtual function -> HostelMember is an abstract class,
    // and every derived class MUST provide its own implementation.
    virtual void displayInfo() const = 0;

    virtual ~HostelMember() {}
};

/* ======================================================================
   Student : public HostelMember
   ====================================================================== */
class Student : public HostelMember {
private:
    int rollNumber;
    int age;

public:
    Student(int roll = 0, string n = "", string addr = "", int a = 0)
        : HostelMember(n, addr), rollNumber(roll), age(a) {}

    // Encapsulation: private fields, public accessors
    int getRollNumber() const { return rollNumber; }
    int getAge() const { return age; }
    void setRollNumber(int r) { rollNumber = r; }
    void setAge(int a) { age = a; }

    // Polymorphism: overrides HostelMember::displayInfo()
    void displayInfo() const override {
        cout << setw(15) << left << rollNumber
             << setw(30) << left << name
             << setw(50) << left << address
             << setw(5)  << left << age << endl;
    }

    static void printHeader() {
        cout << setw(15) << left << "Roll Number"
             << setw(30) << left << "Name"
             << setw(50) << left << "Address"
             << setw(5)  << left << "Age" << endl;
    }
};

/**
 * Add Student to Vector
*/
void addStudent(vector<Student>& students) {
    int roll, age;
    string name, address;

    cout << "Enter roll number: ";
    cin >> roll;
    cout << "Enter name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter address: ";
    getline(cin, address);
    cout << "Enter age: ";
    cin >> age;

    students.push_back(Student(roll, name, address, age));
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

    int roll;
    while (inFile >> roll) {
        string name, address;
        int age;
        inFile.ignore(); // Ignore the comma
        getline(inFile, name, ',');
        getline(inFile, address, ',');
        inFile >> age;
        students.push_back(Student(roll, name, address, age));
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

    outFile << student.getRollNumber() << "," << student.getName() << ","
            << student.getAddress() << "," << student.getAge() << endl;

    outFile.close();
    cout << "Student data appended to " << filename << endl;
}

/**
 * Overwrite a students list into file system
*/
void overwriteStudentsToFile(const vector<Student>& students, const string& filename) {
    ofstream outFile(filename, ios_base::trunc);
    if (!outFile.is_open()) {
        cout << "Error opening file for appending." << endl;
        return;
    }

    for (const auto& student : students) {
        outFile << student.getRollNumber() << "," << student.getName() << ","
                << student.getAddress() << "," << student.getAge() << endl;
    }
    outFile.close();
    cout << "Student data appended to " << filename << endl;
}

/**
 * Remove Student from Vector
*/
void removeStudent(vector<Student>& students, int rollNumber) {
    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->getRollNumber() == rollNumber) {
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
 * (Calls displayInfo() polymorphically through the HostelMember interface)
*/
void displayStudents(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No students in the hostel." << endl;
        return;
    }

    Student::printHeader();
    for (const auto& student : students) {
        const HostelMember& member = student; // upcast -> polymorphic call
        member.displayInfo();
    }
}

/**
 * Search Students
*/
void searchStudent(const vector<Student>& students, int rollNumber) {
    for (const auto& student : students) {
        if (student.getRollNumber() == rollNumber) {
            Student::printHeader();
            student.displayInfo();
            return;
        }
    }
    cout << "Student with roll number " << rollNumber << " not found!" << endl;
}

/* ======================================================================
   Applicant : public HostelMember
   ----------------------------------------------------------------------
   Replaces the old "Application" struct. Everything that used to be a
   public field is now private, accessed through getters/setters.
   ====================================================================== */
class Applicant : public HostelMember {
private:
    string fathersName, department, nationality, email;
    int rollNumber, adm, merit;
    long long int pnum;

public:
    Applicant(string n = "", string fn = "", string dept = "", string nat = "",
               string addr = "", string em = "", int roll = 0, int a = 0,
               int m = 0, long long int phone = 0)
        : HostelMember(n, addr), fathersName(fn), department(dept),
          nationality(nat), email(em), rollNumber(roll), adm(a),
          merit(m), pnum(phone) {}

    // Getters
    string getFathersName() const { return fathersName; }
    string getDepartment() const { return department; }
    string getNationality() const { return nationality; }
    string getEmail() const { return email; }
    int getRollNumber() const { return rollNumber; }
    int getAdm() const { return adm; }
    int getMerit() const { return merit; }
    long long int getPnum() const { return pnum; }

    // Setters
    void setFathersName(const string& v) { fathersName = v; }
    void setDepartment(const string& v) { department = v; }
    void setNationality(const string& v) { nationality = v; }
    void setEmail(const string& v) { email = v; }
    void setRollNumber(int v) { rollNumber = v; }
    void setAdm(int v) { adm = v; }
    void setMerit(int v) { merit = v; }
    void setPnum(long long int v) { pnum = v; }

    // Polymorphism: its own version of displayInfo()
    void displayInfo() const override {
        cout << "Name: " << name << endl;
        cout << "Father's name: " << fathersName << endl;
        cout << "Roll Number: " << rollNumber << endl;
        cout << "Admission letter number: " << adm << endl;
        cout << "Merit number: " << merit << endl;
        cout << "Department: " << department << endl;
        cout << "Nationality: " << nationality << endl;
        cout << "Address: " << address << endl;
        cout << "Email: " << email << endl;
        cout << "Phone number: " << pnum << endl << endl;
    }
};

/**
 * Read all applications from file system
*/
void readApplicationsFromFile(vector<Applicant>& applications, const string& filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cout << "Error opening file for reading." << endl;
        return;
    }

    string line;
    while (getline(inFile, line)) {
        if (line.empty()) continue;

        // Parse the whole line with a single delimiter strategy (comma),
        // instead of mixing getline() and >> which left the stream
        // sitting on unconsumed commas and corrupted the numeric fields
        // (this is what was garbling the phone number).
        istringstream ss(line);
        string name, fathersName, department, nationality, address, email;
        string rollStr, admStr, meritStr, pnumStr;

        getline(ss, name, ',');
        getline(ss, fathersName, ',');
        getline(ss, department, ',');
        getline(ss, nationality, ',');
        getline(ss, address, ',');
        getline(ss, email, ',');
        getline(ss, rollStr, ',');
        getline(ss, admStr, ',');
        getline(ss, meritStr, ',');
        getline(ss, pnumStr, ',');

        int rollNumber = rollStr.empty() ? 0 : stoi(rollStr);
        int adm = admStr.empty() ? 0 : stoi(admStr);
        int merit = meritStr.empty() ? 0 : stoi(meritStr);
        long long int pnum = pnumStr.empty() ? 0 : stoll(pnumStr);

        applications.push_back(Applicant(name, fathersName, department, nationality,
                                          address, email, rollNumber, adm, merit, pnum));
    }

    inFile.close();
}

/**
 * Append an application into file system
*/
void appendApplicationToFile(const Applicant& application, const string& filename) {
    ofstream outFile(filename, ios_base::app);
    if (!outFile.is_open()) {
        cout << "Error opening file for appending." << endl;
        return;
    }

    outFile << application.getName() << "," << application.getFathersName() << ","
            << application.getDepartment() << "," << application.getNationality() << ","
            << application.getAddress() << "," << application.getEmail() << ","
            << application.getRollNumber() << "," << application.getAdm() << ","
            << application.getMerit() << "," << application.getPnum() << endl;

    outFile.close();
    cout << "Application data appended to " << filename << endl;
}

class Hosteler {
public:
    // Method for hosteler to apply online
    Applicant applyOnline() {
        string name, fathersName, department, nationality, address, email;
        int rollNumber, adm, merit;
        long long int pnum;

        cout << "Name of student: ";
        cin.ignore(1, '\n');
        getline(cin, name);
        cout << "Father's name: ";
        getline(cin, fathersName);
        cout << "Roll Number: ";
        cin >> rollNumber;
        cout << "Admission letter number: ";
        cin >> adm;
        cout << "Merit number: ";
        cin >> merit;
        cout << "Department: ";
        cin.ignore(1, '\n');
        getline(cin, department);
        cout << "Nationality: ";
        getline(cin, nationality);
        cout << "Address: ";
        getline(cin, address);
        cout << "Email: ";
        cin >> email;
        cout << "Phone Number: ";
        cin >> pnum;

        return Applicant(name, fathersName, department, nationality,
                          address, email, rollNumber, adm, merit, pnum);
    }
};

/* HostelManager inherits from Hosteler -> a manager IS-A hosteler-facing
   role that additionally administers submitted applications. */
class HostelManager : public Hosteler {
private:
    vector<Applicant> applications;

public:
    // Method to display all online applications
    void displayApplications() {
        readApplicationsFromFile(applications, "applications.txt");

        cout << "\nOnline Applications:\n";
        if (applications.empty()) {
            cout << "No applications submitted yet.\n";
        } else {
            for (const auto& app : applications) {
                const HostelMember& member = app; // polymorphic call
                member.displayInfo();
            }
        }
    }

    // Method to add an application
    void addApplication(const Applicant& application) {
        applications.push_back(application);
        appendApplicationToFile(applications.back(), "applications.txt");
        cout << "Application submitted successfully!\n";
    }
};

/* ======================================================================
   PaymentRecord - converted from struct to class (encapsulation)
   ====================================================================== */
class PaymentRecord {
private:
    string studentName;
    double amountPaid;

public:
    PaymentRecord(string name = "", double amount = 0.0)
        : studentName(name), amountPaid(amount) {}

    string getStudentName() const { return studentName; }
    double getAmountPaid() const { return amountPaid; }
};

class HostelPaymentManager {
private:
    vector<PaymentRecord> paymentRecords;

public:
    void addPaymentRecord(const string& studentName, double amountPaid) {
        paymentRecords.push_back(PaymentRecord(studentName, amountPaid));
        cout << "Payment record added successfully." << endl;
    }

    void deletePaymentRecord(int index) {
        if (index >= 0 && index < (int)paymentRecords.size()) {
            paymentRecords.erase(paymentRecords.begin() + index);
            cout << "Payment record deleted successfully." << endl;
        } else {
            cout << "Invalid index. No payment record deleted." << endl;
        }
    }

    void displayPaymentRecords() const {
        if (paymentRecords.empty()) {
            cout << "No payment records available." << endl;
        } else {
            cout << "Payment Records:" << endl;
            for (size_t i = 0; i < paymentRecords.size(); ++i) {
                cout << "Index: " << i << ", Student Name: " << paymentRecords[i].getStudentName()
                     << ", Amount Paid: Rs." << paymentRecords[i].getAmountPaid() << endl;
            }
        }
    }
};

/* ======================================================================
   Room - converted from struct to class (encapsulation)
   (the old duplicate "Room1" struct has been removed)
   ====================================================================== */
class Room {
private:
    int roomNumber;
    string roomType;
    bool occupied;
    float price;

public:
    Room(int num, string type, bool occ, float p)
        : roomNumber(num), roomType(type), occupied(occ), price(p) {}

    int getRoomNumber() const { return roomNumber; }
    string getRoomType() const { return roomType; }
    bool isOccupied() const { return occupied; }
    float getPrice() const { return price; }

    void displayInfo() const {
        cout << "Room Number: " << roomNumber << endl;
        cout << "Room Type: " << roomType << endl;
        cout << "Occupied: " << (occupied ? "Yes" : "No") << endl;
        cout << "Room Rent per person: Rs." << price << "/-" << endl;
    }
};

/* ======================================================================
   Mess - converted from struct to class (encapsulation)
   ====================================================================== */
class Mess {
private:
    string name;
    float costPerMeal;
    int capacity;
    int mealsServed;

public:
    Mess(string n, float cost, int cap, int served)
        : name(n), costPerMeal(cost), capacity(cap), mealsServed(served) {}

    void displayInfo() const {
        cout << "Mess Name: " << name << endl;
        cout << "Cost per Meal: Rs." << costPerMeal << endl;
        cout << "Capacity: " << capacity << " students" << endl;
        cout << "Meals Served: " << mealsServed << endl;
    }
};

class HostellerFee {
private:
    int messBill = 500;
    int electricityBill = 500;
    int laundryBill = 200;
    int hostelRent = 1500;

public:
    void showInfo() const {
        cout << "\n\n\t\t\t ***** FEE DETAILS *****\n\n\n";
        cout << "MESS BILL\tELEC. BILL\tLAUNDRY BILL\tHOSTEL RENT\tTOTAL BILL\n";
        cout << messBill << "\t\t" << electricityBill << "\t\t" << laundryBill << "\t\t"
             << hostelRent << "\t\t" << (messBill + electricityBill + laundryBill + hostelRent);
    }
};

int main() {
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
                        case 3:
                            displayStudents(students);
                            break;
                        case 4: {
                            int rollNumber;
                            cout << "Enter roll number of the student to search: ";
                            cin >> rollNumber;
                            searchStudent(students, rollNumber);
                            break;
                        }
                        case 5:
                            manager.displayApplications();
                            break;
                        case 6: {
                            HostelPaymentManager paymentManager;
                            int pchoice;
                            do {
                                cout << "\nHostel Payment Management System" << endl;
                                cout << "1. Add Payment Record" << endl;
                                cout << "2. Delete Payment Record" << endl;
                                cout << "3. Display Payment Records" << endl;
                                cout << "4. Exit" << endl;
                                cout << "Enter your choice: ";
                                cin >> pchoice;

                                switch (pchoice) {
                                    case 1: {
                                        string name;
                                        double amount;
                                        cout << "Enter student name: ";
                                        cin >> name;
                                        cout << "Enter amount paid: ";
                                        cin >> amount;
                                        paymentManager.addPaymentRecord(name, amount);
                                        break;
                                    }
                                    case 2: {
                                        int index;
                                        cout << "Enter index of payment record to delete: ";
                                        cin >> index;
                                        paymentManager.deletePaymentRecord(index);
                                        break;
                                    }
                                    case 3:
                                        paymentManager.displayPaymentRecords();
                                        break;
                                    case 4:
                                        cout << "Exiting.." << endl;
                                        break;
                                    default:
                                        cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
                                }
                            } while (pchoice != 4);
                            break;
                        }
                        case 7:
                            cout << "Returned to main menu..." << endl;
                            break;
                        default:
                            cout << "Invalid choice! Please try again." << endl;
                    }
                } while (choice != 7);
                break;
            }
            case 2: {
                Applicant newApplication = hosteler.applyOnline();
                manager.addApplication(newApplication);
                break;
            }
            case 3: {
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
                            cout << "\n\nSTANDING RULES REGARDING WIFI LOGIN:\n\n";
                            cout << "1. Wifi services are available for 24 hours." << endl;
                            cout << "2. Please do not pay for any wifi bill on any payment link." << endl;
                            cout << "3. For the sake of privacy, different wifi passwords have been issued to the students." << endl;
                            cout << "4. Please DO NOT share your password with anybody else." << endl;
                            cout << "\n\nCONNECTION NAME: H8_5G \nPlease enter your 6-digit password\nPASSWORD:";
                            string pass;
                            cin >> pass;
                            string password1 = "CHD@h8";
                            string password2 = "ASR@h8";
                            string password3 = "PTL@h8";
                            if (pass == password1 || pass == password2 || pass == password3) {
                                cout << "WiFi password accepted!!" << endl;
                            } else {
                                cout << "Incorrect password!!" << endl;
                            }

                            if (pass.length() != 6) {
                                cout << "Please enter exactly 6 digits." << endl;
                                return 1;
                            }
                            break;
                        }
                        case 2: {
                            cout << "\n\nWATER MANAGEMENT PAGE" << endl;
                            cout << endl;
                            cout << "KINDLY NOTE:-  WATER SERVICE CHARGES ARE INCLUDED IN THE HOSTEL FEE.";
                            cout << endl << endl;
                            cout << "STANDING RULES REGARDING WATER AMENITIES:\n\n";
                            cout << "1. Please do not pay for any water bill on any payment link." << endl;
                            cout << "2. Fresh water is available in the mornings from 6AM to 9AM and from 6PM to 9PM in the evenings.\n";
                            cout << "3. Tank water is available 24/7. ";
                            cout << "4. Make sure to keep a check on any leakage from pipes or taps." << endl;
                            cout << "5. In case of any leakage, inform the authorities immediately or call on 1800652349." << endl;
                            cout << "6. Please be responsible and DO NOT waste water.\n ";
                            break;
                        }
                        case 3: {
                            HostellerFee fee;
                            fee.showInfo();
                            break;
                        }
                        case 4: {
                            vector<Room> hostelRooms = {
                                Room(101, "Single", true, 2500),
                                Room(102, "Double", false, 2000),
                                Room(103, "Single", true, 2500),
                                Room(104, "Double", false, 2000),
                                Room(105, "Single", false, 2500),
                                Room(106, "Double", true, 2000)
                            };

                            cout << "Hostel Room Information:" << endl;
                            for (const auto& room : hostelRooms) {
                                room.displayInfo();
                                cout << endl;
                            }
                            break;
                        }
                        case 5: {
                            vector<Mess> messList = {
                                Mess("Mess A", 40, 100, 0),
                                Mess("Mess B", 45, 80, 0)
                            };

                            cout << "Mess Information:" << endl;
                            for (const auto& mess : messList) {
                                mess.displayInfo();
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
                break;
            }
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (integer != 4);
    return 0;
}
