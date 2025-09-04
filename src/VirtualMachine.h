// src/VirtualMachine.h
#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

#include <string>
#include <vector>
#include "Token.h"

class VirtualMachine {
public:
    VirtualMachine(Token& token);

    bool execute(const std::string& contractCode, double gasLimit);

private:
    Token& managedToken;

    double gasRemaining;

    std::vector<std::string> parse(const std::string& code);
};

#endif