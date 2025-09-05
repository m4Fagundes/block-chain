#include <iostream>
#include "VirtualMachine.h"
#include "Token.h"

int main() {
    std::cout << "Iniciando o projeto Blockchain..." << std::endl;

    Token myToken("MEU_TOKEN");
    myToken.mint("Endereco_A", 1000.0);
    myToken.mint("Endereco_B", 500.0);
    
    std::cout << "\nSaldos iniciais:" << std::endl;
    std::cout << "Endereco_A: " << myToken.getBalance("Endereco_A") << " MEU_TOKEN" << std::endl;
    std::cout << "Endereco_B: " << myToken.getBalance("Endereco_B") << " MEU_TOKEN" << std::endl;

    VirtualMachine vm(myToken);

    // Exemplo 1: Contrato com Condição Verdadeira
    std::cout << "\n--- Executando Contrato com IF Verdadeiro ---" << std::endl;
    std::string conditionalContract1 = "SET(saldoA, GET_BALANCE(Endereco_A)); IF(saldoA>500); TRANSFER(Endereco_A, Endereco_B, 100);";
    vm.execute(conditionalContract1, 300.0);

    // Exemplo 2: Contrato com Condição Falsa
    std::cout << "\n--- Executando Contrato com IF Falso ---" << std::endl;
    std::string conditionalContract2 = "SET(saldoB, GET_BALANCE(Endereco_B)); IF(saldoB>1000); TRANSFER(Endereco_A, Endereco_B, 100);";
    vm.execute(conditionalContract2, 300.0);

    std::cout << "\n--- Saldos Finais ---" << std::endl;
    std::cout << "Endereco_A: " << myToken.getBalance("Endereco_A") << " MEU_TOKEN" << std::endl;
    std::cout << "Endereco_B: " << myToken.getBalance("Endereco_B") << " MEU_TOKEN" << std::endl;

    return 0;
}