#include <iostream>
#include <string>
#include <vector>

struct Elf {
    int index;
    Elf* p;
    Elf* n;

    void disconnect() {
        p->n = n;
        n->p = p;
    }
};

int main(int /*argc*/, char** argv) {
    int s = std::stoi(argv[1]);

    std::vector<Elf> elves(s);
    for (int i = 0; i < s; ++i) {
        elves[i].index = i+1;
    }

    for (int i = 0; i < s; ++i) {
        elves[i].p = &elves[(i+s-1) % s];
        elves[i].n = &elves[(i+1) % s];
    }

    Elf* e = &elves[0];
    for (int i = 0; i < s-1; ++i) {
        e->n->disconnect();
        e = e->n;
    }
    std::cout << e->index << std::endl;

    return 0;
}
