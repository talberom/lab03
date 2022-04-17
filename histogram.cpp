#include "histogram.h"

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
