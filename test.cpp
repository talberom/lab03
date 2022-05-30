#include "test.h"
#include "histogram.h"


void test_positive(){
    double min = 0;
    double max = 0;
    find_minmax({1, 2, 3}, min, max);
    assert(min == 0);
    assert(max == 3);
    // assert(max == 4);
}

void test_negative(){
    double min = 0;
    double max = 0;
    find_minmax({-1, -2, -3}, min, max);
    assert(min == -3);
    assert(max == 0);
}

void test_same(){
    double min = 0;
    double max = 0;
    find_minmax({1, 1, 1}, min, max);
    assert(min == 0);
    assert(max == 1);
}

void test_one_num(){
    double min = 0;
    double max = 0;
    find_minmax({-5}, min, max);
    assert(min == -5);
    assert(max == 0);
}

void test_glass_array(){
    double min = 0;
    double max = 0;
    find_minmax({}, min, max);
    assert(min == 0);
    assert(max == 0);
}
