#ifndef DAY_HPP
#define DAY_HPP

#include <iostream>
#include <cstring>
#include "commitment.hpp"

// Define an appointment node in a linked list
typedef struct NodeDay {
    Commitment commitment;
    struct NodeDay *next;
} NodeDay;

// Define a linked list for appointments
typedef struct {
    NodeDay *start;
    NodeDay *end;
    int size;

    // Functions provided for an appointment list
    void buildDay();
    void destroyDay();
    void insertCommitment(Commitment&);
    bool removeCommitment(int, int);
    void showDay();
    void showDayFilteredByDate(int, int);

} Day;

#endif
