#include <iostream>
#include <cstdint>
#include <string.h>
#include <vector>

class Register{
    private:
    u_int8_t data = 0x00;

    public:
    Register(){
    }

    void load(const u_int8_t & val){
        this->data = val;
    }

    u_int8_t read(){
        return this->data;
    }   
};

class ALU{

    private:
    Register SREG = Register();

    public:
    ALU(){}

    void add(Register * reg1, Register * reg2){
        uint8_t result = reg1->read() + reg2->read();
        reg1->load(result);
    };

    void addImmediate(Register & reg1, u_int8_t val){
        uint8_t result = reg1.read() + val;
        reg1.load(result);
    };


};

class Arduino{

    private:
    Register PC = Register();
    
    public:
    Register* registers[32];
    ALU alu;

    Arduino(){
        alu = ALU();
        for (size_t i = 1; i < 32; i++)
        {
            Register* t_reg = new Register();
            registers[i] = t_reg;
        }
        
    }

};

std::string instructions[32] ={"LDI 1 4", "LDI 2 8", "ADD 1 2"};
Arduino arduino = Arduino();

void instructionReader(std::string inst){
    std::vector<std::string> tokens;
    std::string token = "";
    for (size_t i = 0; i < inst.length(); i++)
    {
        if(inst[i] == ' '){
            tokens.push_back(token);
            token = "";
            continue;
        }

        token += inst[i];
    }

    if (!token.empty()) {
    tokens.push_back(token);
}
    
    if(tokens[0] == "LDI"){
        int tmpint = std::stoi(tokens[2]);
        int tmpreg = std::stoi(tokens[1]);
        arduino.registers[tmpreg]->load(static_cast<int8_t>(tmpint));
    }else if(tokens[0] == "ADD"){
        int tmpreg1 = std::stoi(tokens[1]);
        int tmpreg2 = std::stoi(tokens[2]);
        arduino.alu.add(arduino.registers[tmpreg1], arduino.registers[tmpreg2]);
    }
}

int main(){
    instructionReader(instructions[0]);
    instructionReader(instructions[1]);
    instructionReader(instructions[2]);
    std::cout << static_cast<int>(arduino.registers[1]->read());
    return 0;
}