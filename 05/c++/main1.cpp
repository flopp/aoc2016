#include <iostream>
#include <string>
#include "md5.h"

static const char* hex = "0123456789abcdef";

int main(int /*argc*/, char** argv) {
    std::string base = argv[1];
    std::string pass;
    uint32_t h[4];
    for (int i = 0; /**/; ++i) {
        const std::string s = base + std::to_string(i);
        md5(s, h);
        if ((h[0] & 0x00F0FFFF) != 0) continue;
        pass += hex[(h[0] & 0x000F0000) >> 16];
        if (pass.length() == 8) break;
    }
    
    std::cout << pass << std::endl;
    
    return 0;
}
