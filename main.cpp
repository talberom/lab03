#include <iostream>
#include <vector>
#include <math.h>
#include "histogram.h"
#include "svg.h"

using namespace std;

vector<double> input_numbers(size_t count){
    vector<double> result(count);
    for (size_t i = 0; i < count; i++){
        cin >> result[i];
    }
    return result;
}


vector<size_t> make_histogram(const vector<double>& numbers, size_t bin_count) {
    double min, max;
    find_minmax(numbers, min, max);
    vector<size_t> bins(bin_count);
    for (double number : numbers) {
        size_t bin = (size_t)((number - min) / (max - min) * bin_count);
        if (bin == bin_count) {
            bin--;
        }
        bins[bin]++;
    }
    return bins;
}

void show_histogram_text(const vector<size_t>& bins){

    const size_t SCREEN_WIDTH = 80;                                  // ������������ ���������� ��������.
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;                // ������� "�������" ��� �����, ����� ��������.( 1-3 ������� � | )

    size_t max_bins;
    max_bins = bins[0];

    for (size_t bin : bins){                                          // ��� ������� �������� �� bins ������� �������� � bin. �������������� ������ for.
        if (bin > max_bins)
        {
            max_bins = bin;
        }
    }

    for (size_t bin : bins) {
        double height = bin;
        if (max_bins > MAX_ASTERISK)                                       // ���� ������ ������� ������ �������� ����������� ���������� ������� ������� ( �� ������� )
        {                                                                  // �� ��������� ���������������
            height = MAX_ASTERISK * (static_cast<double>(bin) / max_bins); // ������������� ��������� bin ��� ������� ��� double.
        }

// 2 "if-a" - ��������� ��� ����������� ������
        if (bin < 100)
        {
            cout << " ";
        }
        if (bin < 10)
        {
            cout << " ";
        }
        cout << bin << "|";
        for (size_t zv = 0; zv < height; zv++)                        // ����� �������� � ������������ � ����������� �����
        {
            cout << "*";
        }
        cout << endl;
    }
}


int main()
{
    const char* name = "Vladimir";
    const char* surname = "Ilyich Lenin";
    int year = 1870;
    double balance = 343.773;
    printf("%s %s was born in %d.\nHe have %.2f $ on his card now.\n", name, surname, year, balance);
    //printf("%08x\n", 0x1234567);
    return 0;

    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;

    cerr << "Enter numbers: ";
    const auto numbers = input_numbers(number_count);

    size_t bin_count;
    cerr << "Enter column count: ";
    cin >> bin_count;

    int bin_height;
    cerr << "Enter column height: ";
    cin >> bin_height;

    const auto bins = make_histogram(numbers, bin_count);
    show_histogram_svg(bins, bin_height);

    return 0;
}
