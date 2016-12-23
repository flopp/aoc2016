#include <iostream>
#include <regex>
#include <string>
#include <vector>


enum class OpCode {
    TGL,
    INC,
    DEC,
    CPY,
    JNZ
};


struct Cmd {
    Cmd(OpCode op, const std::string& p1, const std::string& p2 = "0") {
        this->op = op;
        reg1 = isReg(p1);
        reg2 = isReg(p2);
        op1 = reg1 ? (p1[0] - 'a') : std::stoi(p1);
        op2 = reg2 ? (p2[0] - 'a') : std::stoi(p2);
    }

    static bool isReg(const std::string& s) {
        return (s == "a") || (s == "b") || (s == "c") || (s == "d");
    }

    OpCode op;
    bool reg1;
    bool reg2;
    int op1;
    int op2;
};


struct VM {
    std::vector<Cmd> cmds;
    int pc{0};
    std::vector<int> reg{0, 0, 0, 0};

    void parse(const std::string& s) {
        std::cout << s << std::endl;
        static const std::regex re_TGL("tgl ([a-d])");
        static const std::regex re_INC("inc ([a-d])");
        static const std::regex re_DEC("dec ([a-d])");
        static const std::regex re_CPY("cpy (-?\\d+|[a-d]) ([a-d])");
        static const std::regex re_JNZ("jnz (-?\\d+|[a-d]) (-?\\d+|[a-d])");
        std::smatch m;

        /**/ if (std::regex_match(s, m, re_TGL)) { cmds.push_back(Cmd{OpCode::TGL, m[1]}); }
        else if (std::regex_match(s, m, re_INC)) { cmds.push_back(Cmd{OpCode::INC, m[1]}); }
        else if (std::regex_match(s, m, re_DEC)) { cmds.push_back(Cmd{OpCode::DEC, m[1]}); }
        else if (std::regex_match(s, m, re_CPY)) { cmds.push_back(Cmd{OpCode::CPY, m[1], m[2]}); }
        else if (std::regex_match(s, m, re_JNZ)) { cmds.push_back(Cmd{OpCode::JNZ, m[1], m[2]}); }
        else {
            std::cerr << "bad cmd: " << s << std::endl;
        }
    }

    void toggle(int i) {
        if (i < 0 || i >= static_cast<int>(cmds.size())) {
            return;
        }

        auto& c = cmds[i];
        switch (c.op) {
            case OpCode::TGL: c.op = OpCode::INC; return;
            case OpCode::INC: c.op = OpCode::DEC; return;
            case OpCode::DEC: c.op = OpCode::INC; return;
            case OpCode::CPY: c.op = OpCode::JNZ; return;
            case OpCode::JNZ: c.op = OpCode::CPY; return;
        }
    }


    void run() {
        while (pc >= 0 && pc < static_cast<int>(cmds.size())) {
            exec(cmds[pc]);
        }
    }


    void exec(Cmd& c) {
        switch (c.op) {
            case OpCode::TGL:
                toggle(pc + reg[c.op1]);
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
            case OpCode::CPY:
                if (c.reg2) {
                    reg[c.op2] = (c.reg1 ? reg[c.op1] : c.op1);
                }
                pc++;
                return;
            case OpCode::JNZ:
                pc += ((c.reg1 ? reg[c.op1] : c.op1) ? (c.reg2 ? reg[c.op2] : c.op2) : 1);
                return;
        }
    }
};


int main(int argv, char** argc) {
    VM vm;

    if (argv > 1) {
        vm.reg[0] = std::stoi(argc[1]);
    }

    std::string line;
    while (std::getline(std::cin, line)) {
        vm.parse(line);
    }

    vm.run();

    std::cout << "a = " << vm.reg[0] << std::endl;
    return 0;
}
