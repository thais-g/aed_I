#include <stdio.h>
#include <stdlib.h>
#include "agenda (1).h"
#include "calendario (2).h"
#include "menu.h"

int dias_do_mes[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
char *meses[]=
{
	" ",
	"\n\n\nJaneiro",
	"\n\n\nFevereiro",
	"\n\n\nMarço",
	"\n\n\nAbril",
	"\n\n\nMaio",
	"\n\n\nJunho",
	"\n\n\nJulho",
	"\n\n\nAgosto",
	"\n\n\nSetembro",
	"\n\n\nOutubro",
	"\n\n\nNovembro",
	"\n\n\nDezembro"
};
char *nome_meses[]=
{
	" ",
	"Janeiro",
	"Fevereiro",
	"Março",
	"Abril",
	"Maio",
	"Junho",
	"Julho",
	"Agosto",
	"Setembro",
	"Outubro",
	"Novembro",
	"Dezembro"
};

int get_codigo_dia(int ano)
{
	int codigo_dia;
	int d1, d2, d3;

	d1 = (ano - 1.) / 4.0;
	d2 = (ano - 1.) / 100.;
	d3 = (ano - 1.) / 400.;
	codigo_dia = (ano + d1 - d2 + d3) % 7;
	return codigo_dia;
}

int get_ano_bissexto(int ano)
{
	if (ano % 4 == FALSE && ano % 100 != FALSE || ano % 400 == FALSE)
	{
		dias_do_mes[2] = 29;
		return TRUE;
	}
	else
	{
		dias_do_mes[2] = 28;
		return FALSE;
	}
}

int **gera_calendario_mes(int mes, int ano, int *semana, int *dia_inicio)
{
	int dia, i, **mat, codigo_dia;
	mat = (int**) malloc(1*sizeof(int*));
	mat[0] = (int*) malloc(7*sizeof(int));

	*semana = 0;

	get_ano_bissexto(ano);
	codigo_dia = get_codigo_dia(ano);

	for(i = 1; i < mes; i++)
		codigo_dia = (codigo_dia + dias_do_mes[i]) % 7;
	for (dia = 0; dia < codigo_dia; dia++)
		mat[*semana][dia] = 0;

	i = dia;
	*dia_inicio = dia;
	for (dia = 1; dia <= dias_do_mes[mes]; dia++)
	{
		mat[*semana][i] = dia;
		i++;
		if(i == 7)
		{
			*semana = *semana+1;
			mat = (int**) realloc(mat, (*semana+1)*sizeof(int*));
			mat[*semana] = (int*) malloc(7*sizeof(int));
			i = 0;
		}
	}

	if(i < 7)
	{
		for(;i < 7; i++)
			mat[*semana][i] = 0;
	}


	return mat;
}

void show_calendario(int semana, int dia_inicio, int **mat, int *selected_pos_x, int *selected_pos_y, int debug_mode)
{
	int cont_s, cont_d, selected;

	*selected_pos_x = dia_inicio;
	*selected_pos_y = 0;

	char ch = ' ', select_1, select_2;

	while(ch != '\n')
	{
		printf("\e[1;1H\e[2J");
		printf(" dom seg ter qua qui sex sab \n");
		for(cont_s = 0; cont_s < (semana+1); cont_s++)
		{
			for(cont_d = 0; cont_d < 7; cont_d++)
			{
				selected = 0;
				if(cont_d == *selected_pos_x && cont_s == *selected_pos_y)
					selected = 1;
				if(mat[cont_s][cont_d] != 0)
				{
					if(selected == 1)
						printf("[%02d]", mat[cont_s][cont_d]);
					if(selected == 0)
						printf(" %02d ", mat[cont_s][cont_d]);
				}
					
				else
					printf(" ## ");
			}
			printf("\n");
		}

		setbuf(stdin, NULL);
		ch = getch();

		if(ch == 'A' && (*selected_pos_y != 0) && (mat[*selected_pos_y-1][*selected_pos_x] != 0))
			*selected_pos_y = *selected_pos_y-1;
    	if((ch == 'B') && (*selected_pos_y != (semana)) && (mat[*selected_pos_y+1][*selected_pos_x] != 0))
        	*selected_pos_y = *selected_pos_y+1;
		if(ch == 'C' && (*selected_pos_x != 6) && (mat[*selected_pos_y][*selected_pos_x+1] != 0))
			*selected_pos_x = *selected_pos_x+1;
		if(ch == 'D' && (*selected_pos_x != 0) && (mat[*selected_pos_y][*selected_pos_x-1] != 0))
			*selected_pos_x = *selected_pos_x-1;
	}	
}