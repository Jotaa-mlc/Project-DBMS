#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers/definitions.h"


/**
 * Cria a tabela conforme as entradas do usuário
 * 
 * @returns 
*/
int criar_tabela()
{
    char *nome_tb;//nome da tabela
    char *nome_at;//nome do atributo
    char input_nome_tipo_at[MAX_NAME_LENGTH+10] = {0};//variável auxiliar de entrada do nome + tipo do atributo
    char *tipo_at;//tipo do atributo
    int tb_ok = 0, at_ok = 0;//var auxiliares de erros

    while (!tb_ok)
    {
        printf("Por favor, insira o nome da tabela a ser criada:\n");
        fgets(nome_tb, MAX_NAME_LENGTH, stdin);

        int nome_ok = checar_nome(nome_tb);
        if(nome_ok == 2)
        {
            //checar se a tabela já existe
                //criar arquivo
        }
        else if (nome_ok == 1)
        {
            free(nome_tb);
            continue;
        }
        else if (nome_ok == 0)
        {
            printf("Cancelando operação...\n");
            return 0;
        }
    }

    while (!at_ok)
    {
        printf("Qual o nome do atributo que deseja incluir na tabela %s? Informe seguindo a formatação\n'nome_do_atributo tipo_de_dado'\nTipos de dados disponíveis: int, float, double, char e string\n", nome_tb);
        fgets(input_nome_tipo_at, MAX_NAME_LENGTH+7, stdin);
        nome_at = strtok(input_nome_tipo_at, " ");
        tipo_at = strtok(NULL, " ");

        if(checar_nome(nome_at) == 2)//se nome válido
        {
            //editar arquivo
        }
    }
    

    return 0;//sem erros durante a operação
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

int checar_tipo(char *tipo)
{
    int tipo_int = 0;
    
    for(tipo_int = 0; tipo_int < 5; tipo_int++)
    {
        if(strcmp(tipo, tipos_list[tipo_int]) == 0) return tipo_int;
    }

    printf("Tipo de variável não reconhecido.\n");
    return try_again();
}

int try_again(){
    int resposta = 2;

    printf("Deseja tentar denovo? (1)\nDeseja cancelar a operação? (0)");
    scanf("%c", &resposta);

    return resposta;
}