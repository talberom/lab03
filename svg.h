#ifndef SVG_H_INCLUDED
#define SVG_H_INCLUDED

#include <vector>
#include <iostream>
#include "histogram.h"
#include <windows.h>
#include <tchar.h>

using namespace std;

struct Input {
    vector<double> numbers;
    size_t bin_count;
    size_t number_count;
    string decoration;
};

void svg_begin(double width, double height);
void svg_end();

void svg_text(double left, double baseline, string text, string decorate);
void svg_rect(double x, double y, double width, double height, string stroke, string color);

void show_histogram_svg(const vector <size_t> &bins, Input input);
void get_version_info(DWORD &version_major, DWORD &version_minor, DWORD &build);


#endif // SVG_H_INCLUDED
