#include "histogram.h"

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
