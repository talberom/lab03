#ifndef HISTOGRAM_H_INCLUDED
#define HISTOGRAM_H_INCLUDED

#include <vector>

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

#endif // HISTOGRAM_H_INCLUDED
