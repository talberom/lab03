#include <vector>
#include <iostream>
#include "histogram.h"
#include "svg.h"

void svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void svg_end() {
    cout << "</svg>\n";
}

void svg_text_hw(double left, double baseline, string text, ostream &stream, string decorate = "none"){
    stream << "<text x='" << left << "' y='" << baseline << "' text-decoration='" << decorate << "'>" << text << "</text>";
}

void svg_text(double left, double baseline, string text){
    cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>";
}

void svg_rect(double x, double y, double width, double height, string stroke = "black", string color = "black"){
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width <<"' height='" << height << "' stroke= '" << stroke << "' fill='" << color << "' />";
}

void show_histogram_svg(const vector <size_t> &bins, size_t bin_count){
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;

    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;
    string decorate;
    cout << "Input style of text: "; cin >> decorate;
    bool flag = true;
    double bin_width;

    for (size_t bin : bins) {
        double maxb = -1;

        for (size_t bin : bins) {

        if (bin > maxb){
            maxb = bin;
            }
        }

        if (maxb > IMAGE_WIDTH / BIN_HEIGHT){
            flag = false;
        }


        if (flag) {
            bin_width = BLOCK_WIDTH * bin;
        }
        else {
            bin_width = BLOCK_WIDTH  * bin / (maxb / BLOCK_WIDTH);
        }

        svg_text_hw(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin), cout, decorate); // svg_text_hw - ???????? decorate - ????????? ????????
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, "black", "mediumturquoise");
        top += BIN_HEIGHT;
    }
    svg_end();
}
