#include "commandlinereader.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

#define COMANDO_DEBITAR "debitar"
#define COMANDO_CREDITAR "creditar"
#define COMANDO_LER_SALDO "lerSaldo"
#define COMANDO_TRANSFERIR "transferir"
#define COMANDO_SIMULAR "simular"
#define COMANDO_SAIR "sair"
#define COMANDO_STERMINAL "sair-terminal"
#define CMD_T_DEBITAR 0
#define CMD_T_CREDITAR 1
#define CMD_T_LERSALDO 2
#define CMD_T_TRANSFERIR 3
#define CMD_T_SIMULAR 4
#define CMD_T_SAIR 5

#define MAXARGS 4
#define BUFFER_SIZE 100

typedef struct {
    int operacao;
    int idContaOrigem;
    int idContaDestin;
    int valor;
    pid_t pid; //terminal que vai receber o output
} comando_t;

void produtor(int operacao, int idContaOrigem, int idContaDestin, int valor);

int errno, pipe1, pipe2;

int main(int argc, char** argv) {
    char *args[MAXARGS + 1], buffer[BUFFER_SIZE];
    char pipeName[BUFFER_SIZE];

    sprintf(pipeName, "pipe-terminal-%d", (unsigned)getpid());
    unlink(pipeName);
    if ((pipe1 = mkfifo(pipeName, O_RDWR | S_IWGRP)) < 0) {
        perror("Erro ao criar pipe");
        exit(EXIT_FAILURE);
    }

    //pipe de comunicação de 
    pipe1 = open(pipeName, O_RDONLY);
    
    while (1) {
        int numargs = readLineArguments(args, MAXARGS+1, buffer, BUFFER_SIZE);

        pipe2 = open(argv[1], O_WRONLY);

        //EOF (end of file) do stdin ou comando sair
        if (numargs < 0 || (numargs > 0 && (strcmp(args[0], COMANDO_SAIR) == 0))) {
            //Sair agora
            if (numargs > 1) {
                if (strcmp(args[1], "agora") == 0) {
                    produtor(CMD_T_SAIR, 0, 0, 1);
                    continue;
                }
                else {
                    printf("%s: Sintaxe inválida, tente de novo\n\n", COMANDO_SAIR);
                    continue;
                }
            }

            produtor(CMD_T_SAIR, 0, 0, 0);
        }

        //nenhum argumento; ignora e volta a pedir
        else if (numargs == 0) continue;

        //sair-terminal
        else if (strcmp(args[0], COMANDO_STERMINAL) == 0) {
            close(pipe2);
            exit(EXIT_SUCCESS);
        }
            
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

            produtor(CMD_T_SIMULAR, 0, 0, numAnos);
        }

        //comando inexistente
        else printf("Comando desconhecido. Tente de novo.\n\n");
    }

    return 0;
}

void produtor(int operacao, int idContaOrigem, int idContaDestin, int valor) {
    char buff[BUFFER_SIZE];
    comando_t comando;
    time_t timeSend, timeReturn;

    comando.operacao = operacao;
    comando.idContaOrigem = idContaOrigem;
    comando.idContaDestin = idContaDestin;
    comando.valor = valor;
    comando.pid = getpid();

    timeSend = time(NULL);
    if (write(pipe2, &comando, sizeof(comando_t)) < 0) {
        perror("Não foi encontrado servidor, a terminar");
        exit(EXIT_FAILURE);
    }
    if (!(operacao == CMD_T_SAIR || operacao == CMD_T_SIMULAR)) {
        while (read(pipe1, buff, sizeof(buff)) == 0);
        timeReturn = time(NULL);
        printf("%s\nTempo de execução: %fs\n", buff, difftime(timeSend, timeReturn));
    }

    close(pipe2);
}