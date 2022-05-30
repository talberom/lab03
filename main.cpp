#include <iostream>
#include <vector>
#include <math.h>
#include <windows.h>
#include <tchar.h>
#define vWIN_BUFFER 32767

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
    DWORD vWIN = GetVersion();

    printf("Windows version: %u\n", vWIN);
    printf("Windows version: %08x\n", vWIN);

    DWORD mask = 0b00000000'00000000'11111111'11111111;
    DWORD version = vWIN & mask;
    printf("Version: %08x\n", version);

    DWORD platform = vWIN >> 16;
    DWORD version_mask = 0b00000000'11111111;
    DWORD version_major = version & version_mask;
    DWORD version_minor = version >> 8;

    DWORD build;
    if ((vWIN & 0x80000000) == 0) {
        build = platform;
    }

    printf("Windows v%u.%u (build %u)\n", version_major, version_minor, build);

    TCHAR infoBuf[vWIN_BUFFER];
    DWORD bufCharCount = vWIN_BUFFER;

    if (!GetComputerName(infoBuf, &bufCharCount)){
        printf("GetComputername");
    }
    printf("\nComputer name: %s\n", infoBuf);

    return 0;
    size_t number_count;
    cerr << "enter number count: ";
    cin >> number_count;
    const auto numbers = input_numbers(number_count);
    size_t bin_count;
    cerr << "enter bin count: ";
    cin >> bin_count;
    const auto bins = make_histogram(numbers, bin_count);
    show_histogram_svg(bins, bin_count);
}
