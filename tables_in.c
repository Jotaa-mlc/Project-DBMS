#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers/definitions.h"
#include "headers/io_files.h"

char sep[] = "|#@!";//separador dos atributos das tabelas
char file_extension[] = ".itp";

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
    for(int tipo_int = 0; tipo_int < 5; tipo_int++)
    {
        if(strcmp(tipo, tipos_list[tipo_int]) == 0) return tipo_int+2;
    }

    printf("Tipo de variável não reconhecido.\n");
    return try_again();
}

/**
 * Cria a tabela conforme as entradas do usuário
 * 
 * @returns 
*/
int criar_tabela()
{
    char *nome_tb = calloc(MAX_NAME_LENGTH, sizeof(char));//nome da tabela
    char *nome_pk = calloc(MAX_NAME_LENGTH, sizeof(char));//nome da tabela
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
            nome_ok = existe_tabela(nome_tb) ? try_again() : 2;
            tb_ok = (nome_ok == 2) ? 1 : 0;
        }
        //não é um elif por conta da alteração de nome_ok caso a tabela já exista
        if (nome_ok == 1)
        {
            memset(nome_tb, 0, sizeof(nome_tb));
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
        int pk_ok = 0;
        while(!pk_ok)
        {
            printf("Defina o nome da CHAVE PRIMARIA (pk): ");
            scanf("\n%s", nome_pk);
            pk_ok = checar_nome(nome_pk);
            if(pk_ok == 0)
            {
                printf("Cancelando operação...\n");
                return 0;
            } 
        }

        printf("Qual o nome do atributo que deseja incluir na tabela %s? Informe seguindo a formatação\n'nome_do_atributo tipo_de_dado'\nTipos de dados disponíveis: int, float, double, char e string\n", nome_tb);
        scanf("\n%s %s", nome_at, tipo_at);

        nome_ok = checar_nome(nome_at);
        if(nome_ok == 2)
        {
            nome_ok = checar_tipo(tipo_at);
            at_ok = (nome_ok > 1) ? 1 : 0;
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

    Tabela * tb = alocar_tabela(1,0);
    strcpy(tb->nome_tb, nome_tb);
    strcpy(tb->nomes_at[0], nome_at);
    tb->tipos_at[0] =  nome_ok - 2;
    strcpy(tb->nome_pk, nome_pk);
    if(arquivar_tabela(tb) != 2)
    {
        printf("Cancelando operação...\n");
        return -1;
    }

    free(nome_at);
    free(nome_tb);
    free(tipo_at);
    free_tabela(tb);

    printf("Tabela Incluida com sucesso!\n\n");
    return 2;//sem erros durante a operação
}

int existe_dupla_pk(Tabela *tb)
{
    for (unsigned int i = 0; i < tb->qte_reg; i++)
    {
        for (unsigned int j = i+1; j < tb->qte_reg; j++)
        {
            if (tb->registros[i].id == tb->registros[j].id) return 1;
        }
    }
    
    return 0;
}

int inserir_registro()
{
    int insert_ok = 0, reg_ok = 0;

    char *nome_tb = calloc(MAX_NAME_LENGTH, sizeof(char));//nome da tabela

    Tabela * tb = NULL;
    while (!insert_ok)
    {
        printf("Em qual tabela deseja inserir um registro? ");
        scanf("%s", nome_tb);

        if(existe_tabela(nome_tb))
        {
            tb = carregar_tabela(nome_tb);
            Registro * new_registros = realloc(tb->registros, (sizeof(Registro) * (tb->qte_reg+1)));
            if (new_registros != NULL)
            {
                tb->registros = new_registros;
                tb->registros[tb->qte_reg].at = calloc(tb->qte_at, sizeof(Atributo));
                while (!reg_ok)
                {
                    printf("Insira os atributos do registro conforme:\n");
                    printf("%s ", tb->nome_pk);
                    for (unsigned int i = 0; i < tb->qte_at; i++) printf("%s (%s) ", tb->nomes_at[i], tipos_list[tb->tipos_at[i]]);
                    printf("\n");
                    
                    scanf("%u ", &tb->registros[tb->qte_reg].id);
                    for (unsigned int i = 0; i < tb->qte_at; i++)
                    {
                        switch (tb->tipos_at[i])
                        {
                            case 0:
                                scanf("%d", &tb->registros[tb->qte_reg].at[i].inteiro);
                                break;
                            case 1:
                                scanf("%f", &tb->registros[tb->qte_reg].at[i].real);
                                break;
                            case 2:
                                scanf("%lf", &tb->registros[tb->qte_reg].at[i].dupla);
                                break;
                            case 3:
                                scanf("%c", &tb->registros[tb->qte_reg].at[i].caractere);
                                break;
                            case 4:
                                scanf("%s", tb->registros[tb->qte_reg].at[i].string);
                                break;
                            default:
                                break;
                        }
                    }
                    if (!existe_dupla_pk(tb))
                    {
                        tb->qte_reg++;
                        reg_ok = 1, insert_ok = 1;
                    }
                    else
                    {
                        printf("Já existe um resgisto com essa chave primária!\n");
                        reg_ok = !try_again();
                    }
                }
            }
            else
            {
                printf("ERRO: houve um problema ao inserir um registro\n");
                break;
            }
        }
        else
        {
            printf("A tabela %s não existe!\n", nome_tb);
            insert_ok = !try_again();
        }
        if(reg_ok) break;
    }

    if (insert_ok && reg_ok)
    {
        if(arquivar_tabela(tb) == 2) printf("Registro inserido com sucesso!\n");
        else printf("ERRO: houve um problema ao salvar a tabela.\n");
    }
    else
    {
        printf("Cancelando operação...\n");
    }
    
    free(nome_tb);
    if(tb != NULL) free_tabela(tb);
}