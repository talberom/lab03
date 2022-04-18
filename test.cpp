#include "histogram.h"
#include "svg.h"
#include <iostream>
#include <sstream>
#include <cassert>

using namespace std;

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

void test_hw1(){
    stringstream stroka1; string stroka2;
    svg_text_hw(50, 100, to_string(5), stroka1, "none");
    getline(stroka1, stroka2);
    assert(stroka2 == "<text x='50' y='100' text-decoration='none'>5</text>");
}

void test_hw2(){
    stringstream stroka1; string stroka2;
    svg_text_hw(50, 100, to_string(7), stroka1, "underline");
    getline(stroka1, stroka2);
    assert(stroka2 == "<text x='50' y='100' text-decoration='underline'>7</text>");
}


int main() {
    test_positive();
    test_negative();
    test_same();
    test_one_num();
    test_glass_array();
    test_hw1();
    test_hw2();
    return 0;
}

