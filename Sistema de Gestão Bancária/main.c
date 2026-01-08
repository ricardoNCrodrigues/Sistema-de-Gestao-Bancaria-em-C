#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Cliente {
    int id;
    char nome[50];
    float saldo;
    struct Cliente* prox;
} Cliente;

Cliente* criarCliente(int id, const char* nome, float saldo) {
    Cliente* novoCliente = (Cliente*)malloc(sizeof(Cliente));
    novoCliente->id = id;
    strcpy(novoCliente->nome, nome);
    novoCliente->saldo = saldo;
    novoCliente->prox = NULL;
    return novoCliente;
}

void adicionarCliente(Cliente** listaClientes, int id, const char* nome, float saldo) {
    Cliente* novoCliente = criarCliente(id, nome, saldo);
    if (*listaClientes == NULL) {
        *listaClientes = novoCliente;
    } else {
        Cliente* clienteAtual = *listaClientes;
        while (clienteAtual->prox != NULL) {
            clienteAtual = clienteAtual->prox;
        }
        clienteAtual->prox = novoCliente;
    }
}

void exibirClientes(Cliente* listaClientes) {                                                               
    if (listaClientes == NULL) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }
    printf("Lista de Clientes:\n");
    Cliente* clienteAtual = listaClientes;
    while (clienteAtual != NULL) {
        printf("cl ID: %d, Nome: %s, Saldo: %.2f\n", clienteAtual->id, clienteAtual->nome, clienteAtual->saldo);
        clienteAtual = clienteAtual->prox;
    }
}

Cliente* buscarCliente(Cliente* listaClientes, int id) {
    Cliente* clienteAtual = listaClientes;
    while (clienteAtual != NULL) {
        if (clienteAtual->id == id) {
            return clienteAtual;
        }
        clienteAtual = clienteAtual->prox;
    }
    return NULL;
}

void removerCliente(Cliente** listaClientes, int id) {
    Cliente* clienteAtual = *listaClientes;
    Cliente* clienteAnterior = NULL;

    while (clienteAtual != NULL && clienteAtual->id != id) {
        clienteAnterior = clienteAtual;
        clienteAtual = clienteAtual->prox;
    }

    if (clienteAtual == NULL) {
        printf("Cliente com ID %d nao encontrado.\n", id);
        return;
    }

    if (clienteAnterior == NULL) {
        *listaClientes = clienteAtual->prox;
    } else {
        clienteAnterior->prox = clienteAtual->prox;
    }

    free(clienteAtual);
    printf("Cliente com ID %d removido com sucesso.\n", id);
}

void depositar(Cliente* cliente, float valor) {
    cliente->saldo += valor;
    printf("Valor depositado na conta de %s.\n", cliente->nome);
}

void sacar(Cliente* cliente, float valor) {
    if (cliente->saldo >= valor) {
        cliente->saldo -= valor;
        printf("Valor sacado da conta de %s.\n", cliente->nome);
    } else {
        printf("Saldo insuficiente na conta de %s.\n", cliente->nome);
    }
}

void consultarSaldo(Cliente* cliente) {
    printf("Saldo da conta de %s: %.2f\n", cliente->nome, cliente->saldo);
}

void liberarClientes(Cliente* listaClientes) {
    Cliente* clienteAtual = listaClientes;
    while (clienteAtual != NULL) {
        Cliente* clienteProx = clienteAtual->prox;
        free(clienteAtual);
        clienteAtual = clienteProx;
    }
}

void salvarClientes(Cliente* listaClientes, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Cliente* clienteAtual = listaClientes;
    while (clienteAtual != NULL) {
        fprintf(arquivo, "%d,%s,%.2f\n", clienteAtual->id, clienteAtual->nome, clienteAtual->saldo);
        clienteAtual = clienteAtual->prox;
    }

    fclose(arquivo);
    printf("Dados dos clientes salvos com sucesso.\n");
}

int main() {
    Cliente* listaClientes = NULL;
    int pin;
    int opcao;
    int id;
    float valor;
    pin = 1234;
    system("COLOR 1F");
    printf("Introduza a palavra passe para entrar no sistema de gestao do banco:\n");
    scanf("%d", &pin);
    if (pin != 1234) {
        printf(" pin incorreto\n");
        printf(" por favor tente mais tarde :(\n");

        return 0;
    }
    do {
        printf("\n ----------------------Selecione uma opcao:----------------------\n");
        printf("1. Adicionar cliente\n");
        printf("2. Exibir clientes\n");
        printf("3. Buscar cliente\n");
        printf("4. Remover cliente\n");
        printf("5. Depositar\n");
        printf("6. Sacar\n");
        printf("7. Consultar saldo\n");
        printf("8. Salvar dados dos clientes em arquivo\n");
        printf("9. Sair\n");

        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                {
                    int id;
                    char nome[50];
                    float saldo;
                    printf("Digite o ID do cliente: ");
                    scanf("%d", &id);
                    printf("Digite o nome do cliente: ");
                    scanf("%s", nome);
                    printf("Digite o saldo do cliente: ");
                    scanf("%f", &saldo);
                    adicionarCliente(&listaClientes, id, nome, saldo);
                    printf("Cliente adicionado com sucesso.\n");
                }
                break;
            case 2:
                exibirClientes(listaClientes);
                break;
            case 3:
                {
                    printf("Digite o ID do cliente: ");
                    scanf("%d", &id);
                    Cliente* cliente = buscarCliente(listaClientes, id);
                    if (cliente != NULL) {
                        printf("Cliente encontrado:\n");
                        printf("ID: %d, Nome: %s, Saldo: %.2f\n", cliente->id, cliente->nome, cliente->saldo);
                    } else {
                        printf("Cliente com ID %d nao encontrado.\n", id);
                    }
                }
                break;
            case 4:
                {
                    printf("Digite o ID do cliente a ser removido: ");
                    scanf("%d", &id);
                    removerCliente(&listaClientes, id);
                }
                break;
            case 5:
                {
                    printf("Digite o ID do cliente para depositar: ");
                    scanf("%d", &id);
                    printf("Digite o valor a ser depositado: ");
                    scanf("%f", &valor);
                    Cliente* cliente = buscarCliente(listaClientes, id);
                    if (cliente != NULL) {
                        depositar(cliente, valor);
                    } else {
                        printf("Cliente com ID %d nao encontrado.\n", id);
                    }
                }
                break;
            case 6:
                {
                    printf("Digite o ID do cliente para sacar: ");
                    scanf("%d", &id);
                    printf("Digite o valor a ser sacado: ");
                    scanf("%f", &valor);
                    Cliente* cliente = buscarCliente(listaClientes, id);
                    if (cliente != NULL) {
                        sacar(cliente, valor);
                    } else {
                        printf("Cliente com ID %d nao encontrado.\n", id);
                    }
                }
                break;
            case 7:
                {
                    int id;
                    printf("Digite o ID do cliente para consultar o saldo: ");
                    scanf("%d", &id);
                    Cliente* cliente = buscarCliente(listaClientes, id);
                    if (cliente != NULL) {
                        consultarSaldo(cliente);
                    } else {
                        printf("Cliente com ID %d nao encontrado.\n", id);
                    }
                }
                break;
            case 8:
                {
                    char nomeArquivo[50];
                    printf("Digite o nome do arquivo para salvar os dados dos clientes: ");
                    scanf("%s", nomeArquivo);
                    salvarClientes(listaClientes, nomeArquivo);
                }
                break;
            case 9:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 9);
    liberarClientes(listaClientes);
}