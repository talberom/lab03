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
    // Ввод данных
    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;                                             // Количество чисел в массиве

    vector<double> numbers(number_count);                            // исходный массив
    numbers = input_numbers(number_count);

    size_t bin_count;                                               // Количество "корзин"
    cerr << "Enter bin count: ";
    cin >>  bin_count;


    // Расчёт гистограммы
    vector<size_t> bins(bin_count, 0);                              // В каждую ячейку из массива корзин записать значение 0

    double min = numbers[0];
    double max = numbers[0];
// Начальное значение для максимума и минимума

    for (double number : numbers)                                   // для каждого элемента из numbers запишем значение в number
    {
        if (min > number)                                           // Вычисление минимума из массива
        {
            min = number;
        }
        if (max < number)                                           // Вычисление максимума из массива
        {
            max = number;
        }
    }

    double bin_size = (max - min) / bin_count;
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

    // Вывод данных

    const size_t SCREEN_WIDTH = 80;                                  // Максимальное количество звёздочек.
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;                // Сколько "съедает" наш вывод, кроме звёздочек.( 1-3 пробела и | )

    size_t max_bins;
    max_bins = bins[0];                                              // Размер максимальной корзины

    for (size_t bin : bins)                                          // Для каждого элемента из bins запишем значение в bin. Альтернативный способ for.
    {
        if (bin > max_bins)
        {
            max_bins = bin;
        }
    }

    for (size_t bin : bins)
    {

        double height = bin;
        if (max_bins > MAX_ASTERISK)                                       // Если размер корзины больше заданого максимально возможного размера корзины ( по условию )
        {                                                                  // то выполнить масштабирование
            height = MAX_ASTERISK * (static_cast<double>(bin) / max_bins); // рассматривать выражение bin как имеющее тип double.
        }

// 2 "if-a" - табуляция для корректного вывода
        if (bin < 100)
        {
            cout << " ";
        }
        if (bin < 10)
        {
            cout << " ";
        }
        cout << bin << "|";
        for (size_t zv = 0; zv < height; zv++)                        // Вывод звёздочек в соответствии с количеством чисел
        {
            cout << "*";
        }
        cout << endl;
    }
    return 0;
}
