#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers/definitions.h"
#include "headers/io_files.h"

char sep[] = "|#@!";//separador dos atributos das tabelas

int try_again()
{
    int resposta = 2;

    printf("Deseja tentar denovo? (1)\nDeseja cancelar a operação? (0)\n");
    scanf("%i", &resposta);

    return resposta;
}
/**
 * Confere se o nome está válido, i.e.
 * Não contém o [sep]
 * 
 * @return 2: sucesso; 1: repetir processo; 0: cancelar operação;
*/
int checar_nome(char *nome)
{
    int nome_size = strlen(nome);
    if(nome_size<1)
    {
        printf("Por favor, insira um nome.\n");
        return try_again();
    }
    else
    {
        if(strstr(nome, sep) != NULL)
        {
            printf("A sequência de caracteres '%s' não pode ser usada por ser reservada pelo programa.\n", sep);
            return try_again(); 
        }
    }

    return 2;//não ocorreram erros ao declarar o nome
}
/**
 * confere a entrada do tipo do atributo
 * 
 * @return 0 || 1: try_again(); 2: int, 3: float, 4: double, 5: char, 6: string
*/
int checar_tipo(char *tipo)
{
    /**
    * Lista com os possíveis tipos para os parâmetros
    * 
    * @return srt com o nome do tipo [int, float, double, char, string]
    */
    char tipos_list[5][8] = {
        "int",//0
        "float",//1
        "double",//2
        "char",//3
        "string"//4
    };

    for(int tipo_int = 0; tipo_int < 5; tipo_int++)
    {
        if(strcmp(tipo, tipos_list[tipo_int]) == 0) return tipo_int+2;
    }

    printf("Tipo de variável não reconhecido.\n");
    return try_again();
}

Tabela new_tabela(char *nome_tb, char *nome_at, int tipo_at)
{
    Tabela tb;
    tb.nome_tb = calloc(strlen(nome_tb), sizeof(char));
    strcpy(tb.nome_tb, nome_tb);

    tb.nomes_at = malloc(sizeof(char*));
    tb.nomes_at[0] = calloc(strlen(nome_at), sizeof(char));
    strcpy(tb.nomes_at[0], nome_at);

    tb.tipos_at = calloc(1, sizeof(int));
    tb.tipos_at[0] = tipo_at;

    tb.qte_at = 1;
    tb.qte_reg = 0;
    
    tb.registros = NULL;

    return tb;
}

/**
 * Cria a tabela conforme as entradas do usuário
 * 
 * @returns 
*/
int criar_tabela()
{
    char *nome_tb = calloc(MAX_NAME_LENGTH, sizeof(char));//nome da tabela
    char *nome_at = calloc(MAX_NAME_LENGTH, sizeof(char));//nome do atributo
    char *tipo_at = calloc(MAX_NAME_LENGTH, sizeof(char));//tipo do atributo
    char input_nome_tipo_at[MAX_NAME_LENGTH+10] = {0};//variável auxiliar de entrada do nome + tipo do atributo
    int tb_ok = 0, at_ok = 0, nome_ok = 0;//var auxiliar de erros

    while (!tb_ok)
    {
        printf("Por favor, insira o nome da tabela a ser criada: ");
        scanf("%s", nome_tb);

        nome_ok = checar_nome(nome_tb);
        if(nome_ok == 2)
        {
            nome_ok = existe_tabela(nome_tb);
            if(nome_ok == 2) tb_ok = 1;
        }
        //não é um elif por conta da alteração de nome_ok caso a tabela já exista
        if (nome_ok == 1)
        {
            memset(nome_tb, '\0', MAX_NAME_LENGTH+8);
        }
        //não é um elif por conta da alteração de nome_ok caso a tabela já exista
        if (nome_ok == 0)
        {
            printf("Cancelando operação...\n");
            return 0;
        }
    }

    while (!at_ok)
    {
        printf("Qual o nome do atributo que deseja incluir na tabela %s? Informe seguindo a formatação\n'nome_do_atributo tipo_de_dado'\nTipos de dados disponíveis: int, float, double, char e string\n", nome_tb);
        scanf("\n%s %s", nome_at, tipo_at);

        nome_ok = checar_nome(nome_at);
        if(nome_ok == 2)
        {
            nome_ok = checar_tipo(tipo_at);
            if(nome_ok > 1) at_ok = 1;
        }
        //não é um elif por conta da alteração de nome_ok caso ocorra um erro na seleção do tipo
        if (nome_ok == 1)
        {
            free(nome_at);
        }
        //não é um elif por conta da alteração de nome_ok caso ocorra um erro na seleção do tipo
        if (nome_ok == 0)
        {
            printf("Cancelando operação...\n");
            return 0;
        }
    }

    int tipo_at_int = nome_ok - 2;//por conta do conflito entre os retornos

    Tabela tb = new_tabela(nome_tb, nome_at, tipo_at_int);
    if(arquivar_tabela(tb) != 2)
    {
        printf("Cancelando operação...\n");
        return -1;
    }

    printf("Tabela Incluida com sucesso!\n\n");
    return 2;//sem erros durante a operação
}