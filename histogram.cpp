#include <vector>
#include "histogram.h"

using namespace std;

void find_minmax(const vector<double> &numbers, double &min, double &max){
    for (double number : numbers)                                   // ��� ������� �������� �� numbers ������� �������� � number
    {
        if (min > number)                                           // ���������� �������� �� �������
        {
            min = number;
        }
        if (max < number)                                           // ���������� ��������� �� �������
        {
            max = number;
        }
    }
}


double make_histogram(const vector<double> &numbers, size_t bin_count){
    double min; double max;
    if (numbers.size() > 0){
        min = numbers[0];
        max = numbers[0];
    }
    else{
        min = 0;
        max = 0;
    }
    find_minmax(numbers, min, max);
    double bin_size = (max - min) / bin_count;
    return bin_size;
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
