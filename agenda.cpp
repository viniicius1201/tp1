#include "agenda.hpp"
#include "day.hpp"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;

// Show an interative menu so the user can choose an option
int Agenda::showMenu() {
    int choice;
    cout << "#####################################################" << endl;
    cout << "## 1) Open agenda                                  ##" << endl;
    cout << "## 2) Add commitment                               ##" << endl;
    cout << "## 3) Remove commitment                            ##" << endl;
    cout << "## 4) List all commitments of a day                ##" << endl;
    cout << "## 5) Check commitment by date                     ##" << endl;
    cout << "## 6) Save agenda and exit                         ##" << endl;
    cout << "## 7) Exit without saving current status           ##" << endl;
    cout << "#####################################################" << endl;
    cout << "Choose your action: ";
    cin >> choice;
    return choice;
}

// Build the agenda based on the number of days for each month
void Agenda::buildAgenda() {
    start = end = nullptr; size = 0;
    isOpen = false;
    int daysHash[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int i = 1;
    while (i <= 12) {
        Month month {.month=i, .numDays=daysHash[i - 1]};
        month.commitments = new Day[month.numDays + 1];
        int j = 0; i++;
        for (; j <= month.numDays; j++) {
            month.commitments[j].buildDay();
        }
        insertAgenda(month);
    }
}

// Free the memory used to store the agenda
void Agenda::destroyAgenda() {
    NodeAgenda *curr = start;
    while (curr != nullptr) {
        NodeAgenda *aux = curr;
        for (int i = 0; i <= aux->month.numDays; i++) {
            aux->month.commitments[i].destroyDay();
        }
        curr = curr->next;
        delete [] aux->month.commitments; delete aux;
    }
}

// Add a month to the agenda
void Agenda::insertAgenda(Month &month) {
    NodeAgenda *novoNodo = new NodeAgenda;
    novoNodo->month = month; novoNodo->next = nullptr;
    size++;
    if (start == nullptr) start = end = novoNodo;
    else end->next = novoNodo; end = novoNodo;
}

// Seek a month in the linked list
NodeAgenda* Agenda::seekAgenda(int month) {
    if (!isMonthValid(month, size)) return nullptr;
    NodeAgenda *ptr = start;
    for (; ptr != nullptr && ptr->month.month != month; ptr = ptr->next); 
    return ptr;
}

// Restore the agenda by loading the data file
void Agenda::loadAgenda() {
    ifstream fp("agenda_file.txt"); // Open the file for reading
    if (!fp) {
        cout << "Error. Could not open the file." << endl;
        exit(1);
    }
    // If nothing went wrong, we read the file and store each commitment
    string row = "";
    while (getline(fp, row)) {
        istringstream splitter(row);
        string value, descr;
        int indx = 1, month = 0, day = 0, hr = 0, min = 0;
        // Breaking the line into fields for filling up the commitment
        while (getline(splitter, value, '#')) {
            if (indx == 1)      istringstream(value) >> month;
            else if (indx == 2) istringstream(value) >> day;
            else if (indx == 3) istringstream(value) >> hr;
            else if (indx == 4) istringstream(value) >> min;
            else descr = value;
            indx++;
        }
        // Add the commitment to the agenda
        Commitment commitment;
        commitment.hour = hr;
        commitment.minute = min;
        commitment.description = descr;
        NodeAgenda *ptrMonth = seekAgenda(month);
        ptrMonth->month.commitments[day].insertCommitment(commitment);
    }
    fp.close();
}

// Save current status to a file
void Agenda::saveAgenda() {
    ofstream fp("agenda_file.txt"); // Open the file for writing
    if (!fp) {
        cout << "Error. Could not open the file." << endl;
        exit(1);
    }
    // If nothing went wrong, we write all the appointments back to the file
    NodeAgenda *ptrMonth = start;
    while (ptrMonth != nullptr) { // Look into every month
        Month month = ptrMonth->month;
        int days = month.numDays, i = 1;
        for (; i <= days; i++) { // Look into all days
            Day day = month.commitments[i];
            NodeDay *ptrDay = day.start;
            while (ptrDay != nullptr) { // Look into every commitment in a list
                fp << month.month << "#" << i << "#" << ptrDay->commitment.hour << "#"
                        << ptrDay->commitment.minute << "#" << ptrDay->commitment.description << endl;
                ptrDay = ptrDay->next;
            }
        }
        ptrMonth = ptrMonth->next;
    }
    fp.close();
}
