#ifndef MAX_NAME_LENGTH

#define MAX_NAME_LENGTH 250 //tamanho máximo para nomes de tabelas, atributos, etc
#define SEP_LEN 4 //tamanho do vetor do separador
typedef struct table
{
    char *nome;
    char **atributos;


} Tabela;

/**
 * Lista com os possíveis tipos para os parâmetros
 * 
 * @return srt com o nome do tipo [int, float, double, char, string]
*/
char tipos_list[5][8] = {
        "int\0",//tipo 0
        "float\0",//tipo 1
        "double\0",//tipo 2
        "char\0",//tipo 3
        "string\0"//tipo 4
    };

char sep[SEP_LEN+1] = "|#@!\0";//separador dos atributos das tabelas
#endif



