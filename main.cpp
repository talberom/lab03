#include <iostream>
#include <vector>
#include <math.h>
#include "histogram.h"
#include "svg.h"
#include "test.h"

using namespace std;

struct Input{
    vector<double> numbers;
    size_t bin_count;
    size_t number_count;
};


vector<double> input_numbers(istream& in, size_t count){
    vector<double> result(count);
    for (size_t i = 0; i < count; i++){
        in >> result[i];
    }
    return result;
}

Input read_input(istream& in){

    Input data;

    cerr << "Enter number count: ";
    size_t number_count;
    in >> number_count;
    cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);
    cerr << "Enter bin count: ";
    size_t bin_count;
    in >> data.bin_count;

    return data;
}

int main()
{
    Input data = read_input(cin);

    const auto bins = make_histogram(data.numbers, data.bin_count);

    show_histogram_svg(bins);

    return 0;
}
