#include <iostream>
#include <string>

int main(int /*argc*/, char** argv) {
    std::string a;
    std::getline(std::cin, a);
    const int rows = std::stoi(argv[1]);
    const int cols = static_cast<int>(a.size());
    std::string b(cols, '?');

    int safe = 0;
    for (int row = 0; row < rows; ++row) {
        for (const auto& c: a) { safe += (c == '.'); }

        b[0] = (a[1] == '^') ? '^' : '.';
        for (int i = 1; i < cols-1; ++i) {
            b[i] = (a[i-1] != a[i+1]) ? '^' : '.';
        }
        b[cols-1] = (a[cols-2] == '^') ? '^' : '.';

        std::swap(a, b);
    }
    std::cout << safe << std::endl;

    return 0;
}
