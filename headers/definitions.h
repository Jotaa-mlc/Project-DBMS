#ifndef MAX_NAME_LENGTH
#define MAX_NAME_LENGTH 250 //tamanho máximo para nomes de tabelas, atributos, etc
typedef union properties
{
    int inteiro;
    float real;
    double dupla;
    char caractere;
    char string[MAX_NAME_LENGTH];
} Atributo;

typedef struct reg
{
    unsigned int id;
    Atributo *at;
} Registro;

typedef struct table
{
    char *nome_tb;
    char *nome_pk;
    char **nomes_at;
    int *tipos_at;//int, float, double, char, string
    unsigned int qte_at, qte_reg;
    Registro *registros;
} Tabela;
#endif