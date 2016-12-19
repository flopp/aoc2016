#include <iostream>
#include <string>
#include <vector>

int main(int /*argc*/, char** argv) {
    int s = std::stoi(argv[1]);
    std::vector<int> elves(s);
    for (int i = 0; i < s; ++i) {
        elves[i] = i+1;
    }

    int i = 0;
    while (s > 1) {
        if ((s % 1000) == 0 || s < 1000) std::cout << s << std::endl;
        int op = (i + s/2) % s;
        for (int j = op + 1; j < s; ++j) { elves[j-1] = elves[j]; }
        --s;
        if (op > i) { ++i; }
        i %= s;
    }

    std::cout << elves[0] << std::endl;

    return 0;
}
