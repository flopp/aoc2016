#pragma once

#include <cctype>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>

inline std::string trim(const std::string &s)
{
   auto wsfront = std::find_if_not(s.begin(), s.end(), [](int c){return std::isspace(c);});
   auto wsback = std::find_if_not(s.rbegin(), s.rend(), [](int c){return std::isspace(c);}).base();
   return (wsback <= wsfront ? std::string() : std::string(wsfront, wsback));
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> items;
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        items.push_back(item);
    }
    return items;
}
