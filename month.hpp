#include "day.hpp"

// A structure to describe a month
typedef struct Month {
    int month;
    int numDays;
    Day *commitments;
} Month;
