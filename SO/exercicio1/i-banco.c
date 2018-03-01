// // // // // // // // // // // // // // // // // // //
//                                                    //
//               PROJETO SO - ENTREGA 1               //
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
#include <sys/types.h>
#include <sys/wait.h>

#define COMANDO_DEBITAR "debitar"
#define COMANDO_CREDITAR "creditar"
#define COMANDO_LER_SALDO "lerSaldo"
#define COMANDO_SIMULAR "simular"
#define COMANDO_SAIR "sair"

#define MAXARGS 3
#define BUFFER_SIZE 100

void apanhaAlarme(int sign);

//estado: guarda a terminação de cada filho
//alarmFlag: será usada para aguardar pela última simulação
//estadoSaida: recebe o return do simular(1) (terminou via interrupção/normalmente)
int estado, nFilhos = 0, alarmFlag = 0, estadoSaida;

int main(int argc, char** argv) {

    char *args[MAXARGS + 1], buffer[BUFFER_SIZE], sEstado[13];
    pid_t pid, pid2;
    inicializarContas();

    //Arma os signals de interrupção de simulação e alarme
    if (signal(SIGUSR1, apanhaSairAgora) == SIG_ERR ||
        signal(SIGALRM, apanhaAlarme) == SIG_ERR) {
        perror("Erro na instalação dos signal handlers.");
        exit(EXIT_FAILURE);
    }

    printf("Bem-vinda/o ao i-banco\n\n");
      
    while (1) {
        int numargs;
    
        numargs = readLineArguments(args, MAXARGS+1, buffer, BUFFER_SIZE);

        //EOF (end of file) do stdin ou comando "sair"
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
                    printf("%s: Sintaxe inválida, tente de novo.\n", COMANDO_SAIR);
                    continue;
                }
            }
            //espera que acabe a última simulação
            while (alarmFlag > 0);

            //Saída sincronizada
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

        //Nenhum argumento; ignora e volta a pedir
        else if (numargs == 0) continue;
            
        //Debitar
        else if (strcmp(args[0], COMANDO_DEBITAR) == 0) {
            int idConta, valor;
            if (numargs < 3) {
                printf("%s: Sintaxe inválida, tente de novo.\n", COMANDO_DEBITAR);
                continue;
            }

            idConta = atoi(args[1]);
            valor = atoi(args[2]);

            if (debitar (idConta, valor) < 0)
                printf("%s(%d, %d): Erro.\n\n", COMANDO_DEBITAR, idConta, valor);
            else
                printf("%s(%d, %d): OK\n\n", COMANDO_DEBITAR, idConta, valor);
        }

        //Creditar
        else if (strcmp(args[0], COMANDO_CREDITAR) == 0) {
            int idConta, valor;
            if (numargs < 3) {
                printf("%s: Sintaxe inválida, tente de novo.\n", COMANDO_CREDITAR);
                continue;
            }

            idConta = atoi(args[1]);
            valor = atoi(args[2]);

            if (creditar (idConta, valor) < 0)
                printf("%s(%d, %d): Erro\n\n", COMANDO_CREDITAR, idConta, valor);
            else
                printf("%s(%d, %d): OK\n\n", COMANDO_CREDITAR, idConta, valor);
        }

        //Ler Saldo
        else if (strcmp(args[0], COMANDO_LER_SALDO) == 0) {
            int idConta, saldo;

            if (numargs != 2) {
                printf("%s: Sintaxe inválida, tente de novo.\n", COMANDO_LER_SALDO);
                continue;
            }
            idConta = atoi(args[1]);
            saldo = lerSaldo (idConta);
            if (saldo < 0)
                printf("%s(%d): Erro.\n\n", COMANDO_LER_SALDO, idConta);
            else
                printf("%s(%d): O saldo da conta é %d.\n\n", COMANDO_LER_SALDO, idConta, saldo);
        }

        //Simular
        else if (strcmp(args[0], COMANDO_SIMULAR) == 0) {
            int numAnos;

            if (numargs < 2) {
                printf("%s: Sintaxe inválida, tente de novo.\n", COMANDO_SIMULAR);
                continue;
            }

            numAnos = atoi(args[1]);
            if (numAnos < 0) {
                printf("%s(%d): Erro.\n\n", COMANDO_SIMULAR, numAnos);
                continue;
            }
            //faz fork e vê se foi sucedido
            if ((pid = fork()) < 0) {
                perror("Erro na criacao do processo, tente de novo.\n");
                continue;
            }
            //processo-filho
            if (pid == 0) {
                estadoSaida = simular(numAnos);
                if (estadoSaida) printf("Simulacao terminada por signal\n");
                kill(0, SIGALRM);
                exit(EXIT_SUCCESS);
            }
            //processo-pai: adiciona aos contadores de filhos
            else {alarmFlag++; nFilhos++;}
        }
        //Comando inexistente
        else printf("Comando desconhecido. Tente de novo.\n");
    } 
}

//Signal handler para o fim de uma simulação
//  quando um filho termina, diminui o contador de filhos
void apanhaAlarme(int sign) {
    if (signal(SIGALRM, apanhaAlarme) == SIG_ERR)
        perror("Erro na instalação do signal handler.");
    alarmFlag--;
}