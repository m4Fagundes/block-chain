#include "VirtualMachine.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>

void trim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}



VirtualMachine::VirtualMachine(Token& token)
    : managedToken(token), gasRemaining(0) {
    std::cout << "Máquina Virtual inicializada e conectada ao token." << std::endl;
}

/**
 * O parser agora é mais robusto para lidar com comandos aninhados
 * como argumento, por exemplo: SET(var, GET_BALANCE(Addr))
 */
std::vector<std::string> VirtualMachine::parse(const std::string& code) {
    std::vector<std::string> tokens;
    size_t start_paren = code.find('(');
    size_t end_paren = code.find_last_of(')');

    if (start_paren == std::string::npos || end_paren == std::string::npos) {
        tokens.push_back(code);
        return tokens;
    }

    
    tokens.push_back(code.substr(0, start_paren));

    
    std::string args_str = code.substr(start_paren + 1, end_paren - start_paren - 1);
    
    std::string current_arg;
    int paren_level = 0;
    for (char c : args_str) {
        if (c == '(') paren_level++;
        if (c == ')') paren_level--;
        
        if (c == ',' && paren_level == 0) {
            trim(current_arg);
            tokens.push_back(current_arg);
            current_arg.clear();
        } else {
            current_arg += c;
        }
    }
    trim(current_arg);
    if (!current_arg.empty()) {
        tokens.push_back(current_arg);
    }
    return tokens;
}

bool VirtualMachine::evaluateCondition(const std::string& condition, double& gasUsed) {
    gasUsed = 10.0;
    
    size_t operator_pos = condition.find_first_of("><=");
    if (operator_pos == std::string::npos) return false;


    std::string varName = condition.substr(0, operator_pos);
    std::string op = condition.substr(operator_pos, 1);
    std::string valueStr = condition.substr(operator_pos + 1);
    trim(varName);
    trim(valueStr);

    if (variables.find(varName) == variables.end()) {
        std::cout << "Erro de execução: Variável '" << varName << "' não definida." << std::endl;
        return false;
    }

    double varValue = variables[varName];
    double compareValue = std::stod(valueStr);

    if (op == ">") return varValue > compareValue;
    if (op == "<") return varValue < compareValue;
    // Adicionar suporte para '=='
    return false;
}

bool VirtualMachine::execute(const std::string& contractCode, double gasLimit) {
    std::cout << "Executando o contrato com " << gasLimit << " de gás..." << std::endl;
    gasRemaining = gasLimit;
    variables.clear(); 

    std::stringstream codeStream(contractCode);
    std::string commandStr;
    bool skipNextCommand = false;

    while (std::getline(codeStream, commandStr, ';')) {
        trim(commandStr);
        if (commandStr.empty()) continue;

        if (skipNextCommand) {
            std::cout << "Comando pulado devido à condição IF falsa: " << commandStr << std::endl;
            skipNextCommand = false;
            continue;
        }

        std::vector<std::string> parsedCommand = parse(commandStr);
        std::string command = parsedCommand[0];

        if (command == "SET") {
            gasRemaining -= 10.0;
            if (parsedCommand.size() != 3) { return false; }

            std::string varName = parsedCommand[1];
            std::string valueSource = parsedCommand[2];
            
            if (valueSource.rfind("GET_BALANCE", 0) == 0) {
                std::vector<std::string> nestedParse = parse(valueSource);
                std::string address = nestedParse[1];
                variables[varName] = managedToken.getBalance(address);
                std::cout << "SET: Variável '" << varName << "' definida com o saldo de " << address << " (" << variables[varName] << ")." << std::endl;
            } else {
                variables[varName] = std::stod(valueSource);
                 std::cout << "SET: Variável '" << varName << "' definida com o valor " << variables[varName] << "." << std::endl;
            }
        } 
        else if (command == "IF") {
            gasRemaining -= 20.0;
            if (parsedCommand.size() != 2) { return false; }

            double gasForEval = 0;
            bool conditionResult = evaluateCondition(parsedCommand[1], gasForEval);
            gasRemaining -= gasForEval;

            std::cout << "IF: Condição '" << parsedCommand[1] << "' é " << (conditionResult ? "Verdadeira." : "Falsa.") << std::endl;
            if (!conditionResult) {
                skipNextCommand = true;
            }
        }
        else if (command == "TRANSFER") {
            gasRemaining -= 100.0;
            if (parsedCommand.size() != 4) { return false; }
            
            std::string from = parsedCommand[1];
            std::string to = parsedCommand[2];
            double amount = std::stod(parsedCommand[3]);
            
            if (managedToken.transfer(from, to, amount)) {
                std::cout << "TRANSFER: Sucesso! " << amount << " MEU_TOKEN de " << from << " para " << to << "." << std::endl;
            } else {
                std::cout << "TRANSFER: Falhou! Saldo insuficiente." << std::endl;
                return false;
            }
        } else {
             std::cout << "Erro: Comando desconhecido '" << command << "'" << std::endl;
             return false;
        }

        if (gasRemaining < 0) {
            std::cout << "Falha na execução: Gás insuficiente!" << std::endl;
            return false;
        }
    }
    std::cout << "Execução do contrato concluída. Gás restante: " << gasRemaining << std::endl;
    return true;
}