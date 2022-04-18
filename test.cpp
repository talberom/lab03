#include "histogram.h"
#include "svg.h"

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

void test_1(const vector <size_t> &bins, size_t bin_count){
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

    for (size_t bin : bins) {
        double bin_width;

        if (bin > IMAGE_WIDTH){
            flag = false;
        }

        if (flag) {
            bin_width = BLOCK_WIDTH * bin;
        }
        else {
            bin_width = bin;
        }

        svg_text_hw(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin), decorate); // svg_text_hw - добавить decorate - последний аргумент
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, "black", "mediumturquoise");
        top += BIN_HEIGHT;
    }
    svg_end();
}

void test_2(const vector <size_t> &bins, size_t bin_count){
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;

    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;

    bool flag = true;

    for (size_t bin : bins) {
        double bin_width;

        if (bin > IMAGE_WIDTH){
            flag = false;
        }

        if (flag) {
            bin_width = BLOCK_WIDTH * bin;
        }
        else {
            bin_width = bin;
        }

        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin)); // svg_text_hw - добавить decorate - последний аргумент
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, "black", "mediumturquoise");
        top += BIN_HEIGHT;
    }
    svg_end();
}

int main() {
    test_positive();
    test_negative();
    test_same();
    test_one_num();
    test_glass_array();
    /*
    size_t bin_count;
    cerr << "Enter bin count: ";
    cin >>  bin_count;
    vector<size_t> bins(bin_count, 0);
    test_1(bins, bin_count);
    test_2(bins, bin_count);
    */
    return 0;
}
