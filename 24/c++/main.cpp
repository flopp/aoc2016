#include <algorithm>
#include <deque>
#include <iostream>
#include <string>
#include <vector>

struct Maze {
    std::string map;
    int w{0};

    void read(std::istream& is) {
        std::string line;
        while (std::getline(is, line)) {
            w = line.size();
            map += line;
        }
    }

    std::vector<unsigned int> computeDists(int start) const {
        std::vector<unsigned int> dists(8, 0);
        const auto pos = map.find('0' + start);
        if (pos == std::string::npos) {
            return dists;
        }

        static std::vector<int> dist;
        dist.assign(map.size(), -1);
        dist[pos] = 0;

        static std::deque<unsigned int> pending;
        pending.push_back(pos);

        while (!pending.empty()) {
            const unsigned int p = pending.front();
            pending.pop_front();

            for (auto offset: {-w, +1, +w, -1}) {
                const unsigned int n = p + offset;
                if (map[n] != '#' && (dist[n] < 0 || dist[n] > dist[p] + 1)) {
                    dist[n] = dist[p] + 1;
                    pending.push_back(n);
                }
            }
        }

        for (int i = 0; i < 8; ++i) {
            const auto pos = map.find('0' + i);
            if (pos != std::string::npos) {
                dists[i] = dist[pos];
            }
        }
        return dists;
    }

    std::vector<unsigned int> computePairwise() const {
        std::vector<unsigned int> dists(8*8);
        for (int i = 0; i < 8; ++i) {
            const std::vector<unsigned int> d = computeDists(i);
            for (int j = 0; j < 8; ++j) {
                dists[i * 8 + j] = d[j];
                dists[j * 8 + i] = d[j];
            }
        }
        return dists;
    }

    unsigned int solve(int part) const {
        const std::vector<unsigned int> pwDist = computePairwise();

        std::vector<int> order = {1, 2, 3, 4, 5, 6, 7};
        unsigned int min = 0;
        do {
            unsigned int d = 0;
            int last = 0;
            for (const auto& i: order) {
                d += pwDist[last * 8 + i];
                last = i;
            }

            // return to 0 is part==2
            if (part == 2) {
                d += pwDist[last * 8 + 0];
            }

            if (min == 0 || d < min) {
                min = d;
            }
        } while (std::next_permutation(order.begin(), order.end()));

        return min;
    }
};


int main() {
    Maze m;
    m.read(std::cin);
    std::cout << "part 1: min path = " << m.solve(1) << std::endl;
    std::cout << "part 2: min path = " << m.solve(2) << std::endl;
    return 0;
}
