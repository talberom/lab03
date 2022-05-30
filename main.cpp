#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <istream>

#include "svg.h"
#include "histogram.h"

#include <curl/curl.h>

using namespace std;

vector<double> input_numbers(istream& in, size_t count){
    vector<double> result(count);
    for (size_t i = 0; i < count; i++){
        in >> result[i];
    }
    return result;
}

Input read_input(istream& in, bool prompt){

    Input data;
    if (prompt){
        cerr << "Enter number count: ";
    }
    size_t number_count;
    in >> number_count;
    if (prompt){
        cerr << "Enter numbers: ";
    }
    data.numbers = input_numbers(in, number_count);
    if (prompt){
        cerr << "Enter bin count: ";
    }
    size_t bin_count;
    in >> data.bin_count;
    if (prompt){
        cerr << "Enter style of text: ";
    }
    string decoration;
    in >> data.decoration;

    return data;
}

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
        else
        {
            bins[input.bin_count - 1]++;
        }
    }
    return bins;
}

void show_histogram_text(const vector<size_t>& bins){

    const size_t SCREEN_WIDTH = 80;                                  // Максимальное количество звёздочек.
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;                // Сколько "съедает" наш вывод, кроме звёздочек.( 1-3 пробела и | )

    size_t max_bins;
    max_bins = bins[0];

    for (size_t bin : bins){                                          // Для каждого элемента из bins запишем значение в bin. Альтернативный способ for.
        if (max_bins < bin)
        {
            max_bins = bin;
        }
    }

   for (size_t bin : bins) {
        if (bin < 100) {
            cout << " ";
        }
        if (bin < 10) {
            cout << " ";
        }
        cout << bin << "|";
        size_t height;
        if (max_bins > MAX_ASTERISK)
        {
            height = MAX_ASTERISK * (static_cast<double>(bin) / max_bins);
        }
        else
        {
            height = bin;
        }
        for (size_t i = 0; i < height; i++)
        {
            cout << "*";
        }
        cout << endl;
    }
}

size_t write_data(void *items, size_t item_size, size_t item_count, void *ctx){
    stringstream *buffer = reinterpret_cast<stringstream*>(ctx);
    size_t data_size = item_size * item_count;
    buffer->write((char*)items, data_size);
    return data_size;
}

Input download(const string &address){
    stringstream buffer;
     CURL* curl = curl_easy_init();
    if (curl) {
        CURLcode res;
        double namelookup;
        curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        res = curl_easy_perform(curl);
        if(CURLE_OK == res) {
            res = curl_easy_getinfo(curl, CURLINFO_NAMELOOKUP_TIME, &namelookup);
            if(CURLE_OK == res) {
                cerr << "Time: " << namelookup << endl;
            }
        }
        curl_easy_cleanup(curl);
    }
    return read_input(buffer, true);
}




int main(int argc, char* argv[])
{
    Input data;
    if (argc > 1){
        data = download(argv[1]);
    }
    else {
        data = read_input(cin, false);
    }

    const auto bins = make_histogram(data);
    show_histogram_svg(bins, data);

    return 0;
}
