#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers/definitions.h"
#include "headers/io_files.h"

extern char sep[];

/**
* Lista com os possíveis tipos para os parâmetros
* 
* @return srt com o nome do tipo [int, float, double, char, string]
*/
char * tipos_list[5] = {
    "int",//0
    "float",//1
    "double",//2
    "char",//3
    "string"//4
};

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

int existe_id(unsigned int id, Tabela * tb)
{
    for (unsigned int i = 0; i < tb->qte_reg; i++)
    {
        if (tb->registros[i].id == id)
            return 1;
    }
    return 0;
}

/**
 * confere a entrada do tipo do atributo
 * 
 * @return 0 || 1: try_again(); 2: int, 3: float, 4: double, 5: char, 6: string
*/
int checar_tipo(char *tipo)
{
    for(int tipo_int = 0; tipo_int < 5; tipo_int++)
    {
        if(strcmp(tipo, tipos_list[tipo_int]) == 0) return tipo_int+2;
    }

    printf("Tipo de variável não reconhecido!\n");
    return try_again();
}

int existe_dupla_pk(Tabela *tb)
{
    for (unsigned int i = 0; i < tb->qte_reg; i++)
    {
        for (unsigned int j = i+1; j < tb->qte_reg+1; j++)
        {
            if (tb->registros[i].id == tb->registros[j].id) return 1;
        }
    }
    
    return 0;
}

/**
 * Recebe um nome de uma tabela do usuário, realiza os testes necessários considerando
 * se a tabela deve existir ou não (0, 1)
 * @return NULL se o user cancelar a operação;
*/
char * get_nome_tabela(int deve_existir)
{
    char * nome_tb = calloc(MAX_NAME_LENGTH, sizeof(char));
    int tb_ok = 0;

    while (!tb_ok)
    {
        printf("Nome da Tabela: ");
        scanf("%s", nome_tb);

        if (deve_existir)
        {
            if (existe_tabela(nome_tb))
            {
                return nome_tb;
            }
            else
            {
                printf("A tabela %s não existe!\n", nome_tb);
                memset(nome_tb, 0, MAX_NAME_LENGTH);
                tb_ok = !try_again();
            }
        }
        else
        {
            if (existe_tabela(nome_tb))
            {
                printf("Já existe uma tabela chamada '%s'!\n", nome_tb);
                memset(nome_tb, 0, MAX_NAME_LENGTH);
                tb_ok = !try_again();
            }
            else
            {
                if (checar_nome(nome_tb) == 2)
                {
                    return nome_tb;
                }
                else
                {
                    memset(nome_tb, 0, MAX_NAME_LENGTH);
                    tb_ok = !try_again();
                }
            }
        }
    }
    free(nome_tb);
    printf("Cancelando a operação...\n");
    return NULL;
}