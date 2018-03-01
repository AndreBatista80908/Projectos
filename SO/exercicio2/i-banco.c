// // // // // // // // // // // // // // // // // // //
//                                                    //
//               PROJETO SO - ENTREGA 2               //
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
#include <sys/types.h>
#include <sys/wait.h>

/*#define COMANDO_SIMULAR "simular"*/
#define COMANDO_DEBITAR "debitar"
#define COMANDO_CREDITAR "creditar"
#define COMANDO_LER_SALDO "lerSaldo"
#define COMANDO_SAIR "sair"
#define NUM_TRABALHADORAS 3
#define CMD_BUFFER_DIM (NUM_TRABALHADORAS * 2)
#define CMD_T_DEBITAR 0
#define CMD_T_CREDITAR 1
#define CMD_T_LERSALDO 2
#define CMD_T_SAIR 3

#define cons_out do {pthread_mutex_unlock(&trinco_cons); sem_post(&pode_prod);} while(0)

#define MAXARGS 3
#define BUFFER_SIZE 100

void apanhaAlarme(int sign);
void* consumidor(void*);
void produtor(int operacao, int idConta, int valor);

typedef struct {
    int operacao;
    int idConta;
    int valor;
} comando_t;


int buff_write_idx = 0, buff_read_idx = 0;

pthread_mutex_t trinco_cons;
pthread_t thr_pool[NUM_TRABALHADORAS];
sem_t pode_prod, pode_cons;
comando_t cmd_buffer[CMD_BUFFER_DIM];

int main(int argc, char** argv) {

    char *args[MAXARGS + 1], buffer[BUFFER_SIZE]/*, sEstado[13]*/;
    /*pid_t pid, pid2;*/

    sem_init(&pode_prod, 0, CMD_BUFFER_DIM);
    sem_init(&pode_cons, 0, 0);

    inicializarContas();

    //criação das tarefas trabalhadoras
    for (int i = 0; i < NUM_TRABALHADORAS; i++) {
        if (pthread_create(&thr_pool[i], NULL, consumidor, NULL)) {
            fprintf(stderr, "Erro ao criar a thread\n");
            exit(EXIT_FAILURE);
        }
    }

    printf("Bem-vinda/o ao i-banco\n\n");
      
    while (1) {
        int numargs;
    
        numargs = readLineArguments(args, MAXARGS+1, buffer, BUFFER_SIZE);

        //EOF (end of file) do stdin ou comando "sair"
        if (numargs < 0 || (numargs > 0 && (strcmp(args[0], COMANDO_SAIR) == 0))) {
            
            //cria comandos de saída
            for (int i = 0; i < NUM_TRABALHADORAS; i++) {
                
                produtor(CMD_T_SAIR, 0, 0);
                sem_post(&pode_cons);
            }

            //espera que todas as tarefas saiam
            for (int i = 0; i < NUM_TRABALHADORAS; i++) {
                if (pthread_join(thr_pool[i], NULL)) {
                    perror("Erro na terminação.");
                    exit(EXIT_FAILURE);
                }
            }

            printf("i-banco vai terminar\n--\n");
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

            produtor(CMD_T_DEBITAR, idConta, valor);
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

            produtor(CMD_T_CREDITAR, idConta, valor);
        }

        //Ler Saldo
        else if (strcmp(args[0], COMANDO_LER_SALDO) == 0) {
            int idConta;

            if (numargs != 2) {
                printf("%s: Sintaxe inválida, tente de novo.\n", COMANDO_LER_SALDO);
                continue;
            }
            idConta = atoi(args[1]);

            produtor(CMD_T_LERSALDO, idConta, 0);
        }
        
        //Comando inexistente
        else printf("Comando desconhecido. Tente de novo.\n");
    } 
}

void produtor(int operacao, int idConta, int valor) {
    sem_wait(&pode_prod);
    cmd_buffer[buff_write_idx].operacao = operacao;
    cmd_buffer[buff_write_idx].idConta = idConta;
    cmd_buffer[buff_write_idx].valor = valor;
    buff_write_idx = (buff_write_idx + 1) % CMD_BUFFER_DIM;
    sem_post(&pode_cons);
}

//Função das tarefas
void* consumidor(void* nada) {
    while (1) {
        int function_return;

        sem_wait(&pode_cons);
        pthread_mutex_lock(&trinco_cons);
        comando_t comando = cmd_buffer[buff_read_idx];
        buff_read_idx = (buff_read_idx + 1) % CMD_BUFFER_DIM;

        switch (comando.operacao) {

            case CMD_T_DEBITAR:
                function_return = debitar(comando.idConta, comando.valor);
                cons_out;
                if (function_return < 0)
                    printf("%s(%d, %d): Erro.\n\n", COMANDO_DEBITAR, comando.idConta, comando.valor);
                else
                    printf("%s(%d, %d): OK.\n\n", COMANDO_DEBITAR, comando.idConta, comando.valor);
                break;

            case CMD_T_CREDITAR:
                function_return = creditar(comando.idConta, comando.valor);
                cons_out;
                if (function_return < 0)
                    printf("%s(%d, %d): Erro.\n\n", COMANDO_CREDITAR, comando.idConta, comando.valor);
                else
                    printf("%s(%d, %d): OK.\n\n", COMANDO_CREDITAR, comando.idConta, comando.valor);
                break;

            case CMD_T_LERSALDO:
                function_return = lerSaldo(comando.idConta);
                cons_out;
                if (function_return < 0)
                    printf("%s(%d): Erro.\n\n", COMANDO_LER_SALDO, comando.idConta);
                else
                    printf("%s(%d): O saldo da conta é %d.\n\n", COMANDO_LER_SALDO, comando.idConta, function_return);
                break;

            case CMD_T_SAIR:
                cons_out;
                pthread_exit(NULL);
        }
    }
}