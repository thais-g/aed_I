#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <termios.h>
#include <unistd.h>
#include "menu.h"

Menu *addOption(Menu *menu, char *str)
{
    if(menu == NULL)
    {
        printf("entrou aqui\n");
        menu = (Menu*) malloc(sizeof(Menu));
        menu->size = 0;
        menu->option_mat = NULL;
    }
    
    menu->option_mat = (char**) realloc(menu->option_mat, (menu->size+1) * sizeof(char*));
    menu->option_mat[menu->size] = (char*) malloc(STRING_LENGTH * sizeof(char));
    strcpy(menu->option_mat[menu->size], str);
    menu->size++;

    return menu;
}
Menu *removeOption(Menu *menu, int option)
{
    int i;

    for(i = option; i < menu->size; i++)
    {
        if(i != (menu->size-1))
        {
            menu->option_mat[i] = menu->option_mat[i+1];
        }
    }

    menu->option_mat = (char**) realloc(menu->option_mat, (menu->size-1) * sizeof(char*));
    menu->size--;
}
Menu *menu_gen(int menu_size, ...)
{
    Menu *menu;
    char **gen_menu;
    int i;
    va_list option;
    va_start(option, menu_size);

    menu = (Menu*) malloc(sizeof(Menu));
    menu->option_mat = (char**) malloc(menu_size * sizeof(char*));
    menu->size = menu_size;
    
    for(i = 0; i < menu_size; i++)
    {
        menu->option_mat[i] = (char*) malloc(STRING_LENGTH * sizeof(char));
        menu->option_mat[i] = va_arg(option, char*);
    }

    return menu;

}

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

int menu_mechanics(char *select_vect, char move, int selected_pos, int menu_size)
{
    /**
     * Calcula a posição do '>' no menu, para qual opção está sendo apontado após movimento capturado.
     */
    
    int i;

    select_vect[selected_pos] = ' ';

    if((move == 'A') && (selected_pos != 0))
        selected_pos--;
    if((move == 'B') && (selected_pos != (menu_size - 1)))
        selected_pos++;

    select_vect[selected_pos] = '>';

    return selected_pos;
}

int show_menu(char* menu_title, Menu *menu, void (*func)(), int debug_mode)
{
    /**
     * Implementa o loop que mostra o menu e a opção destacada pelo '>' até que o usuário aperte o 
     * enter e selecione de fato aquela opção.
     */
    
    int i, selected_pos = 0;
    char *select_vect, move = ' ';

    select_vect = (char*) malloc(menu->size * sizeof(char));
    select_vect[0] = '>';
    for(i = 1; i < menu->size; i++)
        select_vect[i] = ' ';


    while(move != '\n')
    {   
        if(!debug_mode) printf("\e[1;1H\e[2J");
        //printf("\033[%d;%dH", x, y);
        printf("%s\n\n", menu_title);
        if(func != NULL) func();
        for(i = 0; i < menu->size; i++)
        {
            //printf("\033[%dC", y-5);
            printf("%c ", select_vect[i]);
            printf("%s\n", menu->option_mat[i]);
            
        }
        setbuf(stdin, NULL);
        move = getch();
        selected_pos = menu_mechanics(select_vect, move, selected_pos, menu->size); 
    }
    return selected_pos;

}

int pos_option(Menu *menu, char *str)
{
    /**
     * Retorna a posição da string na matriz de strings de opções, caso ela exista.
     */
    
    int i;

    for(i = 0; i < menu->size; i++)
    {
        if(!(strcmp(menu->option_mat[i], str)))
            return i;
    }

}

int menu_mechanics_rolagem(char move, void *vect_option, int option_index, int vect_option_len)
{
    /**
     * Implementa a mecânica de rolagem do menu de rolagem.
     * Conforme o movimento capturado, movimenta o indice do vetor de opções para que uma nova opção seja mostrada.
     */
    
    int i;

    if((move == 'A') && (option_index != 0))
        option_index--;
    if((move == 'B') && (option_index != (vect_option_len - 1)))
        option_index++;

    return option_index;
}

int show_menu_rolagem_int(char* menu_title, Menu *menu, int *vect_option, int vect_option_len, void (*func)(), int debug_mode, int two_dig)
{ 
    /**
     * Mostra o menu de rolagem com um vetor de inteiros como vetor de opções.
     */
    
    int i, option_index = 0;
    char move = ' ';

    while(move != '\n')
    {   
        if(!debug_mode) printf("\e[1;1H\e[2J");
        printf("%s\n\n", menu_title);
        if(func != NULL) func();
        for(i = 0; i < menu->size; i++)
        {
            if(two_dig)
                printf("%s:%02d\n", menu->option_mat[i], vect_option[option_index]);
            else
                printf("%s:%d\n", menu->option_mat[i], vect_option[option_index]);
            
            
        }
        setbuf(stdin, NULL);
        move = getch();
        option_index = menu_mechanics_rolagem(move, vect_option, option_index, vect_option_len);
    }
    return option_index;

}

int show_menu_rolagem_char(char* menu_title, Menu *menu, char **vect_option, int vect_option_len, void (*func)(), int debug_mode)
{
    /**
     * Mostra o menu de rolagem com um vetor de strings como vetor de opções.
     */

    int i, option_index = 0;
    char move = ' ';

    while(move != '\n')
    {   
        if(!debug_mode) printf("\e[1;1H\e[2J");
        //printf("\033[%d;%dH", x, y);
        printf("%s\n\n", menu_title);
        if(func != NULL) func();
        for(i = 0; i < menu->size; i++)
        {
            //printf("\033[%dC", y-5);
            printf("%s:%s\n", menu->option_mat[i], vect_option[option_index]);
            
        }
        setbuf(stdin, NULL);
        move = getch();
        option_index = menu_mechanics_rolagem(move, vect_option, option_index, vect_option_len);
    }
    return option_index;

}

void free_menu(Menu *menu)
{
    int i;

    free(menu->option_mat);
    free(menu);
}
