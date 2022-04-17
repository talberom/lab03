#include <iostream>
#include <vector>
#include <math.h>
#include "histogram.h"

using namespace std;

vector<double> input_numbers(size_t count){
    vector<double> result(count);
    for (size_t i = 0; i < count; i++){
        cin >> result[i];
    }
    return result;
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

    const size_t SCREEN_WIDTH = 80;                                  // Максимальное количество звёздочек.
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;                // Сколько "съедает" наш вывод, кроме звёздочек.( 1-3 пробела и | )

    size_t max_bins;
    max_bins = bins[0];

    for (size_t bin : bins){                                          // Для каждого элемента из bins запишем значение в bin. Альтернативный способ for.
        if (bin > max_bins)
        {
            max_bins = bin;
        }
    }

    for (size_t bin : bins) {
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
}

void svg_begin(double width, double height) {
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void svg_end() {
    cout << "</svg>\n";
}

void svg_text(double left, double baseline, string text){
    cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>";
}

void svg_rect(double x, double y, double width, double height, string stroke = "black", string color = "black"){
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width <<"' height='" << height << "' stroke= '" << stroke << "' fill='" << color << "' />";
}

void show_histogram_svg(const vector <size_t> &bins, size_t bin_count){
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    const auto INDENT = 3;

    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;
    for (size_t bin : bins) {
        double bin_width;
        if (bin <= IMAGE_WIDTH) {
            bin_width = BLOCK_WIDTH * bin;
        }
        else {
            bin_width = bin;
        }
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, "black", "mediumturquoise");
        top += BIN_HEIGHT;
    }
    svg_end();
}


int main()
{
    // Ввод данных
    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;
                                                // Количество чисел в массиве
    const vector<double> numbers = input_numbers(number_count);

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
    return 0;
}
