//cadastroUsuariosV2.h
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>


using namespace std;

typedef struct{
	char nome[30];
	char CPF[12];
	char RG[8];
	char Endereco [100];
}Usuario;

void cadastrarUsuario(int len, Usuario* ptrUsuario); // registra 4 inputs de char da struct, usar gets();
void printarUsuarios(int len, Usuario* ptrUsuario);   // printa os usuarios na tela, mensagem de erro se len=0
//void removerUsuario(int len, Usuario* ptrUsuario);   // remove o ultimo usuario, realloc pra len-1
/* removerUsuario foi removido pois a alocacao de memoria por funcoes nao funcionava, resolvi fazer as
alocacoes na main */
void gravarArquivo(int len, Usuario* ptrUsuario); // grava os usuarios registrados na execucao em um arquivo txt
int findLineAmount(int len);
void carregarDatabase(int len, Usuario *ptrUsuario);

/* -- Carregar Base de Dados
1) Encontrar quantas linhas há no arquivo para saber o tamanho do malloc
2) Necessario pois minhas alocacoes não têm funcionado dentro de funções, apenas na main
3) Ao encontrar a quantidade de linhas do arquivos com findLineAmount(), passarei a mesma/4 para o len da main (por return)
4) Inicializar o malloc no case 5 (main) e puxar a função carregarDatabase()
5) Tentei diversas soluções antes de tomar esta decisão, mas alocar memória na main foi a única que funcionou.
*/
