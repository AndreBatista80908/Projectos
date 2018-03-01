#include "contas.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>

#define atrasar() usleep(ATRASO)

//contasSaldos: tem os saldos das contas
//contasSaldosAux: guarda as simulações de cada ano
//stopFlag: se faz "sair agora", passa a 1 e interrompe o ciclo
//estado2: se faz "sair agora", passa a 1 e avisa que terminou por interrupção
int contasSaldos[NUM_CONTAS],
    contasSaldosAux[NUM_CONTAS],
    stopFlag = 0, estado2 = 0;

int contaExiste(int idConta) {
    return (idConta > 0 && idConta <= NUM_CONTAS);
}

void inicializarContas() {
    int i;
    for (i = 0; i < NUM_CONTAS; i++)
        contasSaldos[i] = 0;
}

int debitar(int idConta, int valor) {
    atrasar();
    if (!contaExiste(idConta))
        return -1;
    if (contasSaldos[idConta - 1] < valor)
        return -1;
    atrasar();
    contasSaldos[idConta - 1] -= valor;
    return 0;
}

int creditar(int idConta, int valor) {
    atrasar();
    if (!contaExiste(idConta))
        return -1;
    contasSaldos[idConta - 1] += valor;
    return 0;
}

int lerSaldo(int idConta) {
    atrasar();
    if (!contaExiste(idConta))
        return -1;
    return contasSaldos[idConta - 1];
}

int simular(int numAnos) {
    int i, j, aux;

    printf("SIMULACAO: Ano 0\n=================\n");
    atrasar();
    //copia os saldos para o aux e imprime
    for (i = 0; i < NUM_CONTAS; i++) {
        aux = contasSaldosAux[i] = contasSaldos[i];
        printf("Conta %d, Saldo %d\n", i+1, aux);
        atrasar();
    } printf("\n");
    //
    for (i = 1; i <= numAnos && stopFlag != 1; i++) {
        printf("SIMULACAO: Ano %d\n=================\n", i);
        atrasar();

        for (j = 0; j < NUM_CONTAS; j++) {
            aux = contasSaldosAux[j] * (1 + TAXAJURO) - CUSTOMANUTENCAO;
            if (aux > 0) contasSaldosAux[j] = aux;
            else contasSaldosAux[j] = aux = 0;
            printf("Conta %d, Saldo %d\n", j+1, aux);
            atrasar();
        } printf("\n");
    }
    return estado2;
}

//Rotina de tratamento do comando "sair agora"
void apanhaSairAgora(int sign) {
    if (signal(SIGUSR1, apanhaSairAgora) == SIG_ERR)
        perror("Erro na instalação do signal handler.");
    stopFlag = estado2 = 1;
}