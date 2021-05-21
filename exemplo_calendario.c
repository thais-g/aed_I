/*
 	Compilar:
 	gcc -c menu.c
 	gcc -c calendario.c
 	gcc exemplo_calendario.c menu.o calendario.o -o excal
*/

#include <stdio.h>
#include "calendario.h"

int main()
{
	int ano, mes, semana, dia_inicio, pos_x, pos_y, **mat;
	printf("Informe o ano: ");
	scanf("%d", &ano);
	printf("Informe o mes: ");
	scanf("%d", &mes);

	/* 	
		Gera um calendário dos dias do mês do ano que foi passado  e o mostra como menu selecionável de dias.

		*	Salva a semana de inicio na variável 'semana' para depois ser usado 
			na função que irá mostrar o calendário como menu. 

		*	Salva o dia de início na variável 'dia_inicio' para depois usar na 
			função 'show_calendario' que vai exibir o calendário como menu.

		*	A função 'show_calendario' recebe a matriz de inteiros gerada por 'gera_calendario_mes'
			a transformando em um menu com os dias selecionáveis. Salva a posição da matriz que
			foi selecionada em 'pos_x' (coluna) e 'pos_y' (linha). 
		
			**	mat[pos_y][pos_x] = dia selecionado.
	*/
	mat = gera_calendario_mes(mes, ano, &semana, &dia_inicio);
	show_calendario(semana, dia_inicio, mat, &pos_x, &pos_y, 0);

	printf("Dia selecionado: %d\n", mat[pos_y][pos_x]);
}
