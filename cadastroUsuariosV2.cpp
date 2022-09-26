//cadastroUsuariosV2.cpp
#include"cadastroUsuariosV2.h"

void cadastrarUsuario(int len, Usuario* ptrUsuario)
{
		
	int x = len-1;
	
	//registrando os valores
	printf("Digite o nome do usuario: ");
	gets(ptrUsuario[x].nome);
	fflush(stdin);
	

	printf("Digite o CPF do usuario: ");
	gets(ptrUsuario[x].CPF);
	fflush(stdin);
	

	printf("Digite o RG do usuario: ");
	gets(ptrUsuario[x].RG);
	fflush(stdin);
	

	printf("Digite o Endereco do usuario: ");
	gets(ptrUsuario[x].Endereco);
	fflush(stdin);
}

void printarUsuarios(int len, Usuario* ptrUsuario)
{
	int i = 0;
	
	if (len < 1)
	{
		printf("\n\nNENHUM USUARIO CADASTRADO!\n\n");
	}
		else
		{
			for (i = 0 ; i < len; i++)
			{
				printf("\n\nUsuario %d: \n",i+1);
				printf("Nome: %s\n",ptrUsuario[i].nome);
				printf("CPF: %s\n",ptrUsuario[i].CPF);
				printf("RG: %s\n",ptrUsuario[i].RG);
				printf("Endereco: %s\n",ptrUsuario[i].Endereco);
			}
		}
}

/* void removerUsuario(int len, Usuario* ptrUsuario)
{
	if (len < 1)
	{
		printf("\n\nNAO HA USUARIOS CADASTRADOS!\n\n");
	}
		else
		{
			ptrUsuario = (Usuario*) realloc(ptrUsuario, (len-1) * sizeof(Usuario));
			printf("\nUSUARIO REMOVIDO!\n\n");
		}
} 
retirado pois a alocacao retornava erro, apesar de aparentemente dar certo, funcao transferida para main.
*/

void gravarArquivo(int len, Usuario* ptrUsuario)
{
	if (len < 1)  // caso nao haja usuarios, nao registrar nada no arquivo. 
	{
		printf("\n\nNENHUM USUARIO REGISTRADO NO ARQUIVO!\n");
	}
		else
		{
			FILE *arquivo; // declaracao do ponteiro de arquivo
	
			arquivo = fopen("userDatabase.txt","w"); // abertura do arquivo para escrita (w = write)
	
			if (arquivo == NULL)
				{
				printf("\n\nErro na abertura do arquivo!\n");
				}
					else
					{
						for (int i = 0 ; i < len; i++)
						{
							fprintf(arquivo, "%s\n",ptrUsuario[i].nome);
							fprintf(arquivo, "%s\n",ptrUsuario[i].CPF);
							fprintf(arquivo, "%s\n",ptrUsuario[i].RG);
							fprintf(arquivo, "%s\n",ptrUsuario[i].Endereco);
						}
					}
			fclose(arquivo);			
			
		}
}

int findLineAmount(int len)
{
	FILE* arquivo; 
	char stringFile[256][100]; // vetor de string que guardará cada linha do arquivo.
	// 100 = tamanho maximo da linha; 256 = maximo de linhas a ser lido
	int linha(0), i, j; // quantidade de linhas do arquivo, sera relevante na hora de alocar memoria
	
	arquivo = fopen("userDatabase.txt", "r");
	
	if(arquivo == NULL)
	{
		printf("\nERRO AO CARREGAR BASE DE DADOS!\n");
		printf("\nCertifique-se que voce tenha cadastrado usuarios na execucao anterior.\n");
		exit(1);
	}
	
	while (!feof(arquivo) && !ferror(arquivo)) // verificando fim do arquivo e erro na leitura
	{
		if(fgets(stringFile[linha], 100, arquivo) != NULL ) // 100 = tam maximo de uma linha (def. na struct)
			{
				linha++; // caso nao seja a ultima linha, incremente linha
			}
	}
	
	//fechando o arquivo
	fclose(arquivo);
	
	//retorne linha/4 para len (agora tenho o valor pra fazer o malloc na main)
	//Explicação: a struct possui 4 atributos, ao dividir as linhas do arquivo por 4 obtém-se a qtd de usuarios;
	return(linha/4);
}




void carregarDatabase(int len, Usuario *ptrUsuario)
{
	// Código reaproveitado da função findLineAmount(). Tentei chamar a função dentro dessa mas sem sucesso
	
	FILE* arquivo; 
	char stringFile[128][100]; // vetor de string que guardará cada linha do arquivo.
	// 100 = tamanho maximo da linha; 128 = maximo de linhas a ser lido
	int linha(0), i, j; // quantidade de linhas do arquivo, sera relevante na hora de alocar memoria
	
	arquivo = fopen("userDatabase.txt", "r");
	
	if(arquivo == NULL)
	{
		printf("\nERRO AO CARREGAR BASE DE DADOS!\n");
		exit(1);
	}
	

	while (!feof(arquivo) && !ferror(arquivo)) // verificando fim do arquivo e erro na leitura
	{
		if(fgets(stringFile[linha], 100, arquivo) != NULL ) // 100 = tam maximo de uma linha (def. na struct)
			{
				strtok(stringFile[linha], "\n"); // Eliminando a quebra de linha da string (IMPORTANTISSIMO)
				linha++; // caso nao seja a ultima linha, incremente linha
			}
	}
	
	fclose(arquivo);
	
	
	//carregando os nomes do arquivo no vetor
	j = 0;
	for(i = 0; i < linha; i +=4)
	{
		strcpy(ptrUsuario[j].nome, stringFile[i]); //j = 0
		j++; 
	}
		
	//carregando CPFS
	j = 0;
	for(i = 1; i < linha; i+=4)
	{
		strcpy(ptrUsuario[j].CPF, stringFile[i]);
		j++;
		
	}
		
	//carregando RGS
	j = 0; 
	for(i = 2; i < linha; i+=4)
	{
		strcpy(ptrUsuario[j].RG, stringFile[i]);
		j++;
	}
		
		
	//carregando Enderecos
	j = 0;
	for(i = 3; i < linha; i+=4)
	{
		strcpy(ptrUsuario[j].Endereco, stringFile[i]);
		j++;	
	}
	
	printf("\n\nDADOS CARREGADOS!\n\n");
	
}
