#ifndef RESERVA_PASSAGENS_H // Essa macro ESCOLA_H já foi definida? se sim, ignore...
#define RESERVA_PASSAGENS_H // Se nao, defina
#include <stdbool.h>

// Especificação do registro
typedef struct _passageiro Passageiro;
typedef struct _conta Conta;
// typedef struct _passagem Passagem;
typedef struct _bus Bus;
typedef struct _dadosViagem DadosViagem;

// Especificaçõa das funções
Bus *criar_vec_bus(unsigned int capacidade);
Passageiro *criar_paginaCadastroPassageiros(unsigned int capacidadeMax);
void add_bus(Bus *bus, unsigned int numBus, const char *origem, const char *destino, unsigned int capacidade, float valorPassagem, char *horarioPartida, char *horarioChegada, char *dataPartida, char *dataChegada);
void comprar_passagem(Passageiro *passageiro ,Bus *bus, const char *cpf, unsigned int numBus);
void bus_print(const Bus *bus);
void passageiro_print(const Passageiro *passageiro);
void passageiroDadosConta_print(const Passageiro *passageiro);
void pass_Append(Passageiro *pass, const char *nome, unsigned int idade, const char *cpf, unsigned int numConta, float saldo);
void limparBuffer();
bool validarCPF(const char *cpf);
void gerarPassagemOnline(Bus *bus, const char *cpf);

#endif
