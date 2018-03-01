#include "contas.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>
#include <sys/types.h>
#include <errno.h>

#define atrasar() usleep(ATRASO)

int errno, rc;
pthread_mutex_t trinco_contas[NUM_CONTAS];

int contasSaldos[NUM_CONTAS],
    stopFlag = 0, estado2 = 0;

int contaExiste(int idConta) {
    return (idConta > 0 && idConta <= NUM_CONTAS);
}

void inicializarContas() {
    int i;
    for (i = 0; i < NUM_CONTAS; i++)
        contasSaldos[i] = 0;
}

int debitarCore(int idConta, int valor) {
    if (contasSaldos[idConta - 1] < valor)
        return -1;
    contasSaldos[idConta - 1] -= valor;
    return 0;
}

int debitar(int idConta, int valor) {
    int r;
    if (!contaExiste(idConta))
        return -1;

    lock_conta(idConta - 1);
    r = debitarCore(idConta, valor);
    unlock_conta(idConta - 1);

    return r;
}

void creditarCore(int idConta, int valor) {
    contasSaldos[idConta - 1] += valor;
}

int creditar(int idConta, int valor) {
    if (!contaExiste(idConta))
        return -1;
    lock_conta(idConta - 1);
    creditarCore(idConta, valor);
    unlock_conta(idConta - 1);

    return 0;
}

int lerSaldo(int idConta) {
    atrasar();
    if (!contaExiste(idConta))
        return -1;

    lock_conta(idConta - 1);
    int saldo = contasSaldos[idConta - 1];
    unlock_conta(idConta - 1);

    return saldo;
}

int transferir(int idContaOrigem, int idContaDestin, int valor) {
    if (!contaExiste(idContaOrigem) ||
        !contaExiste(idContaDestin) ||
        idContaOrigem == idContaDestin)
        return -1;

    if (idContaOrigem < idContaDestin) {
        lock_conta(idContaOrigem - 1);
        lock_conta(idContaDestin - 1);
    } else {
        lock_conta(idContaDestin - 1);
        lock_conta(idContaOrigem - 1);
    }
    if (debitarCore(idContaOrigem, valor) < 0) {
        unlock_conta(idContaOrigem - 1);
        unlock_conta(idContaDestin - 1);
        return -1;
    }
    creditarCore(idContaDestin, valor);
    unlock_conta(idContaOrigem - 1);
    unlock_conta(idContaDestin - 1);
    return 0;
}

int simular(int numAnos) {
    int i, j, saldo;
    atrasar();
    
    for (i = 0; i <= numAnos && stopFlag != 1; i++) {
        printf("SIMULAÇÃO: Ano %d\n=================\n", i);
        atrasar();

        for (j = 1; j <= NUM_CONTAS; j++) {
            if (i > 0) {
                saldo = lerSaldo(j);
                creditarCore(j, saldo * TAXAJURO);
                saldo = lerSaldo(j);
                debitarCore(j, (CUSTOMANUTENCAO > saldo) ? saldo : CUSTOMANUTENCAO);
            }
            saldo = lerSaldo(j);

            while (printf("Conta %5d,\t Saldo %10d\n", j, saldo) < 0) {
                if (errno == EINTR) continue;
                else break;
            }
        } printf("\n");
    }
    if (stopFlag == 1) printf("Simulação terminada por signal.\n\n");
    return 0;
}


//Rotina de tratamento do comando "sair agora"
void apanhaSairAgora(int sign) {
    if (signal(SIGUSR1, apanhaSairAgora) == SIG_ERR)
        perror("Erro na instalação do signal handler.");
    stopFlag = 1;
}

void lock_conta(int idConta) {
    if ((rc = pthread_mutex_lock(&trinco_contas[idConta]))) {
        errno = rc;
        perror("Erro no lock da conta.");
        exit(EXIT_FAILURE);
    }
}

void unlock_conta(int idConta) {
    if ((rc = pthread_mutex_unlock(&trinco_contas[idConta]))) {
        errno = rc;
        perror("Erro no unlock da conta.");
        exit(EXIT_FAILURE);
    }
}