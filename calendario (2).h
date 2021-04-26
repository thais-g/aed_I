#define TRUE            1
#define FALSE           0

extern int  dias_do_mes[]   ;
extern char *meses[]        ;
extern char *nome_meses[]   ;

int     get_codigo_dia(int ano)                                                                                 			;
int     get_ano_bissexto(int ano)                                                                               			;
int     **gera_calendario_mes(int mes, int ano, int *semana, int *dia_inicio)                                   			;
void    show_calendario(int semana, int dia_inicio, int **mat, int *selected_pos_x, int *selected_pos_y, int debug_mode)	;