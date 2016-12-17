#include <iostream>
#include <string>

std::string computeBits(const std::string& init, std::size_t length) {
    std::string current = init;
    std::string next;
    
    while (current.size() < length) {
        next = current;
        next += "0";
        for (auto c = current.rbegin(); c != current.rend(); ++c) {
            next += (*c == '0') ? '1' : '0';
        }
        std::swap(current, next);
    }

    return current.substr(0, length);
}

std::string computeChecksum(const std::string& bits) {
    std::string current = bits;
    std::string next;
    
    while ((current.size() & 1) == 0) {
        next.clear();
        
        for (auto i = 0u; i < current.size(); i += 2) {
            next += (current[i] == current[i+1]) ? '1' : '0';
        }
        
        std::swap(current, next);
    }
    
    return current;
}

int main(int /*argc*/, char** argv) {
    const auto length = static_cast<std::size_t>(std::stoi(argv[1]));
    const std::string init = argv[2];
    const std::string bits = computeBits(init, length);
    const std::string chksum = computeChecksum(bits);
    std::cout << "chksum: " << chksum << std::endl;
    
    return 0;
}
