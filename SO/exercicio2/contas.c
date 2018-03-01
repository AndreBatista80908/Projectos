#include "contas.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>
#include <sys/types.h>

#define atrasar() usleep(ATRASO)

pthread_mutex_t trinco_contas[NUM_CONTAS];

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
    /*atrasar();*/
    if (!contaExiste(idConta))
        return -1;

    pthread_mutex_lock(&trinco_contas[idConta]);
    if (contasSaldos[idConta - 1] < valor) {
        pthread_mutex_unlock(&trinco_contas[idConta]);
        return -1;
    }
    /*atrasar();*/
    contasSaldos[idConta - 1] -= valor;
    pthread_mutex_unlock(&trinco_contas[idConta]);

    return 0;
}

int creditar(int idConta, int valor) {
    /*atrasar();*/
    if (!contaExiste(idConta))
        return -1;

    pthread_mutex_lock(&trinco_contas[idConta]);
    contasSaldos[idConta - 1] += valor;
    pthread_mutex_unlock(&trinco_contas[idConta]);

    return 0;
}

int lerSaldo(int idConta) {
    /*atrasar();*/
    if (!contaExiste(idConta))
        return -1;

    pthread_mutex_lock(&trinco_contas[idConta]);
    int saldo = contasSaldos[idConta - 1];
    pthread_mutex_unlock(&trinco_contas[idConta]);

    return saldo;
}