#include <windows.h>
#include <tchar.h>
#include "svg.h"

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

void get_version_info(DWORD &version_major, DWORD &version_minor, DWORD &build) {
    DWORD vWIN = GetVersion();

    DWORD mask = 0b00000000'00000000'11111111'11111111;
    DWORD version = vWIN & mask;
    DWORD platform = vWIN >> 16;

    DWORD version_mask = 0b00000000'11111111;
    version_major = version & version_mask;
    version_minor = version >> 8;

    if ((vWIN & 0x80000000) == 0) {
        build = platform;
    }
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
    const auto vWIN_BUFFER = 32767;

    size_t max_bins = bins[0];
    for (size_t bin : bins)
    {
        if (max_bins < bin)
        {
            max_bins = bin;
        }
    }

    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    double top = 0;
    for (size_t i = 0; i < bins.size(); i++) {
        size_t height = bins[i] * BLOCK_WIDTH;
        if (max_bins * BLOCK_WIDTH > IMAGE_WIDTH - TEXT_WIDTH)
        {
            height = (IMAGE_WIDTH - TEXT_WIDTH) * (static_cast<double>(bins[i]) / max_bins);
        }
        const double bin_width = height;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bins[i]));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, "cyan", "black");
        top += BIN_HEIGHT;
    }

    DWORD version_minor, version_major;
    DWORD build; DWORD  bufCharCount = vWIN_BUFFER;
    TCHAR  infoBuf[vWIN_BUFFER];
    GetComputerName(infoBuf, &bufCharCount);
    get_version_info(version_major, version_minor, build);

    svg_text(TEXT_LEFT, top + 20, "Windows version " + to_string(version_major) + "." + to_string(version_minor) + ", build " + to_string(build));
    svg_text(TEXT_LEFT, top + 40, "Computer name: ");
    svg_text(TEXT_LEFT + 110, top + 40, infoBuf);
    svg_end();
}
