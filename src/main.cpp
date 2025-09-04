// src/main.cpp
#include <iostream>
#include "VirtualMachine.h"
#include "Token.h"

int main() {
    std::cout << "Iniciando o projeto Blockchain..." << std::endl;

    Token myToken("MEU_TOKEN");
    myToken.mint("Endereco_A", 1000.0);
    myToken.mint("Endereco_B", 500.0);
    
    std::cout << "\nSaldos antes da transferencia:" << std::endl;
    std::cout << "Endereco_A: " << myToken.getBalance("Endereco_A") << " MEU_TOKEN" << std::endl;
    std::cout << "Endereco_B: " << myToken.getBalance("Endereco_B") << " MEU_TOKEN" << std::endl;

    VirtualMachine vm(myToken);

    std::cout << "\nExecutando o Smart Contract..." << std::endl;

    std::string contractCode = "TRANSFER(Endereco_A, Endereco_B, 150.0)";
    
    vm.execute(contractCode, 200.0);
    
    std::cout << "\nTentando executar com gás insuficiente..." << std::endl;
    vm.execute(contractCode, 50.0);

    std::cout << "\nSaldos depois da transferencia:" << std::endl;
    std::cout << "Endereco_A: " << myToken.getBalance("Endereco_A") << " MEU_TOKEN" << std::endl;
    std::cout << "Endereco_B: " << myToken.getBalance("Endereco_B") << " MEU_TOKEN" << std::endl;

    return 0;
}