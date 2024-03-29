#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers/definitions.h"
#include "headers/tables_func.h"
#include "headers/io_files.h"

void remover_registro()
{
    char * nome_tb;
    unsigned int id_remove;
    int tb_ok = 0, id_ok = 0;

    while (!tb_ok)
    {
        printf("De qual tabela deseja remover um registro?\n");
        nome_tb = get_nome_tabela(1);

        if (nome_tb != NULL)
            tb_ok = 1;
        else
            break;
    }

    Tabela * tb = carregar_tabela(nome_tb);

    while (!id_ok && tb_ok)
    {
        printf("Qual o(a) %s do registro que deseja remover? ", tb->nome_pk);
        scanf("%u", &id_remove);

        if (existe_id(id_remove, tb))
            id_ok = 1;            
        else
        {
            printf("O(a) %s indicado(a) é inválido(a) para a Tabela %s\n", tb->nome_pk, tb->nome_tb);
            id_ok = !try_again();
        }
    }

    if (id_ok)
    {
        for (unsigned int i = 0; i < tb->qte_reg; i++)
        {
            if (tb->registros[i].id == id_remove)
            {
                free(tb->registros[i].at);

                for (unsigned int j = i; j < tb->qte_reg-1; j++)
                    tb->registros[j] = tb->registros[j+1];

                tb->qte_reg--;
            }
        }
        id_ok = arquivar_tabela(tb);
        if (id_ok == 2)
            printf("Registro removido com sucesso!\n");
        else
            printf("ERRO: não foi possível atualizar a planilha.\n");
    }

    free_tabela(tb);
}

void remover_tabela()
{
    char * nome_tb;
    unsigned int id_remove;
    int tb_ok = 0, id_ok = 0;
    Tabela * tb = NULL;

    while (!tb_ok)
    {
        printf("Qual tabela deseja excluir?\n");
        nome_tb = get_nome_tabela(1);

        if (nome_tb != NULL)
            tb_ok = 1;
        else
            break;
    }

    if (tb_ok)
    {
        tb = carregar_tabela(nome_tb);
        remover_arq_tb(tb);
        printf("Tabela removida com sucesso!\n");
    }

    if (tb != NULL) free_tabela(tb);
}