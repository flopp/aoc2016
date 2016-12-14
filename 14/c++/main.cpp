#include <algorithm>
#include <deque>
#include <iostream>
#include <string>
#include <vector>
#include "md5.h"

int hexi(char c) {
    return (c < 'a') ? (c - '0') : (c - 'W');
}

char* createPass(MD5& md5, const std::string& s, int additionalRounds) {
    char* hash = md5.digestString(const_cast<char*>(s.c_str()));
    for (int r = 0; r < additionalRounds; ++r) {
        hash = md5.digestString(hash);
    }
    return hash;
}

int main() {
    int additionalRounds;
    std::string salt; 
    std::cin >> additionalRounds >> salt;
    
    MD5 md5;
    std::vector<std::deque<int>> pending(16);
    std::vector<int> passwords;
    
    for (int step = 0; /**/; ++step) {
        char* pass = createPass(md5, salt + std::to_string(step), additionalRounds);
        
        // check for 5-tuples
        for (int i = 4; i < 32; ++i) {
            if (pass[i] == pass[i-1] &&
                pass[i] == pass[i-2] &&
                pass[i] == pass[i-3] &&
                pass[i] == pass[i-4]) {
                auto& d = pending[hexi(pass[i])];
                while (!d.empty() && d.front() < step) { d.pop_front(); }
                while (!d.empty() && d.front() >= step) {
                    passwords.push_back(d.front() - 1000);
                    d.pop_front();
                    
                    std::sort(passwords.begin(), passwords.end());
                    if (passwords.size() >= 64 && (passwords[63] + 1000) < step) {
                        std::cout << passwords[63] << std::endl;
                        return 0;
                    }
                }
            }
        }
        
        // check for first triple
        for (int i = 2; i < 32; ++i) {
            if (pass[i] == pass[i-1] &&
                pass[i] == pass[i-2]) {
                auto& d = pending[hexi(pass[i])];
                d.push_back(step + 1000);
                break;
            }
        }
    }
    return 0;
}
