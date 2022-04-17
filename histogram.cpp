#include <vector>
#include "histogram.h"

using namespace std;

void find_minmax(const vector<double> &numbers, double &min, double &max){
    for (double number : numbers)                                   // дл€ каждого элемента из numbers запишем значение в number
    {
        if (min > number)                                           // ¬ычисление минимума из массива
        {
            min = number;
        }
        if (max < number)                                           // ¬ычисление максимума из массива
        {
            max = number;
        }
    }
}

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

void svg_text(double left, double baseline, string text, string decorate = "none"){
    cout << "<text x='" << left << "' y='" << baseline << "' text-decoration='" << decorate << "'>" << text << "</text>";
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
    for (size_t bin : bins) {
        double bin_width;
        if (bin <= IMAGE_WIDTH) {
            bin_width = BLOCK_WIDTH * bin;
        }
        else {
            bin_width = bin;
        }
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin), decorate);
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, "black", "mediumturquoise");
        top += BIN_HEIGHT;
    }
    svg_end();
}

