#include <iostream>
#include <string>
#include <vector>

int main(int /*argc*/, char** argv) {
    int count = std::stoi(argv[1]);
    std::vector<int> elves(count);
    for (int i = 0; i < count; ++i) {
        elves[i] = i+1;
    }

    std::vector<int> next; next.reserve(count);
    while (elves.size() > 1) {
        for (auto i = 0u; i < elves.size(); i += 2) {
            elves[(i+1) % elves.size()] = 0;
        }
        next.clear();
        for (const auto& e: elves) { if (e) next.push_back(e); }
        std::swap(elves, next);
    }

    std::cout << elves[0] << std::endl;

    return 0;
}
