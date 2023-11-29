#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 250 //tamanho máximo para nomes de tabelas, atributos, etc
#define SEP_LEN 4 //tamanho do vetor do separador

char sep[SEP_LEN+1] = "|#@!\0";//separador dos atributos das tabelas

int criar_tabela()
{
    char nome_tb[MAX_NAME_LENGTH + 1] = {0};//nome da tabela
    char nome_at[MAX_NAME_LENGTH + 1] = {0};//nome do atributo
    char input_nome_tipo_at[MAX_NAME_LENGTH+10] = {0};//variável auxiliar de entrada do nome + tipo do atributo
    char tipo_at[6] = {0};//string que definirá o tipo do atributo
    int tb_ok = 0, at_ok = 0;//var auxiliares de erros

    while (!tb_ok)
    {
        printf("Por favor, insira o nome da tabela a ser criada:\n");
        fgets(nome_tb, MAX_NAME_LENGTH, stdin);

        if(checar_nome(nome_tb) == 2)//se nome válido
        {
            //checar se a tabela já existe
                //criar arquivo
        }
    }

    while (!at_ok)
    {
        printf("Qual o nome do atributo que deseja incluir na tabela %s? Informe seguindo a formatação\n'nome_do_atributo tipo_de_dado'\nTipos de dados disponíveis: int, float, double, char e string\n", nome_tb);
        fgets(input_nome_tipo_at, MAX_NAME_LENGTH+7, stdin);//max_name+7 por conta do tipo de variavel
        nome_at = strtok(input_nome_tipo_at, " ");//quebra a input no nome
        tipo_at = strtok(NULL, " ");//resgata o resto da input

        if(checar_nome(nome_at) == 2)//se nome válido
        {
            //editar arquivo
        }
    }
    

    return 0;//sem erros durante a operação
}

int checar_nome(char *nome)
{
    int nome_size = strlen(nome);
    int resposta = 2;

    if(nome_size<1)//tamanho de nome inválido
    {
        printf("Por favor, insira um nome.\n");
        resposta = try_again();
        return resposta;
    }
    else//sequencia de caracteres inválidos
    {
        if(strstr(nome, sep) != NULL)//compara a str nome com o separador
        {
            printf("A sequência de caracteres '%s' não pode ser usada por ser reservada pelo programa.\n", sep);
            resposta = try_again();
            return resposta;
        }
    }

    return resposta;//não ocorreram erros ao declarar o nome
}

int checar_tipo(char *tipo)
{
    int tipo_int = 0;
    char tipos_list[5][7] = {
        "int\0",//tipo 0
        "float\0",//tipo 1
        "double\0",//tipo 2
        "char\0",//tipo 3
        "string\0"//tipo 4
    };

    for(tipo_int = 0; tipo_int < 5; tipo_int++)
    {
        if(strcmp(tipo, tipos_list[tipo_int]) == 0) return tipo_int;
    }

    printf("Tipo de variável não reconhecido.\n");//se processou essa parte, não achou nenhum dos tipos
    int resposta = try_again();
}

int try_again(){
    int resposta = 2;

    printf("Deseja tentar denovo? (1)\nDeseja cancelar a operação? (0)");
    scanf("%c", &resposta);

    return resposta;
}