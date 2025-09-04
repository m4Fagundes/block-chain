// src/Token.cpp
#include "Token.h"
#include <iostream>

Token::Token(const std::string& _symbol)
    : symbol(_symbol) {}

double Token::getBalance(const std::string& owner) const {
    auto it = balances.find(owner);
    if (it != balances.end()) {
        return it->second;
    }
    return 0.0;
}

bool Token::transfer(const std::string& from, const std::string& to, double amount) {
    if (balances[from] >= amount) {
        balances[from] -= amount;
        balances[to] += amount;
        std::cout << "Transferência de " << amount << " " << symbol << " de " << from << " para " << to << " concluída." << std::endl;
        return true;
    }
    std::cout << "Falha na transferência: saldo insuficiente." << std::endl;
    return false;
}

void Token::mint(const std::string& to, double amount) {
    balances[to] += amount;
    std::cout << "Novos " << amount << " " << symbol << " emitidos para " << to << std::endl;
}