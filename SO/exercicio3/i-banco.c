// // // // // // // // // // // // // // // // // // //
//                                                    //
//               PROJETO SO - ENTREGA 3               //
//                                                    //
//                André Batista, 80908                //
//                Filipe Colaço, 84715                //
//                      Grupo 71                      //
//                (sexta-feira, 14h00)                //
//                                                    //
//                     Baseado em                     //
//         Projeto SO- exercicio 1, version 1         //
//    Sistemas Operativos, DEI/IST/ULisboa 2016-17    //
//                                                    //
// // // // // // // // // // // // // // // // // // //

#include "commandlinereader.h"
#include "contas.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

#define COMANDO_DEBITAR "debitar"
#define COMANDO_CREDITAR "creditar"
#define COMANDO_LER_SALDO "lerSaldo"
#define COMANDO_TRANSFERIR "transferir"
#define COMANDO_SIMULAR "simular"
#define COMANDO_SAIR "sair"
#define CMD_T_DEBITAR 0
#define CMD_T_CREDITAR 1
#define CMD_T_LERSALDO 2
#define CMD_T_TRANSFERIR 3
#define CMD_T_SAIR 4
#define NUM_TRABALHADORAS 3
#define CMD_BUFFER_DIM (NUM_TRABALHADORAS * 2)

#define MAXARGS 4
#define BUFFER_SIZE 100

void produtor(int operacao, int idContaOrigem, int idContaDestin, int valor);
void* consumidor(void*);
void wait_pode_cons();
void post_pode_cons();
void wait_pode_prod();
void post_pode_prod();
void lock_buffer();
void unlock_buffer();
void lock_no2();
void unlock_no2();

typedef struct {
    int operacao;
    int idContaOrigem;
    int idContaDestin;
    int valor;
} comando_t;

int estado, nFilhos = 0;
int buff_write_idx = 0, buff_read_idx = 0;
int nComandos = 0;
int errno, rc;

pthread_mutex_t trinco_cons, trinco_no2;
pthread_cond_t condicao;
pthread_t thr_pool[NUM_TRABALHADORAS];

sem_t pode_prod, pode_cons;
comando_t cmd_buffer[CMD_BUFFER_DIM];

int main(int argc, char** argv) {

    char *args[MAXARGS + 1], buffer[BUFFER_SIZE], sEstado[13];
    pid_t pid, pid2;

    //inicialização dos semáforos
    if (sem_init(&pode_prod, 0, CMD_BUFFER_DIM)) {
        perror("Erro na inicialização do semáforo \"pode_prod\".");
        exit(EXIT_FAILURE);
    }
    if (sem_init(&pode_cons, 0, 0)) {
        perror("Erro na inicialização do semáforo \"pode_cons\".");
        exit(EXIT_FAILURE);
    }

    //inicialização de mutex e variável de condição (devolvem sempre 0)
    pthread_mutex_init(&trinco_cons, NULL);
    pthread_cond_init(&condicao, NULL);

    inicializarContas();

    //arma os signals de interrupção de simulação e alarme
    if (signal(SIGUSR1, apanhaSairAgora) == SIG_ERR) {
        perror("Erro na instalação dos signal handlers.");
        exit(EXIT_FAILURE);
    }

    //criação das tarefas trabalhadoras
    for (int i = 0; i < NUM_TRABALHADORAS; i++) {
        if (pthread_create(&thr_pool[i], NULL, consumidor, NULL)) {
            fprintf(stderr, "Erro ao criar a thread.");
            exit(EXIT_FAILURE);
        }
    }

    printf("Bem-vinda/o ao i-banco\n\n");
      
    while (1) {
        int numargs;
    
        numargs = readLineArguments(args, MAXARGS+1, buffer, BUFFER_SIZE);

        //EOF (end of file) do stdin ou comando sair
        if (numargs < 0 || (numargs > 0 && (strcmp(args[0], COMANDO_SAIR) == 0))) {
            //Sair agora
            if (numargs > 1) {
                if (strcmp(args[1], "agora") == 0) {
                    if (kill(0, SIGUSR1) < 0) {
                        perror("Erro na terminação.");
                        exit(EXIT_FAILURE);
                    }
                }
                else {
                    printf("%s: Sintaxe inválida, tente de novo.\n\n", COMANDO_SAIR);
                    continue;
                }
            }

            //cria comandos de saída para as tarefas
            for (int i = 0; i < NUM_TRABALHADORAS; i++)
                produtor(CMD_T_SAIR, 0, 0, 0);

            //espera que todas as tarefas saiam
            for (int i = 0; i < NUM_TRABALHADORAS; i++) {
                if (pthread_join(thr_pool[i], NULL)) {
                    perror("Erro na terminação.");
                    exit(EXIT_FAILURE);
                }
            }

            //terminação sincronizada de processos
            for (printf("i-banco vai terminar\n--\n"); nFilhos > 0; nFilhos--) {
                if ((pid2 = wait(&estado)) < 0) {
                    perror("Erro na terminação.");
                    exit(EXIT_FAILURE);
                }
                if (WIFEXITED(estado)) strcpy(sEstado, "normalmente");
                else strcpy(sEstado, "abruptamente");
                printf("FILHO TERMINADO (PID=%d; terminou %s)\n", pid2, sEstado);
            }
            printf("--\ni-banco terminou\n");

            exit(EXIT_SUCCESS);
        }

        //nenhum argumento; ignora e volta a pedir
        else if (numargs == 0) continue;
            
        //debitar
        else if (strcmp(args[0], COMANDO_DEBITAR) == 0) {
            if (numargs < 3) {
                printf("%s: Sintaxe inválida, tente de novo.\n\n", COMANDO_DEBITAR);
                continue;
            }

            produtor(CMD_T_DEBITAR, atoi(args[1]), 0, atoi(args[2]));
        }

        //creditar
        else if (strcmp(args[0], COMANDO_CREDITAR) == 0) {
            if (numargs < 3) {
                printf("%s: Sintaxe inválida, tente de novo.\n\n", COMANDO_CREDITAR);
                continue;
            }

            produtor(CMD_T_CREDITAR, atoi(args[1]), 0, atoi(args[2]));
        }

        //ler saldo
        else if (strcmp(args[0], COMANDO_LER_SALDO) == 0) {

            if (numargs != 2) {
                printf("%s: Sintaxe inválida, tente de novo.\n\n", COMANDO_LER_SALDO);
                continue;
            }

            produtor(CMD_T_LERSALDO, atoi(args[1]), 0, 0);
        }

        //transferir
        else if (strcmp(args[0], COMANDO_TRANSFERIR) == 0) {
            if (numargs < 4) {
                printf("%s: Sintaxe inválida, tente de novo.\n\n", COMANDO_TRANSFERIR);
                continue;
            }

            produtor(CMD_T_TRANSFERIR, atoi(args[1]), atoi(args[2]), atoi(args[3]));
        }

        //simular
        else if (strcmp(args[0], COMANDO_SIMULAR) == 0) {
            int numAnos;

            if (numargs < 2) {
                printf("%s: Sintaxe inválida, tente de novo.\n\n", COMANDO_SIMULAR);
                continue;
            }

            numAnos = atoi(args[1]);
            if (numAnos < 0) {
                printf("%s(%d): Erro.\n\n", COMANDO_SIMULAR, numAnos);
                continue;
            }

            //espera que as tarefas terminem
            lock_no2();
            while (nComandos) pthread_cond_wait(&condicao, &trinco_no2);
            unlock_no2();

            //faz fork e vê se foi sucedido
            if ((pid = fork()) < 0) {
                perror("Erro na criacao do processo, tente de novo.\n\n");
                continue;
            }
            //processo-filho
            if (pid == 0) {
                simular(numAnos);
                exit(EXIT_SUCCESS);
            }
            //processo-pai: adiciona aos contadores de filhos
            else nFilhos++;
        }

        //comando inexistente
        else printf("Comando desconhecido. Tente de novo.\n\n");
    } 
}

//função produtora
void produtor(int operacao, int idContaOrigem, int idContaDestin, int valor) {
    wait_pode_prod();
    cmd_buffer[buff_write_idx].operacao = operacao;
    cmd_buffer[buff_write_idx].idContaOrigem = idContaOrigem;
    cmd_buffer[buff_write_idx].idContaDestin = idContaDestin;
    cmd_buffer[buff_write_idx].valor = valor;
    buff_write_idx = (buff_write_idx + 1) % CMD_BUFFER_DIM;
    nComandos++;
    post_pode_cons();
}

//função das tarefas
void* consumidor(void* nada) {
    while (1) {
        int function_return;

        wait_pode_cons();
        lock_buffer();
        comando_t comando = cmd_buffer[buff_read_idx];
        buff_read_idx = (buff_read_idx + 1) % CMD_BUFFER_DIM;

        switch (comando.operacao) {

            case CMD_T_DEBITAR:
                function_return = debitar(comando.idContaOrigem, comando.valor);
                unlock_buffer(); post_pode_prod();
                if (function_return < 0)
                    printf("%s(%d, %d): Erro.\n\n", COMANDO_DEBITAR, comando.idContaOrigem, comando.valor);
                else
                    printf("%s(%d, %d): OK.\n\n", COMANDO_DEBITAR, comando.idContaOrigem, comando.valor);
                break;

            case CMD_T_CREDITAR:
                function_return = creditar(comando.idContaOrigem, comando.valor);
                unlock_buffer(); post_pode_prod();
                if (function_return < 0)
                    printf("%s(%d, %d): Erro.\n\n", COMANDO_CREDITAR, comando.idContaOrigem, comando.valor);
                else
                    printf("%s(%d, %d): OK.\n\n", COMANDO_CREDITAR, comando.idContaOrigem, comando.valor);
                break;

            case CMD_T_LERSALDO:
                function_return = lerSaldo(comando.idContaOrigem);
                unlock_buffer(); post_pode_prod();
                if (function_return < 0)
                    printf("%s(%d): Erro.\n\n", COMANDO_LER_SALDO, comando.idContaOrigem);
                else
                    printf("%s(%d): O saldo da conta é %d.\n\n", COMANDO_LER_SALDO, comando.idContaOrigem, function_return);
                break;

            case CMD_T_TRANSFERIR:
                function_return = transferir(comando.idContaOrigem, comando.idContaDestin, comando.valor);
                unlock_buffer(); post_pode_prod();
                if (function_return < 0)
                    printf("%s(%d, %d, %d): Erro ao transferir valor da conta %d para a conta %d.\n\n",
                        COMANDO_TRANSFERIR, comando.idContaOrigem, comando.idContaDestin, comando.valor,
                        comando.idContaOrigem, comando.idContaDestin);
                else
                    printf("%s(%d, %d, %d): OK.\n\n",
                        COMANDO_TRANSFERIR, comando.idContaOrigem, comando.idContaDestin, comando.valor);
                break;

            case CMD_T_SAIR:
                unlock_buffer(); post_pode_prod();
                pthread_exit(NULL);
        }
        lock_no2();
        pthread_cond_signal(&condicao);
        nComandos--;
        unlock_no2();
    }
}

void wait_pode_cons() {
    while (sem_wait(&pode_cons)) {
        if (errno == EINTR) continue;
        perror("Erro no wait do semáforo \"pode_cons\".");
        exit(EXIT_FAILURE);
    }
}

void post_pode_cons() {
    if (sem_post(&pode_cons)) {
        perror("Erro no post do semáforo \"pode_cons\".");
        exit(EXIT_FAILURE);
    }
}

void wait_pode_prod() {
    while (sem_wait(&pode_prod)) {
        if (errno == EINTR) continue;
        perror("Erro no wait do semáforo \"pode_prod\".");
        exit(EXIT_FAILURE);
    }
}

void post_pode_prod() {
    if (sem_post(&pode_prod)) {
        perror("Erro no post do semáforo \"pode_prod\".");
        exit(EXIT_FAILURE);
    }
}

void lock_buffer() {
    if ((rc = pthread_mutex_lock(&trinco_cons))) {
        errno = rc;
        perror("Error in pthread_mutex_lock");
        exit(EXIT_FAILURE);
    }
}

void unlock_buffer() {
    if ((rc = pthread_mutex_unlock(&trinco_cons))) {
        errno = rc;
        perror("Error in pthread_mutex_unlock");
        exit(EXIT_FAILURE);
    }
}

void lock_no2() {
    if ((rc = pthread_mutex_lock(&trinco_no2))) {
        errno = rc;
        perror("Error in pthread_mutex_lock");
        exit(EXIT_FAILURE);
    }
}

void unlock_no2() {
    if ((rc = pthread_mutex_unlock(&trinco_no2))) {
        errno = rc;
        perror("Error in pthread_mutex_unlock");
        exit(EXIT_FAILURE);
    }
}