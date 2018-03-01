/*
// Operações sobre contas, versao 1
// Sistemas Operativos, DEI/IST/ULisboa 2016-17
*/

#ifndef CONTAS_H
#define CONTAS_H

#define NUM_CONTAS 10
#define TAXAJURO 0.1
#define CUSTOMANUTENCAO 1

#define ATRASO 500000 //microsegundos (meio-segundo)

void inicializarContas();
int contaExiste(int idConta);
int debitarCore(int idConta, int valor);
int debitar(int idConta, int valor);
void creditarCore(int idConta, int valor);
int creditar(int idConta, int valor);
int lerSaldo(int idConta);
int transferir(int idContaOrigem, int idContaDestin, int valor);
int simular(int numAnos);
void apanhaSairAgora(int sign);
void lock_conta(int idConta);
void unlock_conta(int idConta);

#endif