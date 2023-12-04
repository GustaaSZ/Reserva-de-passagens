#include "reserva_passagens.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#define TAMAMHO_NOME 100
#define TAMANHO_CPF 12
#define LISTA_PASSAGEIROS 100
#define LISTA_ONIBUS 10
#define TamanhoData 11
#define TamanhoHorario 10

typedef struct _passageiro{
    char nome[TAMAMHO_NOME];
    unsigned int idade;
    char cpf[TAMANHO_CPF];
    Passageiro *vec_passageiros;
    unsigned int numPass;
    unsigned int capacidadeMax;
    Conta *conta;
} Passageiro;

// typedef struct _passagem{
//     Passageiro *passageiro;
//     DadosViagem *dadosViagem;
//     Bus *bus;
//     int numero_assento;
// } Passagem;

typedef struct _conta{
    unsigned int numero_conta;
    float saldo;
} Conta;

typedef struct _bus{
    int numero_bus;
    char *origem;
    char *destino;
    int capacidade;
    int assentos_disponiveis;
    Passageiro *lista_passageiros;
    Bus *vec_onibus;
    unsigned int num_bus_in_vec;
    unsigned int capacidadeMaxvector;
    float valor_passagem;
    DadosViagem *dados_da_viagem;
} Bus;

// typedef struct _dadosViagem{
//     Tempo partida;
//     Tempo chegada;
// } DadosViagem;

typedef struct _dadosViagem{
    char dataPartida_str[TamanhoData];
    char dataChegada_str[TamanhoData];
    char horarioPartida_str[TamanhoHorario];
    char horarioChegada_str[TamanhoHorario];
} DadosViagem;

// Implementação das funções especificadas em reserva_passagens.h

// ********************* FUNÇÕES PRIVADAS *********************

bool lista_vazia(int cont){
    if(cont == 0){
        return true;
    } else {
        return false;
    }
}

// ********************* FUNÇÕES PUBLICAS *********************

// cria vetor para passageiros
Passageiro *criar_paginaCadastroPassageiros(unsigned int capacidadeMax){
    Passageiro *passageiro = (Passageiro *) calloc(1, sizeof(Passageiro));

    passageiro->numPass = 0;
    passageiro->capacidadeMax = capacidadeMax;

    passageiro->vec_passageiros = (Passageiro *) calloc(capacidadeMax, sizeof(Passageiro)); // Alocação de memoria para a o vetor de passageiros

    return passageiro;
}

// cria um vetor para os onibus
Bus *criar_vec_bus(unsigned int capacidade){
    Bus *bus = (Bus *) calloc(1, sizeof(Bus));
    
    bus->num_bus_in_vec = 0;
    bus->capacidadeMaxvector = capacidade;

    // Inicializa a lista de onibus
    bus->vec_onibus = (Bus *) calloc(capacidade, sizeof(Bus));

    return bus;
}

// Add onibus ao vetor de onibus
void add_bus(Bus *bus, unsigned int numBus, const char *origem, const char *destino, unsigned int capacidade, float valorPassagem, char *dataPartida, char *dataChegada, char *horarioPartida, char *horarioChegada){
    if(bus->num_bus_in_vec <= bus->capacidadeMaxvector){
        Bus new_bus;
        new_bus.numero_bus = numBus;
        new_bus.origem = strdup(origem); // Alocando memoria para o ponteiro origem
        new_bus.destino= strdup(destino); // Alocando memoria para o ponteiro destino
        new_bus.capacidade = capacidade;
        new_bus.assentos_disponiveis = capacidade;
        new_bus.valor_passagem = valorPassagem;

        bus->vec_onibus[bus->num_bus_in_vec] = new_bus;

        // Aloca memória para a lista de passageiros do ônibus
        bus->vec_onibus[bus->num_bus_in_vec].lista_passageiros = (Passageiro *)calloc(capacidade, sizeof(Passageiro));

        // Aloca memória para os dados da viagem
        bus->vec_onibus[bus->num_bus_in_vec].dados_da_viagem = (DadosViagem *) calloc(1, sizeof(DadosViagem));;

        if(bus->vec_onibus->dados_da_viagem == NULL){
            perror("Erro ao alocar memoria para os dados da viagem!\n");
            exit(EXIT_FAILURE);
        }

        if (bus->vec_onibus->lista_passageiros == NULL) {
            perror("Erro ao alocar memoria para a lista de passageiros do onibus!\n");
            exit(EXIT_FAILURE);
        }
        // preenchendo os dados da viagem
        strcpy(bus->vec_onibus[bus->num_bus_in_vec].dados_da_viagem->dataPartida_str, dataPartida);
        strcpy(bus->vec_onibus[bus->num_bus_in_vec].dados_da_viagem->dataChegada_str, dataChegada);
        strcpy(bus->vec_onibus[bus->num_bus_in_vec].dados_da_viagem->horarioPartida_str, horarioPartida);
        strcpy(bus->vec_onibus[bus->num_bus_in_vec].dados_da_viagem->horarioChegada_str, horarioChegada);

        bus->num_bus_in_vec++;
        printf("\nOnibus de numero %d cadastrado com sucesso!\n\n", numBus);

    } else {
        fprintf(stderr,"Error in 'add_bus', you are trying add bussers"
        " in bus vector, but there aren't spaces!\n"); // Mensagem de erro
        exit(EXIT_FAILURE); // mata o programa aqui e informa ao sistema operacional sobre esta falha
    }
    
}


void pass_Append(Passageiro *pass, const char *nome, unsigned int idade, const char *cpf, unsigned int numConta, float saldo){
    if(pass->numPass < LISTA_PASSAGEIROS){
        Passageiro new_pass;
        strcpy(new_pass.nome, nome);
        new_pass.idade = idade;
        if(validarCPF(cpf) != true){ // validação do cpf
            printf("\nNao foi possivel fazer seu cadastro pois o cpf digitado e invalido!\n");
            exit(EXIT_FAILURE);
        }
        strcpy(new_pass.cpf, cpf);
    
        // Adicionar o novo passageiro ao vetor
        pass->vec_passageiros[pass->numPass] = new_pass;

        pass->vec_passageiros[pass->numPass].conta = (Conta *) calloc(1, sizeof(Conta)); // alocação de memoria para o ponteiro conta
        if (pass->vec_passageiros->conta == NULL) {
            perror("Erro ao alocar memória para a conta.\n");
            exit(EXIT_FAILURE);
        }
        // Preencher os dados da conta
        pass->vec_passageiros[pass->numPass].conta->numero_conta = numConta;
        pass->vec_passageiros[pass->numPass].conta->saldo = saldo;

        pass->numPass++;
        printf("\nPassageiro cadastrado no site!\n\n");
    } else {
        fprintf(stderr,"Error in 'pass_Append', you are trying add passengers"
        " in a vector, but there aren't available spaces!\n"); // Mensagem de erro
        exit(EXIT_FAILURE); // mata o programa aqui e informa ao sistema operacional sobre esta falha
    }
}


// Adiciona passageiros no onibus
void comprar_passagem(Passageiro *passageiro, Bus *bus, const char *cpf, unsigned int numBus) {
    int position = -1;

    // Verificando se a lista de passageiros e de onibus se encontra vazia
    if(lista_vazia(passageiro->numPass) == true || lista_vazia(bus->num_bus_in_vec) == true){
        fprintf(stderr, "\nError: Para comprar uma passagem, voce precisa cadastrar onibus e passageiros!\n");
        exit(EXIT_FAILURE);

    } else { // caso as duas listas nao estejam vazias...

        for (int i = 0; i < passageiro->numPass; i++) {
            // Verificando se o cpf e valido
            if(validarCPF(cpf) != true){
                fprintf(stderr,"\nError: Cpf invalido!\n");
                exit(EXIT_FAILURE);
            }

            if (strcmp(passageiro->vec_passageiros[i].cpf, cpf) == 0) {
                printf("\nPassageiro encontrado!\n");

                Passageiro novo_passageiro;
                strcpy(novo_passageiro.nome, passageiro->vec_passageiros[i].nome);
                novo_passageiro.idade = passageiro->vec_passageiros[i].idade;

                // Encontrando o ônibus
                // percorrendo a lista de onibus
                for (int j = 0; j < bus->vec_onibus->num_bus_in_vec; j++) {
                    if (bus->vec_onibus[j].numero_bus == numBus) { // se o onibus foi encontrado
                        printf("Onibus de numero %d encontrado!\n", bus->vec_onibus[j].numero_bus);
                        position = j;
                        break;
                    }
                }

                // Verificando se realmente o onibus foi encontrado
                if (position == -1) {
                    fprintf(stderr, "Erro: Onibus nao encontrado!\n");
                    exit(EXIT_FAILURE);
                }
                
                // Verificação se o saldo da conta é suficiente para adquirir uma passagem
                if(passageiro->vec_passageiros[i].conta->saldo >= bus->vec_onibus[position].valor_passagem){

                    // Atualizando o valor saldo da conta do passageiro que comprou a passagem
                    passageiro->vec_passageiros[i].conta->saldo -= bus->vec_onibus[position].valor_passagem;
                
                

                    if (position != -1) { // se a posiçao tiver um valor diferente de -1

                        // calculo da posicao que deve inserir o novo passageiro na lista de passageiros do onibus de posicao j 
                        int posicao_inserir = bus->vec_onibus[position].capacidade - bus->vec_onibus[position].assentos_disponiveis;

                        // Adicionar o novo passageiro diretamente à lista
                        bus->vec_onibus[position].lista_passageiros[posicao_inserir] = novo_passageiro;
                        

                        // Atualizar assentos disponíveis
                        bus->vec_onibus[position].assentos_disponiveis--;

                        printf("_______________________________________________________________________\n");
                        printf("\n%s, voce acaba de adquirir uma passagem no onibus de numero %d!\n", passageiro->vec_passageiros[i].nome, bus->vec_onibus[position].numero_bus);
                        printf("_______________________________________________________________________\n");

                    } else {
                        fprintf(stderr, "Erro: Onibus de numero %d nao encontrado!\n", numBus);
                        exit(EXIT_FAILURE);
                    }
                    break;  // Saia do loop depois de encontrar o passageiro

                } else {
                    fprintf(stderr, "Error: %s voce nao possui saldo suficiente para comprar uma passagem do onibus %d!\n", passageiro->vec_passageiros[i].nome, bus->vec_onibus[i].numero_bus);
                    exit(EXIT_FAILURE);
                }
            } else {
                printf("Passageiro de cpf %s nao encontrado!\n", cpf);
            }
        }
    }
}

void bus_print(const Bus *bus) {
    int dp, mesPartida, ap, dc, mesChegada, ac;
    int hp, mp, sp, hc, mc, sc;
    // Verificando se a lista de onibus está vazia
    if(lista_vazia(bus->num_bus_in_vec) != true){

        printf("\nD A D O S   D O S   O N I B U S\n");
        printf("- - - - - - - - - - - - - - - - - - \n");
        printf("\nNumero de onibus cadastrados na plataforma: %d\n", bus->num_bus_in_vec);
        for (int i = 0; i < bus->num_bus_in_vec; i++) {
            printf("\n\nNumero do Onibus: %d\n", bus->vec_onibus[i].numero_bus);
            printf("Origem: %s\n", bus->vec_onibus[i].origem);
            printf("Destino: %s\n", bus->vec_onibus[i].destino);
            printf("Capacidade: %d\n", bus->vec_onibus[i].capacidade);
            printf("Assentos Disponiveis: %d\n", bus->vec_onibus[i].assentos_disponiveis);
            printf("Valor da passagem: R$ %.2f\n", bus->vec_onibus[i].valor_passagem);

            
            sscanf(bus->vec_onibus[i].dados_da_viagem->dataPartida_str, "%d/%d/%d", &dp, &mesPartida, &ap);

            // Converte a string do dia de partida em dia, mes, ano
            sscanf(bus->vec_onibus[i].dados_da_viagem->dataChegada_str, "%d/%d/%d", &dc, &mesChegada, &ac);

            // Converte a string do dia de partida em dia, mes, ano
            sscanf(bus->vec_onibus[i].dados_da_viagem->horarioPartida_str, "%d:%d", &hp, &mp);

            // Converte a string do dia de partida em dia, mes, ano
            sscanf(bus->vec_onibus[i].dados_da_viagem->horarioChegada_str, "%d:%d:%d", &hc, &mc);
            
            printf("Data de Partida: %d/%d/%d\n", dp,mesPartida,ap);
            printf("Data de Chegada: %d/%d/%d\n", dc,mesChegada,ac);
            printf("Horario de Partida: %d:%d\n", hp,mp);
            printf("'Provavel' Horario de Chegada: %d:%d\n", hc,mc);

            // Imprime a lista de passageiros
            printf("\n\n* LISTA DE PASSAGEIROS\n\n");
            printf("_____________________________\n\n");
            if (lista_vazia(bus->vec_onibus[i].lista_passageiros->numPass) == true) { 
                printf("Vazio.\n");
            } else {
                for (int j = 0; j < bus->vec_onibus[i].capacidade - bus->vec_onibus[i].assentos_disponiveis; j++) {
                    printf("\nPassageiro %d:\n", j + 1);
                    printf("Nome: %s\n", bus->vec_onibus[i].lista_passageiros[j].nome);
                    printf("Idade: %d\n", bus->vec_onibus[i].lista_passageiros[j].idade);
                    printf("\n");
                }
            }
            printf("_____________________________\n\n");
        }
        printf("- - - - - - - - - - - - - - - - - - \n\n");

    } else {
        printf("\nNenhuma onibus cadastrado na pagina!\n");
    }
    
}

void passageiro_print(const Passageiro *passageiro){
    if(lista_vazia(passageiro->numPass) != true){
        printf("\nD A D O S   D O S   P A S S A G E I R O S   C A D A S T R A D O S   N O    S I T E\n");
        printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n\n");
        printf("Numeros de passageiros cadastrados na pagina: %d\n\n", passageiro->numPass);
        for (int i = 0; i < passageiro->numPass; i++) {

            printf("Nome: %s\n", passageiro->vec_passageiros[i].nome);
            printf("Idade: %d\n", passageiro->vec_passageiros[i].idade);
            printf("Cpf: %s\n", passageiro->vec_passageiros[i].cpf);
            printf("\n");
        }
        printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n\n");
    } else {
        printf("\nPagina de passageiros vazia. Faca cadastro na pagina primeiro!\n");
    }
}

void passageiroDadosConta_print(const Passageiro *passageiro){
    if(lista_vazia(passageiro->numPass) != true){
        printf("\nD A D O S   B A N C A R I O S\n");
        printf("- - - - - - - - - - - - - - - - \n\n");
        for (int i = 0; i < passageiro->numPass; i++) {

            printf("Titular da conta: %s\n", passageiro->vec_passageiros[i].nome);
            printf("Numero da conta: %d\n", passageiro->vec_passageiros[i].conta->numero_conta);
            printf("Saldo: R$ %.2f\n", passageiro->vec_passageiros[i].conta->saldo);
            printf("\n");
            
        }
        printf("- - - - - - - - - - - - - - - - \n\n");
    } else {
        printf("\nNao ha nenhum passageiro cadastrado na pagina!\n");
    }
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Função para verificar se um CPF é válido

bool validarCPF(const char *cpf) {
    // Verificar se o CPF tem 11 dígitos
    if (strlen(cpf) != 11) {
        return false;
    }

    // Verificar se todos os caracteres são dígitos
    for (int i = 0; i < 11; i++) {
        if (!isdigit(cpf[i])) {
            return false;
        }
    }

    // Calcular os dígitos verificadores
    int digito1 = 0, digito2 = 0;
    for (int i = 0; i < 9; i++) {
        int digito = cpf[i] - '0';
        digito1 += digito * (10 - i);
        digito2 += digito * (11 - i);
    }

    digito1 = (digito1 % 11 < 2) ? 0 : 11 - (digito1 % 11);
    digito2 += digito1 * 2;
    digito2 = (digito2 % 11 < 2) ? 0 : 11 - (digito2 % 11);

    // Verificar se os dígitos calculados coincidem com os dois últimos dígitos do CPF
    if(digito1 == cpf[9] - '0' && digito2 == cpf[10] - '0'){
        return true;
    } else {
        return false;
    }
}