#ifndef HISTOGRAM_H_INCLUDED
#define HISTOGRAM_H_INCLUDED

#include <vector>
#include <iostream>

using namespace std;

struct Input{
    vector<double> numbers;
    size_t bin_count;
    size_t number_count;
};

void find_minmax(const vector<double> &numbers, double &min, double &max);
vector<size_t> make_histogram(Input input);
void show_histogram_text(const vector<size_t>& bins);
#endif // HISTOGRAM_H_INCLUDED
