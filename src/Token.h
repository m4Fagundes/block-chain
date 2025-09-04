// src/Token.h
#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <map>

class Token {
private:
    std::string symbol;
    std::map<std::string, double> balances;

public:
    Token(const std::string& _symbol);
    double getBalance(const std::string& owner) const;
    bool transfer(const std::string& from, const std::string& to, double amount);
    void mint(const std::string& to, double amount);
};

#endif