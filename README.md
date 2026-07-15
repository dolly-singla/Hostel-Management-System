# Hostel Management System (C++ OOP)

A console-based **Hostel Management System** developed in **C++** using **Object-Oriented Programming (OOP)** concepts. The project simulates hostel administration by allowing hostel managers to manage students, process hostel applications, maintain payment records, and provide hostel-related information such as rooms, mess, Wi-Fi, and fee details.

---

## 📌 Features

### 👨‍💼 Manager Module
- Add new students
- Remove existing students
- Search student by roll number
- Display all registered students
- View hostel applications
- Manage hostel payment records
  - Add payment record
  - Delete payment record
  - Display payment records

### 📝 Hostel Registration
- Students can apply for hostel accommodation online.
- Stores applicant information in a file.

### 🏠 Hosteller Module
- Wi-Fi service information
- Water management guidelines
- Hostel fee structure
- Room information
- Mess information

---

## 🛠️ Technologies Used

- **Language:** C++
- **Programming Paradigm:** Object-Oriented Programming (OOP)
- **Data Structures:** Vector (STL)
- **File Handling:** Text Files
- **Compiler:** GCC / MinGW / CodeBlocks / Visual Studio

---

## 📂 Project Structure

```
HostelManagementSystem/
│
├── HMS.cpp
├── students.txt
├── applications.txt
└── README.md
```

---

## 💾 File Storage

The project uses text files for persistent storage.

### students.txt
Stores registered hostel students.

Format:

```
RollNumber,Name,Address,Age
```

Example

```
101,John Doe,Delhi,20
102,Rahul Sharma,Chandigarh,21
```

### applications.txt

Stores hostel applications.

Format

```
Name,FatherName,Department,Nationality,Address,Email,RollNo,AdmissionNo,MeritNo,PhoneNumber
```

---

## 📚 OOP Concepts Implemented

### Encapsulation
- Private data members with public getter and setter methods.
- Classes such as:
  - Student
  - Applicant
  - PaymentRecord
  - Room
  - Mess

### Inheritance
- `HostelMember` is an abstract base class.
- `Student` and `Applicant` inherit from `HostelMember`.
- `HostelManager` inherits from `Hosteler`.

### Polymorphism
- Pure virtual function:

```cpp
virtual void displayInfo() const = 0;
```

- Overridden by:
  - Student
  - Applicant

### Abstraction
- `HostelMember` serves as an abstract class to represent common properties of hostel members.

---

## 📖 Modules

### Student Management
- Add Student
- Remove Student
- Search Student
- Display Students

### Hostel Application Management
- Submit Application
- View Applications

### Payment Management
- Add Payment
- Delete Payment
- View Payments

### Hostel Information
- Fee Structure
- Room Details
- Mess Details
- Wi-Fi Information
- Water Management Guidelines

---

## 📸 Sample Menu

```
1. Manager
2. Register for Hostel
3. Hosteller
4. Exit
```

Manager Menu

```
1. Add Student
2. Remove Student
3. Display All Students
4. Search Student
5. Check Applications
6. Hostel Payment Record
7. Return
```

---

## 🎯 Learning Outcomes

This project demonstrates practical implementation of:

- Object-Oriented Programming
- File Handling
- STL Vector
- Class Design
- Inheritance
- Polymorphism
- Encapsulation
- Abstraction
- Console-based Application Development

---

## 🔮 Future Enhancements

- Login Authentication
- Admin Password Protection
- Database Integration (MySQL/MongoDB)
- GUI using Qt or C#
- Room Allocation System
- Complaint Management
- Attendance System
- Fee Payment Gateway
- Search using Multiple Filters
- Hostel Analytics Dashboard

---

## 👨‍💻 Author

**Dolly Singla**

B.E. Computer Science Engineering  
University Institute of Engineering & Technology (UIET)  
Panjab University, Chandigarh

---

## 📄 License

This project is developed for educational purposes to demonstrate Object-Oriented Programming concepts in C++.
