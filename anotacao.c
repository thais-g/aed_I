#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "anotacao.h"

int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}

struct no
{
	char linha[256];
	struct no *ant;
};

struct no_arquivo
{
    char linha[256];
};

struct pilha
{
	struct no *topo;
	struct no *base;
	int tam;
};

struct pilha *empilhar(struct pilha *p, struct no *novo_no)
{
	
	if(p->topo == NULL)
	{
		p->topo = novo_no;
		p->base = novo_no;
		//printf("empilhou o novo nó em uma pilha vazia\n");
		return p;
	}

	novo_no->ant = p->topo;
	p->topo = novo_no;
	++p->tam;

	//printf("empilhou o novo nó na pilha\n");

	return p;
}

struct pilha *desempilhar(struct pilha *p)
{
	struct no *no_desemp;

	if(p->topo == NULL)
		return p;

	no_desemp = p->topo;
	p->topo = p->topo->ant;
	free(no_desemp);
	--p->tam;

	return p;
}

struct no *pop(struct pilha *p)
{
	struct no *no_desemp;

	if(p->topo == NULL)
		return NULL;

	no_desemp = p->topo;
	p->topo = p->topo->ant;
	--p->tam;

	return no_desemp;
}

struct pilha *iniciar_pilha()
{
	struct pilha *p;

	p = (struct pilha*) malloc(sizeof(struct pilha));
	p->topo = NULL;
	p->tam = 0;
	return p;
}

int pilha_vazia(struct pilha *p)
{
	return (p->topo == NULL) ? 1 : 0;
}

void mostrar_pilha(struct no *no_linha, struct pilha *p, int anot_ant)
{
    if(no_linha == p->base)
	{
		if(no_linha == p->topo) 
        {
            if(anot_ant) 
                printf("%s\n", no_linha->linha);
            else
                printf("%s", no_linha->linha);
            
        }
		else
			printf("%s\n", no_linha->linha);	
	}	
	else
	{
		mostrar_pilha(no_linha->ant, p, anot_ant);
		if(no_linha == p->topo)
			printf("%s", no_linha->linha);
		else
			printf("%s\n", no_linha->linha);
	}

	return;
}

struct no *criar_nova_linha()
{
	struct no *nova_linha;
	int i;

	nova_linha = (struct no*) malloc(sizeof(struct no));
	nova_linha->ant = NULL;
	for(i = 0; i < 256; i++)
		nova_linha->linha[i] = 0;

	return nova_linha;
}

int pos_cursor(char *str)
{
	int i = 0;

	while(str[i] != 0)
		i++;

	return i;
}

void print_diario()
{
    struct pilha *p = iniciar_pilha();
    FILE *fptr = fopen("diario.bin", "rb");
    int cont = 0;
    struct no_arquivo no_arq;

    if(fptr == NULL)
        return;
    while (fread(&no_arq, sizeof(struct no_arquivo), 1, fptr))
    {
        struct no *nova_linha = criar_nova_linha();
        
        strcpy(nova_linha->linha, no_arq.linha);
        empilhar(p, nova_linha);

        cont++;

    }
    
    if(cont > 0)
    {
        printf("######## Anotações Anteriores ########\n");
        mostrar_pilha(p->topo, p, 1);
        printf("\n");
    }

    fclose(fptr);
}

void diario_func()
{
    struct pilha *p = iniciar_pilha();
	struct no *nova_linha;
	char tecla, cursor = 219;
	int indice_char_linha;


	indice_char_linha = 0;

	while(tecla != 12)
	{	
		if(pilha_vazia(p))
		{
			nova_linha = criar_nova_linha();
			empilhar(p, nova_linha);
		}
		printf("\e[1;1H\e[2J");
        print_diario();
        printf("######## Anotações ########\n(CTRL+L para encerrar a inserção da anotação)\n");
		mostrar_pilha(p->topo, p, 0);
		printf("%c", cursor);
		tecla = getch();
		
		if(tecla == 127 && indice_char_linha >= 0)
		{
			if(indice_char_linha == 0 && p->topo->linha[0] == 0)
			{
				p = desempilhar(p);
				if(!pilha_vazia(p))
					indice_char_linha = pos_cursor(p->topo->linha);
				
			}
			else
			{
				indice_char_linha--;
				p->topo->linha[indice_char_linha] = 0;
			}
		}
		
		else if(tecla == 10 || indice_char_linha == 30)
		{
            nova_linha = criar_nova_linha();
			p = empilhar(p, nova_linha);
			indice_char_linha = 0;
		}
		else
		{
			p->topo->linha[indice_char_linha] = tecla;
			indice_char_linha++;
		}

	}

    FILE *fptr = fopen("diario.bin", "ab");

    int tam_pilha = p->tam;
    for(int i = 0; i < tam_pilha; i++)
    {

        struct no *pop_no = pop(p);
        struct no_arquivo pop_no_arquivo; 
        strcpy(pop_no_arquivo.linha, pop_no->linha);
        fwrite(&pop_no_arquivo, sizeof(struct no_arquivo), 1, fptr);
    }
    fclose(fptr);
}