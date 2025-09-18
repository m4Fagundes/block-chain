# Projeto Block-Chain: Máquina Virtual para Contratos Inteligentes

Este projeto é uma implementação educacional em C++ de um sistema simplificado de blockchain, focado na criação de uma **Máquina Virtual (VM)** capaz de interpretar e executar contratos inteligentes (*smart contracts*).

O objetivo é simular os componentes essenciais de um blockchain, como a emissão de tokens, a transferência de saldos e, principalmente, a execução determinística de uma lógica programada (o contrato) com um sistema de **gás** para limitar os recursos computacionais.

## ✨ Funcionalidades Principais

* **Token Digital:** Simulação de um token (semelhante a um ERC-20) com funcionalidades de `mint` (emissão) e `transfer`.
* **Máquina Virtual (VM):** O coração do projeto. Um interpretador que lê e executa o código de contratos inteligentes.
* **Linguagem de Contrato Própria:** Uma linguagem de scripting simples, baseada em comandos, criada especificamente para este projeto.
* **Sistema de Gás:** Cada operação executada pelo contrato consome uma quantidade de "gás", prevenindo loops infinitos e ataques de negação de serviço. A execução é interrompida se o gás acabar.
* **Execução Condicional:** Suporte para lógica `IF`, permitindo que os contratos tomem decisões baseadas no estado do blockchain (ex: o saldo de uma carteira).
* **Variáveis Internas:** Os contratos podem declarar variáveis para armazenar e manipular valores durante a execução.

## 🛠️ Tecnologias Utilizadas

* **Linguagem:** C++ (com padrão C++11 ou superior)
* **Sistema de Build:** CMake 

## 🚀 Como Compilar e Executar

Certifique-se de ter um compilador C++ (`g++` ou `clang`) e o `CMake` instalados.

```bash
# 1. Clone o repositório (se estiver no Git)
# git clone https://...

# 2. Crie um diretório de build
mkdir build
cd build

# 3. Execute o CMake para configurar o projeto
cmake ..

# 4. Compile o código
make

# 5. Execute o programa principal
./blockchain
