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

    void addImmediate(Register * reg1, u_int8_t val){
        uint8_t result = reg1->read() + val;
        reg1->load(result);
    };

    void sub(Register * reg1, Register * reg2){
        uint8_t result = reg1->read() - reg2->read();
        reg1->load(result);
    };

    void subImmediate(Register * reg1, u_int8_t val){
        uint8_t result = reg1->read() - val;
        reg1->load(result);
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

std::string instructions[32] ={"LDI 1 8", "INC 1", "DEC 1"};
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

const std::string opcode = tokens[0];
const int tmp1 = std::stoi(tokens[1]);

if(tokens.size() <= 2){
    if(opcode == "INC"){
        arduino.alu.addImmediate(arduino.registers[tmp1], 1);
    }else if(opcode == "DEC"){
        arduino.alu.subImmediate(arduino.registers[tmp1], 1);
    }
}else if(tokens.size() >= 3){
    const int tmp2 = std::stoi(tokens[2]);
    
    if(opcode == "LDI"){
        arduino.registers[tmp1]->load(static_cast<int8_t>(tmp2));
    }else if(opcode == "ADD"){
        arduino.alu.add(arduino.registers[tmp1], arduino.registers[tmp2]);
    }else if(opcode == "MOV"){
        arduino.registers[tmp1]->load(arduino.registers[tmp2]->read());
    }else if(opcode == "SUB"){
        arduino.alu.sub(arduino.registers[tmp1], arduino.registers[tmp2]);
    }
    
}
}

int main(){
    instructionReader(instructions[0]);
    instructionReader(instructions[1]);
    instructionReader(instructions[2]);
    std::cout << static_cast<int>(arduino.registers[1]->read());
    return 0;
}