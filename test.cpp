#include "histogram.h"

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

int main() {
    test_positive();
    return 0;
}
