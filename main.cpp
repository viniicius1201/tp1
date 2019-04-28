#include <iostream>
#include <cstring>
#include "agenda.hpp"
#include "day.hpp"
using namespace std;

// Main user-accessible function to open the agenda
void actionOpenAgenda(Agenda &agenda) {
    if (!agenda.isOpen) { // Check whether the agenda has already been opened before
        agenda.loadAgenda();
        cout << endl << "The agenda has just been opened." << endl << endl;
        agenda.isOpen = true;
    } else
        cout << "You cannot open the agenda twice." << endl << endl;
}

// Main user-accessible function to add a commitment
void actionAddCommitment(Agenda &agenda) {
    if (!agenda.isOpen) { // Check whether the agenda is open
        cout << "You must open the agenda before changing it." << endl;
        return;
    }
    int month, day;
    cout << "Month: ";
    cin >> month;
    cout << "Day: ";
    cin >> day;
    NodeAgenda *ptrMonth = agenda.seekAgenda(month);
    if (ptrMonth == nullptr) {
        cout << "The month is not valid." << endl;
        return;
    }
    if (!isDayValid(day, ptrMonth->month.numDays)) {
        cout << "The day is not valid." << endl;
        return;
    } 
    Commitment commitment;
    cout << "Hour: ";
    cin >> commitment.hour;
    cout << "Minute: ";
    cin >> commitment.minute;
    cout << "Commitment Description: ";
    cin.ignore(2, '\n');
    getline(cin, commitment.description);
    if (!isDateValid(commitment.hour, commitment.minute)) {
        cout << "Either hour or minute is not valid." << endl;
        return;
    }
    ptrMonth->month.commitments[day].insertCommitment(commitment);
}

// Main user-accessible function to remove a commitment
void actionRemoveCommitment(Agenda &agenda) {
    if (!agenda.isOpen) {
        cout << "You must open the agenda before changing it." << endl;
        return;
    }
    int month, day, hour, min;
    cout << "Month: ";
    cin >> month;
    cout << "Day: ";
    cin >> day;
    NodeAgenda *ptrMonth = agenda.seekAgenda(month);
    if (ptrMonth == nullptr) {
        cout << "The month is not valid." << endl;
        return;
    }
    if (!isDayValid(day, ptrMonth->month.numDays)) {
        cout << "The day is not valid." << endl;
        return;
    }
    cout << "Hour: ";
    cin >> hour;
    cout << "Minute: ";
    cin >> min;
    if (!isDateValid(hour, min)) {
        cout << "Either hour or minute is not valid." << endl;
        return;
    }
    if (ptrMonth->month.commitments[day].removeCommitment(hour, min))
        cout << "The commitment has been deleted" << endl;
    else
        cout << "The commitment could not be deleted." << endl;
}

// Main user-accessible function to list commitments
void actionListCommitments(Agenda &agenda) {
    if (!agenda.isOpen) {
        cout << "You must open the agenda before changing it." << endl;
        return;
    }
    int month, day;
    cout << "Month: ";
    cin >> month;
    cout << "Day: ";
    cin >> day;
    NodeAgenda *ptrMonth = agenda.seekAgenda(month);
    if (ptrMonth == nullptr) {
        cout << "The month is not valid." << endl;
        return;
    }
    if (!isDayValid(day, ptrMonth->month.numDays)) {
        cout << "The day is invalid." << endl;
        return;
    }
    cout << endl;
    ptrMonth->month.commitments[day].showDay();
    cout << endl;
}

// Main user-accessible function to filter commitments by date
void actionCheckCommitmentByDate(Agenda &agenda) {
    if (!agenda.isOpen) {
        cout << "You must open the agenda before changing it." << endl;
        return;
    }
    int month, day, hour, min;
    cout << "Month: ";
    cin >> month;
    cout << "Day: ";
    cin >> day;
    NodeAgenda *ptrMonth = agenda.seekAgenda(month);
    if (ptrMonth == nullptr) {
        cout << "The month is not valid." << endl;
        return;
    }
    if (!isDayValid(day, ptrMonth->month.numDays)) {
        cout << "The day is not valid." << endl;
        return;
    } 
    cout << "Hour: ";
    cin >> hour;
    cout << "Minute: ";
    cin >> min;
    if (!isDateValid(hour, min)) {
        cout << "Either hour or minute is not valid." << endl;
        return;
    }
    cout << endl;
    ptrMonth->month.commitments[day].showDayFilteredByDate(hour, min);
}

// Main user-accessible function to save and exit the program
void actionSaveAndExit(Agenda &agenda) {
    if (!agenda.isOpen) {
        cout << "The agenda has not been changed. Exitting program." << endl;
        return;
    }
    cout << "All changes have been saved. Exitting program." << endl;
    agenda.saveAgenda();
}

// This function simply prints an exitting message
void actionExit() {
    cout << "Saindo do programa. Todas as alteracoes serao descartadas." << endl;
}

int main() {
    Agenda agenda;
    agenda.buildAgenda();
    int opcao = 0;
    while (opcao != 7 && opcao != 6) {
        opcao = agenda.showMenu();
        switch (opcao) {
            case 1:
                actionOpenAgenda(agenda);
                break;
            case 2:
                actionAddCommitment(agenda);
                break;
            case 3:
                actionRemoveCommitment(agenda);
                break;
            case 4:
                actionListCommitments(agenda);
                break;
            case 5:
                actionCheckCommitmentByDate(agenda);
                break;
            case 6: {
                actionSaveAndExit(agenda);
                break;
            }
            case 7: {
                actionExit();
                break;
            }
            default: {
                cout << "Invalid option." << endl << endl;
            }
        }
    }
    agenda.destroyAgenda(); // Free the memory used
    return 0;
}
