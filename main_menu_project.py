largura = 40
offset = 12

cmd_list = [
    "0 - Criar Tabela",
    "1 - Listar Tabelas",
    "2 - Inserir Registro",
    "3 - Exibir Tabela",
    "4 - Pesquisar",
    "5 - Excluir Registro",
    "6 - Excluir Tabela",
    "7 - Sair do DBSM"
]
print("/"+"".center(largura, "-")+"\\")
for cmd in cmd_list:
        print("|"+offset*" "+cmd+(largura-(len(cmd)+offset))*" "+"|")
print("\\"+"".center(largura, "-")+"/")