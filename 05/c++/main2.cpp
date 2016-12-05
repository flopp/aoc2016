#include <iostream>
#include <string>
#include "md5.h"

static const char* hex = "0123456789abcdef";

int main(int /*argc*/, char** argv) {
    std::string base = argv[1];
    std::string pass = "XXXXXXXX";
    int count = 0;
    uint32_t h[4];
    for (int i = 0; /**/; ++i) {
        const std::string s = base + std::to_string(i);
        md5(s, h);
        if ((h[0] & 0x00F8FFFF) != 0) continue;
        const int pos = (h[0] & 0x000F0000) >> 16;
        if (pass[pos] != 'X') continue;
        pass[pos] = hex[(h[0] & 0xF0000000) >> 28];
        if (++count == 8) break;
    }
    
    std::cout << pass << std::endl;
    
    return 0;
}
