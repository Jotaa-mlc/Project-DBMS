# Projeto 3ª Unidade da matéria de Introdução às Técnicas de Programação - T05 - UFRN - 2023.2

O QUE FOI FEITO:
    Todas as funções solicitadas na explicação do projeto foram implementadas.
    São elas:
        - Criar Tabela;
        - Listar Tabelas;
        - Inserir/Criar um Registro em uma Tabela;
        - Exibir/Listar dados de uma Tabela;
        - Pesquisar valor em uma Tabela*
            Sobre essa função, não foi possível implementar de maneira eficaz o último critério: valores próximos ao informado.
        - Apagar um Registro de uma Tabela;
        - Apagar uma Tabela;

O QUE FARIAMOS DE FORMA DIFERENTE:
    Chagamos a conclusão que seria interessante tentar manter de forma mais uniforme um único padrão para o funcionamento de determinadas funções como: 
        onde vamos organizar as entradas e saídas? 
        onde vamos declarar as variáveis que serão usadas em cada função? como será o nome delas? 
        qual será o padrão de retorno das funções (quando possível) Ex.: 0: sucesso, 1: operação cancelada, -1: erro durante a operação, etc.
    	
   Modularizar melhor o código de forma que ele ficasse mais facilmente legível, tanto em funções quanto em arquivos se necessário.
   
   Por fim, gostaríamos de ter dado um melhor acabamento ao código para que tais mudanças pudessem ser feitas.
   
   
COMO COMPILAR O PROJETO:
	O comando que aconselhamos para compilar o projeto é:
		gcc *.c -o $NOME_DO_EXECUTAVEL$
	Ou, de maneira mais verbosa:
	    gcc home.c io_files.c io_files_aux.c tables_aux.c tables_mk.c tables_read.c tables_rm.c -o $NOME_DO_EXECUTAVEL$

Autores:
    EMILLY VITORIA RODRIGUES GOMES FELIX
    JOÃO ARTUR MEIRA LUIZ DA COSTA

Contribuições:
    João Artur:
        Menu Inicial;
        Criar Tabela;
        Inserir Registro;
    Emilly Vitória:
        Pesquisar valor em uma tabela;