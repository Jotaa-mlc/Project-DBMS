#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 250 //tamanho máximo para nomes de tabelas, atributos, etc

char sep[4] = "|#@!";//separador dos atributos das tabelas

int criar_tabela()
{
    char nome_tb[MAX_NAME_LENGTH] = {0};//nome da tabela
    char nome_at[MAX_NAME_LENGTH] = {0};//nome do atributo
    int tb_ok = 0, at_ok = 0;//var auxiliares de erros

    printf("Por favor, insira o nome da tabela a ser criada:\n");
    fgets(nome_tb, 249, stdin);

    //checar se nome válido
    //checar se a tabela já existe
    //criar arquivo

    if(!tb_ok)
    {

    }

    printf("Digite o nome do atributo que deseja incluir na tabela %s seguindo a formatação\n'nome_da_tabela atributo'\n", nome_tb);
    fgets(nome_at, 249, stdin);

    //checar se nome válido
    //editar arquivo

    return 1;//sem erros durante a operação
}