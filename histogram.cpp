#include "histogram.h"

void find_minmax(const vector<double>& numbers, double& min, double& max) {
    if (numbers.size() == 0) {
        return;
    }
    min = numbers[0];
    max = numbers[0];
    for (double number : numbers) {
        if (number < min) {
            min = number;
        }
        if (number > max) {
            max = number;
        }
    }
    return;
}
