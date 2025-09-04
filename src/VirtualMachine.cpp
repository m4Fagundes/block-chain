// src/VirtualMachine.cpp
#include "VirtualMachine.h"
#include <iostream>
#include <sstream>
#include <vector>

VirtualMachine::VirtualMachine(Token& token)
    : managedToken(token), gasRemaining(0) {
    std::cout << "Máquina Virtual inicializada e conectada ao token." << std::endl;
}

bool VirtualMachine::execute(const std::string& contractCode, double gasLimit) {
    std::cout << "Executando o contrato com " << gasLimit << " de gás..." << std::endl;
    gasRemaining = gasLimit;

    const double TRANSFER_GAS_COST = 100.0;

    std::vector<std::string> parsedCommand = parse(contractCode);

    if (parsedCommand.empty()) {
        std::cout << "Erro: Comando de contrato inválido." << std::endl;
        return false;
    }

    std::string command = parsedCommand[0];

    if (command == "TRANSFER") {
        if (gasRemaining < TRANSFER_GAS_COST) {
            std::cout << "Falha na execução: Gás insuficiente para a operação TRANSFER." << std::endl;
            return false;
        }

        gasRemaining -= TRANSFER_GAS_COST;

        if (parsedCommand.size() != 4) {
            std::cout << "Erro: Número incorreto de argumentos para TRANSFER." << std::endl;
            return false;
        }
        std::string from = parsedCommand[1];
        std::string to = parsedCommand[2];
        double amount = std::stod(parsedCommand[3]);
        
        managedToken.transfer(from, to, amount);
        std::cout << "Gás restante: " << gasRemaining << std::endl;
        return true;
    } else {
        std::cout << "Erro: Comando desconhecido." << std::endl;
        return false;
    }

    return false;
}

std::vector<std::string> VirtualMachine::parse(const std::string& code) {
    std::vector<std::string> tokens;
    std::stringstream ss(code);
    std::string token;

    std::getline(ss, token, '(');
    tokens.push_back(token);

    std::getline(ss, token, ')');
    std::stringstream arg_ss(token);
    while (std::getline(arg_ss, token, ',')) {
        size_t first = token.find_first_not_of(" \t\n\r");
        if (std::string::npos != first) {
            size_t last = token.find_last_not_of(" \t\n\r");
            tokens.push_back(token.substr(first, (last - first + 1)));
        }
    }
    return tokens;
}