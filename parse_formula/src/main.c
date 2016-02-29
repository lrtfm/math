#include "parse_formula.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <readline/readline.h>
#include <readline/history.h>

#define PI 3.1415926
#define STR(value) #value 

#define MAX_FORUMLA_LEN 256
#define MAX_SYM_NUM 4

/* A static variable for holding the line. */
static char *line_read = (char *)NULL;

/* Read a string, and return a pointer to it.
 *    Returns NULL on EOF. */
char * rl_gets ()
{
    /* If the buffer has already been allocated,
     *      return the memory to the free pool. */
    if (line_read)
    {
        free (line_read);
        line_read = (char *)NULL;
    }

    /* Get a line from the user. */
    line_read = readline (">> ");

    /* If the line has any text in it,
    *      save it on the history. */
    if (line_read && *line_read)
        add_history (line_read);

    return (line_read);
}

int get_sym_name_value( char * newline, struct symbol_pair * sp)
{
    while (*newline == ' ' || *newline == '\t') {
        newline++;
    }

    newline += 3;

    while (*newline == ' ' || *newline == '\t') {
        newline++;
    }

    char *p = newline;
    while (*newline != ' ' && *newline != '\t' && *newline != '=' ) {
        *newline++;
    }
    *newline = '\0';

    strcpy(sp->sym_name, p);

    char *p2 = newline + 1;
    while ( *p2 < '0' || *p2 > '9') {
        ++p2;
    }

//    printf("[DEBUG] p2 = %s \n", p2);
    sp->sym_value = atof(p2);

//    printf("[DEBUG] sym %s = %lf \n", sp->sym_name, sp->sym_value);

    return 0;

}
 
int issym( char * newline)
{
    while (*newline == ' ' || *newline == '\t') {
        newline++;
    }

    if (*newline == 's' && *(newline + 1) == 'y' && *(newline+2) == 'm')
    {
        return 1;
    }

    return 0;

}
int main(int argc, char*argv[])
{
    int number;
    char formula_string[10][MAX_FORUMLA_LEN] ; //= "sin("STR(PI)"/2)*cos(0)";
    SYM_PAIR sym_value_map[MAX_SYM_NUM];
    int sym_num = 0;
    real ret = 0;
    int i;
    int len;
    int j = 0;
    int save_str_num = 0;
    char * newline = NULL;

    while (1)
    {
        newline = rl_gets();
        if (newline == NULL) {
            continue;
        }
        else {
            if (!strcmp(newline, "exit")) {
                break;
            }
            else {

                if(issym(newline))
                {
                    if (sym_num < MAX_SYM_NUM) {
                        get_sym_name_value(newline, &sym_value_map[sym_num]);
                        sym_num++;
                    }
                }
                else {
                    F_NODE *formula = NULL;
                    formula = parse(newline);
                    ret = compute(formula, sym_value_map, sym_num);
                    printf("result: %s = %lf\n", newline, ret);
                }
            }
        }
        
        
    }

    /*
    for (i = 0; i < 10; ++i) {
        printf("Please input the symbol and value:\n");
        scanf("%s %lf", sym_value_map[0].sym_name, &sym_value_map[0].sym_value);
        sym_num = 1;
        getchar();
        printf("Please input the formula (without space!!!):\n");
        // scanf("%s", formula_string);
        // TODO input data.
        // gets(formula_string);

        fgets(formula_string[j], MAX_FORUMLA_LEN, stdin);
        len = strlen(formula_string[j]);
        if (formula_string[j][len - 1] == '\n') {
            formula_string[j][len - 1] = '\0';
        }
        

        F_NODE *formula = NULL;
        formula = parse(formula_string[j]);
        ret = compute(formula, sym_value_map, sym_num);
        printf("%s = %lf\n", formula_string[j], ret);
        free_node(formula);

        j = (j + 1) % 10;
        save_str_num++;
        if (save_str_num > 10 ) {
            save_str_num = 10;
        }
    }*/
    
    return 0;
}

