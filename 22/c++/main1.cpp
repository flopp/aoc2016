#include <cassert>
#include <iomanip>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

struct Node {
    std::size_t id;
    int x, y;
    int s, u, a;
};

struct Grid {
    int w, h;
    std::vector<Node> nodes;

    void parse(std::istream& is) {
        w = 0;
        h = 0;

        // /dev/grid/node-x0-y0     94T   65T    29T   69%
        static const std::regex re(
            "/dev/grid/node-x(\\d+)-y(\\d+)\\s+(\\d+)T\\s+(\\d+)T\\s+(\\d+)T\\s+(\\d+)%");
        std::smatch m;
        std::string line;
        std::vector<Node> temp;
        while (std::getline(is, line)) {
            if (!std::regex_match(line, m, re)) { continue; }
            const Node n{0,
                std::stoi(m[1]), std::stoi(m[2]),
                std::stoi(m[3]), std::stoi(m[4]), std::stoi(m[5])};
            temp.push_back(n);
            if (n.x >= w) w = n.x + 1;
            if (n.y >= h) h = n.y + 1;
        }
        assert(w * h == static_cast<int>(temp.size()));

        nodes.resize(temp.size());
        for (const auto tn: temp) {
            Node n = tn;
            n.id = n.y * w + n.x;
            nodes[n.id] = n;
        }
    }

    std::vector<std::pair<std::size_t, std::size_t>> viablePairs() const {
        std::vector<std::pair<std::size_t, std::size_t>> v;
        for (const auto& a: nodes) {
            for (const auto& b: nodes) {
                if ((a.id != b.id) && (a.u > 0) && (a.u <= b.a)) {
                    v.push_back({a.id, b.id});
                }
            }
        }
        return v;
    }

    const Node& get(int x, int y) const {
        return nodes[x + y * w];
    }

    void print(std::ostream& os) const {
        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                const auto& n = nodes[y * w + x];
                if (n.u == 0) {
                    os << "_";
                } else if (n.u > 400) {
                    os << "#";
                } else {
                    os << "o";
                }
            }
            os << std::endl;
        }
    }
};

int main() {
    Grid g;
    g.parse(std::cin);
    g.print(std::cout);
    std::cout << "viable pairs: " << g.viablePairs().size() << std::endl;
    return 0;
}
