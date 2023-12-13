#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers/definitions.h"
#include "headers/tables_func.h"
#include "headers/io_files.h"

extern char sep[];
extern char file_extension[];
extern char * tipos_list[];

void criar_tabela()
{
    char *nome_tb;//nome da tabela
    char *nome_pk = calloc(MAX_NAME_LENGTH, sizeof(char));//nome da chave_primária
    char *nome_at = calloc(MAX_NAME_LENGTH, sizeof(char));//nome do atributo
    char *tipo_at = calloc(MAX_NAME_LENGTH, sizeof(char));//tipo do atributo
    unsigned int qte_at = 0;
    int tipo_at_int = 0;
    int tb_ok = 0, at_ok = 0, nome_ok = 0, pk_ok = 0;//var auxiliar de erros

    while (!tb_ok)
    {
        printf("Por favor, insira o nome da tabela a ser criada: ");
        nome_tb = get_nome_tabela(0);

        if (nome_tb != NULL)
            tb_ok = 1;
        else
            goto CANCELADO;
    }

    while(!pk_ok && tb_ok)
    {
        printf("Defina o nome da CHAVE PRIMARIA (pk): ");
        scanf("\n%s", nome_pk);
        pk_ok = checar_nome(nome_pk);

        if(pk_ok == 0) goto CANCELADO;
    }

    Tabela * tb = NULL;

    if (pk_ok && tb_ok)
    {
        printf("Quantos atributos deseja incluir na tabela %s?", nome_tb);
        scanf("%u", &qte_at);
        tb = alocar_tabela(qte_at, 0);

        printf("Informe os atributos seguindo a formatação\n");
        printf("'nome_do_atributo_1 tipo_de_dado'\n'nome_do_atributo_2 tipo_de_dado...'\nTipos de dados disponíveis: int, float, double, char e string\n");

        for (unsigned int i = 0; i < qte_at; i++)
        {   
            at_ok = 0;
            while (!at_ok)
            {
                memset(nome_at, 0, MAX_NAME_LENGTH);
                memset(tipo_at, 0, MAX_NAME_LENGTH);

                scanf("\n%s %s", nome_at, tipo_at);

                nome_ok = checar_nome(nome_at);
                if(nome_ok == 2)
                {
                    tipo_at_int = checar_tipo(tipo_at);
                    if (tipo_at_int > 1)
                    {
                        tipo_at_int -= 2;//por conta do retorno de checar tipo
                        at_ok = 1;
                    }
                    else if (tipo_at_int == 0)//operação cancelada pelo tipo
                        goto CANCELADO;
                }
                else if (nome_ok == 0)//operação cancelada pelo nome
                    goto CANCELADO;
            }
            if (at_ok)
            {
                strcpy(tb->nomes_at[i], nome_at);
                tb->tipos_at[i] = tipo_at_int;
            }
        }   
    }

    if (at_ok && pk_ok && tb_ok)
    {
        strcpy(tb->nome_tb, nome_tb);
        strcpy(tb->nome_pk, nome_pk);
        
        if(arquivar_tabela(tb) != 2)
            printf("Cancelando operação...\n");
        else
            printf("Tabela Incluida com sucesso!\n\n");
    }
    else
    {
        CANCELADO:
        printf("Cancelando operação...\n");
    }
    
    free(nome_tb);
    free(nome_pk);
    free(nome_at);
    free(tipo_at);
    if (tb != NULL) free_tabela(tb);
}

void inserir_registro()
{
    int insert_ok = 0, reg_ok = 0, tb_ok = 0;
    char *nome_tb;//nome da tabela

    Tabela * tb = NULL;

    while (!tb_ok)
    {
        printf("Em qual tabela deseja inserir um registro?\n");
        nome_tb = get_nome_tabela(1);

        if (nome_tb != NULL)
            tb_ok = 1;
        else
            break;
    }
    
    tb = carregar_tabela(nome_tb);
    Registro * new_registros = realloc(tb->registros, (sizeof(Registro) * (tb->qte_reg+1)));

    if (new_registros != NULL)
    {
        tb->registros = new_registros;
        tb->registros[tb->qte_reg].at = calloc(tb->qte_at, sizeof(Atributo));
    }
    else
    {
        tb_ok = 0;
        printf("ERRO: houve um problema ao inserir um registro\n");
    }

    while (!reg_ok && tb_ok)
    {
        printf("Insira os atributos do registro conforme a formatação:\n");
        //Printa a pk + atributos e tipos
        printf("%s ", tb->nome_pk);
        for (unsigned int i = 0; i < tb->qte_at; i++) printf("%s (%s) ", tb->nomes_at[i], tipos_list[tb->tipos_at[i]]);
        printf("\n");
        
        scanf("%u ", &tb->registros[tb->qte_reg].id);
        for (unsigned int i = 0; i < tb->qte_at; i++)//recebe o atributo baseado no tipo
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
            reg_ok = 1;
        }
        else
        {
            printf("Já existe um resgisto com essa chave primária!\n");
            reg_ok = !try_again();
        }
    }
    
    if (tb_ok && reg_ok)
    {
        tb_ok = arquivar_tabela(tb);
        if (tb_ok == 2) 
            printf("Registro inserido com sucesso!\n");
        else
            printf("ERRO: houve um problema ao salvar a tabela.\n");
    }
    else
    {
        printf("Cancelando Operação...\n");
    }
    
    free(nome_tb);
    if(tb != NULL) free_tabela(tb);
}