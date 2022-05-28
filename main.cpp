#include <iostream>
#include <vector>
#include <math.h>
#include "histogram.h"
#include "svg.h"
#include "test.h"

using namespace std;

vector<double> input_numbers(istream& in, size_t count){
    vector<double> result(count);
    for (size_t i = 0; i < count; i++){
        in >> result[i];
    }
    return result;
}

int main()
{
    // ���� ������
    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;
                                                // ���������� ����� � �������
    const vector<double> numbers = input_numbers(cin, number_count);

    size_t bin_count;                                               // ���������� "������"
    cerr << "Enter bin count: ";
    cin >>  bin_count;


    // ������ �����������
    vector<size_t> bins(bin_count, 0);
                                  // � ������ ������ �� ������� ������ �������� �������� 0
    double min = numbers[0];
    double max = numbers[0];

    double bin_size = make_histogram(numbers, bin_count);

// ������ ����� �������
    for (size_t i = 0; i < number_count; i++)
    {
        bool founded = false;                                       // ���������� ��� ������� ������ (number == max)
        for (size_t j = 0; j < (bin_count - 1) && !founded; j++)
        {
            auto lo = min + bin_size * j;                           // ������ �����
            auto hi = min + bin_size * (j + 1);                     // ������� �����

            if ((lo <= numbers[i]) && (numbers[i] < hi))            // ���� ����� ����� ����� ������ � ������� ������� ( � ���������� ������� )
            {
                bins[j]++;                                          // �� �������� ��� � ��� �������
                founded = true;
            }
        }
        if (!founded)                                               // ������ ������ ��� number == max
        {
            bins[bin_count - 1]++;
        }
    }
    show_histogram_svg(bins, bin_count);

    test_positive();
    test_negative();
    test_same();
    test_one_num();
    test_glass_array();

    return 0;
}
