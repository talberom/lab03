#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <math.h>

#include "histogram.h"
#include "svg.h"

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

    return data;
}

Input download(const string &address){
    stringstream buffer;
    CURL* curl = curl_easy_init();
    if (curl) {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
        res = curl_easy_perform(curl);
        if (res != 0){
            cerr << curl_easy_strerror(res);
            exit(1);
        }
        curl_easy_cleanup(curl);
    }
    return read_input(buffer, false);
}

int main(int argc, char* argv[])
{
    Input data;
    if (argc > 1){
        data = download(argv[1]);
    }
    else{
        data = read_input(cin, true);
    }

    const auto bins = make_histogram(data);
    show_histogram_svg(bins);

    return 0;
}
