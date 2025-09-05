#ifndef VIRTUALMACHINE_H
#define VIRTUALMACHINE_H

#include "Token.h"
#include <string>
#include <vector>
#include <map>

class VirtualMachine {
public:
    // O construtor recebe uma referência para o Token que ele vai gerenciar
    VirtualMachine(Token& token);

    // Ponto de entrada para executar um código de contrato
    bool execute(const std::string& contractCode, double gasLimit);

private:
    Token& managedToken;
    double gasRemaining;
    // Mapa para armazenar variáveis criadas pelo contrato (ex: SET(saldoA, ...))
    std::map<std::string, double> variables;

    // Função para "quebrar" um comando em nome e argumentos (ex: "TRANSFER(A,B,100)")
    std::vector<std::string> parse(const std::string& command);

    // Função para avaliar uma condição do IF (ex: "saldoA>500")
    bool evaluateCondition(const std::string& condition, double& gasUsed);
};

#endif // VIRTUALMACHINE_H