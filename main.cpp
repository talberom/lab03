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
    // Ввод данных
    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;
                                                // Количество чисел в массиве
    const vector<double> numbers = input_numbers(cin, number_count);

    size_t bin_count;                                               // Количество "корзин"
    cerr << "Enter bin count: ";
    cin >>  bin_count;


    // Расчёт гистограммы
    vector<size_t> bins(bin_count, 0);
                                  // В каждую ячейку из массива корзин записать значение 0
    double min = numbers[0];
    double max = numbers[0];

    double bin_size = make_histogram(numbers, bin_count);

// Размер одной корзины
    for (size_t i = 0; i < number_count; i++)
    {
        bool founded = false;                                       // переменная для особого случая (number == max)
        for (size_t j = 0; j < (bin_count - 1) && !founded; j++)
        {
            auto lo = min + bin_size * j;                           // нижняя грань
            auto hi = min + bin_size * (j + 1);                     // верхняя грань

            if ((lo <= numbers[i]) && (numbers[i] < hi))            // если число лежит между нижней и верхней гранями ( в конкретной корзине )
            {
                bins[j]++;                                          // то положить его в эту корзину
                founded = true;
            }
        }
        if (!founded)                                               // особый случай при number == max
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
