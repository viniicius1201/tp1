#include "commitment.hpp"
#include "day.hpp"

// Build a day instance
void Day::buildDay() {
    start = end = nullptr;
    size = 0;
}

// Destroy a day instance by deallocating all the used resources
void Day::destroyDay() {
    NodeDay *curr = start;
    while (curr != nullptr) {
        NodeDay *aux = curr;
        curr = curr->next;
        delete aux;
    }
}

// Add a commitment to the list
void Day::insertCommitment(Commitment &commitment) {
    NodeDay *newDay = new NodeDay;
    newDay->next = nullptr;
    newDay->commitment = commitment;
    size++;
    if (start == nullptr) { // First element to be added
        start = end = newDay;
    } else {
        end->next = newDay;
        end = newDay;
    }
}

// Delete a node from the list
bool Day::removeCommitment(int hour, int min) {
    NodeDay *curr = start;
    NodeDay *prev = start;
    bool deleted = false;
    while (curr != nullptr && deleted == false) { // Percorre a lista enquanto não encontrar o nó
        if (curr->commitment.hour == hour && curr->commitment.minute == min) {
            if (curr == start) start = curr->next;
            else prev->next = curr->next;
            size--;
            delete curr;
            deleted = true;
        }
        else {
            prev = curr; curr = curr->next;
        }
    }
    // Return true if the deletion was successful and false otherwise
    return deleted;
}

// Print all commitments of a day in the standard output
void Day::showDay() {
    NodeDay *curr = start;
    // Iterate over the linked list and print each node
    while (curr != nullptr) {
        cout << curr->commitment.hour << "h" << curr->commitment.minute << "min - ";
        cout << curr->commitment.description << endl;
        curr = curr->next;
    }
}

// Print commitments filtered by a date, i.e hour and minute
void Day::showDayFilteredByDate(int hour, int min) {
    NodeDay *curr = start;
    int count = 0;
    while (curr != nullptr) { // Percorre toda a lista
        if (curr->commitment.minute == min && curr->commitment.hour == hour) {
            cout << curr->commitment.hour << "h" << curr->commitment.minute << "min - ";
            cout << curr->commitment.description << endl;
            count++;
        }
        curr = curr->next;
    }
    if (count == 0) cout << "There is no commitment for this date." << endl;
}
