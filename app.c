#include "reserva_passagens.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define TamanhoNome 100
#define TamanhoCPF 12
#define LISTA_PASSAGEIROS 100
#define LISTA_ONIBUS 100

// Defines utlizado para o onibus
#define CadastrarOnibus 4
#define PrintOnibus 5
#define ComprarPassagem 6

// Defines utilizados para o passageiro
#define CadastrarPassageiro 1
#define print_Passageiros 2
#define ListarContas 3

#define SAIR 8

typedef struct{
    int dia;
    int mes;
    int ano;
    
    int hora;
    int minutos;
    int segundos;
} Hora;

int main(){
    // variaveis
    int op;
    char nome[TamanhoNome];
    unsigned int idade;
    char cpf[TamanhoCPF];
    int numConta;
    float saldo;
    float valorPassagem;
    int numBus;
    int capacidadeBus;
    char origemBus[100];
    char destinoBus[100];
    int n;

    int diaViagem;

    Passageiro *Listapassageiros = criar_paginaCadastroPassageiros(LISTA_PASSAGEIROS);
    Bus *lista_onibus = criar_vec_bus(LISTA_ONIBUS);
    struct tm tempo;
    time_t tempoSeg;
    
    time(&tempoSeg);
    
    tempo = *localtime(&tempoSeg);

    Hora agora; //Chamada do registro da da Hora
    
    do{

        printf("\n1) Cadastar Passageiro.\n");
        printf("2) Listar Passageiros.\n");
        printf("3) Listar contas bancarias dos passageiros.\n");
        printf("4) Cadastrar Onibus.\n");
        printf("5) Listar Onibus.\n");
        printf("6) Comprar passagem de onibus.\n");
        printf("7) ver hora atual.\n");
        // printf("7) Atualizar Aluno.\n");
        // printf("8) Listar Alunos.\n");
        // printf("9) Buscar Aluno.\n");
        // printf("10) Deletar Aluno.\n");
        printf("Sair.\n");

        printf("\nDigite uma opcao: ");
        scanf("%d", &op);

        switch (op){

            case CadastrarPassageiro:
                printf("Quantos passageiros deseja cadastrar na pagina? ");
                scanf("%d", &n);
                for(int i = 0; i < n; i++){
                    if(n <= LISTA_PASSAGEIROS){

                        // DADOS BÁSICOS DO PASSAGEIRO
                        printf("Digite seu nome: ");
                        scanf(" %[^\n]", nome);

                        limparBuffer(); // Chame esta função para limpar o buffer

                        printf("Digite sua idade: ");
                        scanf("%d", &idade);
                        

                        printf("Digite seu cpf: ");
                        scanf(" %[^\n]", cpf);

                        // if(validarCPF(cpf) != true){
                        //     fprintf(stderr, "\nError: Cpf invalido!\n");
                        //     exit(EXIT_FAILURE);
                        // }

                        if(validarCPF(cpf) == true){
                            // DADOS BANCARIOS DA CONTA DO PASSAGEIRO
                            printf("Numero da conta bancaria: ");
                            scanf("%d", &numConta);

                            printf("Saldo da conta bancaria: ");
                            scanf("%f", &saldo);

                            // Adicionando o passageiro na lista de passageiros
                            pass_Append(Listapassageiros, nome, idade, cpf, numConta, saldo);    
                        } else {
                            printf("\nError: Nao foi possivel cadastrar o passageiro na pagina pois o cpf e invalido!\n");
                        }
                    }
                }
            break;
            
            case print_Passageiros:
                passageiro_print(Listapassageiros);
            break;

            case ListarContas: 
                passageiroDadosConta_print(Listapassageiros);
            break;

            case CadastrarOnibus:
                printf("Quantos onibus deseja cadastrar na plataforma? ");
                scanf("%d", &n);
                for(int i = 0; i < n; i++){
                    if(n <= LISTA_PASSAGEIROS){
                        printf("Digite o numero do onibus: ");
                        scanf("%d", &numBus);

                        printf("Digite a origem: ");
                        scanf(" %[^\n]", origemBus);

                        printf("Digite o Destino: ");
                        scanf(" %[^\n]", destinoBus);

                        limparBuffer(); // Chame esta função para limpar o buffer

                        printf("Digite a capacidade maxima: ");
                        scanf("%d", &capacidadeBus);

                        printf("Digite o valor da passagem: ");
                        scanf("%f", &valorPassagem);
                        printf("\n");

                        add_bus(lista_onibus, numBus, origemBus, destinoBus, capacidadeBus, valorPassagem);
                    }
                }
            break;

            case PrintOnibus:
                bus_print(lista_onibus);
            break;

            case ComprarPassagem:
                printf("Digite seu cpf: ");
                scanf(" %[^\n]", cpf);
                printf("Digite o numero do onibus: ");
                scanf("%d", &numBus);
                comprar_passagem(Listapassageiros, lista_onibus, cpf, numBus);
            break;

            case 7:
                // Calculo da hora
                // struct tm tempo;
                // time_t tempoSeg;
                
                // time(&tempoSeg);
                
                // tempo = *localtime(&tempoSeg);

                // Hora agora; //Chamada do registro da da Hora
                
                agora.dia = tempo.tm_mday;
                agora.mes = tempo.tm_mon + 1;
                agora.ano = tempo.tm_year + 1900;
                agora.hora = tempo.tm_hour ;
                agora.minutos = tempo.tm_min;
                agora.segundos = tempo.tm_sec;
                
                printf("%02d/%02d/%d -> %02d:%02d:%02d\n",agora.dia, agora.mes, agora.ano, agora.hora, agora.minutos, agora.segundos);

                // int diaViagem;
                printf("Digite o dia da viagem: ");
                scanf("%d", &diaViagem);

                int faltam =  diaViagem - agora.dia;

                printf("faltam %d dias para sua viagem!\n", faltam);   
                printf("\n");
            break;

            case SAIR:
                printf("Obrigado, Volte Sempre!\n");
            break;

            default:
                printf("Opcao invalida!\n");
            break;

        }

    }while(op != SAIR);
    
    
    return 0;
}
