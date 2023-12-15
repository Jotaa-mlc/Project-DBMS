#ifndef MAX_NAME_LENGTH
#define MAX_NAME_LENGTH 250 //tamanho máximo para nomes de tabelas, atributos, etc

typedef union
{
    int inteiro;
    float real;
    double dupla;
    char caractere;
    char string[MAX_NAME_LENGTH];
} Atributo;

typedef struct
{
    unsigned int id;//CHAVE_PRIMARIA
    Atributo *at;//Lista de atributos
} Registro;

typedef struct
{
    char *nome_tb;//Nome da tabela
    char *nome_pk;//Nome da CHAVE_PRIMARIA
    char **nomes_at;//Lista dos nomes dos Atributos
    int *tipos_at;//Lista auxiliar com o tipo de cada atributo
    unsigned int qte_at;//Quantidade de atributos
    unsigned int qte_reg;//Quantidade de registros
    Registro *registros;//Lista de registros
} Tabela;
#endif