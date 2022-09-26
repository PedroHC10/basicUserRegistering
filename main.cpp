#include"cadastroUsuariosV2.h"

void menuPrincipal()
{
	printf("\n**********BEM VINDO!**********\n");
	printf("Qual operacao deseja realizar?\n\n");
	printf("1 - Cadastrar novo usuario\n");
	printf("2 - Exibir usuarios cadastrados\n");
	printf("3 - Exibir quantidade de usuarios cadastrados\n");
	printf("4 - Remover ultimo usuario cadastrado\n");
	printf("5 - Carregar base de dados da ultima execucao\n");
	printf("6 - Sair\n");
}

int main(int argc, char** argv) {
	
	int opcaoMenu, len = 0; //len sera o tamanho do vetor
	Usuario* vetor; // instanciando um ponteiro para o vetor de Usuario
	
	do
	{
		menuPrincipal();
		scanf("%d",&opcaoMenu);
		fflush(stdin); // garantia pra nao bugar as leituras com gets
		
		switch(opcaoMenu)
		{
			case 1:
				//cadastrar Usuario
				len++;
				if (len == 1)
				{
					vetor =(Usuario*) malloc(sizeof(Usuario)); // aloque para vetor, (usuario) bytes 
					//de memoria no endereco x
					// alocar memoria na funcao estava dando errado, na main funciona normalmente.
				}
					else
				    {
						vetor =(Usuario*) realloc(vetor, len * sizeof(Usuario));
						//realoque pra tamanho + 1 * (sizeof(Usuario))
					}
				cadastrarUsuario(len, vetor);
				break;
			
			case 2:
				//printar Usuarios
				printarUsuarios(len, vetor);
				break;
				
			case 3:
				//exibir len
				printf("\n\nQuantidade de Usuarios Cadastrados: %d\n\n",len);
				break;
				
			case 4:
				//remover ultimo Usuario
				if (len < 1)
				{
					printf("\n\nNAO HA USUARIOS CADASTRADOS!\n\n");
				}
					else
					{
						vetor = (Usuario*) realloc(vetor, (len-1) * sizeof(Usuario));
						printf("\nUSUARIO REMOVIDO!\n\n");
						len--;
					}
				// fiz na main pois manipular memoria por funcao nao funcionava. 
				break;
				
			case 5: 
				if (len == 0)
				{
					//carregar database
					len = findLineAmount(len); 
					// Descobri o len do arquivo, agora aloco:
					vetor = (Usuario*) malloc(len * sizeof(Usuario));
					
					//carregando a base de dados do arquivo no vetor dinâmico:
					carregarDatabase(len, vetor);
				}
					else
					{
						printf("\n\nSo e possivel carregar um arquivo quando nao ha usuarios cadastrados.\n");
						printf("Remova os usuarios cadastrados ou tente novamente em outra execucao.");
						// decisao tomada devido a quantidade de mudancas necessarias para fazer um realloc
						
					}
				break; 
				
			default:
				continue;
		}
		
	} while(opcaoMenu >0 && opcaoMenu < 6);
	
	gravarArquivo(len, vetor);
	free(vetor);
	return(0);
}
