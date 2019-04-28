#ifndef AGENDA_HPP
#define AGENDA_HPP

#include <iostream>
#include "day.hpp"
#include "month.hpp"

// Some macros to make verifications easier
#define isMonthValid(month, sz)  (month > 0 && month <= size)
#define isDayValid(day, numDays) (day > 0   && day <= numDays)
#define isDateValid(hour, min)   (hour >= 0 && hour < 24 && min >= 0 && min < 60)

typedef struct NodeAgenda { // Structure defining a node to the agenda (month)
    Month month;
    struct NodeAgenda *next;
} NodeAgenda;

typedef struct Agenda { // Structure defining the agenda itself
    NodeAgenda *start;
    NodeAgenda *end;
    int size;
    bool isOpen;

    // Functions provided for an Agenda
    void buildAgenda();
    void insertAgenda(Month&);
    void showAgenda();
    void loadAgenda();
    void saveAgenda();
    void destroyAgenda();
    int showMenu();
    NodeAgenda* seekAgenda(int);

    Agenda() {}

} Agenda;

#endif