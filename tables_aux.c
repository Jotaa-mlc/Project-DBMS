#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "headers/definitions.h"
#include "headers/tables_func.h"
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

int nome_repetido(Tabela * tb, char * nome_at)
{
    int repetições = 0;

    for (unsigned int i = 0; i < tb->qte_at; i++)
    {
        if (strcmp(nome_at, tb->nomes_at[i]) == 0) repetições++;
    }
    
    return (repetições > 0) ? 1 : 0;
}

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

Registro * get_registro(unsigned int qte_at, int * tipos_at)
{
    Registro * reg = calloc(1, sizeof(Registro));
    reg->at = calloc(qte_at, sizeof(Atributo));

    scanf("%u", &reg->id);
    for (unsigned int i = 0; i < qte_at; i++)//recebe o atributo baseado no tipo
    {
        switch (tipos_at[i])
        {
            case 0:
                scanf(" %d", &reg->at[i].inteiro);
                break;
            case 1:
                scanf(" %f", &reg->at[i].real);
                break;
            case 2:
                scanf(" %lf", &reg->at[i].dupla);
                break;
            case 3:
                scanf(" %c", &reg->at[i].caractere);
                break;
            case 4:
                scanf(" %s", reg->at[i].string);
                break;
            default:
                break;
        }
    }

    return reg;
}

int get_opcao_pesquisa()
{
    int comparacao;
    char * list_pesq[6] = {">", ">=", "=", "<", "<=", "+/- (disponível apenas para strings)"};

    printf("Selecione uma das opções de pesquisa:\n");
    for (int i = 0; i < 6; i++)
        printf("%i - %s\n", i, list_pesq[i]);

    scanf("%i", &comparacao);

    return comparacao;
}

double convert_at_double(int tipo_at, Atributo atri)
{
    double convertido;
    switch (tipo_at)
    {
        case 0://int
            convertido = (double)atri.inteiro;
            break;
        case 1://float
            convertido = (double)atri.real;
            break;
        case 2://double
            convertido = (double)atri.dupla;
            break;
        case 3://char
            convertido = (double)atri.caractere;
            break;
    }
    
    return convertido;
}

void print_registro(Registro reg, unsigned int qte_at, int * tipos_at)
{
    printf("%u | ", reg.id);
            for (unsigned int j = 0; j < qte_at; j++)
            {
                switch (tipos_at[j])
                {
                    case 0:
                        printf("%d | ", reg.at[j].inteiro);
                        break;
                    case 1:
                        printf("%f | ", reg.at[j].real);
                        break;
                    case 2:
                        printf("%lf | ", reg.at[j].dupla);
                        break;
                    case 3:
                        printf("%c | ", reg.at[j].caractere);
                        break;
                    case 4:
                        printf("%s | ", reg.at[j].string);
                        break;
                }
            }
            printf("\n");
}