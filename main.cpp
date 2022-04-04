#include <iostream>
#include <vector>
#include <math.h>
#include <time.h>

using namespace std;

vector<double> input_numbers(size_t count){
    vector<double> result(count);
    for (size_t i = 0; i < count; i++){
        cin >> result[i];
    }
    return result;
}


int main()
{
    // ���� ������
    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;                                             // ���������� ����� � �������

    vector<double> numbers(number_count);                            // �������� ������
    numbers = input_numbers(number_count);

    size_t bin_count;                                               // ���������� "������"
    cerr << "Enter bin count: ";
    cin >>  bin_count;


    // ������ �����������
    vector<size_t> bins(bin_count, 0);                              // � ������ ������ �� ������� ������ �������� �������� 0

    double min = numbers[0];
    double max = numbers[0];
// ��������� �������� ��� ��������� � ��������

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

    double bin_size = (max - min) / bin_count;
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

    // ����� ������

    const size_t SCREEN_WIDTH = 80;                                  // ������������ ���������� ��������.
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;                // ������� "�������" ��� �����, ����� ��������.( 1-3 ������� � | )

    size_t max_bins;
    max_bins = bins[0];                                              // ������ ������������ �������

    for (size_t bin : bins)                                          // ��� ������� �������� �� bins ������� �������� � bin. �������������� ������ for.
    {
        if (bin > max_bins)
        {
            max_bins = bin;
        }
    }

    for (size_t bin : bins)
    {

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
    return 0;
}
