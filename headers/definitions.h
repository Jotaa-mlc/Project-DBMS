#ifndef MAX_NAME_LENGTH
#define MAX_NAME_LENGTH 250 //tamanho máximo para nomes de tabelas, atributos, etc
#define SEP_LEN 4          //tamanho do vetor do separador
char sep[SEP_LEN + 1] = "|#@!\0"; //separador dos atributos das tabelas

typedef union properties
{
    int inteiro;
    float real;
    double dupla;
    char caractere;
    char *string;
} Atributo;

typedef struct reg
{
    unsigned int id;
    Atributo *at;
} Registro;

typedef struct table
{
    char *nome_tb;
    char **nomes_at;
    int *tipos_at;          // int, float, double, char, string
    unsigned int qte_at, qte_reg;
    Registro *registros;
} Tabela;

/**
 * Lista com os possíveis tipos para os parâmetros
 * 
 * @return srt com o nome do tipo [int, float, double, char, string]
*/
char tipos_list[5][8] = {
    "int",    //tipo 0
    "float",  //tipo 1
    "double", //tipo 2
    "char",   //tipo 3
    "string"  //tipo 4
};
#endif
