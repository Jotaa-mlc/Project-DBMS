PARAMS = -g -W -pedantic

all: home tb_mk tb_rm tb_read tb_aux io io_aux
	gcc Obj_files/*.o -o dbms $(PARAMS)
home: home.c
	gcc -o Obj_files/home.o home.c -c $(PARAMS)
tb_mk: tables_mk.c
	gcc -o Obj_files/tables_mk.o tables_mk.c -c $(PARAMS)
tb_read: tables_read.c
	gcc -o Obj_files/tables_read.o tables_read.c -c $(PARAMS)
tb_rm: tables_rm.c
	gcc -o Obj_files/tables_rm.o tables_rm.c -c $(PARAMS)
tb_aux: tables_aux.c
	gcc -o Obj_files/tables_aux.o tables_aux.c -c $(PARAMS)
io: io_files.c
	gcc -o Obj_files/io_files.o io_files.c -c $(PARAMS)
io_aux: io_files_aux.c
	gcc -o Obj_files/io_files_aux.o io_files_aux.c -c $(PARAMS)