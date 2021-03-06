#ifndef SVG_H_INCLUDED
#define SVG_H_INCLUDED

#include <vector>
#include <iostream>

void svg_begin(double width, double height);
void svg_text(double left, double baseline, string text);
void svg_text_hw(double left, double baseline, string text, ostream &stream, string decorate);
void svg_rect(double x, double y, double width, double height, string stroke, string color);
void svg_end();
void show_histogram_svg(const vector <size_t> &bins, size_t bin_count);

#endif // SVG_H_INCLUDED
