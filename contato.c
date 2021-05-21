#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "agenda (1).h"
#include "contato.h"

Contato *lista_contatos = NULL;
int tam_lista_cont;

void carregar_lista()
{
	FILE *arq_cont;
	Contato contato;
	int i = 0;
	arq_cont = fopen("contatos.bin", "rb");
	if (arq_cont == NULL)
	{
		if (dbgmd)
			printf("Erro 101: Abertura de arquivo\n Variável: arq_cont\n Arquivo: contatos.bin\n Função: carregar_lista\n");

		tam_lista_cont = 0;
	}
	else
	{
		fseek(arq_cont, 0, SEEK_END);
		tam_lista_cont = ftell(arq_cont);
		rewind(arq_cont);
		lista_contatos = (Contato *)malloc(tam_lista_cont);
		tam_lista_cont = tam_lista_cont / sizeof(Contato);
		while (fread(&contato, sizeof(Contato), 1, arq_cont))
		{
			strcpy(lista_contatos[i].nome, contato.nome);
			strcpy(lista_contatos[i].telefone, contato.telefone);
			strcpy(lista_contatos[i].data_nasc, contato.data_nasc);
			strcpy(lista_contatos[i].email, contato.email);
			lista_contatos[i].id = contato.id;
			i++;
		}
		fclose(arq_cont);
	}
}

void salvar_lista_cont()
{
	FILE *arq_cont;
	int i;
	arq_cont = fopen("contatos.bin", "wb+");
	if (arq_cont == NULL)
	{
		if (dbgmd)
			printf("Erro 101: Abertura de arquivo\n Variável: arq_cont\n Arquivo: contatos.bin\n Função: salvar_lista_cont\n");
		exit(1);
	}
	else
	{
		for (i = 0; i < tam_lista_cont; i++)
			fwrite(&lista_contatos[i], sizeof(Contato), 1, arq_cont);
		fclose(arq_cont);
	}
}

void cadastrar_contato()
{
	char nome[TAM_STR_NOME];
	int indice_cont, id;

	id = gerar_id(); // Gera um id único para o contato
	/*
		Aloca ou realoca o vetor da lista de contatos para receber o novo contato a ser adicionado
		Verifica se o vetor foi corretamente alocado
	*/
	lista_contatos = (Contato *)realloc(lista_contatos, (tam_lista_cont + 1) * sizeof(Contato));
	if (lista_contatos == NULL)
	{
		if (dbgmd)
			printf("Erro 100: Alocação dinâmica de memória\nVariável: vect\nFunção: cadastrar_contato()\n");
		exit(1);
	}
	/* 
		Usuário entra com os dados do novo contato
			-> Função getchar usada para consumir o '/n' do buffer da entrada scanf 
	*/
	printf("CADASTRAR CONTATO\n");
	printf("Nome:\n");
	scanf("%[^\n]", lista_contatos[tam_lista_cont].nome);
	getchar();
	printf("Telefone:\n");
	limpar_str(lista_contatos[tam_lista_cont].telefone, TAM_STR_TEL);
	scanf("%[^\n]", lista_contatos[tam_lista_cont].telefone);
	getchar();
	printf("Data de Nascimento:\n");
	limpar_str(lista_contatos[tam_lista_cont].data_nasc, TAM_STR_DATA_NASC);
	scanf("%[^\n]", lista_contatos[tam_lista_cont].data_nasc);
	getchar();
	printf("E-mail:\n");
	limpar_str(lista_contatos[tam_lista_cont].email, TAM_STR_EMAIL);
	scanf("%[^\n]", lista_contatos[tam_lista_cont].email);
	getchar();
	lista_contatos[tam_lista_cont].id = id;
	/* 
		Atualiza o tamanho da lista de contatos
		Salva a lista de contatos atualizada no arquivo
	*/
	tam_lista_cont++;
	salvar_lista_cont();
}

void mostrar_contatos(int *vect, char *nome_menu)
{
	int i, j, option, indice_cont = -1, pos_saida, opcao_menu_edicao, indice_cont_lista, excluido;
	char *str = (char *)calloc(256, sizeof(char));
	Menu *menu_contatos = NULL, *menu_opcoes_cont = NULL;

	/**
	 * Gera strings com todas as informações dos contatos que estão no vetor vect.
	 * Concatena as strings com as informações de nome  telefone, data de nascimento e e-mail em uma string só.
	 * Adiciona essas strings a um menu menu_contatos, que será utilizado para mostrar e selecionar um contato para editar.
	 */
	j = 0;
	for (i = 0; i < tam_lista_cont; i++)
	{
		if (lista_contatos[i].id == vect[j])
		{
			str_dados_contato(str, 90, lista_contatos[i]);
			menu_contatos = addOption(menu_contatos, str);
			j++;
		}
	}

	/**
	 * Adiciona a opção de retornar ao menu menu_contatos, que exibirá os contatos e os tratará como opções escolhíveis
	 * Gera um menu para edição dos contatos, com as opções de editar e excluir.
	 */
	menu_contatos = addOption(menu_contatos, "Retornar");
	menu_opcoes_cont = menu_gen(3, "Editar", "Excluir", "Retornar");
	pos_saida = pos_option(menu_contatos, "Retornar");
	/**
	 * Implementa o loop que mostra o menu.
	 * A função show_menu retorna o indice do contato selecionado na matriz de strings do menu ou da opção retornar.
	 */
	while (indice_cont != pos_saida)
	{
		indice_cont = show_menu(nome_menu, menu_contatos, NULL, dbgmd);
		if (indice_cont != pos_saida)
		{
			/**
			 * Implementa o loop que mostra o menu de opções para manipulação do contato.
			 */
			while (opcao_menu_edicao != 2 && opcao_menu_edicao != 1)
			{
				opcao_menu_edicao = show_menu(menu_contatos->option_mat[indice_cont], menu_opcoes_cont, NULL, dbgmd);
				indice_cont_lista = busca_id_lista_cont_principal(vect[indice_cont]);
				if (opcao_menu_edicao == 0)
				{
					editar_contato(vect[indice_cont]);
					limpar_str(menu_contatos->option_mat[indice_cont], STRING_LENGTH);
					str_dados_contato(str, 256, lista_contatos[indice_cont_lista]);
					strcpy(menu_contatos->option_mat[indice_cont], str);
				}
				if (opcao_menu_edicao == 1)
				{
					excluir_contato(indice_cont_lista);
					removeOption(menu_contatos, indice_cont);
					pos_saida = pos_option(menu_contatos, "Retornar");
				}
			}
		}
	}

	free_menu(menu_contatos);
	free_menu(menu_opcoes_cont);
	free(str);
}

void mostrar_todos_contatos()
{
	/**
	 *  Procedimento que mostra todos os contatos cadastrados na lista de contatos
	 */

	int i, *vect = (int *)malloc(tam_lista_cont * sizeof(int));

	if (vect == NULL)
	{
		if (dbgmd)
			printf("Erro 100: Alocação dinâmica de memória\nVariável: vect\nFunção:mostrar_todos_contatos\n");
		exit(1);
	}

	for (i = 0; i < tam_lista_cont; i++)
		vect[i] = lista_contatos[i].id;

	mostrar_contatos(vect, "CONTATOS");

	free(vect);
}

void pesquisar_contato()
{
	/**
	 * Função que implementa a tela de pesquisa de contatos.
	 */

	char nome_buscado[TAM_STR_NOME];
	int i, encontrado = 0, *vect;

	printf("Digite o nome do contato que deseja encontrar:\n");
	scanf("%[^\n]", nome_buscado);
	vect = busca_lista_cont_semelhantes(nome_buscado, &encontrado);
	if (encontrado)
		mostrar_contatos(vect, "CONTATOS ENCONTRADOS");
	else
		printf("Nenhum contato foi encontrado\n");

	free(vect);
}

void editar_contato(int id)
{
	/** 
	 * Função que implementa a edição de um contato a partir do id dele.
	 * Encontra o contato na lista e mostra o menu de campos para que o usuário escolha qual editar.
	 */

	int indice = 0, opcao;
	Menu *menu_edicao;

	indice = busca_id_lista_cont_principal(id);

	if (indice != -1)
	{
		menu_edicao = menu_gen(4, "Nome", "Telefone", "E-mail", "Voltar");

		while (opcao != 3)
		{
			opcao = show_menu("EDITAR CONTATO", menu_edicao, NULL, dbgmd);

			if (opcao == 0)
			{
				limpar_str(lista_contatos[indice].nome, TAM_STR_NOME);

				printf("Digite o novo nome:\n");
				scanf("%[^\n]", lista_contatos[indice].nome);
				getchar();
			}
			if (opcao == 1)
			{
				limpar_str(lista_contatos[indice].telefone, TAM_STR_TEL);

				printf("Digite o novo telefone:\n");
				scanf("%[^\n]", lista_contatos[indice].telefone);
				getchar();
			}
			if (opcao == 2)
			{
				limpar_str(lista_contatos[indice].email, TAM_STR_EMAIL);

				printf("Digite o novo email:\n");
				scanf("%[^\n]", lista_contatos[indice].email);
				getchar();
			}

			salvar_lista_cont();
		}
	}

	free_menu(menu_edicao);
}

int *busca_lista_cont_semelhantes(char *nome_buscado, int *encontrado)
{
	/**
	 * Busca os contatos que tem o nome com uma determinada % de semelhança ao da string nome_buscado.
	 * Os contatos que forem semelhantes têm seus ids adicionados ao vetor vect que será retornado.
	 */

	int i, tam_lista = 1, *vect = NULL, j;
	double semelhanca;

	Contato *lista_cont_encontrado = NULL;
	j = 0;
	for (i = 0; i < tam_lista_cont; i++)
	{
		semelhanca = compara_nome(nome_buscado, lista_contatos[i].nome);
		if (semelhanca >= PORCENTAGEM_SEMELHANCA)
		{
			*encontrado = *encontrado + 1;
			vect = (int *)realloc(vect, *encontrado * sizeof(int));
			if (vect == NULL)
			{
				if (dbgmd)
					printf("Erro 100: Alocação dinâmica de memória\nVariável: vect\nFunção: busca_lista_cont_semelhantes\n");
				exit(1);
			}
			vect[j] = lista_contatos[i].id;
			j++;
		}
	}

	return vect;
}

int busca_id_lista_cont_principal(int id)
{
	/**
	 * Busca na lista de contatos aquele ao qual o id é o mesmo do id passado por parâmetro.
	 * Retorna o índice do contato caso o id exista.
	 */

	int i = -1;

	for (i = 0; i < tam_lista_cont; i++)
	{
		if (lista_contatos[i].id == id)
			return i;
	}

	return -1;
}

char *str_dados_contato(char *str, int tamanho_str, Contato contato)
{
	/**
	 * Função auxiliar para concatenar os dados de nome, data de nascimento, telefone e e-mail em 
	 * uma só string e retornar para mostrar_contatos utilizar no menu de contatos.
	 */

	char str_aux[90];

	limpar_str(str, tamanho_str);

	strcpy(str_aux, contato.nome);
	strcat(str_aux, " ");
	strcpy(str, str_aux);
	limpar_str(str_aux, 90);
	strcpy(str_aux, contato.telefone);
	strcat(str_aux, " ");
	strcat(str, str_aux);
	limpar_str(str_aux, 90);
	strcpy(str_aux, contato.data_nasc);
	strcat(str_aux, " ");
	strcat(str, str_aux);
	limpar_str(str_aux, 90);
	strcpy(str_aux, contato.email);
	strcat(str_aux, " ");
	strcat(str, str_aux);

	return str;
}

double compara_nome(char *nome_1, char *nome_2)
{
	/**
	 * Função auxiliar que compara duas strings e retorna um índice em % de semelhança entre elas para busca_lista_cont_semelhantes.
	 */
	double cont = 0, indice_sem;
	int i = 0, tam_nome_2;

	while (((nome_1[i] == nome_2[i]) || ((nome_1[i] + 32) == nome_2[i]) || (nome_1[i] == (nome_2[i] + 32))) && nome_1[i] != '\0' && nome_2[i] != '\0')
	{
		cont++;
		i++;
	}
	tam_nome_2 = strlen(nome_2);

	indice_sem = (double)(cont / tam_nome_2);

	return indice_sem;
}

int gerar_id()
{

	/**
	 * Função auxiliar que abre o arquivo de id (cria, caso não exista), lê o último id criado, incrementa e retorna o novo
	 * id para a função cadastrar_contato.
	 */
	int id_lido, novo_id = 0;
	FILE *fptr = fopen("id.bin", "rb+");
	if (fptr == NULL)
	{
		fptr = fopen("id.bin", "wb");
	}
	else
	{
		fread(&id_lido, sizeof(int), 1, fptr);
		novo_id = id_lido + 1;
		rewind(fptr);
	}

	fwrite(&novo_id, sizeof(int), 1, fptr);

	fclose(fptr);

	return novo_id;
}

void limpar_str(char *str, int tamanho)
{
	/**
	 * Função auxiliar que limpa strings para que não seja exibido lixo de memória
	 */

	int i;

	for (i = 0; i < tamanho; i++)
		str[i] = 0;
}

void excluir_contato(int indice)
{
	/**
	 * Função que exclui um contato na lista de contatos.
	 * Sobrepõe o contato a ser excluído com os contatos seguintes, realoca diminuindo o tamanho do 
	 * vetor e atualiza o novo tamanho do vetor.
	 */

	int i;
	Menu *menu;

	for (i = indice; i < tam_lista_cont; i++)
	{
		if (i != (tam_lista_cont - 1))
			lista_contatos[i] = lista_contatos[i + 1];
	}

	lista_contatos = realloc(lista_contatos, ((tam_lista_cont - 1) * sizeof(Contato)));
	tam_lista_cont--;
	if (lista_contatos == NULL && tam_lista_cont > 0)
	{
		if (dbgmd)
			printf("Erro 100: Alocação dinâmica de memória\nVariável: lista_contatos\nFunção: excluir_contato\n");
		exit(1);
	}
	salvar_lista_cont();

	menu = menu_gen(1, "Retornar");
	show_menu("O contato foi excluido", menu, NULL, dbgmd);

	free_menu(menu);
}

void free_lista_cont()
{
	free(lista_contatos);
}