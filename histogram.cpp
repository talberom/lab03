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


// vector<size_t> make_histogram(const vector<double>& numbers, size_t bin_count){

vector<size_t> make_histogram(Input input)
{
    double min, max;
    find_minmax(input.numbers, min, max);
    double bin_size = (max - min) / input.bin_count;
    vector<size_t> bins(input.bin_count, 0);
    for (size_t i = 0; i < input.numbers.size(); i++)
    {
        bool flag = false;
        for (size_t j = 0; j < input.bin_count - 1 && !flag; j++)
        {
            auto lo = min + j * bin_size;
            auto hi = min + (j + 1) * bin_size;

            if (lo <= input.numbers[i] && input.numbers[i] < hi)
            {
                bins[j]++;
                flag = true;
            }
        }
        if (flag)
        {
            ;
        }
        else{
            bins[input.bin_count - 1]++;
        }
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
