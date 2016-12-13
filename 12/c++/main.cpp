#include <cassert>
#include <iostream>
#include <regex>
#include <string>
#include <vector>


enum class OpCode {
    CPY,  // REG[op1] <= REG[op2]; PC++
    CPYi, // REG[op1] <= op2; PC++
    INC,  // REG[op1]++; PC++
    DEC,  // REG[op2]++; PC++
    JNZ,  // PC += op2 if REG[op1] != 0 else PC++
    JNZi  // PC += op2 if op1 != 0 else PC++
};


struct Cmd {
    OpCode op;
    int op1;
    int op2;
};


struct VM {
    std::vector<Cmd> cmds;
    int pc{0};
    std::vector<int> reg{0, 0, 0, 0};
    
    
    static int r(const std::string& s) {
        if (s == "a") return 0;
        else if (s == "b") return 1;
        else if (s == "c") return 2;
        else if (s == "d") return 3;
        else {
            std::cerr << "bad reg: " << s << std::endl;
            assert(false);
            return -1;
        }
    }
    
    
    void parse(const std::string& s) {
        static const std::regex re_CPY("cpy ([a-d]) ([a-d])");
        static const std::regex re_CPYi("cpy (-?\\d+) ([a-d])");
        static const std::regex re_INC("inc ([a-d])");
        static const std::regex re_DEC("dec ([a-d])");
        static const std::regex re_JNZ("jnz ([a-d]) (-?\\d+)");
        static const std::regex re_JNZi("jnz (-?\\d+) (-?\\d+)");
        std::smatch m;
        
             if (std::regex_match(s, m, re_CPY))  { cmds.push_back(Cmd{OpCode::CPY,  r(m[1]),         r(m[2])}); }
        else if (std::regex_match(s, m, re_CPYi)) { cmds.push_back(Cmd{OpCode::CPYi, std::stoi(m[1]), r(m[2])}); }
        else if (std::regex_match(s, m, re_INC))  { cmds.push_back(Cmd{OpCode::INC,  r(m[1]),         0}); }
        else if (std::regex_match(s, m, re_DEC))  { cmds.push_back(Cmd{OpCode::DEC,  r(m[1]),         0}); }
        else if (std::regex_match(s, m, re_JNZ))  { cmds.push_back(Cmd{OpCode::JNZ,  r(m[1]),         std::stoi(m[2])}); }
        else if (std::regex_match(s, m, re_JNZi)) { cmds.push_back(Cmd{OpCode::JNZi, std::stoi(m[1]), std::stoi(m[2])}); }
        else {
            std::cerr << "bad cmd: " << s << std::endl;
            assert(false);
        }
    }
    
    
    void run() {
        while (pc >= 0 && pc < static_cast<int>(cmds.size())) {
            exec(cmds[pc]);
        }
    }
    
    
    void exec(const Cmd& c) {
        switch (c.op) {
            case OpCode::CPY:
                reg[c.op2] = reg[c.op1];
                pc++;
                return;
            case OpCode::CPYi:
                reg[c.op2] = c.op1;
                pc++;
                return;
            case OpCode::INC:
                reg[c.op1]++;
                pc++;
                return;
            case OpCode::DEC:
                reg[c.op1]--;
                pc++;
                return;
            case OpCode::JNZ:
                pc += (reg[c.op1] ? c.op2 : 1);
                return;
            case OpCode::JNZi:
                pc += (c.op1 ? c.op2 : 1);
                return;
        }
    }    
};


int main(int argv, char** argc) {
    VM vm;
    
    if (argv > 1) {
        vm.reg[2] = std::stoi(argc[1]);
    }
    
    std::string line;
    while (std::getline(std::cin, line)) {
        vm.parse(line);
    }
    
    vm.run();
    
    std::cout << "a = " << vm.reg[0] << std::endl;
    return 0;
}
